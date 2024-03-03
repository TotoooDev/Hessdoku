#ifndef SWORDFISH_H
#define SWORDFISH_H

#include "Grid.h"
#include <assert.h>

/**
 * Removes notes if a swordfish has been detected
 * @param grid The grid to solve.
 * @param k The swordfish param
 * @param outputFile The logs file
 * @return `true` if the grid has changed, `false` otherwise.
*/
bool solveSwordfish(T_Grid grid, int k, FILE* outputFile);

#endif
