#include <Grid.h>
#include <Log.h>
#include <string.h>
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
            grid[x][y] = createCell(0);                 // FIXME : handle the NULL case (assertion ?)

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
                setCell(grid, x, y, nb);

        }
        skipUntil(fd, '|', sizeX + 2);                  // TODO: Peut être détecter les fins avec \n
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
        LOG("Génération du fichier séquenciel");
        return generateGridFromSequence(path);
    }

    LOG("Génération du fichier en table");
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
            freeCell(getCell(grid, x, y));

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
    unsigned int sqrtSize = getGridSqrtSize(grid);

    for(unsigned int i = 0; i < size; i++)
    {
        if(i % sqrtSize == 0)
        {
            for(unsigned int k = 0; k < size; k++) 
                printf("####");
            printf("#\n");
        }

        for(unsigned int k = 0; k < size; k++) {
            printf(k % sqrtSize == 0 ? "#" : "|");

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

        for (unsigned int k = 0; (k < size) && (i % sqrtSize != (sqrtSize - 1)); k++)
        {
            printf(k % sqrtSize == 0 ? "#" : "+");
            printf("---");

        }
        if(i % sqrtSize != (sqrtSize -1))
            printf("#\n");
    }

    // Ending line
    for(unsigned int k = 0; k < size; k++)
        printf("####");

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
                if (isNoteInCell(getCell(grid, x, y), i))
                {
                    printf("%d", i);
                }
                else
                {
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




/* ----------------------------------------------------------------- */
/*                                                                   */
/*            Function for testing the validity of a Grid            */
/*                                                                   */
/* ----------------------------------------------------------------- */

/**
 * Reset/set a table to 0
 *
 * @param grid : the grid (for the size)
 * @param b : a table of 9 unsigned char
 *
 * @author Marie
 */
void createBaton(T_Grid grid, unsigned char* b)
{
    for (unsigned int i = 0; i < getGridSize(grid); i++)
        b[i] = 0;
}

int** createCoo(int size)
{
    int** res = malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++)
    {
        int* tempo = malloc(sizeof(int) * 2);
        res[i] = tempo;
    }
    return res;
}

/**
 * Verify if the number of a cell has already been seen
 *
 * @param baton : an array of 9 unsigned char
 * @param val   : the value of the cell
 *
 * @return false if we already saw this value, 
 *			true if not
 *
 * @author Marie
 */
bool checkValidityOfCell(unsigned char* baton, int val)
{
    if (val == 0)
        return true;

    if (baton[val - 1] == 0)
    {
        baton[val - 1] = 1;
        return true;
    }

    return false;
}

/**
 * Verif the validity of a zone
 *
 * @param grid : the sudoku
 * @param minX, maxX, minY, maxY
 * @param baton : a table of 9 unsigned char
 *					baton[i-1] = 0 if we didn't see i in the zone
 *					baton[i-1] = 1 if we already see i
 * @param errorValue : the value of the cell that causes an error
 * @param cooErrorValue : the coordinates of the two cell that causes an error
 *
 * @return false if the zone isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfRect(T_Grid grid, int minX, int maxX, int minY, int maxY, unsigned char* baton, int* errorValue, int** cooErrorValue)
{
    int** cooCell = createCoo(getGridSize(grid));
    for (int i = minX; i < maxX; i++)
        for (int j = minY; j < maxY; j++)
        {
            if (!checkValidityOfCell(baton, getValue(grid, i, j)))
            {
                //to keep track of which and where we have an error
                *errorValue = getValue(grid, i, j);
                cooErrorValue[0] = cooCell[getValue(grid, i, j)-1];
                cooErrorValue[1][0] = i;
                cooErrorValue[1][1] = j;
                return false;
            }
            if (getValue(grid, i, j) != 0)
            {
                cooCell[getValue(grid, i, j) - 1][0] = i;
                cooCell[getValue(grid, i, j) - 1][1] = j;
            }
        }
    return true;
}

/**
 * Verif if the lines of a sudoku are valid
 *
 * @param grid : the sudoku
 * @param errorValue : the value of the cell that causes an error
 * @param cooErrorValue : the coordinates of the two cell that causes an error
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfLine(T_Grid grid, int* errorValue, int** cooErrorValue)
{
    unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
    createBaton(grid, baton);
    for (unsigned int i = 0; i < getGridSize(grid); i++)
    {
        if (!checkValidityOfRect(grid, i, i + 1, 0, getGridSize(grid), baton, errorValue, cooErrorValue))
            return false;
        createBaton(grid, baton);
    }
    free(baton);
    return true;
}

/**
 * Verif if the columns of a sudoku are valid
 *
 * @param grid : the sudoku
 * @param errorValue : the value of the cell that causes an error
 * @param cooErrorValue : the coordinates of the two cell that causes an error
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfColumn(T_Grid grid, int* errorValue, int** cooErrorValue)
{
    unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
    createBaton(grid, baton);

    for (unsigned int i = 0; i < getGridSize(grid); i++)
    {
        if (!checkValidityOfRect(grid, 0, getGridSize(grid), i, i + 1, baton, errorValue, cooErrorValue))
            return false;

        createBaton(grid, baton);
    }

    free(baton);
    return true;
}

/**
 * Verif if the squares of a sudoku are valid
 *
 * @param grid : the sudoku
 * @param errorValue : the value of the cell that causes an error
 * @param cooErrorValue : the coordinates of the two cell that causes an error
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfSquare(T_Grid grid, int* errorValue, int** cooErrorValue)
{
    unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
    createBaton(grid, baton);
    int X = 0;
    int Y = 0;
    for (unsigned int k = 0; k < getGridSize(grid); k++)
    {
        if (!checkValidityOfRect(grid, X, X + getGridSqrtSize(grid), Y, Y + getGridSqrtSize(grid), baton, errorValue, cooErrorValue))
            return false;

        Y += getGridSqrtSize(grid);
        if (Y == getGridSize(grid))
        {
            Y = 0;
            X += getGridSqrtSize(grid);
        }
        if (X == getGridSize(grid))
            X = 0;
        createBaton(grid, baton);
    }

    free(baton);
    return true;
}

bool checkValidityOfGrid(T_Grid grid, int* errorValue, int** cooErrorValue)
{
    return (checkValidityOfLine(grid, errorValue, cooErrorValue) && checkValidityOfColumn(grid, errorValue, cooErrorValue) && checkValidityOfSquare(grid, errorValue, cooErrorValue));
}

bool areGridEqual(T_Grid g1, T_Grid g2)
{
    if (g1.size != g2.size)
    {
        return false;
    }

        
    for (int i = 0; i < g1.size; i++)
    {
        for (int j = 0; j < g1.size; j++)
        {
            if (getCellArray(getCell(g1, i, j)) != getCellArray(getCell(g2, i, j)))
                return false;
        }
    }

    return true;
}