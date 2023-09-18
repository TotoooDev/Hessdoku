#include <Game.h>

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));

    game->grid = generateGrid(sizeX, sizeY);

    return game;
}