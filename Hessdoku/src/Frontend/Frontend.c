#include <Frontend/Frontend.h>
#include <Frontend/Window.h>
#include <stdlib.h>

#define FRONTEND_WINDOW_TITLE "Hessdoku"
#define FRONTEND_WINDOW_WIDTH 800
#define FRONTEND_WINDOW_HEIGHT 600

typedef struct T_Frontend {
    T_Window* window;
    T_Font* font;
    T_Grid grid;
} T_Frontend;

T_Frontend* createFrontend(T_Grid grid)
{
    T_Frontend* frontend = (T_Frontend*)malloc(sizeof(T_Frontend));

    frontend->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    frontend->font = loadFont("OpenSans-Regular.ttf", 16);
    frontend->grid = grid;

    return frontend;
}

void runFrontend(T_Frontend* frontend)
{
    while (isWindowOpen(frontend->window))
    {
        updateWindow(frontend->window);
        clearWindow(frontend->window, 127, 127, 127);

        drawGrid(frontend, 10, 10, 64);

        presentWindow(frontend->window);
    }
}

void freeFrontend(T_Frontend* frontend)
{
    freeWindow(frontend->window);
    free(frontend);
}

void drawGrid(T_Frontend* frontend, int xOffset, int yOffset, int rectSize)
{
    for (unsigned int i = 0; i < getGridSqrtSize(frontend->grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSqrtSize(frontend->grid); ii++)
        {
            setDrawColor(frontend->window, 255, 255, 255);
            drawRect(frontend->window, ii * rectSize + xOffset, i * rectSize + yOffset, rectSize, rectSize);
            
            unsigned int value = getValue(frontend->grid, ii, i);
            if (value == 0)
                continue;
            
            char text[2];
            sprintf(text, "%d", value);
            setDrawColor(frontend->window, 0, 0, 0);
            drawText(frontend->window, frontend->font, (T_Color){ 0, 0, 0 }, text, ii * rectSize + xOffset, i * rectSize + yOffset, 1.0f);
        }
    }

    setDrawColor(frontend->window, 0, 0, 0);
    for (unsigned int i = 0; i < getGridSqrtSize(frontend->grid) + 1; i++)
    {
        drawLine(frontend->window, i * rectSize + xOffset, yOffset, i * rectSize + xOffset, rectSize * getGridSqrtSize(frontend->grid) + yOffset);
        drawLine(frontend->window,  xOffset, i * rectSize + yOffset, rectSize * getGridSqrtSize(frontend->grid) + xOffset, i * rectSize + yOffset);
    }
}
