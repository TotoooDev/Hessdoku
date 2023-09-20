#ifndef GRID_H
#define GRID_H

#include <Cell.h>


typedef T_Cell* ** T_Grid;

/**
 * Allocates a grid and fills it by default cells (value : 0 : empty)
 *
 * @param sizeX The size of the columns of the grid
 * @param sizeY The size of the lines of the grid
 *
 * @author Phileas
 */
T_Grid generateGrid(int sizeX, int sizeY);


/**
 * Frees the grid
 *
 * @param grid The grid to be fred
 * @param sizeX The size of the columns of the grid
 * @param sizeY The size of the lines of the grid
 *
 * @author Phileas
 */
T_Grid freeGrid(T_Grid grid, int sizeX, int sizeY);

/**
 * Change the value of a cell. If the new value is 0, the cell is treatde as empty.
 *
 * @param grid The grid of the modified cell
 * @param x The x position of the cell
 * @param y The y position of the cell
 * @param value The new value of the cell
 *
 * @author Toto
 */
void setCell(T_Grid grid, unsigned char x, unsigned char y, char value);

/**
 * Changes the cell's value to 0 (empty)
 *
 * @param grid The grid the cell will be removed from
 * @param x The x position of the cell
 * @param y The y position of the cell
 *
 * @author Toto
 */
void setCellEmpty(T_Grid grid, unsigned char x, unsigned char y);

/**
 * Displays the given grid in a verry pretty way in the console.
 *
 * @param grid The grid to display
 * @param size The size of the grid (square)
 * 
 * @author Baptiste
 */
void displayGridToConsole(T_Grid grid, int size);

/**
 * Displays the notes for a given sudoku grid in the console.
 *
 * @param grid Where the notes are
 * @param size The size of the grid
 * 
 * @author Baptiste
 */
void displayNotesToConsole(T_Grid grid, int size);


#endif