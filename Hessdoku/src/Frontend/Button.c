#include <Frontend/Button.h>
#include <stdlib.h>
#include <string.h>

typedef struct T_Button
{
    int x, y; /** The coordiantes of the button */
    int width, height; /** The size of the button */
    char* text;
    T_ButtonFunction function; /** The function pointer that executes the code when the button is pressed */
} T_Button;

T_Button* createButton(int x, int y, int width, int height, const char* text, T_ButtonFunction function)
{
    T_Button* button = (T_Button*)malloc(sizeof(T_Button));

    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    button->function = function;

    button->text = malloc(sizeof(char) * strlen(text));
    strcpy(button->text, text);

    return button;
}

void freeButton(T_Button* button)
{
    free(button->text);
    free(button);
}

void setButtonCoordinates(T_Button* button, int x, int y)
{
    button->x = x;
    button->y = y;
}

void setButtonSize(T_Button* button, int width, int height)
{
    button->width = width;
    button->height = height;
}

void setButtonFunction(T_Button* button, T_ButtonFunction function)
{
    button->function = function;
}

void getButtonCoordinates(T_Button* button, int* x, int* y)
{
    if (x != NULL)
        *x = button->x;
    if (y != NULL)
        *y = button->y;
}

void getButtonSize(T_Button* button, int* width, int* height)
{
    if (width != NULL)
        *width = button->width;
    if (height != NULL)
        *height = button->height;
}

char* getButtonText(T_Button* button)
{
    return button->text;
}

T_ButtonFunction getButtonFunction(T_Button* button)
{
    return button->function;
}
