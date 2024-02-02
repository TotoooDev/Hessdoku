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

        // LOG("squareCellsIndices[%d][1]: %d", i, squareCellsIndices[i][1]);
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

unsigned int** getIntersectionZoneSquare(unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int** intersections = (unsigned int**)malloc(sqrtGridSize * sizeof(unsigned int*));
    unsigned int currentIndex = 0;
    for (unsigned int i = 0; i < gridSize; i++)
    {

        bool isIncluded = false;
        for (unsigned int ii = 0; ii < gridSize; ii++)
        {
            LOG("square[%d]: %d, %d", i, square[i][0], square[i][1]);
            LOG("zone[%d]: %d, %d", i, zone[ii][0], zone[ii][1]);

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

    LOG("Expected intersections: %d", sqrtGridSize);
    LOG("Found intersections: %d", currentIndex);

    return intersections;
}

void freeIntersections(unsigned int** intersection, unsigned int sqrtGridSize)
{
    for (unsigned int i = 0; i < sqrtGridSize; i++)
        free(intersection[i]);
    free(intersection);
}

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
            // LOG("Current i: %d", i);
            // LOG("square[i]: %d, %d", square[i][0], square[i][1]);
            // LOG("zone[ii]: %d, %d", zone[ii][0], zone[ii][1]);

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

    // LOG("numExclusions: %d", numExclusions);
    // LOG("Found exclusions: %d", currentIndex);

    return exclusions;
}

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
            // LOG("Current i: %d", i);
            // LOG("square[i]: %d, %d", square[i][0], square[i][1]);
            // LOG("zone[ii]: %d, %d", zone[ii][0], zone[ii][1]);

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

    // LOG("numExclusions: %d", numExclusions);
    // LOG("Found exclusions: %d", currentIndex);

    return exclusions;
}

void freeExclusions(unsigned int** exclusion, unsigned int gridSize, unsigned int sqrtGridSize)
{
    unsigned int numExclusions = gridSize - sqrtGridSize;
    for (unsigned int i = 0; i < numExclusions; i++)
        free(exclusion[i]);
    free(exclusion);
}

// TODO: rename this function.
void bam(T_Grid grid, unsigned int x, unsigned int** square, unsigned int** zone, unsigned int gridSize, unsigned int sqrtGridSize)
{
    for (unsigned int i = 0; i < sqrtGridSize; i++)
    {
        // LOG("Bam i: %d", i);

        unsigned int k = 0;
        
        unsigned int** intersections = getIntersectionZoneSquare(square, zone, gridSize, sqrtGridSize);
        
        unsigned int numExclusions = gridSize - sqrtGridSize;
        unsigned int** squareExclusions = getSquareExclusionZoneSquare(square, zone, gridSize, sqrtGridSize);
        unsigned int** zoneExclusions = getZoneExclusionZoneSquare(square, zone, gridSize, sqrtGridSize);

        for (unsigned int ii = 0; ii < sqrtGridSize; ii++)
        {
            unsigned int intersectionCellX = intersections[ii][0];
            unsigned int intersectionCellY = intersections[ii][1];
            if (isNoteInCell(getCell(grid, intersectionCellX, intersectionCellY), x))
                k++;
        }

        bool isPointing = true;
        bool isBox = true;

        if (k >= 2)
        {
            for (unsigned int ii = 0; ii < numExclusions; ii++)
            {
                unsigned int exclusionCellX = squareExclusions[ii][0];
                unsigned int exclusionCellY = squareExclusions[ii][1];
                isPointing = !isNoteInCell(getCell(grid, exclusionCellX, exclusionCellY), x);
            }

            for (unsigned int ii = 0; ii < numExclusions; ii++)
            {
                unsigned int exclusionCellX = zoneExclusions[ii][0];
                unsigned int exclusionCellY = zoneExclusions[ii][1];
                isPointing = !isNoteInCell(getCell(grid, exclusionCellX, exclusionCellY), x);
            }
        }

        if (isBox)
        {
            for (unsigned int ii = 0; ii < numExclusions; ii++)
            {
                unsigned int exclusionCellX = squareExclusions[ii][0];
                unsigned int exclusionCellY = squareExclusions[ii][1];
                unsetNoteCell(getCell(grid, exclusionCellX, exclusionCellY), x);
            }
        }

        if (isPointing)
        {
            for (unsigned int ii = 0; ii < numExclusions; ii++)
            {
                unsigned int exclusionCellX = zoneExclusions[ii][0];
                unsigned int exclusionCellY = zoneExclusions[ii][1];
                unsetNoteCell(getCell(grid, exclusionCellX, exclusionCellY), x);
            }
        }

        freeExclusions(squareExclusions, gridSize, sqrtGridSize);
        freeExclusions(zoneExclusions, gridSize, sqrtGridSize);
        freeIntersections(intersections, sqrtGridSize);
    }
}

void solvePointingTuples(T_Grid grid)
{
    unsigned int gridSize = getGridSize(grid);
    unsigned int sqrtGridSize = getGridSqrtSize(grid);

    // Loop through every square of the grid
    for (unsigned int i = 0; i < gridSize; i++)
    {
        // LOG("i: %d", i);
        unsigned int** square = getSquareCellIndices(gridSize, sqrtGridSize, i);

        for (unsigned int x = 0; x < 9; x++)
        {
            for (unsigned int currentLine = 0; currentLine < sqrtGridSize; currentLine++)
            {
                unsigned int y = (i / sqrtGridSize) * sqrtGridSize + currentLine;

                // LOG("Current line: %d", currentLine);
                LOG("y: %d", y);

                unsigned int** line = getLineIndices(gridSize, y);
                bam(grid, x, square, line, gridSize, sqrtGridSize);
                freeZone(line, gridSize);
            }
            for (unsigned int currentColumn = 0; currentColumn < sqrtGridSize; currentColumn++)
            {
                unsigned int x = (i % sqrtGridSize) * sqrtGridSize + currentColumn;

                LOG("Current column: %d", currentColumn);
                LOG("x: %d", x);

                unsigned int** column = getColumnIndices(gridSize, x);
                bam(grid, x, square, column, gridSize, sqrtGridSize);
                freeZone(column, gridSize);
            }
        }

        freeZone(square, gridSize);
    }
}
