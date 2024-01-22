#include <Grid.h>
#include <Log.h>
#include <String.h>
#include <assert.h>
#include "FileHandler.h"

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

T_Grid generateGridFromSequence(const char* path)
{
    FILE* fd = openFile(path);

    int gridSize = 9;
    T_Grid grid = generateGrid(gridSize, gridSize / 3);

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            int next = readNextInteger(fd);
            setCell(grid, i, j, next);
        }
    }

    printf("Test");

    closeFile(fd);
    displayGridToConsole(grid);

    return grid;
}

T_Grid generateGridFromTable(const char* path)
{
    FILE* fd = openFile(path);

    int sizeX = readNumbersUntil(fd, ',');
    int sizeY = readNumbersUntil(fd, '\n');

    T_Grid grid = generateGrid(sizeX * sizeX, sizeX);

    skipUntil(fd, '|', 1);
    for (int x = 0; x < sizeX * sizeX; x++)
    {
        for (int y = 0; y < sizeY * sizeY; y++)
        {
            int nb = readNumbersUntil(fd, '|');

            if (nb != 0)
            {
                setCell(grid, x, y, nb);
            }
        }
        skipUntil(fd, '|', sizeX + 2);                  // TODO: Peut �tre d�tecter les fins avec \n
    }

    closeFile(fd);

    return grid;
}

// TODO: docs in .h
T_Grid generateGridFromFile(const char* path)
{
    int dotIndex = 0;

    char* extension = ".seq";
    char fileExtension[10];

    int res = getFileExtension(path, fileExtension);
    assert(res == 0);

    printf("%s %s %d\n", fileExtension, extension, strcmp(fileExtension, extension));

    if (strcmp(fileExtension, extension) == 0)
    {
        printf("Génération du fichier séquenciel");
        return generateGridFromSequence(path);
    }

    printf("Génération du fichier en table");
    return generateGridFromTable(path);
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