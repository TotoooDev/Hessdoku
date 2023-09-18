#ifndef GRID_H
#define GRID_H

#include <Cell.h>

typedef T_Cell** T_Grid;

/**
 * @author Phileas
 */
T_Grid generateGrid(int sizeX, int sizeY);

#endif