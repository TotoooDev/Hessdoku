#include <Grid.h>
#include <Log.h>

T_Grid generateGrid(int sizeX, int sizeY)
{
    T_Cell* ** grid = malloc(sizeX * sizeof(T_Cell**));
    for (int x = 0; x < sizeX; x++)
    {
         grid[x] = malloc(sizeY * sizeof(T_Cell*));     // FIXME : handle the NULL case (assertion ?)

        // initializing the new cells
        for (int y = 0; y < sizeY; y++)
        {
            grid[x][y] = createCell(0);                 // FIXME : handle the NULL case (assertion ?)
        }  
    }

    return grid;
}

// TODO: tests
T_Grid freeGrid(T_Grid grid, int sizeX, int sizeY) 
{
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

unsigned int getValue(T_Grid grid, int x, int y)
{
    return getValueOfCell(grid[x][y]);
}

void setCell(T_Grid grid, unsigned char x, unsigned char y, char value)
{
    if (!grid[x][y])
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    setValueOfCell(grid[x][y], value);
}

void setCellEmpty(T_Grid grid, unsigned char x, unsigned char y)
{
    if (!grid[x][y])
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    setValueOfCell(grid[x][y], 0);
}

void displayGridToConsole(T_Grid grid, const int size) 
{

    for(int i = 0; i < size; i++)
    {
        if(i % SQRT_GRID_SIZE == 0)
        {
            for(int k = 0; k < size; k++) printf("####");
            printf("#\n");
        }

        for(int k = 0; k < size; k++) {
            printf(k % SQRT_GRID_SIZE == 0 ? "#" : "|");

            if(getValue(grid, i, k) == 0) 
            {
                printf("   ");
            } 
            else 
            {
                printf("%2hu ", getValue(grid, i, k));
            }

        }
        printf("#\n");

        for (int k = 0; k < size && i % SQRT_GRID_SIZE != (SQRT_GRID_SIZE - 1); k++)
        {
            printf(k % SQRT_GRID_SIZE == 0 ? "#" : "+");
            printf("---");

        }
        if(i % SQRT_GRID_SIZE != (SQRT_GRID_SIZE-1)) printf("#\n");
    }

    // Ending line
    for(int k = 0; k < size; k++) 
    {
        printf("####");
    }
    printf("#\n");

}

void displayNotesToConsole(T_Grid grid, int size)
{

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            printf("%d\n", grid[x][y]->notes);
            printf("|");
        }
        printf("\n");
    }

}
