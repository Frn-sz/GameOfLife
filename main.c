#include "game_logic.c"
#include "matrix_logic.c"
#include "const.h"
#include "print_simulation.h"
#include "libs.h"

/*
Regras

- Células com menos de dois vizinhos morrem / com fome
- Células com 2 ou 3 vizinhos ficam vivas
- Células com mais de 3 vizinhos morrem / superpopulação
- Células mortas com exatamente 3 vizinhos nascem / reprodução

*/

int main(int argc, char const *argv[])
{
    int **current_state = initialize_matrix();
    int **next_state = initialize_matrix();

    randomize_matrix(current_state);
    initializeSDL();

    for (int i = 0; i < MAX_GENERATIONS; i++)
    {
        update_game(current_state, next_state);

        int **temp = current_state;
        current_state = next_state;
        next_state = temp;

        drawMatrix(current_state);
        SDL_Delay(100);
    }

    closeSDL();

    free_space(current_state);
    free_space(next_state);

    return 0;
}
