#ifndef SOLVER_H
#define SOLVER_H

#include <Grid.h>



/**
 * Reset/set a table to 0
 *
 * @param b : a table of 9 unsigned char
 *
 * @author Marie
 */
void createBaton(unsigned char* b);


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
bool allVerif(T_Grid grid, int minX, int maxX, int minY, int maxY, unsigned char* baton);


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
bool cellVerif(unsigned char* baton, int val);


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
bool lineVerif(T_Grid grid);


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
bool columnVerif(T_Grid grid);


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
bool squareVerif(T_Grid grid);


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
bool gridVerif(T_Grid grid);

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


//PREVIOUS CODE


/**
 * Reset a table to false
 * 
 * @param w : a table of 9 booleans
 * 
 * @return w with all his value at false
 * 
 * @author Marie
 */
//void resetWitness(bool *w);


/**
* Display a table of 9 booleans
* 
* @param w : a table of 9 booleans
* 
* @author Marie
*/
//void aff_witness(bool* w);


/**
* Check if the sudoku is correct
* 
* @param grid : the sudoku
* 
* @returns true (1) : no error ; false (0) : error
* 
* @author Marie
*/
//bool checkingAccuracy(T_Grid grid);

#endif