#ifndef SOLVER_H
#define SOLVER_H

#include <Grid.h>

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


#endif