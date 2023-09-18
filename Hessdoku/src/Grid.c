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

/**
 * Displays the given grid in a verry pretty way in the console.
 *
 * @param grid The grid to display
 * @param size The size of the grid (square)
 * @author Baptiste
 */
void displayGridToConsole(T_Grid grid, int size) {

    for(int i = 0; i < size; i++) 
    {
        if(i%3 == 0) 
        {
            for(int k = 0; k < size; k++) printf("####");
            printf("#\n");
        }

        for(int k = 0; k < size; k++) {
            printf(k%3 == 0 ? "#" : "|");

            if(grid[i][k].value == 0) 
            {
                printf("   ");
            } 
            else 
            {
                printf(" %hu ", grid[i][k].value);
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

T_Grid generateGrid(int sizeX, int sizeY)
{
    T_Cell** grid = malloc(sizeX * sizeof(T_Cell*));
    for (int x = 0; x < sizeX; x++)
    {
        grid[x] = malloc(sizeY * sizeof (T_Cell));

        // initializing the new cells
        for (int y = 0; y < sizeY; y++)
        {
            grid[x][y] = createCell(0);
        }
    }

    return grid;
}