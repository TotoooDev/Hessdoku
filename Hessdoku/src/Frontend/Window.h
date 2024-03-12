#ifndef WINDOW_H
#define WINDOW_H

#include <Grid.h>
#include <Frontend/Color.h>
#include <Frontend/Font.h>
#include <Frontend/Button.h>
#include <stdbool.h>

/**
 * A data structure representing a window.
 */
typedef struct T_Window T_Window;

/**
 * A function that is called when a mouse button press is detected.
 * @param int The button that is pressed.
 * @param int The number of clicks.
 * @param void* A pointer to something you want to access.
*/
typedef void(*T_ButtonDownFunction)(int, int, void*);
typedef void(*T_ButtonRightDownFunction)(int, int, void*);

/**
 * A function that is called when a mouse button release is detected.
 * @param int The button that is pressed.
 * @param int The number of clicks.
 * @param void* A pointer to something you want to access.
*/

typedef void(*T_ButtonUpFunction)(int, void*);
/**
 * A function that is called when a mouse movement is detected.
 * @param int The button that is pressed.
 * @param int The number of clicks.
 * @param void* A pointer to something you want to access.
*/

typedef void(*T_MouseMovedFunction)(int, int, void*);

/**
 * A function that is called when a key press is detected.
 * @param int The button that is pressed.
 * @param int The number of clicks.
 * @param void* A pointer to something you want to access.
*/
typedef void(*T_KeyDownFunction)(int, void*);

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
 * Returns the time since the window system was initialized.
 * @return The number of milliseconds since the window system was initialized.
*/
unsigned long getTicks();

/**
 * Polls the window events and update the window.
 * @param window The window to update
 */
void updateWindow(T_Window* window, T_Font* font);

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
 * Draws all the widgets (buttons, ...) of the window.
 * @param window The window to draw the widgets of.
 */
void drawWidgets(T_Window* window, T_Font* font);

/**
 * Returns whether the window is open or not. What can close a window include inputs like clicking the x button, ressing Alt-F4, and probably other things.
 * @param window The window to check for.
 * @return `true` if the window is open, `false` otherwise.
*/
bool isWindowOpen(T_Window* window);

/**
 * Adds a button to the window.
 * @param window The window to add the button to.
 * @param button The button to add to the window.
*/
void addButton(T_Window* window, T_Button* button);

/**
 * Removes a button from the window.
 * @param window The window to remove the button from.
 * @param button The button to remove.
 * @note This function also calls `freeButton`, which destroys the button. This function is also called in `freeWindow` for every button in the window.
*/
void removeButton(T_Window* window, T_Button* button);

/**
 * Sets the draw color for the next draw calls.
 * @param window The window to set the draw color to.
 * @param r The red component of the clear color (0-255).
 * @param g The blue component of the clear color (0-255).
 * @param b The green component of the clear color (0-255).
 */
void setDrawColor(T_Window* window, T_Color color);

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
 * Draws some text.
 * @param window The window to draw to.
 * @param font The font to use.
 * @param color The color to use.
 * @param text The text to draw.
 * @param x The x position of the text.
 * @param y The y position of the text.
 * @param sizeRatio A multiplicator for the size of the text.
*/
void drawText(T_Window* window, T_Font* font, T_Color color, const char* text, int x, int y, float sizeRatio);

/**
 * Adds an event function tied to a mouse button press.
 * @param window The window you want the event to be detected on.
 * @param func The function that is called when the event is triggered.
 * @param userData A pointer to the data passed un `func`.
*/
void addButtonDownFunction(T_Window* window, T_ButtonDownFunction func, void* userData);
void addButtonRightDownFunction(T_Window* window, T_ButtonRightDownFunction func, void* userData);

/**
 * Adds an event function tied to a mouse button release.
 * @param window The window you want the event to be detected on.
 * @param func The function that is called when the event is triggered.
 * @param userData A pointer to the data passed un `func`.
*/
void addButtonUpFunction(T_Window* window, T_ButtonUpFunction func, void* userData);

/**
 * Adds an event function tied to a mouse movement.
 * @param window The window you want the event to be detected on.
 * @param func The function that is called when the event is triggered.
 * @param userData A pointer to the data passed un `func`.
*/
void addMouseMovedFunction(T_Window* window, T_MouseMovedFunction func, void* userData);

/**
 * Adds an event function tied to a key press.
 * @param window The window you want the event to be detected on.
 * @param func The function that is called when the event is triggered.
 * @param userData A pointer to the data passed un `func`.
*/
void addKeyDownFunction(T_Window* window, T_KeyDownFunction func, void* userData);

#endif
