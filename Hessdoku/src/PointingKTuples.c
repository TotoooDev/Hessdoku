#include <PointingKTuples.h>
#include <Cell.h>
#include <Log.h>

// Returns an array that contains the coordinates (represented as a array with two cells) of the cells contained in the current square.
// Please free the returned table with `freeSquareCellIndices`.
unsigned int** getSquareCellIndices(unsigned int gridSize, unsigned int sqrtGridSize, unsigned int squareIndex)
{
    unsigned int** squareCellsIndices = (unsigned int**)malloc(gridSize * sizeof(unsigned int*));
    for (unsigned int i = 0; i < gridSize; i++)
    {
        squareCellsIndices[i] = (unsigned int*)malloc(2 * sizeof(unsigned int));
        squareCellsIndices[i][0] = (squareIndex % sqrtGridSize) * sqrtGridSize + i % sqrtGridSize;
        squareCellsIndices[i][1] = (squareIndex / sqrtGridSize) * sqrtGridSize + i / sqrtGridSize;
    }
    return squareCellsIndices;
}

// Returns the coordinates of the y-th line `y`.
// Please free the returned line with `freeZone`.
unsigned int** getLineIndices(unsigned int gridSize, unsigned int y)
{
    unsigned int** line = (unsigned int**)malloc(gridSize * sizeof(unsigned int*));
    for (unsigned int i = 0; i < gridSize; i++)
    {
        line[i] = (unsigned int*)malloc(2 * sizeof(unsigned int));
        line[i][0] = i;
        line[i][1] = y;
    }
    return line;
}

// Same as `getLineIndices`, but with columns.
unsigned int** getColumnIndices(unsigned int gridSize, unsigned int x)
{
    unsigned int** column = (unsigned int**)malloc(gridSize * sizeof(unsigned int*));
    for (unsigned int i = 0; i < gridSize; i++)
    {
        column[i] = (unsigned int*)malloc(2 * sizeof(unsigned int));
        column[i][0] = x;
        column[i][1] = i;
    }
    return column;
}

void freeZone(unsigned int** array, unsigned int gridSize)
{
    // No garbage collector :(
    for (unsigned int i = 0; i < gridSize; i++)
        free(array[i]);
    free(array);
}

// Returns the intersection between a zone and a square (which are represented as arrays of `gridSize` coordinates). 
// It returns an array of the common coordinates. The array must be freed with `freeIntersections`.
unsigned int** getIntersectionZoneSquare(unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int** intersections = (unsigned int**)malloc(sqrtGridSize * sizeof(unsigned int*));
    unsigned int currentIndex = 0;
    for (unsigned int i = 0; i < gridSize; i++)
    {
        bool isIncluded = false;
        for (unsigned int ii = 0; ii < gridSize; ii++)
        {
            if (square[i][0] == zone[ii][0] && square[i][1] == zone[ii][1])
                isIncluded = true;
        }

        if (isIncluded)
        {
            intersections[currentIndex] = (unsigned int*)malloc(2 * sizeof(unsigned int));
            intersections[currentIndex][0] = square[i][0];
            intersections[currentIndex][1] = square[i][1];
            currentIndex++;
        }

    }

    return intersections;
}

void freeIntersections(unsigned int** intersection, unsigned int sqrtGridSize)
{
    for (unsigned int i = 0; i < sqrtGridSize; i++)
        free(intersection[i]);
    free(intersection);
}

// Returns the exclusion (like an exclusive or) of a zone and a square (represented by an array of `gridSize` coordinates).
// It returns an array of the exclusive coordinates of the square. The array must be freed with `freeExclusions`.
unsigned int** getSquareExclusionZoneSquare(unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int numExclusions = gridSize - sqrtGridSize;
    unsigned int** exclusions = (unsigned int**)malloc(numExclusions * sizeof(unsigned int*));
    unsigned int currentIndex = 0;

    for (unsigned int i = 0; i < gridSize; i++)
    {
        bool isIncluded = false;
        for (unsigned int ii = 0; ii < gridSize; ii++)
        {
            if (square[i][0] == zone[ii][0] && square[i][1] == zone[ii][1])
                isIncluded = true;
        }

        if (!isIncluded)
        {
            exclusions[currentIndex] = (unsigned int*)malloc(2 * sizeof(unsigned int));
            exclusions[currentIndex][0] = square[i][0];
            exclusions[currentIndex][1] = square[i][1];
            currentIndex++;
        }
    }

    return exclusions;
}

// Same as `getSquareExclusionZoneSquare`, but returns the array of the exclusive coordinates if the zone. 
unsigned int** getZoneExclusionZoneSquare(unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int numExclusions = gridSize - sqrtGridSize;
    unsigned int** exclusions = (unsigned int**)malloc(numExclusions * sizeof(unsigned int*));
    unsigned int currentIndex = 0;

    for (unsigned int i = 0; i < gridSize; i++)
    {
        bool isIncluded = false;
        for (unsigned int ii = 0; ii < gridSize; ii++)
        {
            if (square[i][0] == zone[ii][0] && square[i][1] == zone[ii][1])
                isIncluded = true;
        }

        if (!isIncluded)
        {
            exclusions[currentIndex] = (unsigned int*)malloc(2 * sizeof(unsigned int));
            exclusions[currentIndex][0] = zone[i][0];
            exclusions[currentIndex][1] = zone[i][1];
            currentIndex++;
        }
    }

    return exclusions;
}

void freeExclusions(unsigned int** exclusion, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int numExclusions = gridSize - sqrtGridSize;
    for (unsigned int i = 0; i < numExclusions; i++)
        free(exclusion[i]);
    free(exclusion);
}

unsigned int countValuesInIntersection(T_Grid grid, unsigned int** intersections, unsigned int noteValue, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int numValuesInIntersection = 0;

    for (unsigned int i = 0; i < sqrtGridSize; i++)
    {
        unsigned int intersectionCellX = intersections[i][0];
        unsigned int intersectionCellY = intersections[i][1];
        if (isNoteInCell(getCell(grid, intersectionCellX, intersectionCellY), noteValue))
            numValuesInIntersection++;
    }

    return numValuesInIntersection;
}

bool getIsPointing(T_Grid grid, unsigned int** squareExclusions, unsigned int numExclusions, unsigned int noteValue)
{
    bool isPointing = true;

    for (unsigned int i = 0; i < numExclusions; i++)
    {
        unsigned int exclusionCellX = squareExclusions[i][0];
        unsigned int exclusionCellY = squareExclusions[i][1];

        if (isNoteInCell(getCell(grid, exclusionCellX, exclusionCellY), noteValue))
            isPointing = false;
    }

    return isPointing;
}

bool getIsBox(T_Grid grid, unsigned int** zoneExclusions, unsigned int numExclusions, unsigned int noteValue)
{
    bool isBox = true;

    for (unsigned int ii = 0; ii < numExclusions; ii++)
    {
        unsigned int exclusionCellX = zoneExclusions[ii][0];
        unsigned int exclusionCellY = zoneExclusions[ii][1];

        if (isNoteInCell(getCell(grid, exclusionCellX, exclusionCellY), noteValue))
            isBox = false;
    }

    return isBox;
}

void removeNotesSquare(T_Grid grid, unsigned int** squareExclusions, unsigned int numExclusions, unsigned int noteValue)
{
    for (unsigned int i = 0; i < numExclusions; i++)
    {
        unsigned int exclusionCellX = squareExclusions[i][0];
        unsigned int exclusionCellY = squareExclusions[i][1];
        unsetNoteCell(getCell(grid, exclusionCellX, exclusionCellY), noteValue);
    }
}

void removeNotesZone(T_Grid grid, unsigned int** zoneExclusions, unsigned int numExclusions, unsigned int noteValue)
{
    for (unsigned int ii = 0; ii < numExclusions; ii++)
    {
        unsigned int exclusionCellX = zoneExclusions[ii][0];
        unsigned int exclusionCellY = zoneExclusions[ii][1];
        unsetNoteCell(getCell(grid, exclusionCellX, exclusionCellY), noteValue);
    }
}

void removePointingTuplesOfSquare(T_Grid grid, unsigned int noteValue, unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int** intersections = getIntersectionZoneSquare(square, zone, gridSize, sqrtGridSize);
    
    unsigned int numExclusions = gridSize - sqrtGridSize;
    unsigned int** squareExclusions = getSquareExclusionZoneSquare(square, zone, gridSize, sqrtGridSize);
    unsigned int** zoneExclusions = getZoneExclusionZoneSquare(square, zone, gridSize, sqrtGridSize);

    unsigned int numValuesInIntersection = countValuesInIntersection(grid, intersections, noteValue, gridSize, sqrtGridSize);

    bool isPointing = true;
    bool isBox = true;

    if (numValuesInIntersection >= 2)
    {
        isPointing = getIsPointing(grid, squareExclusions, numExclusions, noteValue);
        isBox = getIsBox(grid, zoneExclusions, numExclusions, noteValue);
    }

    if (isBox)
        removeNotesSquare(grid, squareExclusions, numExclusions, noteValue);

    if (isPointing)
        removeNotesZone(grid, zoneExclusions, numExclusions, noteValue);

    freeExclusions(squareExclusions, gridSize, sqrtGridSize);
    freeExclusions(zoneExclusions, gridSize, sqrtGridSize);
    freeIntersections(intersections, sqrtGridSize);
}

void solvePointingTuples(T_Grid grid)
{
    unsigned int gridSize = getGridSize(grid);
    unsigned int sqrtGridSize = getGridSqrtSize(grid);

    // Loop through every square of the grid
    for (unsigned int i = 0; i < gridSize; i++)
    {
        unsigned int** square = getSquareCellIndices(gridSize, sqrtGridSize, i);

        // Loop through every note value
        for (unsigned int noteValue = 0; noteValue < gridSize; noteValue++)
        {
            // Loop through every line that intersects the current square
            for (unsigned int currentLine = 0; currentLine < sqrtGridSize; currentLine++)
            {
                // The y coordinate of the current line
                unsigned int y = (i / sqrtGridSize) * sqrtGridSize + currentLine;

                unsigned int** line = getLineIndices(gridSize, y);
                removePointingTuplesOfSquare(grid, noteValue, square, line, gridSize, sqrtGridSize);
                freeZone(line, gridSize);
            }

            // Loop through every column that intersects the current square
            for (unsigned int currentColumn = 0; currentColumn < sqrtGridSize; currentColumn++)
            {
                // The x coordinate of the current column
                unsigned int x = (i % sqrtGridSize) * sqrtGridSize + currentColumn;

                unsigned int** column = getColumnIndices(gridSize, x);
                removePointingTuplesOfSquare(grid, noteValue, square, column, gridSize, sqrtGridSize);
                freeZone(column, gridSize);
            }
        }

        freeZone(square, gridSize);
    }
}
