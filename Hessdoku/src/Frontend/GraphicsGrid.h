#ifndef GRAPHICS_FRONTEND_H
#define GRAPHICS_FRONTEND_H

#include <Frontend/Frontend.h>
#include <Grid.h>

typedef struct T_GraphicsGrid T_GraphicsGrid;

T_GraphicsGrid* createGraphicsGrid(T_Grid grid, int x, int y, int squareSize);
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

void drawGrid(T_Frontend* frontend, T_GraphicsGrid* grid);

#endif
