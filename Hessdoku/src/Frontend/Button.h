#ifndef BUTTON_H
#define BUTTON_H

#include <Frontend/Font.h>
#include <stdbool.h>

/**
 * A function pointer type for the function called when a button is pressed.
 * @param button The button that is pressed
 * @param clicks 1 for single click, 2 for double click, ...
 * @param userData A pointer to the button's user data. It is used to pass any arbitrary data to the function.
 */
typedef void(*T_ButtonFunction)(int button, int clicks, void* userData);

/**
 * A structure that represents a button.
 */
typedef struct T_Button T_Button;

/**
 * Creates a new button.
 * @param x The x coordinate of the new button.
 * @param y The y coordinate of the new button.
 * @param text The text displayed in the button.
 * @param function The function to call when the button is pressed.
 * @param userData A pointer to any data structure that is passed in the button's function. You can use it to pass any data in `function`.
 * @note If `function` is NULL, then clicking the button won't do anything. `userData` can be NULL.
 */
T_Button* createButton(int x, int y, const char* text, T_ButtonFunction function, void* userData);

/**
 * Destroys a button.
 * @param button The button to destroy.
 * @note You need to remove the button from the window or your app will probably crash.
 */
void freeButton(T_Button* button);

/**
 * Moves a button to a new position.
 * @param button The button to move.
 * @param x The new x coordinate.
 * @param y The new y coordinate.
 */
void setButtonCoordinates(T_Button* button, int x, int y);

/**
 * Sets the size of the outer border of the button.
 * @param button The button to modify.
 * @param border The new border.
*/
void setButtonBorder(T_Button* button, int border);

/**
 * Sets the size of the inner padding of the button.
 * @param button The button to modify.
 * @param padding The new padding.
*/
void setButtonPadding(T_Button* button, int padding);

/**
 * Sets whether the button is being clicked or not.
 * @param button The button to modify.
 * @param toggle `true` if the button is currently clicked, `false` otherwise.
*/
void setButtonClicked(T_Button* button, bool toggle);

/**
 * Sets whether the button is being hobered by the mouse or not.
 * @param button The button to modify.
 * @param toggle `true` if the button is currently hovered, `false` otherwise.
*/
void setButtonHovered(T_Button* button, bool toggle);

/**
 * Sets the function to call when the button is pressed.
 * @param button The button to modify.
 * @param function The new function.
 * @note If `function` is NULL, then clicking the button won't do anything.
 */
void setButtonFunction(T_Button* button, T_ButtonFunction function);

/**
 * Puts a button's coordinates into `x` and `y`.
 * @param button The button to get the coordinates from.
 * @param x A pointer to a variable that will contain the x coordinate.
 * @param y A pointer to a variable that will contain the y coordinate.
 * @note `x` and `y` can be NULL.
 */
void getButtonCoordinates(T_Button* button, int* x, int* y);

/**
 * Returns the button's inner padding.
 * @param button The button in question.
 * @returns The inner padding in question.
*/
int getButtonBorder(T_Button* button);

/**
 * Returns the button's outer border.
 * @param button The button in question.
 * @returns The outer border in question.
*/
int getButtonPadding(T_Button* button);

/**
 * Calculates the total size of the button, including padding and border.
 * @param button The button to get the size of.
 * @param font The font that is used when calculating the size of the button.
 * @param sizeRatio The size ratio of the font.
 * @param width A pointer to the emplacement of the width.
 * @param height A pointer to the emplacement of the height.
 * @note `width` and `height` can be NULL.
*/
void getButtonDimensions(T_Button* button, T_Font* font, float sizeRatio, int* width, int* height);

/**
 * Returns the text contained inside a button.
 * @param button The button to get the text of.
 * @returns The text of the button.
 */
char* getButtonText(T_Button* button);

/**
 * Returns whether or not the button is currently clicked.
 * @param button The button in question.
 * @returns `true` if the button is currently clicked, `false` otherwise.
*/
bool isButtonClicked(T_Button* button);

/**
 * Returns whether or not the button is currently hovered by the mouse.
 * @param button The button in question.
 * @returns `true` if the button is currently hovered, `false` otherwise.
*/
bool isButtonHovered(T_Button* button);

/**
 * Returns a button's function.
 * @param button The button to get the function from.
 * @return A function pointer to the function called when the button is pressed.
 */
T_ButtonFunction getButtonFunction(T_Button* button);

/**
 * Returns the user data of the button.
 * @param button The button to get the user data of.
 * @return The user data of the button.
 */
void* getButtonUserData(T_Button* button);

#endif
