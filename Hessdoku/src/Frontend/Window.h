#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

/**
 * A data structure representing a window.
 */
typedef struct T_Window T_Window;

/**
 * Creates a window and displays it at the center of the screen.
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return The newly created window.
 */
T_Window* createWindow(const char* title, int width, int height);

/**
 * Destroys a window.
 * @param window The window to destroy.
 */
void freeWindow(T_Window* window);

/**
 * Polls the window events and update the window.
 * @param window The window to update
 */
void updateWindow(T_Window* window);

/**
 * Clears the window with a given color.
 * @param window The window to clear.
 * @param r The red component of the clear color (0-255).
 * @param g The blue component of the clear color (0-255).
 * @param b The green component of the clear color (0-255).
 */
void clearWindow(T_Window* window, unsigned char r, unsigned char g, unsigned char b);

/**
 * Presents all the drawings to the window. You need to call this function to see anything on the screen.
 * @param window The window to present.
 */
void presentWindow(T_Window* window);

/**
 * Returns whether the window is open or not. What can close a window include inputs like:
 * - Clicking the x button.
 * - Pressing Alt-F4.
 * - And probably other things.
 * @param window The window to check for.
 * @return `true` if the window is open, `false` otherwise.
*/
bool isWindowOpen(T_Window* window);

#endif
