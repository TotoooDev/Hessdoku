#include <Frontend/Window.h>
#include <Log.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

static unsigned int NumWindows = 0;

typedef struct T_Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;
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

    NumWindows++;

    return window;
}

void freeWindow(T_Window* window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}
