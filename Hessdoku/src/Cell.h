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
 * @author Phileas, Baptiste
 */
T_Cell *createCell();


/**
 * Frees the cell in parameter.
 *
 * @param cell a pointer to the cell that must be fred
 *
 * @author Phileas
 */
void freeCell(T_Cell* cell);

/**
 * Adds a specific note to a cell. This function probably won't be used in this program, but it exists nonetheless. 
 * 
 * @param cell The cell where to add the note.
 * @param noteValue The note's value to add.
 * 
 * @author Baptiste
 */
void setNoteCell(T_Cell* cell, unsigned int noteValue);

/**
 * Removes a specific note to a cell.
 *
 * @param cell The cell where to remove the note.
 * @param noteValue The note's value to remove.
 * 
 * @return A boolean indicating if the value changed
 * 
 * @author Baptiste
 */
bool unsetNoteCell(T_Cell* cell, unsigned int noteValue);

/**
 * Returns the value of a cell. 
 * Note: the value of a cell is defined when there's a single note in a cell. 
 * 
 * @param cell The cell where to get the value from
 * 
 * @returns Returns the value of the cell if defined. Returns 0 otherwise.
 * 
 * @author Baptiste
 */
unsigned int getValueOfCell(T_Cell* cell);


/**
 * Sets the value of a cell to a specific value.
 * 
 * @param cell The cell where to edit the value
 * @param value The new value of the cell
 * 
 * @author Baptiste
 */
void setValueOfCell(T_Cell* cell, unsigned int value);

#endif