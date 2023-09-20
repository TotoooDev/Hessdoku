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

void setCell(T_Grid grid, unsigned char x, unsigned char y, char value)
{
    if (!grid[x][y])
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    grid[x][y]->value = value;
}

void setCellEmpty(T_Grid grid, unsigned char x, unsigned char y)
{
    if (!grid[x][y])
    {
        LOG("Trying to modify NULL cell at %d,%d!", x, y);
        return;
    }
    grid[x][y]->value = 0;
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
    printf("#\n");

}

void displayNotesToConsole(T_Grid grid, int size)
{

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int i = 0; i < 9; i++)
            {
                printf(grid[x][y]->notes[i] == 0 ? " " : "%d", i + 1);
            }
            printf("|");
        }
        printf("\n");
    }

}
