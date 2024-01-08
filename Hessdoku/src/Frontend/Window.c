#include <Frontend/Window.h>
#include <Log.h>
#include <SDL2/SDL.h>
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
    ASSERT(SDL_Init(SDL_INIT_EVERYTHING) > 0, "Failed to initialize SDL! SDL error: %s", SDL_GetError());
}

T_Window* createWindow(const char* title, int width, int height)
{
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
