#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * A simple type representing a cell of the sudoku grid.
 *
 * @member notes An array of the possible values for this cell according to the sudoku rules
 * @member value The value of the current cell (from 1 to 9, encoded on 4 bits)
 */
typedef struct T_Cell
{
    unsigned int notes : 9;
} T_Cell;

/**
 * Allocates, initialize and returns a Sudoku grid cell.
 * 
 * @param value The cell's value. It must be contained in 4 bits
 * 
 * @author Phileas
 */
T_Cell *createCell(unsigned char value);


/**
 * Frees the cell in parameter.
 *
 * @param cell a pointer to the cell that must be fred
 *
 * @author Phileas
 */
void freeCell(T_Cell* cell);

#endif