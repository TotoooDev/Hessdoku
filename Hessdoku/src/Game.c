#include <Game.h>
#include <stdlib.h>

T_Game* createGame(int sizeX, int sizeY)
{
    T_Game* game = (T_Game*)malloc(sizeof(T_Game));

    game->grid = generateGrid(sizeX, sizeY);

    setCell(game->grid, 0, 0, 3);
    setCell(game->grid, 1, 0, 2);
    setCell(game->grid, 1, 2, 1);

    setCell(game->grid, 0, 3, 8);
    setCell(game->grid, 0, 5, 1);
    setCell(game->grid, 1, 4, 3);
    setCell(game->grid, 2, 3, 2);
    setCell(game->grid, 2, 5, 4);

    setCell(game->grid, 0, 8, 2);
    setCell(game->grid, 1, 6, 6);
    setCell(game->grid, 1, 8, 4);

    setCell(game->grid, 3, 0, 8);
    setCell(game->grid, 3, 2, 9);
    setCell(game->grid, 4, 1, 6);
    setCell(game->grid, 5, 0, 7);
    setCell(game->grid, 5, 2, 2);

    setCell(game->grid, 3, 6, 1);
    setCell(game->grid, 3, 8, 6);
    setCell(game->grid, 4, 7, 5);
    setCell(game->grid, 5, 6, 4);
    setCell(game->grid, 5, 8, 9);

    setCell(game->grid, 7, 0, 9);
    setCell(game->grid, 7, 2, 4);
    setCell(game->grid, 8, 0, 6);

    setCell(game->grid, 6, 3, 5);
    setCell(game->grid, 6, 5, 9);
    setCell(game->grid, 7, 4, 8);
    setCell(game->grid, 8, 3, 1);
    setCell(game->grid, 8, 5, 7);

    setCell(game->grid, 7, 6, 7);
    setCell(game->grid, 7, 8, 5);
    setCell(game->grid, 8, 8, 3);

    //test erreur ligne
    //setCell(game->grid, 5, 4, 4);

    //test erreur colonne
    //setCell(game->grid, 6, 8, 6);

    //test erreur carre
    //setCell(game->grid, 8, 4, 5); //NOPE


    displayGridToConsole(game->grid, GRID_SIZE);

    const gridValidity = gridVerif(game->grid);
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