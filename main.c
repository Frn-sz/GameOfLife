#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_GENERATIONS 10

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

    for (int i = 0; i < MAX_GENERATIONS; i++)
    {
        update_game(current_state, next_state);

        int **temp = current_state;
        current_state = next_state;
        next_state = temp;

        sleep(1);
        print_matrix(current_state);
    }

    free_space(current_state);
    free_space(next_state);

    return 0;
}
