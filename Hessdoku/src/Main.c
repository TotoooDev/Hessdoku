#include <stdlib.h>
#include <stdio.h>
#include <Game.h>

void setGridToDemoGrid(T_Grid grid)
{
    int testGrid[GRID_SIZE][GRID_SIZE] = {
        {2, 1, 3, 5, 9, 7, 0, 6, 0},
        {7, 0, 6, 0, 8, 1, 3, 2, 5},
        {0, 5, 4, 3, 0, 6, 9, 1, 7},
        {9, 4, 2, 6, 0, 8, 7, 0, 0},
        {6, 3, 0, 1, 7, 0, 0, 4, 2},
        {1, 7, 8, 2, 3, 4, 5, 9, 6},
        {5, 6, 1, 8, 0, 3, 0, 7, 9},
        {3, 0, 9, 7, 6, 2, 1, 5, 0},
        {0, 2, 7, 0, 1, 5, 6, 8, 3} };

    for (int x = 0; x < getGridSize(grid); x++)
    {
        for (int y = 0; y < getGridSize(grid); y++)
        {
            if (testGrid[x][y] != 0)
            {
                setCell(grid, x, y, testGrid[x][y]);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    //T_Game* game = createGame(GRID_SIZE, GRID_SIZE);
    T_Grid grid = generateGrid(GRID_SIZE, SQRT_GRID_SIZE);
    setGridToDemoGrid(grid);

    /*
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
    */

    //test erreur ligne
    //setCell(game->grid, 5, 4, 4);

    //test erreur colonne
    //setCell(game->grid, 6, 8, 6);

    //test erreur carre
    //setCell(game->grid, 8, 4, 5); //NOPE

    printf("Grid before solving algorithm :\n");
    displayGridToConsole(grid);
    displayNotesToConsole(grid);

    /* MOVE THIS PIECE OF CODE TO THE APPROPRIATE PLACE */
    bool hasChanged = true;

    while (hasChanged)
    {
        hasChanged &= removeNotesInGridByZones(grid);

        if (!hasChanged)
        {
            // Next algorithm step
        }
    }
    /* END OF MOVE */

    printf("Grid after solving algorithm :\n");
    displayGridToConsole(grid);
    displayNotesToConsole(grid);

    const gridValidity = checkValidityOfGrid(grid);
    if (gridValidity == true)
    {
        printf("The grid is valid.");
    }
    else
    {
        printf("Warning : The grid is invalid !");
    }

    return 0;
}