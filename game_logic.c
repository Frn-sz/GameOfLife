#include "const.h"

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