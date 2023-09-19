#include <Game.h>
#include <stdlib.h>

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));

    game->grid = generateGrid(9, 9);

    return game;
}

void destroyGame(T_Game* game, T_Grid grid)
{
    freeGrid(grid, 9, 9);
    free(game);
}