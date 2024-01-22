#include <Frontend/Button.h>
#include <stdlib.h>
#include <string.h>

typedef struct T_Button
{
    int x, y;
    char* text;

    bool isClicked;
    bool isHovered;

    int border;
    int padding;

    T_ButtonFunction function;
    void* userData;
} T_Button;

T_Button* createButton(int x, int y, const char* text, T_ButtonFunction function, void* userData)
{
    T_Button* button = (T_Button*)malloc(sizeof(T_Button));

    button->x = x;
    button->y = y;

    button->isClicked = false;
    button->isHovered = false;

    button->border = 3;
    button->padding = 3;

    button->function = function;
    button->userData = userData;

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

void setButtonBorder(T_Button* button, int border)
{
    button->border = border;
}

void setButtonPadding(T_Button* button, int padding)
{
    button->padding = padding;
}

void setButtonClicked(T_Button* button, bool toggle)
{
    button->isClicked = toggle;
}

void setButtonHovered(T_Button* button, bool toggle)
{
    button->isHovered = toggle;
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

int getButtonBorder(T_Button* button)
{
    return button->border;
}

int getButtonPadding(T_Button* button)
{
    return button->padding;
}

void getButtonDimensions(T_Button* button, T_Font* font, float sizeRatio, int* width, int* height)
{
    getTextDimensions(font, button->text, width, height, sizeRatio);

    *width += button->border + button->padding;
    *height += button->border + button->padding;
}

char* getButtonText(T_Button* button)
{
    return button->text;
}

bool isButtonClicked(T_Button* button)
{
    return button->isClicked;
}

bool isButtonHovered(T_Button* button)
{
    return button->isHovered;
}

T_ButtonFunction getButtonFunction(T_Button* button)
{
    return button->function;
}

void* getButtonUserData(T_Button* button)
{
    return button->userData;
}
