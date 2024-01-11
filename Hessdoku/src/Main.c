#include <Grid.h>
#include <Frontend/Frontend.h>

int main(int argc, char* argv[])
{
    T_Grid grid = generateGrid(81, 9);
    T_Frontend* frontend = createFrontend(grid);

    runFrontend(frontend);

    freeFrontend(frontend);
    freeGrid(grid);

    return 0;
}