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

T_Frontend* FrontendInstance;

void createFrontend(T_Grid grid)
{
    FrontendInstance = (T_Frontend*)malloc(sizeof(T_Frontend));

    FrontendInstance->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    FrontendInstance->font = loadFont("OpenSans-Regular.ttf", 32);
    FrontendInstance->grid = createGraphicsGrid(grid, 5, 5, 64);
    FrontendInstance->isRunning = true;
    FrontendInstance->drawNotes = false;
}

void quit(int button, int clicks, void* userData) { FrontendInstance->isRunning = false; } // cool oneliner

void openGridFile(int button, int clicks, void* userData)
{
    const char* filePath = openFileDialog();
    if (filePath == NULL)
        return;

    freeGrid(getGrid(FrontendInstance->grid));
    setGrid(FrontendInstance->grid, generateGridFromFile(filePath));
}

void showHideNotes(int button, int clicks, void* userData) { setGraphicsGridDrawNotes(FrontendInstance->grid, getGraphicsGridDrawNotes(FrontendInstance->grid) ^ 1); } // even cooler oneliner

void removeSomeNotes(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    removeNotesInGridByZones(grid);
}

void removeNotes1Tuple(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 1);
}

void removeNotes2Tuple(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 2);
}

void removeNotes3Tuple(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 3);
}

void addButtons()
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
    addButton(frontend->window, createButton(600, 150, "Remove some notes", removeSomeNotes, frontend));
    addButton(frontend->window, createButton(600, 200, "Remove singletons", removeNotes1Tuple, frontend));
    addButton(frontend->window, createButton(600, 250, "Remove pairs", removeNotes2Tuple, frontend));
    addButton(frontend->window, createButton(600, 300, "Remove triples", removeNotes3Tuple, frontend));
    addButton(frontend->window, createButton(600, 350, "Quit", quit, frontend));
}

void runFrontend()
{
    addButtons();

    while (FrontendInstance->isRunning && isWindowOpen(FrontendInstance->window))
    {
        updateWindow(FrontendInstance->window, FrontendInstance->font);
        clearWindow(FrontendInstance->window, 127, 127, 127);

        drawGrid(FrontendInstance, FrontendInstance->grid);

        drawWidgets(FrontendInstance->window, FrontendInstance->font);
        presentWindow(FrontendInstance->window);
    }
}

void freeFrontend()
{
    freeWindow(FrontendInstance->window);
    free(FrontendInstance);
}

T_Window* getWindow()
{
    return FrontendInstance->window;
}

T_Font* getFont()
{
    return FrontendInstance->font;
}
