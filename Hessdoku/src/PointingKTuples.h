#ifndef POINTING_K_TUPLES_H
#define POINTING_K_TUPLES_H

#include <Solver.h>
#include <Grid.h>

/**
 * Removes one pointing pair or triplets.
 * @param grid The grid to solve.
 * @return `true` if the grid has changed, `false` otherwise.
*/
bool solvePointingTuples(T_Grid grid, FILE* outputFile);

#endif
