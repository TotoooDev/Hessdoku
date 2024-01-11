#ifndef WINDOW_H
#define WINDOW_H

#include <Grid.h>
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
 * Returns whether the window is open or not. What can close a window include inputs like clicking the x button, ressing Alt-F4, and probably other things.
 * @param window The window to check for.
 * @return `true` if the window is open, `false` otherwise.
*/
bool isWindowOpen(T_Window* window);

/**
 * Sets the draw color for the next draw calls.
 * @param window The window to set the draw color to.
 * @param r The red component of the clear color (0-255).
 * @param g The blue component of the clear color (0-255).
 * @param b The green component of the clear color (0-255).
 */
void setDrawColor(T_Window* window, unsigned char r, unsigned char g, unsigned char b);

/**
 * Draws a line.
 * @param window The window to draw the line to.
 * @param startX The x starting point of the line.
 * @param startY The y starting point of the line.
 * @param endX The x starting point of the line.
 * @param endY The y ending point of the line.
*/
void drawLine(T_Window* window, int startX, int startY, int endX, int endY);

/**
 * Draws a rectangle shape.
 * @param window The window to draw the line to.
 * @param x The x starting point of the rect.
 * @param y The y starting point of the rect.
 * @param width The width of the rect.
 * @param height The height of the shape.
*/
void drawRect(T_Window* window, int x, int y, int width, int height);

/**
 * Draws a whole grid.
 * @param window The window to draw the line to.
 * @param grid The grid to draw.
 * @param xOffset The x offset to apply when drawing the grid.
 * @param xOffset The y offset to apply when drawing the grid.
 * @param rectSize The size of a grid square.
*/
void drawGrid(T_Window* window, T_Grid grid, int xOffset, int yOffset, int rectSize);

#endif
