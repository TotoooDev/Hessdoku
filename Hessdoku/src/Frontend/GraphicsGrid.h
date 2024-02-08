#ifndef GRAPHICS_FRONTEND_H
#define GRAPHICS_FRONTEND_H

#include <Frontend/Frontend.h>
#include <Grid.h>

/**
 * A structure to represent a grid that is drawn to the screen.
*/
typedef struct T_GraphicsGrid T_GraphicsGrid;

/**
 * Creates a new graphics grid.
 * @param grid The grid associated with this graphics grid.
 * @param x The x position of the grid.
 * @param x The y position of the grid.
 * @param squareSize The size of the squares of the grid.
 * @returns The new grid.
*/
T_GraphicsGrid* createGraphicsGrid(T_Grid grid, int x, int y, int squareSize);

/**
 * Frees a graphics grid.
 * @param grid the graphics grid to free.
*/
void freeGraphicsGrid(T_GraphicsGrid* grid);

void setGrid(T_GraphicsGrid* graphicsGrid, T_Grid grid);
void setGraphicsGridPos(T_GraphicsGrid* grid, int x, int y);
void setGraphicsGridSquareSize(T_GraphicsGrid* grid, int squareSize);
void setGraphicsGridDrawNotes(T_GraphicsGrid* grid, bool drawNotes);
void setGraphicsGridSelectedCell(T_GraphicsGrid* grid, int x, int y);

T_Grid getGrid(T_GraphicsGrid* grid);
void getGraphicsGridPos(T_GraphicsGrid* grid, int* x, int* y);
int getGraphicsGridSquareSize(T_GraphicsGrid* grid);
bool getGraphicsGridDrawNotes(T_GraphicsGrid* grid);

void drawGrid(T_Frontend* frontend, T_GraphicsGrid* grid, int** invalidValue, bool isValid);

#endif
