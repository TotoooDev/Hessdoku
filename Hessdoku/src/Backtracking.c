#include "Grid.h"

bool isValidMove(T_Grid grid, int x, int y, int value)
{
    // Check if 'value' is not already used in the current row, column, or 3x3 grid
    for (int i = 0; i < getGridSize(grid); i++)
    {
        // Check row
        if (getValue(grid, x, i) == value) return false;
        // Check column
        if (getValue(grid, i, y) == value) return false;
    }

    // Check 3x3 grid
    int startRow = (x / getGridSqrtSize(grid)) * getGridSqrtSize(grid);
    int startCol = (y / getGridSqrtSize(grid)) * getGridSqrtSize(grid);

    for (int i = startRow; i < startRow + getGridSqrtSize(grid); i++)
        for (int j = startCol; j < startCol + getGridSqrtSize(grid); j++)
            if (getValue(grid, i, j) == value)
                return false;

    return true;
}

bool backtrackingSolve(T_Grid grid)
{
    unsigned int size = getGridSize(grid);

    // Find an empty cell
    int row = -1, col = -1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (getValue(grid, i, j) == 0)
            {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) break;  // Found an empty cell
    }

    // If no empty cell is found, the grid is solved
    if (row == -1 && col == -1)
        return true;

    // Try placing numbers (1-9) in the empty cell
    for (int num = 1; num <= size; num++)
    {
        if (isValidMove(grid, row, col, num))
        {
            // Place the number and recursively solve the grid
            setCell(grid, row, col, num);

            // If the grid is solved recursively, return true
            if (backtrackingSolve(grid))
                return true;

            // If the grid cannot be solved with the current placement, backtrack
            setCellEmpty(grid, row, col);
        }
    }

    // If no valid number can be placed, return false
    return false;
}
