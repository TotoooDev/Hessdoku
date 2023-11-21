#include <Game.h>
#include <stdlib.h>

void setGridToDemoGrid(T_Grid grid)
{
    int testGrid[9][9] = {
        {2, 1, 3, 5, 9, 7, 0, 6, 0},
        {7, 0, 6, 0, 8, 1, 3, 2, 5},
        {0, 5, 4, 3, 0, 6, 9, 1, 7},
        {9, 4, 2, 6, 0, 8, 7, 0, 0},
        {6, 3, 0, 1, 7, 0, 0, 4, 2},
        {1, 7, 8, 2, 3, 4, 5, 9, 6},
        {5, 6, 1, 8, 0, 3, 0, 7, 9},
        {3, 0, 9, 7, 6, 2, 1, 5, 0},
        {0, 2, 7, 0, 1, 5, 6, 8, 3}};

    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            if (testGrid[x][y] != 0)
            {
                setCell(grid, x, y, testGrid[x][y]);
            }
        }
    }
}

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));
    game->grid = generateGrid(sizeX, sizeY);
    return game;
}

void destroyGame(T_Game* game)
{
    freeGrid(game->grid, 9, 9);
    free(game);
}