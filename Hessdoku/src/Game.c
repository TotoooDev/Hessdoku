#include <Game.h>
#include <stdlib.h>

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));
    game->grid = generateGrid(sizeX, sizeY);
    game->sizeX = sizeX;
    game->sizeY = sizeY;
    return game;
}

void destroyGame(T_Game* game)
{
    freeGrid(game->grid, game->sizeX, game->sizeY);
    free(game);
}