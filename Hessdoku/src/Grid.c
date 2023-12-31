#include <Grid.h>
#include <Log.h>

T_Grid generateGrid(int size, int sqrtSize)
{
    T_Grid game;
    T_Cell* ** grid = malloc(size * sizeof(T_Cell**));
    for (int x = 0; x < size; x++)
    {
         grid[x] = malloc(size * sizeof(T_Cell*));     // FIXME : handle the NULL case (assertion ?)

        // initializing the new cells
        for (int y = 0; y < size; y++)
        {
            grid[x][y] = createCell(0);                 // FIXME : handle the NULL case (assertion ?)
        }  
    }
    game.grid = grid;
    game.size = size;
    game.sqrtSize = sqrtSize;

    return game;
}

unsigned int getGridSize(T_Grid grid)
{
    return grid.size;
}

unsigned int getGridSqrtSize(T_Grid grid)
{
    return grid.sqrtSize;
}

// TODO: tests
void freeGrid(T_Grid grid) 
{
    unsigned int size = getGridSize(grid);

    for (unsigned int x = 0; x < size; x++)
    {
        for (unsigned int y = 0; y < size; y++)
        {
            freeCell(getCell(grid, x, y));
        }
        free(grid.grid[x]);
    }
    free(grid.grid);
}

unsigned int getValue(T_Grid grid, int x, int y)
{
    return getValueOfCell(grid.grid[x][y]);
}

void setCell(T_Grid grid, unsigned char x, unsigned char y, char value)
{
    if (!getCell(grid, x, y))
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    setValueOfCell(getCell(grid, x, y), value);
}

void setCellEmpty(T_Grid grid, unsigned char x, unsigned char y)
{
    if (!getCell(grid, x, y))
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    setValueOfCell(getCell(grid, x, y), 0);
}

void displayGridToConsole(T_Grid grid) 
{
    unsigned int size = getGridSize(grid);

    for(unsigned int i = 0; i < size; i++)
    {
        if(i % getGridSqrtSize(grid) == 0)
        {
            for(unsigned int k = 0; k < size; k++) printf("####");
            printf("#\n");
        }

        for(unsigned int k = 0; k < size; k++) {
            printf(k % getGridSqrtSize(grid) == 0 ? "#" : "|");

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

        for (unsigned int k = 0; k < size && i % getGridSqrtSize(grid) != (getGridSqrtSize(grid) - 1); k++)
        {
            printf(k % getGridSqrtSize(grid) == 0 ? "#" : "+");
            printf("---");

        }
        if(i % getGridSqrtSize(grid) != (getGridSqrtSize(grid) -1)) printf("#\n");
    }

    // Ending line
    for(unsigned int k = 0; k < size; k++)
    {
        printf("####");
    }
    printf("#\n");

}

void displayNotesToConsole(T_Grid grid)
{
    unsigned int size = getGridSize(grid);

    for (unsigned int x = 0; x < size; x++)
    {
        for (unsigned int y = 0; y < size; y++)
        {
            for (unsigned int i = 1; i <= 9; ++i) {
                if ((getCell(grid, x, y)->notes & (1 << (i - 1))) != 0) {
                    printf("%d", i);
                }
                else {
                    printf(" ");
                }
            }
            printf(" | ");
        }
        printf("\n");
    }

}

T_Cell* getCell(T_Grid grid, int i, int j)
{
    return grid.grid[i][j];
}