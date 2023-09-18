#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

/**
 * A simple type representing a cell of the sudoku grid.
 */
typedef struct T_Cell
{
    bool* notes;
    unsigned char value : 4;
} T_Cell;

#endif