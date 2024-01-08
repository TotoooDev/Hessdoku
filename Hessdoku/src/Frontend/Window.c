#include <Frontend/Window.h>
#include <Log.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

static unsigned int NumWindows = 0;

typedef struct Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

void initSDL()
{
    ASSERT(SDL_Init(SDL_INIT_EVERYTHING) > 0, "Failed to initialize SDL! SDL error: %s", SDL_GetError());
}

Window* createWindow(const char* title, int width, int height)
{
    Window* window = (Window*)malloc(sizeof(Window));

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

void freeWindow(Window* window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}
