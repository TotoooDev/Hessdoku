#ifndef GRID_H
#define GRID_H

#include <Cell.h>
#include <Macros.h>

/**
 * A struct that contains a matrix (double table) of pointers to cells and its size.
 */
typedef struct T_GridStruct {
	T_Cell*** grid;
	unsigned int size;
	unsigned int sqrtSize;
} T_Grid;

/**
 * Allocates a grid and fills it by default cells (value : 0 : empty)
 *
 * @param size The size of the grid (size x size)
 *
 * @author Phileas
 */
T_Grid generateGrid(int size, int sqrtSize);

T_Grid generateGridFromFile(const char* path);

/**
 * Returns the size of the grid
 *
 * @param grid The grid
 */
unsigned int getGridSize(T_Grid grid);

/**
 * Returns the sqrt size of the grid
 *
 * @param grid The grid
 */
unsigned int getGridSqrtSize(T_Grid grid);

/**
 * Frees the grid
 *
 * @param grid The grid to be fred
 *
 * @author Phileas
 */
void freeGrid(T_Grid grid);

/**
 * Returns the value of a cell.
 *
 * @param grid A Sudoku grid
 * @param x The x position of the cell
 * @param y The y position of the cell
 *
 * @author Baptiste
 */
unsigned int getValue(T_Grid grid, int x, int y);

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
 * Displays the given grid in a very pretty way in the console.
 *
 * @param grid A Sudoku grid
 * 
 * @author Baptiste
 */
void displayGridToConsole(T_Grid grid);

/**
 * Displays the notes for a given sudoku grid in the console.
 *
 * @param grid A Sudoku grid
 * 
 * @author Baptiste
 */
void displayNotesToConsole(T_Grid grid);

/**
 * Returns the cell.
 *
 * @param grid A Sudoku grid
 * @param i The x position of the cell
 * @param j The y position of the cell
 *
 * @author Marie
 */
T_Cell* getCell(T_Grid grid, int i, int j);

/**
 * Initialize an array of boolean to false
 *
 * @param grid : the sudoku
 * @param b : the array
 *
 * @author Marie
 */
void createBaton(T_Grid grid, unsigned char* b);

/**
 * Verif the sudoku entirely
 *
 * @param grid : the sudoku
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfGrid(T_Grid grid, int* errorValue, int** cooErrorValue);


#endif