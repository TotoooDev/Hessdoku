#include <Grid.h>
#include <Log.h>

void addCell(T_Grid grid, unsigned char x, unsigned char y, T_Cell* cell)
{
    if (!cell)
    {
        LOG("Trying to add a NULL cell at %d,%d!\n", x, y);
        LOG("If you want to remove a cell, use removeCell instead.\n");
        return;
    }

    if (grid[x][y])
    {
        LOG("A cell already exists at %d,%d!", x, y);
        return;
    }

    grid[x][y] = cell;
}

void removeCell(T_Grid grid, unsigned char x, unsigned char y)
{
    if (!grid[x][y])
    {
        LOG("Trying to remove a cell a %d,%d but there was no cell there!", x, y);
        return;
    }

    grid[x][y] = NULL;
}