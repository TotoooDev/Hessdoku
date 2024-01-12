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

void drawNotes(T_Frontend* frontend, int xOffset, int yOffset, int rectSize, unsigned int cellX, unsigned int cellY)
{
    int y = cellY * rectSize + yOffset;
    for (unsigned int i = 0; i < getGridSqrtSize(frontend->grid); i++)
    {
        if (!hasNote(getCell(frontend->grid, cellX, cellY), i))
            continue;
        
        int x = cellX * rectSize + xOffset + (i % 3) * 16;
        if (i % 3 == 0 && i != 0)
            y += 16;

        char text[2];
        sprintf(text, "%d", i + 1);
        setDrawColor(frontend->window, 0, 0, 0);
        drawText(frontend->window, frontend->font, (T_Color){ 0, 0, 0 }, text, x, y, 1.0f);
    }
}

void drawValue(T_Frontend* frontend, int xOffset, int yOffset, int rectSize, int value, unsigned int cellX, unsigned int cellY)
{
    int x = cellX * rectSize + xOffset;
    int y = cellY * rectSize + yOffset;
    char text[2];
    sprintf(text, "%d", value);
    setDrawColor(frontend->window, 0, 0, 0);
    drawText(frontend->window, frontend->font, (T_Color){ 0, 0, 0 }, text, x, y, 2.0f);
}

void drawGrid(T_Frontend* frontend, int xOffset, int yOffset, int rectSize)
{
    for (unsigned int i = 0; i < getGridSqrtSize(frontend->grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSqrtSize(frontend->grid); ii++)
        {
            int x = ii * rectSize + xOffset;
            int y = i * rectSize + yOffset;
            setDrawColor(frontend->window, 255, 255, 255);
            drawRect(frontend->window, x, y, rectSize, rectSize);
            
            unsigned int value = getValue(frontend->grid, ii, i);
            if (value == 0)
                drawNotes(frontend, xOffset, yOffset, rectSize, ii, i);
            else
                drawValue(frontend, xOffset, yOffset, rectSize, value, ii, i);
            
        }
    }

    setDrawColor(frontend->window, 0, 0, 0);
    for (unsigned int i = 0; i < getGridSqrtSize(frontend->grid) + 1; i++)
    {
        drawLine(frontend->window, i * rectSize + xOffset, yOffset, i * rectSize + xOffset, rectSize * getGridSqrtSize(frontend->grid) + yOffset);
        drawLine(frontend->window,  xOffset, i * rectSize + yOffset, rectSize * getGridSqrtSize(frontend->grid) + xOffset, i * rectSize + yOffset);
    }
}
