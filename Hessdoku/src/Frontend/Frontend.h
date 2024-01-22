#ifndef FRONTEND_H
#define FRONTEND_H

#include <Grid.h>
#include <Frontend/Window.h>

/**
 * A frontend structure that holds everything related to the graphical interface.
 */
typedef struct T_Frontend T_Frontend;

/**
 * Creates a frontend structure
 * @param game The game to display to the frontend.
 * @return The new frontend.
*/
T_Frontend* createFrontend(T_Grid grid);

/**
 * Run the frontend. This executes the main loop of the frontend.
 * @param frontend The frontend to run.
 */
void runFrontend(T_Frontend* frontend);

/**
 * Free a frontend. The game associated to the frontend is NOT freed, and it is the responsability of the backend to free the memory.
 * @param frontend The frontend to free.
 */
void freeFrontend(T_Frontend* frontend);

/**
 * Draws a whole grid.
 * @param frontend The frontend to draw to.
 * @param xOffset The x offset to apply when drawing the grid.
 * @param xOffset The y offset to apply when drawing the grid.
 * @param rectSize The size of a grid square.
*/
void drawGrid(T_Frontend* frontend, int xOffset, int yOffset, int rectSize);

T_Window* getWindow(T_Frontend* frontend);
T_Font* getFont(T_Frontend* frontend);
T_Grid getGrid(T_Frontend* frontend);
bool getDrawNotes(T_Frontend* frontend);

#endif
