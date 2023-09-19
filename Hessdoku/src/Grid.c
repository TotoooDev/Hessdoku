#include <Grid.h>
#include <Log.h>

T_Grid generateGrid(int sizeX, int sizeY)
{
    LOG("%d", sizeX * sizeof(T_Cell**));
    T_Cell* ** grid = malloc(sizeX * sizeof(T_Cell**));
    for (int x = 0; x < sizeX; x++)
    {
         grid[x] = malloc(sizeY * sizeof(T_Cell*));

        // initializing the new cells
        for (int y = 0; y < sizeY; y++)
        {
            grid[x][y] = createCell(0);
        }
    }

    return grid;
}

// TODO: tests
T_Grid freeGrid(T_Grid grid, int sizeX, int sizeY) {
    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            freeCell(grid[x][y]);
        }
        free(grid[x]);
    }
    free(grid);
}

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

// FIXME : creates a memory leak ! A cell must be fred. If the goal is to set the value to 0, the 
void removeCell(T_Grid grid, unsigned char x, unsigned char y)
{
    if (!grid[x][y])
    {
        LOG("Trying to remove a cell a %d,%d but there was no cell there!", x, y);
        return;
    }

    grid[x][y] = NULL;
}


void displayGridToConsole(T_Grid grid, int size) 
{

    if(size%3!=0) LOG("Display in console is not optimized for values that aren't multiple of 3.");

    for(int i = 0; i < size; i++) 
    {
        if(i%3 == 0) 
        {
            for(int k = 0; k < size; k++) printf("####");
            printf("#\n");
        }

        for(int k = 0; k < size; k++) {
            printf(k%3 == 0 ? "#" : "|");

            if(grid[i][k]->value == 0) 
            {
                printf("   ");
            } 
            else 
            {
                printf(" %hu ", grid[i][k]->value);
            }

        }
        printf("#\n");

        for(int k = 0; k < size && i%3!=2; k++) 
        {
            printf(k%3 == 0 ? "#" : "+");
            printf("---");

        }
        if(i%3!=2) printf("#\n");
    }

    // Ending line
    for(int k = 0; k < size; k++) 
    {
        printf("####");
    }
    printf("#");

}