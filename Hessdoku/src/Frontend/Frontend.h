#ifndef FRONTEND_H
#define FRONTEND_H

#include <Frontend/Window.h>

/**
 * A frontend structure that holds everything related to the graphical interface.
 */
typedef struct T_Frontend T_Frontend;

/**
 * Creates a frontend structure
 * @param game The game to display to the frontend.
*/
void createFrontend(T_Grid grid);

/**
 * Run the frontend. This executes the main loop of the frontend.
 */
void runFrontend();

/**
 * Free a frontend. The game associated to the frontend is NOT freed, and it is the responsability of the backend to free the memory.
 */
void freeFrontend();

T_Window* getWindow();
T_Font* getFont();

#endif
