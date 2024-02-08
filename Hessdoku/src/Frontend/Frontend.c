#include <Frontend/Frontend.h>
#include <Frontend/Config.h>
#include <Frontend/GraphicsGrid.h>
#include <Frontend/FileDialog.h>
#include <Solver.h>
#include <PointingKTuples.h>
#include <Log.h>
#include <stdlib.h>

bool isCheckPressed = false;
bool isValid = false;
const char* FILENAME = "whatHappened.txt";
FILE* output_file;

void openDoc()
{
    output_file = fopen(FILENAME, "w+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "It's time to solve a sudoku !\n\n");
}

void writeDoc(const char* str)
{
    fprintf(output_file, str);
}

void closeDoc()
{
    fclose(output_file);
}

typedef struct T_Frontend
{
    T_Window* window;
    T_Font* font;
    T_GraphicsGrid* grid;
    T_Theme theme;

    bool isRunning;

    bool drawNotes;
} T_Frontend;

T_Frontend* FrontendInstance = NULL;

void createFrontend(T_Grid grid, T_ThemeType themeType)
{
    ASSERT(FrontendInstance == NULL, "A frontend already exists!");

    FrontendInstance = (T_Frontend*)malloc(sizeof(T_Frontend));

    FrontendInstance->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    FrontendInstance->font = loadFont("OpenSans-Regular.ttf", 32);
    FrontendInstance->grid = createGraphicsGrid(grid, 5, 5, 64);
    FrontendInstance->isRunning = true;
    FrontendInstance->drawNotes = false;

    switch (themeType)
    {
    case THEME_DRACULA:
    default:
        FrontendInstance->theme = getDraculaTheme();
        break;
    }
}

void quit(int button, int clicks, void* userData)
{ 
    FrontendInstance->isRunning = false; // cool oneliner
} 

void openGridFile(int button, int clicks, void* userData)
{
    const char* filePath = openFileDialog();
    if (filePath == NULL)
        return;

    freeGrid(getGrid(FrontendInstance->grid));
    setGrid(FrontendInstance->grid, generateGridFromFile(filePath));
}

void showHideNotes(int button, int clicks, void* userData) 
{
    setGraphicsGridDrawNotes(FrontendInstance->grid, getGraphicsGridDrawNotes(FrontendInstance->grid) ^ 1);  // even cooler oneliner
}

void removeSomeNotes(int button, int clicks, void* userData)
{
    writeDoc("\nRemoving some notes...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    removeNotesInGridByZones(grid);
}

void removeNotes1Tuple(int button, int clicks, void* userData)
{
    writeDoc("\nSearching an 1-uplet...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 1, output_file);
}

void removeNotes2Tuple(int button, int clicks, void* userData)
{
    writeDoc("\nSearching a 2-uplet...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 2, output_file);
}

void removeNotes3Tuple(int button, int clicks, void* userData)
{
    writeDoc("\nSearching a 3-uplet...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    kUpletsSolve(grid, 3, output_file);
}

void removeNotes1TupleUntilUnchanged(int button, int clicks, void* userData)
{
    writeDoc("\nSearching all 1-uplets...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged)
        hasChanged = kUpletsSolve(grid, 1, output_file);
}

void removeNotes2TupleUntilUnchanged(int button, int clicks, void* userData)
{
    writeDoc("\nSearching all 2-uplets...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged)
        hasChanged = kUpletsSolve(grid, 2, output_file);
}

void removeNotes3TupleUntilUnchanged(int button, int clicks, void* userData)
{
    writeDoc("\nSearching all 3-uplet...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = true;
    while (hasChanged)
        hasChanged = kUpletsSolve(grid, 3, output_file);
}

void resolveSudokuGrid(int button, int clicks, void* userData)
{
    writeDoc("\nBig solving !...\n\n");
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    bool hasChanged = false;
    bool end = false;

    while (!end) 
    {
        hasChanged = false;

        hasChanged |= removeNotesInGridByZones(grid);

        if (!hasChanged)
        {
            hasChanged |= kUpletsSolve(grid, 1, output_file);

            if (!hasChanged)
            {
                hasChanged |= kUpletsSolve(grid, 2, output_file);

                if (!hasChanged)
                {
                    hasChanged |= kUpletsSolve(grid, 3, output_file);

                    if (!hasChanged) 
                    {
                        end = true; // Only set end to true if no changes occurred after all functions
                    }
                }
            }
        }
    }
}

void buttoncheckValidityOfGrid(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    isCheckPressed = true;

    if (checkValidityOfGrid(grid))
    {
        isValid = true;
    }
    else
    {
        isValid = false;
    }
}

void getWhatHappened(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    //TODO
}

void buttonCheckPointingTuples(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    solvePointingTuples(grid);
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
    addButton(FrontendInstance->window, createButton(600, 450, "Check", buttoncheckValidityOfGrid, FrontendInstance));
    addButton(FrontendInstance->window, createButton(750, 540, "Quit", quit, FrontendInstance));
    addButton(FrontendInstance->window, createButton(400, 610, "Surprise motherfucker", getWhatHappened, FrontendInstance));
    addButton(FrontendInstance->window, createButton(500, 640, "Solve pointing K-tuples", buttonCheckPointingTuples, FrontendInstance));
}

void drawWhatHappen()
{
    drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.textColor, "Click here when you are done solving -------->", 40, 610, 0.5f);
}



void runFrontend()
{
    addButtons();

    openDoc();

    while (FrontendInstance->isRunning && isWindowOpen(FrontendInstance->window))
    {
        updateWindow(FrontendInstance->window, FrontendInstance->font);
        clearWindow(FrontendInstance->window, FrontendInstance->theme.backgroudColor.r, FrontendInstance->theme.backgroudColor.g, FrontendInstance->theme.backgroudColor.b);

        drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.textColor, "No grid loaded...", 40, 270, 1.0f);
        if (isCheckPressed && isValid)
            drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.validColor, "Grid valid !", 600, 490, 1.0f);
        else if (isCheckPressed && !isValid)
            drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.invalidColor, "Grid invalid !", 600, 490, 1.0f);
        drawWhatHappen();
        drawGrid(FrontendInstance, FrontendInstance->grid);

        drawWidgets(FrontendInstance->window, FrontendInstance->font);
        presentWindow(FrontendInstance->window);
    }

    closeDoc();
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

T_Theme getTheme()
{
    return FrontendInstance->theme;
}
