#include <Frontend/Frontend.h>
#include <Frontend/Window.h>
#include <Frontend/Config.h>
#include <Solver.h>
#include <Log.h>
#include <stdlib.h>

typedef struct T_Frontend {
    T_Window* window;
    T_Font* font;
    T_Grid grid;

    bool isRunning;

    bool drawNotes;
} T_Frontend;

T_Frontend* createFrontend(T_Grid grid)
{
    T_Frontend* frontend = (T_Frontend*)malloc(sizeof(T_Frontend));

    frontend->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    frontend->font = loadFont("OpenSans-Regular.ttf", 32);
    frontend->grid = grid;
    frontend->isRunning = true;
    frontend->drawNotes = true;

    return frontend;
}

void quit(int, int, void* userData) { ((T_Frontend*)userData)->isRunning = false; } // cool oneliner

void showHideNotes(int button, int clicks, void* userData)
{
    ((T_Frontend*)userData)->drawNotes ^= 1;
}

void removeSomeNotes(int, int, void* userData) {
    T_Grid* grid = (T_Grid*)userData;
    removeNotesInGridByZones(*grid);
}

// Example for a button that does something
void exampleButton(int button, int clicks, void* userData)
{
    LOG("Example button was clicked!");
    LOG("button: %d, clicks: %d, userData: %p", button, clicks, userData);
    
    T_Frontend* frontend = (T_Frontend*)userData;
    // do stuff...
}

void runFrontend(T_Frontend* frontend)
{
    // small button example
    addButton(frontend->window, createButton(600, 50, "Quit", quit, frontend));
    addButton(frontend->window, createButton(600, 100, "Show/Hide notes", showHideNotes, frontend));
    addButton(frontend->window, createButton(600, 150, "Remove some notes", removeSomeNotes, &frontend->grid));
    addButton(frontend->window, createButton(600, 200, "Example", exampleButton, frontend));
    
    while (frontend->isRunning && isWindowOpen(frontend->window))
    {
        updateWindow(frontend->window, frontend->font);
        clearWindow(frontend->window, 127, 127, 127);

        drawGrid(frontend, 10, 10, 64);

        drawWidgets(frontend->window, frontend->font);
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
    if (!frontend->drawNotes)
        return;

    int y = cellY * rectSize + yOffset + rectSize / 9;
    for (unsigned int i = 0; i < getGridSize(frontend->grid); i++)
    {
        if (!isNoteInCell(getCell(frontend->grid, cellY, cellX), i + 1))
            continue;
        
        int x = cellX * rectSize + xOffset + (i % 3) * 16 + rectSize / 9;
        if (i % 3 == 0 && i != 0)
            y += 16;

        char text[2];
        sprintf(text, "%d", i + 1);
        drawText(frontend->window, frontend->font, (T_Color){ 127, 127, 127 }, text, x, y, 0.5f);
    }
}

void drawValue(T_Frontend* frontend, int xOffset, int yOffset, int rectSize, int value, unsigned int cellX, unsigned int cellY)
{
    char text[2];
    sprintf(text, "%d", value);

    int width, height;
    getTextDimensions(frontend->font, text, &width, &height, 1.0f);

    int x = cellX * rectSize + xOffset - width / 2 + rectSize / 2;
    int y = cellY * rectSize + yOffset - height / 2 + rectSize / 2;
    drawText(frontend->window, frontend->font, (T_Color){ 0, 0, 0 }, text, x, y, 1.0f);
}

void drawGrid(T_Frontend* frontend, int xOffset, int yOffset, int rectSize)
{
    for (unsigned int i = 0; i < getGridSize(frontend->grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSize(frontend->grid); ii++)
        {
            int x = ii * rectSize + xOffset;
            int y = i * rectSize + yOffset;
            setDrawColor(frontend->window, 255, 255, 255);
            drawRect(frontend->window, x, y, rectSize, rectSize);
            
            unsigned int value = getValue(frontend->grid, i, ii);
            if (value == 0)
                drawNotes(frontend, xOffset, yOffset, rectSize, ii, i);
            else
                drawValue(frontend, xOffset, yOffset, rectSize, value, ii, i);
            
        }
    }

    for (unsigned int i = 0; i < getGridSize(frontend->grid) + 1; i++)
    {
        if (i % 3 == 0)
            setDrawColor(frontend->window, 0, 0, 0);
        else
            setDrawColor(frontend->window, 127, 127, 127);

        drawLine(frontend->window, i * rectSize + xOffset, yOffset, i * rectSize + xOffset, rectSize * getGridSize(frontend->grid) + yOffset);
        drawLine(frontend->window,  xOffset, i * rectSize + yOffset, rectSize * getGridSize(frontend->grid) + xOffset, i * rectSize + yOffset);
    }
}
