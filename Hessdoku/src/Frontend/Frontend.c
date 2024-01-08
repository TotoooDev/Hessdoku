#include <Frontend/Frontend.h>
#include <Frontend/Window.h>
#include <stdlib.h>

#define FRONTEND_WINDOW_TITLE "Hessdoku"
#define FRONTEND_WINDOW_WIDTH 800
#define FRONTEND_WINDOW_HEIGHT 600

typedef struct T_Frontend {
    T_Window* window;
    T_Game* game;
} T_Frontend;

T_Frontend* createFrontend(T_Game* game)
{
    T_Frontend* frontend = (T_Frontend*)malloc(sizeof(T_Frontend));

    frontend->window = createWindow(FRONTEND_WINDOW_TITLE, FRONTEND_WINDOW_WIDTH, FRONTEND_WINDOW_HEIGHT);
    frontend->game = game;

    return frontend;
}

void runFrontend(T_Frontend* frontend)
{
    while (isWindowOpen(frontend->window))
    {
        updateWindow(frontend->window);
        clearWindow(frontend->window, 127, 127, 127);
        presentWindow(frontend->window);
    }
}

void freeFrontend(T_Frontend* frontend)
{
    freeWindow(frontend->window);
    free(frontend);
}