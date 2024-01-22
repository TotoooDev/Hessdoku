#include <Frontend/GraphicsGrid.h>
#include <Frontend/Color.h>

void drawNotes(T_Frontend* frontend, int xOffset, int yOffset, int rectSize, unsigned int cellX, unsigned int cellY)
{
    if (!getDrawNotes(frontend))
        return;

    int y = cellY * rectSize + yOffset + rectSize / 9;
    for (unsigned int i = 0; i < getGridSize(getGrid(frontend)); i++)
    {
        if (!isNoteInCell(getCell(getGrid(frontend), cellY, cellX), i + 1))
            continue;
        
        int x = cellX * rectSize + xOffset + (i % 3) * 16 + rectSize / 9;
        if (i % 3 == 0 && i != 0)
            y += 16;

        char text[2];
        sprintf(text, "%d", i + 1);
        drawText(getWindow(frontend), getFont(frontend), (T_Color){ 127, 127, 127 }, text, x, y, 0.5f);
    }
}

void drawValue(T_Frontend* frontend, int xOffset, int yOffset, int rectSize, int value, unsigned int cellX, unsigned int cellY)
{
    char text[2];
    sprintf(text, "%d", value);

    int width, height;
    getTextDimensions(getFont(frontend), text, &width, &height, 1.0f);

    int x = cellX * rectSize + xOffset - width / 2 + rectSize / 2;
    int y = cellY * rectSize + yOffset - height / 2 + rectSize / 2;
    drawText(getWindow(frontend), getFont(frontend), (T_Color){ 0, 0, 0 }, text, x, y, 1.0f);
}

void drawGrid(T_Frontend* frontend, int xOffset, int yOffset, int rectSize)
{
    for (unsigned int i = 0; i < getGridSize(getGrid(frontend)); i++)
    {
        for (unsigned int ii = 0; ii < getGridSize(getGrid(frontend)); ii++)
        {
            int x = ii * rectSize + xOffset;
            int y = i * rectSize + yOffset;
            setDrawColor(getWindow(frontend), 255, 255, 255);
            drawRect(getWindow(frontend), x, y, rectSize, rectSize);
            
            unsigned int value = getValue(getGrid(frontend), i, ii);
            if (value == 0)
                drawNotes(frontend, xOffset, yOffset, rectSize, ii, i);
            else
                drawValue(frontend, xOffset, yOffset, rectSize, value, ii, i);
            
        }
    }

    for (unsigned int i = 0; i < getGridSize(getGrid(frontend)) + 1; i++)
    {
        if (i % 3 == 0)
            setDrawColor(getWindow(frontend), 0, 0, 0);
        else
            setDrawColor(getWindow(frontend), 127, 127, 127);

        drawLine(getWindow(frontend), i * rectSize + xOffset, yOffset, i * rectSize + xOffset, rectSize * getGridSize(getGrid(frontend)) + yOffset);
        drawLine(getWindow(frontend),  xOffset, i * rectSize + yOffset, rectSize * getGridSize(getGrid(frontend)) + xOffset, i * rectSize + yOffset);
    }
}