#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ROWS 8
#define COLS 8
#define MAX_GENERATIONS 10
#define ALIVE_PERCENTAGE 30
/*
Regras

- Células com menos de dois vizinhos morrem
- Células com 2 ou 3 vizinhos ficam vivas
- Células com mais de 3 vizinhos morrem
- Células mortas com exatamente 3 vizinhos nascem

*/
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int **initialize_matrix()
{
    int **matrix = (int **)(malloc(sizeof(int *) * ROWS));

    for (int i = 0; i < ROWS; i++)
        matrix[i] = (int *)(malloc(sizeof(int) * COLS));

    return matrix;
}

void print_matrix(int **matrix)
{
    clear_screen();
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_space(int **matrix)
{
    for (int i = 0; i < ROWS; i++)
        free(matrix[i]);
    free(matrix);
}

int calc_cell_next_state(int current_cell_state, int qnt_neighbors)
{

    if (current_cell_state == 1)
    {
        if (qnt_neighbors < 2 || qnt_neighbors > 3)
            return 0;

        return 1;
    }
    else
    {
        if (qnt_neighbors == 3)
            return 1;

        return 0;
    }
}

int count_neighbors(int **state, int row, int col)
{
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i == row && j == col)
                continue;

            int neighbor_row = (i + ROWS) % ROWS;
            int neighbor_col = (j + COLS) % COLS;

            count += state[neighbor_row][neighbor_col];
        }
    }

    return count;
}

void update_game(int **current_state, int **next_state)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int neighbors = count_neighbors(current_state, i, j);
            next_state[i][j] = calc_cell_next_state(current_state[i][j], neighbors);
        }
    }
}

void randomize_matrix(int **matrix)
{
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int random_percentage = rand() % 100;
            matrix[i][j] = (random_percentage < ALIVE_PERCENTAGE) ? 1 : 0;
        }
    }
}

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
