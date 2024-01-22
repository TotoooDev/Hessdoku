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

T_Frontend* FrontendInstance = NULL;

void createFrontend(T_Grid grid)
{
    ASSERT(FrontendInstance == NULL, "A frontend already exists!");

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

void removeNotes1TupleUntilUnchanged(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged) {
        hasChanged = kUpletsSolve(grid, 1);
    }
}

void removeNotes2TupleUntilUnchanged(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged) {
        hasChanged = kUpletsSolve(grid, 2);
    }
}

void removeNotes3TupleUntilUnchanged(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged) {
        hasChanged = kUpletsSolve(grid, 3);
    }
}

void resolveSudokuGrid(int button, int clicks, void* userData) {
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = false;
    bool end = false;

    while (!end) {
        hasChanged = false;

        hasChanged |= removeNotesInGridByZones(grid);

        if (!hasChanged) {
            hasChanged |= kUpletsSolve(grid, 1);

            if (!hasChanged) {
                hasChanged |= kUpletsSolve(grid, 2);

                if (!hasChanged) {
                    hasChanged |= kUpletsSolve(grid, 3);

                    if (!hasChanged) {
                        end = true; // Only set end to true if no changes occurred after all functions
                    }
                }
            }
        }
    }

}

void addButtons()
{
    addButton(FrontendInstance->window, createButton(600, 50, "Open grid...", openGridFile, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 90, "Show/Hide notes", showHideNotes, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 130, "Clean notes", removeSomeNotes, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 170, "Remove singletons", removeNotes1Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 210, "Remove pairs", removeNotes2Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 250, "Remove triples", removeNotes3Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 290, "Remove singletons until...", removeNotes1TupleUntilUnchanged, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 330, "Remove pairs until...", removeNotes2TupleUntilUnchanged, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 370, "Remove triples until...", removeNotes3TupleUntilUnchanged, FrontendInstance));
    addButton(FrontendInstance->window, createButton(600, 410, "Solve", resolveSudokuGrid, FrontendInstance));
    addButton(FrontendInstance->window, createButton(750, 450, "Quit", quit, FrontendInstance));
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
