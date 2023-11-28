
#include <stdlib.h>
#include <time.h>

#define ROWS 8
#define COLS 8

#define MAX_GENERATIONS 10
#define ALIVE_PERCENTAGE 30

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