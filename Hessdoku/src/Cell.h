#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stdlib.h>


/**
 * A simple type representing a cell of the sudoku grid.
 *
 * @member notes An array of the possible values for this cell according to the sudoku rules
 * @member value The value of the current cell (from 1 to 9, encoded on 4 bits)
 */
typedef struct T_Cell
{
    bool* notes;
    unsigned char value : 4;
} T_Cell;

/**
 * @author Phileas
 */
T_Cell createCell(value);

#endif