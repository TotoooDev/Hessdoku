#include <Frontend/Window.h>
#include <Log.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

static unsigned int NumWindows = 0;

typedef struct T_Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isOpen;
} T_Window;

void initSDL()
{
    ASSERT(SDL_Init(SDL_INIT_EVERYTHING) == 0, "Failed to initialize SDL! SDL error: %s", SDL_GetError());
    ASSERT(TTF_Init() == 0, "Failed to initialize SDL_ttf! TTF error: %s", TTF_GetError());
}

void quitSDL()
{
    SDL_Quit();
}

T_Window* createWindow(const char* title, int width, int height)
{
    if (NumWindows == 0)
        initSDL();

    T_Window* window = (T_Window*)malloc(sizeof(T_Window));

    window->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    ASSERT(window->window != NULL, "Failed to create window! SDL error: %s", SDL_GetError());

    window->renderer = SDL_CreateRenderer(
        window->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    ASSERT(window->renderer != NULL, "Failed to create renderer! SDL error: %s", SDL_GetError());

    window->isOpen = true;

    NumWindows++;

    return window;
}

void freeWindow(T_Window* window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);

    NumWindows--;
    if (NumWindows == 0)
        quitSDL();
}

void updateWindow(T_Window* window)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            window->isOpen = false;
    }
}

void clearWindow(T_Window* window, unsigned char r, unsigned char g, unsigned char b)
{
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderClear(window->renderer);
}

void presentWindow(T_Window* window)
{
    SDL_RenderPresent(window->renderer);
}

bool isWindowOpen(T_Window* window)
{
    return window->isOpen;
}

void setDrawColor(T_Window* window, unsigned char r, unsigned char g, unsigned char b)
{
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
}

void drawLine(T_Window* window, int startX, int startY, int endX, int endY)
{
    SDL_RenderDrawLine(window->renderer, startX, startY, endX, endY);
}

void drawRect(T_Window* window, int x, int y, int width, int height)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(window->renderer, &rect);
}

void drawGrid(T_Window* window, T_Grid grid, int xOffset, int yOffset, int rectSize)
{
    for (unsigned int i = 0; i < getGridSqrtSize(grid); i++)
    {
        for (unsigned int ii = 0; ii < getGridSqrtSize(grid); ii++)
        {
            setDrawColor(window, 255, 255, 255);
            drawRect(window, ii * rectSize + xOffset, i * rectSize + yOffset, rectSize, rectSize);
        }
    }

    setDrawColor(window, 0, 0, 0);
    for (unsigned int i = 0; i < getGridSqrtSize(grid) + 1; i++)
    {
        drawLine(window, i * rectSize + xOffset, yOffset, i * rectSize + xOffset, rectSize * getGridSqrtSize(grid) + yOffset);
        drawLine(window,  xOffset, i * rectSize + yOffset, rectSize * getGridSqrtSize(grid) + xOffset, i * rectSize + yOffset);
    }
}
