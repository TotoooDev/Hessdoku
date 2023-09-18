#ifndef GRID_H
#define GRID_H

#include <Cell.h>


typedef T_Cell*** T_Grid;

/**
 * Add a cell into the grid.
 *
 * @param grid The grid in which the cell will be added
 * @param x The x position of the new cell
 * @param y The y position of the new cell
 * @param cell The cell to be added
 *
 * @author Toto
 */
void addCell(T_Grid grid, unsigned char x, unsigned char y, T_Cell* cell);

/**
 * Remove a cell from the grid. This does not free the cell.
 *
 * @param grid The grid the cell will be removed from
 * @param x The x position of the cell
 * @param y The y position of the cell
 *
 * @author Toto
 */
void removeCell(T_Grid grid, unsigned char x, unsigned char y);

/**
 * @author Phileas
 */
T_Grid generateGrid(int sizeX, int sizeY);

/**
 * Displays the given grid in a verry pretty way in the console.
 *
 * @param grid The grid to display
 * @param size The size of the grid (square)
 * @author Baptiste
 */
void displayGridToConsole(T_Grid grid, int size);

#endif