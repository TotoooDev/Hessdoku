#ifndef SOLVER_H
#define SOLVER_H

#include <Grid.h>


bool cellVerif(bool* baton, int val);

bool gridVerif(T_Grid grid, int minX, int maxX, int minY, int maxY);




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