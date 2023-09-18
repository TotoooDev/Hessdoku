#ifndef CELL_H
#define CELL_H

/**
 * A simple type representing a cell of the sudoku grid.
*/
typedef struct T_Cell
{
    /**
     * This is the value stored in the cell, defined in 4 bits.
    */
    unsigned char value : 4;
} T_Cell;

#endif