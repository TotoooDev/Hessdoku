
#include <Grid.h>
#include <Frontend/Frontend.h>
#include <stdlib.h>
#include <stdio.h>
#include "Grid.h"
#include "Solver.h"


#include "Swordfish.h"

int main(int argc, char* argv[])
{
    T_Grid grid = generateGrid(0, 0);
    createFrontend(grid, THEME_DRACULA);

    runFrontend();

    freeFrontend();

    //solveSwordfish(grid, 3, NULL);

    freeGrid(grid);

    return 0;
}
