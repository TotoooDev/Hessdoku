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

/**
 * Sets the grid.
 * @param graphicsGrid The graphics grid to change.
 * @param grid The new grid.
*/
void setGrid(T_GraphicsGrid* graphicsGrid, T_Grid grid);

/**
 * Sets the grid position.
 * @param grid The graphics grid to change.
 * @param x The new x position.
 * @param y The new y position.
*/
void setGraphicsGridPos(T_GraphicsGrid* grid, int x, int y);

/**
 * Sets the grid square size.
 * @param grid The graphics grid to change.
 * @param squareSize the new square size.
*/
void setGraphicsGridSquareSize(T_GraphicsGrid* grid, int squareSize);

/**
 * Sets whether the grid should display notes or not.
 * @param grid The graphics grid to change.
 * @param drawNotes `true` if the grid should draw notes, `false` otherwise.
*/
void setGraphicsGridDrawNotes(T_GraphicsGrid* grid, bool drawNotes);

/**
 * Sets the selected cell of the grid.
 * @param grid The graphics grid to change.
 * @param x The new selected cell x position.
 * @param y The new selected cell y position.
*/
void setGraphicsGridSelectedCell(T_GraphicsGrid* grid, int x, int y);

/**
 * Returns the grid associated with a graphics grid.
 * @param grid The graphics grid.
 * @return The grid associated with the graphics grid.
*/
T_Grid getGrid(T_GraphicsGrid* grid);

/**
 * Sets `x` and `y` to the graphics grid position.
 * @param grid The graphics grid.
 * @param x A pointer to the location of the x position.
 * @param y A pointer to the location of the y position.
 * @note `x` and `y` may be NULL.
*/
void getGraphicsGridPos(T_GraphicsGrid* grid, int* x, int* y);

/**
 * Returns the square size of a graphics grid.
 * @param grid The graphics grid.
 * @return The square size of the grid.
*/
int getGraphicsGridSquareSize(T_GraphicsGrid* grid);

/**
 * Returns whether or not the graphics grid should draw the notes or not.
 * @param grid The graphics grid.
 * @return `true` if the grid draws the notes, `false` otherwise.
*/
bool getGraphicsGridDrawNotes(T_GraphicsGrid* grid);

/**
 * Draws the graphics grid to the window.
 * @param frontend The frontend you want to draw the grid to.
 * @param grid The graphics grid to draw.
 * @param invalidValue The two invalid values positions, represented as an array of two positions (represented as an array of two components for x and y).
 * @param isValid `true` if the grid is valid, `false` otherwise.
*/
void drawGrid(T_Frontend* frontend, T_GraphicsGrid* grid, int** invalidValue, bool isValid);

#endif
