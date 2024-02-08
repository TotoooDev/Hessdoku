#include <Frontend/Frontend.h>
#include <Frontend/Config.h>
#include <Frontend/GraphicsGrid.h>
#include <Frontend/FileDialog.h>
#include <Frontend/FileDialog.h>
#include <Frontend/Keyboard.h>
#include <Solver.h>
#include <PointingKTuples.h>
#include <Log.h>
#include <stdlib.h>

bool isCheckPressed = false;
bool isValid = true;
const char* FILENAME = "whatHappened.txt";
FILE* output_file;
int** cooErrorValue;

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

void flushDoc()
{
    fflush(output_file);
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

// This one is an easter egg :O
void changeTheme(int key, void* userData)
{
    if (key == KEY_D)
        ((T_Frontend*)userData)->theme = getDraculaTheme();
    if (key == KEY_N)
        ((T_Frontend*)userData)->theme = getNeoBrutalismTheme();
}

void createFrontend(T_Grid grid, T_ThemeType themeType)
{
    ASSERT(FrontendInstance == NULL, "A frontend already exists!");

    FrontendInstance = (T_Frontend*)malloc(sizeof(T_Frontend));

    FrontendInstance->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    FrontendInstance->font = loadFont("OpenSans-Regular.ttf", 32);
    FrontendInstance->grid = createGraphicsGrid(grid, 16, 16, 64);
    FrontendInstance->isRunning = true;
    FrontendInstance->drawNotes = false;

    // Set the theme
    switch (themeType)
    {
    case THEME_NEO_BRUTALISM:
        FrontendInstance->theme = getNeoBrutalismTheme();
        break;

    case THEME_DRACULA:
    default:
        FrontendInstance->theme = getDraculaTheme();
        break;
    }

    addKeyDownFunction(FrontendInstance->window, changeTheme, FrontendInstance);
}

void quit(int button, int clicks, void* userData)
{ 
    FrontendInstance->isRunning = false;
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
    setGraphicsGridDrawNotes(FrontendInstance->grid, getGraphicsGridDrawNotes(FrontendInstance->grid) ^ 1);  // super cool oneliner
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

    // https://www.youtube.com/watch?v=CFRhGnuXG-4
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
                        hasChanged |= solvePointingTuples(grid);

                        if (!hasChanged) 
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

    int errorValue = 0;
    cooErrorValue = malloc(sizeof(int*) * 2);
    for (int i = 0; i < 2; i++)
    {
        int* tempo = malloc(sizeof(int) * 2);
        cooErrorValue[i] = tempo;
    }

    if (checkValidityOfGrid(grid, &errorValue, cooErrorValue))
        isValid = true;
    else
        isValid = false;
}

void getWhatHappened(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    flushDoc();
    openFileInDefaultApp(FILENAME);
}

void buttonCheckPointingTuples(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);
    solvePointingTuples(grid);
}

void buttonCheckPointingTuplesUntil(int button, int clicks, void* userData)
{
    T_Frontend* frontend = (T_Frontend*)userData;
    T_GraphicsGrid* graphicsGrid = frontend->grid;
    T_Grid grid = getGrid(graphicsGrid);

    while (solvePointingTuples(grid));
}

void addButtons()
{
    addButton(FrontendInstance->window, createButton(630, 50, "Open grid...", openGridFile, FrontendInstance));
    addButton(FrontendInstance->window, createButton(750, 50, "Show/Hide notes", showHideNotes, FrontendInstance));
    
    addButton(FrontendInstance->window, createButton(630, 130, "Clean notes", removeSomeNotes, FrontendInstance));
    
    addButton(FrontendInstance->window, createButton(630, 170, "Remove singletons", removeNotes1Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(900, 170, "Remove singletons until...", removeNotes1TupleUntilUnchanged, FrontendInstance));
    
    addButton(FrontendInstance->window, createButton(630, 210, "Remove pairs", removeNotes2Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(900, 210, "Remove pairs until...", removeNotes2TupleUntilUnchanged, FrontendInstance));
    
    addButton(FrontendInstance->window, createButton(630, 250, "Remove triples", removeNotes3Tuple, FrontendInstance));
    addButton(FrontendInstance->window, createButton(900, 250, "Remove triples until...", removeNotes3TupleUntilUnchanged, FrontendInstance));
    
    addButton(FrontendInstance->window, createButton(630, 290, "Remove pointing K-tuples", buttonCheckPointingTuples, FrontendInstance));
    addButton(FrontendInstance->window, createButton(900, 290, "Remove pointing K-tuples until...", buttonCheckPointingTuplesUntil, FrontendInstance));

    addButton(FrontendInstance->window, createButton(630, 370, "Check the grid", buttoncheckValidityOfGrid, FrontendInstance));
    addButton(FrontendInstance->window, createButton(630, 410, "Solve", resolveSudokuGrid, FrontendInstance));

    addButton(FrontendInstance->window, createButton(630, 490, "Open log file...", getWhatHappened, FrontendInstance));

    addButton(FrontendInstance->window, createButton(1120, 570, "Quit", quit, FrontendInstance));
}



void runFrontend()
{
    addButtons();

    openDoc();

    while (FrontendInstance->isRunning && isWindowOpen(FrontendInstance->window))
    {
        // Window stuff
        updateWindow(FrontendInstance->window, FrontendInstance->font);
        clearWindow(FrontendInstance->window, FrontendInstance->theme.backgroudColor.r, FrontendInstance->theme.backgroudColor.g, FrontendInstance->theme.backgroudColor.b);
        
        // Draw the "No grid found" text first so it gets overwritten by all the other draws
        drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.textColor, "No grid loaded...", 60, 270, 1.0f);

        // Draw the validity text
        if (isCheckPressed && isValid)
            drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.validColor, "Grid valid !", 900, 400, 1.0f);
        else if (isCheckPressed && !isValid)
            drawText(FrontendInstance->window, FrontendInstance->font, FrontendInstance->theme.invalidColor, "Grid invalid !", 900, 400, 1.0f);

        drawGrid(FrontendInstance, FrontendInstance->grid, cooErrorValue, isValid);
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
