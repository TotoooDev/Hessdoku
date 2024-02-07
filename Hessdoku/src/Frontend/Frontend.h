#ifndef FRONTEND_H
#define FRONTEND_H

#include <Frontend/Window.h>
#include <Frontend/Theme.h>

/**
 * A frontend structure that holds everything related to the graphical interface.
 */
typedef struct T_Frontend T_Frontend;

/**
 * Creates a frontend structure
 * @param game The game to display to the frontend.
*/
void createFrontend(T_Grid grid, T_ThemeType themeType);

/**
 * Run the frontend. This executes the main loop of the frontend.
 */
void runFrontend();

/**
 * Free a frontend. The game associated to the frontend is NOT freed, and it is the responsability of the backend to free the memory.
 */
void freeFrontend();

/**
 * @returns The window associated with the frontend.
 */
T_Window* getWindow();

/**
 * @returns The font associated with the frontend.
 */
T_Font* getFont();

T_Theme getTheme();

#endif
