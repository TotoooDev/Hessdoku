#include <Grid.h>
#include <Frontend/Frontend.h>

int main(int argc, char* argv[])
{
    T_Grid grid = generateGrid(81, 9);
    setCell(grid, 0, 0, 1);
    setCell(grid, 1, 0, 2);
    unsetNoteCell(getCell(grid, 2, 0), 1);
    unsetNoteCell(getCell(grid, 3, 0), 5);
    T_Frontend* frontend = createFrontend(grid);

    runFrontend(frontend);

    freeFrontend(frontend);
    freeGrid(grid);

    return 0;
}