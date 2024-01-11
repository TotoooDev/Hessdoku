#ifndef FRONTEND_H
#define FRONTEND_H

#include <Grid.h>

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

#endif
