#include <Frontend/GraphicsGrid.h>
#include <Frontend/Frontend.h>
#include <Frontend/Window.h>
#include <Frontend/Color.h>
#include <Frontend/Mouse.h>
#include <Frontend/Keyboard.h>
#include <Log.h>
#include <stdlib.h>

typedef struct T_GraphicsGrid
{
    T_Grid grid;

    int x;
    int y;
    int squareSize;

    int hoveredCellX;
    int hoveredCellY;
    int selectedCellX;
    int selectedCellY;

    bool drawNotes;
} T_GraphicsGrid;

bool isMouseCursorInGraphicsGrid(T_GraphicsGrid* grid, int mouseX, int mouseY, int* cellX, int* cellY)
{
    for (unsigned int i = 0; i < getGridSize(grid->grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSize(grid->grid); ii++)
        {
            int x = ii * grid->squareSize + grid->x;
            int y = i * grid->squareSize + grid->y;   

            if ((mouseX > x && mouseX < x + grid->squareSize) && (mouseY > y && mouseY < y + grid->squareSize))
            {
                if (cellX != NULL)
                    *cellX = ii;
                if (cellY != NULL)
                    *cellY = i;

                return true;
            }
        }
    }

    if (cellX != NULL)
        *cellX = -1;
    if (cellY != NULL)
        *cellY = -1;

    return false;
}

void graphicsGrid_ButtonDownFunction(int button, int clicks, void* userData)
{
    if (button != BUTTON_LEFT || clicks != 2)
        return;

    T_GraphicsGrid* grid = (T_GraphicsGrid*)userData;

    grid->selectedCellX = grid->hoveredCellX;
    grid->selectedCellY = grid->hoveredCellY;
}

void graphicsGrid_MouseMovedFunction(int x, int y, void* userData)
{
    T_GraphicsGrid* grid = (T_GraphicsGrid*)userData;

    int cellX, cellY;
    if (isMouseCursorInGraphicsGrid(grid, x, y, &cellX, &cellY))
    {
        grid->hoveredCellX = cellX;
        grid->hoveredCellY = cellY;
    }
    else
    {
        grid->hoveredCellX = -1;
        grid->hoveredCellY = -1;
    }
}

void graphicsGrid_KeyDownFunction(int key, void* userData)
{
    T_GraphicsGrid* grid = (T_GraphicsGrid*)userData;

    if (grid->selectedCellX == -1 || grid->selectedCellY == -1)
        return;

    switch (key)
    {
    case KEY_0: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 0); break;
    case KEY_1: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 1); break;
    case KEY_2: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 2); break;
    case KEY_3: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 3); break;
    case KEY_4: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 4); break;
    case KEY_5: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 5); break;
    case KEY_6: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 6); break;
    case KEY_7: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 7); break;
    case KEY_8: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 8); break;
    case KEY_9: setValueOfCell(getCell(grid->grid, grid->selectedCellY, grid->selectedCellX), 9); break;
    default: break;
    }
}

T_GraphicsGrid* createGraphicsGrid(T_Grid grid, int x, int y, int squareSize)
{
    T_GraphicsGrid* graphicsGrid = (T_GraphicsGrid*)malloc(sizeof(T_GraphicsGrid));

    graphicsGrid->grid = grid;
    graphicsGrid->x = x;
    graphicsGrid->y = y;
    graphicsGrid->hoveredCellX = -1;
    graphicsGrid->hoveredCellY = -1;
    graphicsGrid->selectedCellX = -1;
    graphicsGrid->selectedCellY = -1;
    graphicsGrid->squareSize = squareSize;
    graphicsGrid->drawNotes = false;

    addButtonDownFunction(getWindow(), graphicsGrid_ButtonDownFunction, graphicsGrid);
    addMouseMovedFunction(getWindow(), graphicsGrid_MouseMovedFunction, graphicsGrid);
    addKeyDownFunction(getWindow(), graphicsGrid_KeyDownFunction, graphicsGrid);

    return graphicsGrid;
}

void freeGraphicsGrid(T_GraphicsGrid* grid)
{
    free(grid);
}

void setGrid(T_GraphicsGrid* graphicsGrid, T_Grid grid)
{
    graphicsGrid->grid = grid;
}

void setGraphicsGridPos(T_GraphicsGrid* grid, int x, int y)
{
    grid->x = x;
    grid->y = y;
}

void setGraphicsGridSquareSize(T_GraphicsGrid* grid, int squareSize)
{
    grid->squareSize = squareSize;
}

void setGraphicsGridDrawNotes(T_GraphicsGrid* grid, bool drawNotes)
{
    grid->drawNotes = drawNotes;
}

void setGraphicsGridSelectedCell(T_GraphicsGrid* grid, int x, int y)
{
    grid->selectedCellX = x;
    grid->selectedCellY = y;
}

T_Grid getGrid(T_GraphicsGrid* grid)
{
    return grid->grid;
}

void getGraphicsGridPos(T_GraphicsGrid* grid, int* x, int* y)
{
    if (x != NULL)
        *x = grid->x;
    if (y != NULL)
        *y = grid->y;
}

int getGraphicsGridSquareSize(T_GraphicsGrid* grid)
{
    return grid->squareSize;
}

bool getGraphicsGridDrawNotes(T_GraphicsGrid* grid)
{
    return grid->drawNotes;
}

void drawNotes(T_Frontend* frontend, T_GraphicsGrid* grid, int cellX, int cellY)
{
    if (!grid->drawNotes)
        return;

    int y = cellY * grid->squareSize + grid->y + grid->squareSize / 9;
    for (unsigned int i = 0; i < getGridSize(grid->grid); i++)
    {
        if (!isNoteInCell(getCell(grid->grid, cellY, cellX), i + 1))
            continue;
        
        int x = cellX * grid->squareSize + grid->x + (i % 3) * 16 + grid->squareSize / 9;
        if (i % 3 == 0 && i != 0)
            y += 16;

        char text[2];
        sprintf(text, "%d", i + 1);
        drawText(getWindow(frontend), getFont(frontend), (T_Color){ 127, 127, 127 }, text, x, y, 0.5f);
    }
}

void drawValue(T_Frontend* frontend, T_GraphicsGrid* grid, int value, int cellX, int cellY)
{
    char text[2];
    sprintf(text, "%d", value);

    int width, height;
    getTextDimensions(getFont(frontend), text, &width, &height, 1.0f);

    int x = cellX * grid->squareSize + grid->x - width / 2 + grid->squareSize / 2;
    int y = cellY * grid->squareSize + grid->y - height / 2 + grid->squareSize / 2;
    drawText(getWindow(frontend), getFont(frontend), (T_Color){ 0, 0, 0 }, text, x, y, 1.0f);
}

void drawGrid(T_Frontend* frontend, T_GraphicsGrid* grid)
{
    for (unsigned int i = 0; i < getGridSize(grid->grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSize(grid->grid); ii++)
        {
            int x = ii * grid->squareSize + grid->x;
            int y = i * grid->squareSize + grid->y;

            if (ii == grid->selectedCellX && i == grid->selectedCellY)
                setDrawColor(getWindow(frontend), 221, 220, 220);
            else
                setDrawColor(getWindow(frontend), 255, 255, 255);
            drawRect(getWindow(frontend), x, y, grid->squareSize, grid->squareSize);
            
            unsigned int value = getValue(grid->grid, i, ii);
            if (value == 0)
                drawNotes(frontend, grid, ii, i);
            else
                drawValue(frontend, grid, value, ii, i);
            
        }
    }

    for (unsigned int i = 0; i < getGridSize(grid->grid) + 1; i++)
    {
        if (i % 3 == 0)
            setDrawColor(getWindow(frontend), 0, 0, 0);
        else
            setDrawColor(getWindow(frontend), 127, 127, 127);

        drawLine(getWindow(frontend), i * grid->squareSize + grid->x, grid->y, i * grid->squareSize + grid->x, grid->squareSize * getGridSize(grid->grid) + grid->y);
        drawLine(getWindow(frontend),  grid->x, i * grid->squareSize + grid->y, grid->squareSize * getGridSize(grid->grid) + grid->x, i * grid->squareSize + grid->y);
    }
}