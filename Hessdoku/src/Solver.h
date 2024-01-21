#ifndef SOLVER_H
#define SOLVER_H

#include <Grid.h>



/**
 * Reset/set a table to 0
 *
 * @param grid : the grid (for the size)
 * @param b : a table of 9 unsigned char
 *
 * @author Marie
 */
void createBaton(T_Grid grid, unsigned char* b);


/**
 * Verif the validity of a zone
 *
 * @param grid : the sudoku
 * @param minX, maxX, minY, maxY 
 * @param baton : a table of 9 unsigned char 
 *					baton[i-1] = 0 if we didn't see i in the zone
 *					baton[i-1] = 1 if we already see i
 *
 * @return false if the zone isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfRect(T_Grid grid, int minX, int maxX, int minY, int maxY, unsigned char* baton);


/**
 * Verif if the number of a cell has already been seen
 *
 * @param baton : a table of 9 unsigned char
 * @param val : the value of the cell
 *
 * @return false if we already see this value
 *			true if not
 *
 * @author Marie
 */
bool checkValidityOfCell(unsigned char* baton, int val);


/**
 * Verif if the lines of a sudoku are valid
 *
 * @param grid : the sudoku
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfLine(T_Grid grid);


/**
 * Verif if the columns of a sudoku are valid
 *
 * @param grid : the sudoku
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfColumn(T_Grid grid);


/**
 * Verif if the squares of a sudoku are valid
 *
 * @param grid : the sudoku
 *
 * @return false if it isn't valid
 *			true if it is
 *
 * @author Marie
 */
bool checkValidityOfSquare(T_Grid grid);


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
bool checkValidityOfGrid(T_Grid grid);

/**
 * Applies the rules #1, 2 and 3 of the Sudoku Solving process.
 * 
 * @param grid : the sudoku grid
 * 
 * @return A boolean indicating wether the grid changed or not 
 * 
 * @author Baptiste
 */
bool removeNotesInGridByZones(T_Grid grid);


/**
 * 
 */
bool kUpletsSolve(T_Grid grid, const int k);

void testBouh(T_Grid grid);

void testMwah(T_Grid grid);

#endif