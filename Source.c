#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (30 + 2)
#define XY_TO_I(x, y) y *SIZE + x
#define ALIVE '*'
#define DEAD ' '
#define ext_size SIZE *SIZE + 2 * SIZE

// random spawn of cells in 1st generation ( рандомное появление клеток в 1ой генирации)
void grid_spawncells(char* grid)
{
    for (int i = 0; i < SIZE * SIZE; ++i)
        grid[i] = (rand() % 2) ? ALIVE : DEAD;
}

// generating walls( генирируем стены )
void grid_drawborders(char* grid)
{
    int i = 0;
    for (i = 1; i < SIZE - 1; ++i)
    {
        grid[i] = '-';
        grid[XY_TO_I(i, (SIZE - 1))] = '-';
    }

    for (i = 1; i < SIZE - 1; ++i)
    {
        grid[XY_TO_I(0, i)] = '|';
        grid[XY_TO_I((SIZE - 1), i)] = '|';
    }

    grid[XY_TO_I(0, 0)] = '+';
    grid[XY_TO_I((SIZE - 1), 0)] = '+';
    grid[XY_TO_I((SIZE - 1), (SIZE - 1))] = '+';
    grid[XY_TO_I(0, (SIZE - 1))] = '+';
}

void grid_init(char* grid)
{
    grid_spawncells(grid);
    grid_drawborders(grid);
}

// Neighbors counting( подсчет соседей )
int grid_countneighbors(char* grid, int x, int y)
{
    int count = 0;
    int i = -1;
    int j = -1;
    for (; i <= 1; ++i)
    {
        for (j = -1; j <= 1; ++j)
        {
            int neighborX = x + i;
            int neighborY = y + j;

            // Skip current cell ( пропускаем текущую ячейку )
            if (i == 0 && j == 0)
                continue;

            // Check if neighbor is within grid boundaries ( проверяем наличие соседей в окрестностях )
            if (neighborX > 0 && neighborY > 0 && neighborX < SIZE - 1 && neighborY < SIZE - 1)
                count += grid[XY_TO_I(neighborX, neighborY)] == ALIVE;
        }
    }
    return count;
}

// Grid printing( отрисовка поля )
void grid_print(char* grid)
{
    int i = 0;
    int j = 0;
    for (; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
            printf("%c", grid[XY_TO_I(j, i)]);

        printf("\n");
    }
}

// Updating grid to next generation ( переход к новой генирации )
void grid_update(char* grid)
{
    char nextGrid[ext_size];
    grid_drawborders(nextGrid);
    int j = 1;
    int i = 1;
    for (; i < SIZE - 1; ++i)
    {
        for (j = 1; j < SIZE - 1; ++j)
        {
            int neighbors = grid_countneighbors(grid, i, j);

            // game rules ( правила игры )
            if (grid[XY_TO_I(i, j)] == ALIVE)
            {
                if (neighbors < 2 || neighbors > 3)
                    nextGrid[XY_TO_I(i, j)] = DEAD;
                else
                    nextGrid[XY_TO_I(i, j)] = ALIVE;
            }
            else
            {

            }
            {
                if (neighbors == 3)
                    nextGrid[XY_TO_I(i, j)] = ALIVE;

                else
                    nextGrid[XY_TO_I(i, j)] = DEAD;
            }
        }
    }

    // Copy next grid to current grid ( копируем следующее поле в текущее )
    memcpy(grid, nextGrid, ext_size);
}

// screen clear( очистка экрана )
void clear_screen()
{
    system("cls");
}

int main()
{
    srand(time(NULL));
    char grid[ext_size];
    char prev_grid[ext_size];
    memset(grid, 0, ext_size);
    memcpy(prev_grid, grid, ext_size);
    // Initialize grid randomly ( задаем поле случайно )
    grid_init(grid);

    // Run game of life iterations ( запуск итераций игры )
    while (1)
    {
        clear_screen();
        grid_print(grid);
        grid_update(grid);
        // The game lasts until the current generation coincides with the previous one.
        // Игра длится до тех пор, пока нынешнея генирация не совпадет с предыдущей.
        if (!memcmp(grid, prev_grid, ext_size))
            break;

        memcpy(prev_grid, grid, ext_size);
    }
    return 0;
}
