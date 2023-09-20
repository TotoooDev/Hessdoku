#include <Game.h>
#include <stdlib.h>

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));

    game->grid = generateGrid(sizeX, sizeY);
    setCell(game->grid, 5, 5, 9);
    setCell(game->grid, 5, 6, 9);
    displayGridToConsole(game->grid, 9);
    
    const gridValidity = checkingAccuracy(game->grid);
    printf("\n");
    if (gridValidity == true) 
    {
        printf("The grid is valid.");
    }
    else 
    {
        printf("Warning : The grid is invalid !");
    }

    return game;
}

void destroyGame(T_Game* game, T_Grid grid)
{
    freeGrid(grid, 9, 9);
    free(game);
}