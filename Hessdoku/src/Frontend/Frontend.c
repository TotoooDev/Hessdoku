#include <Frontend/Frontend.h>
#include <Frontend/Config.h>
#include <Frontend/GraphicsGrid.h>
#include <Frontend/FileDialog.h>
#include <Solver.h>
#include <Log.h>
#include <stdlib.h>

typedef struct T_Frontend {
    T_Window* window;
    T_Font* font;
    T_GraphicsGrid* grid;

    bool isRunning;

    bool drawNotes;
} T_Frontend;

T_Frontend* createFrontend(T_Grid grid)
{
    T_Frontend* frontend = (T_Frontend*)malloc(sizeof(T_Frontend));

    frontend->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    frontend->font = loadFont("OpenSans-Regular.ttf", 32);
    frontend->grid = createGraphicsGrid(grid, 5, 5, 64);
    frontend->isRunning = true;
    frontend->drawNotes = false;

    return frontend;
}

void quit(int button, int clicks, void* userData) { ((T_Frontend*)userData)->isRunning = false; } // cool oneliner

void openGridFile(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;

    const char* filePath = openFileDialog();
    if (filePath == NULL)
        return;

    freeGrid(getGrid(frontend->grid));
    setGrid(frontend->grid, generateGridFromFile(filePath));
}

void showHideNotes(int button, int clicks, void* userData) { setGraphicsGridDrawNotes(((T_Frontend*)userData)->grid, getGraphicsGridDrawNotes(((T_Frontend*)userData)->grid) ^ 1); } // even cooler oneliner

void removeSomeNotes(int button, int clicks, void* userData) {
    T_Grid* grid = (T_Grid*)userData;
    removeNotesInGridByZones(*grid);
}

void removeNotes1Tuple(int button, int clicks, void* userData) {
    T_Grid* grid = (T_Grid*)userData;
    kUpletsSolve(*grid, 1);
}

void removeNotes2Tuple(int button, int clicks, void* userData) {
    T_Grid* grid = (T_Grid*)userData;
    kUpletsSolve(*grid, 2);
}

void removeNotes3Tuple(int button, int clicks, void* userData) {
    T_Grid* grid = (T_Grid*)userData;
    kUpletsSolve(*grid, 3);
}

// Example for a button that does something
void exampleButton(int button, int clicks, void* userData)
{
    LOG("Example button was clicked!");
    LOG("button: %d, clicks: %d, userData: %p", button, clicks, userData);
    
    T_Frontend* frontend = (T_Frontend*)userData;
    // do stuff...
}

void addButtons(T_Frontend* frontend)
{
    addButton(frontend->window, createButton(600, 50, "Open grid...", openGridFile, frontend));
    addButton(frontend->window, createButton(600, 100, "Show/Hide notes", showHideNotes, frontend));
    addButton(frontend->window, createButton(600, 150, "Remove some notes", removeSomeNotes, &(frontend->grid)));
    addButton(frontend->window, createButton(600, 200, "Remove singletons", removeNotes1Tuple, &(frontend->grid)));
    addButton(frontend->window, createButton(600, 250, "Remove pairs", removeNotes2Tuple, &(frontend->grid)));
    addButton(frontend->window, createButton(600, 300, "Remove triples", removeNotes3Tuple, &(frontend->grid)));
    addButton(frontend->window, createButton(600, 350, "Quit", quit, frontend));
}

void runFrontend(T_Frontend* frontend)
{
    addButtons(frontend);

    while (frontend->isRunning && isWindowOpen(frontend->window))
    {
        updateWindow(frontend->window, frontend->font);
        clearWindow(frontend->window, 127, 127, 127);

        drawGrid(frontend, frontend->grid);

        drawWidgets(frontend->window, frontend->font);
        presentWindow(frontend->window);
    }
}

void freeFrontend(T_Frontend* frontend)
{
    freeWindow(frontend->window);
    free(frontend);
}

T_Window* getWindow(T_Frontend* frontend)
{
    return frontend->window;
}

T_Font* getFont(T_Frontend* frontend)
{
    return frontend->font;
}
