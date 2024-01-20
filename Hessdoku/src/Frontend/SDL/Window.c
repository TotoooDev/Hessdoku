#include <Frontend/Config.h>

#ifdef FRONTEND_SDL

#include <Frontend/Window.h>
#include <Frontend/SDL/Font.h>
#include <Log.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

// arbitrary number lol
#define WINDOW_MAX_BUTTONS 128

static unsigned int NumWindows = 0;

typedef struct T_Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isOpen;

    T_Button* buttons[WINDOW_MAX_BUTTONS];
    unsigned int numButtons;
} T_Window;

bool isCursorInButton(int mouseX, int mouseY, T_Button* button, T_Font* font);

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

    for (unsigned int i = 0; i < WINDOW_MAX_BUTTONS; i++)
        window->buttons[i] = NULL;
    window->numButtons = 0;

    NumWindows++;

    return window;
}

void freeWindow(T_Window* window)
{
    for (unsigned int i = 0; i < window->numButtons; i++)
        freeButton(window->buttons[i]);

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);

    NumWindows--;
    if (NumWindows == 0)
        quitSDL();
}

void buttonDown(T_Window* window, T_Font* font, SDL_Event event)
{
    for (unsigned int i = 0; i < window->numButtons; i++)
    {
        T_Button* button = window->buttons[i];
        if (!isCursorInButton(event.button.x, event.button.y, button, font))
            continue;
        setButtonClicked(button, true);
    }
}

void buttonUp(T_Window* window, T_Font* font, SDL_Event event)
{
    for (unsigned int i = 0; i < window->numButtons; i++)
    {
        T_Button* button = window->buttons[i];
        if (isButtonClicked(button) && isCursorInButton(event.button.x, event.button.y, button, font))
        {
            // functional programming hell
            T_ButtonFunction function = getButtonFunction(button);
            if (function != NULL)
                function(event.button.button, event.button.clicks, getButtonUserData(button));
        }
        setButtonClicked(button, false);
    }
}

void updateWindow(T_Window* window, T_Font* font)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            window->isOpen = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            buttonDown(window, font, event);
            break;

        case SDL_MOUSEBUTTONUP:
            buttonUp(window, font, event);
            break;

        default:
            break;
        }
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

void drawButtons(T_Window* window, T_Font* font)
{
    for (unsigned int i = 0; i < window->numButtons; i++) {
        T_Button* button = window->buttons[i];

        int border = 6;
        int padding = 3;
        int x, y, width, height;
        getButtonCoordinates(button, &x, &y);
        getTextDimensions(font, getButtonText(button), &width, &height, 0.5f);

        setDrawColor(window, 60, 60, 60);
        drawRect(window, x - border, y - border, width + border * 2, height + border * 2);

        if (isButtonClicked(button))
            setDrawColor(window, 200, 200, 200);
        else
            setDrawColor(window, 220, 220, 220);

        drawRect(window, x - padding, y - padding, width + padding * 2, height + padding * 2);
        drawText(window, font, (T_Color){ 10, 10, 10 }, getButtonText(window->buttons[i]), x, y, 0.5f);
    }
}

void drawWidgets(T_Window* window, T_Font* font)
{
    drawButtons(window, font);
}

bool isWindowOpen(T_Window* window)
{
    return window->isOpen;
}

void addButton(T_Window* window, T_Button* button)
{
    ASSERT(window->numButtons < WINDOW_MAX_BUTTONS, "Failed to add button! The button array is full.");
    window->buttons[window->numButtons] = button;
    window->numButtons++;
}

void removeButton(T_Window* window, T_Button* button)
{
    int index = -1;
    for (unsigned int i = 0; i < window->numButtons; i++) {
        if (window->buttons[i] == button) {
            index = i;
            break;
        }
    }

    ASSERT(index != -1, "Failed to find button %p in array! It's not in the array.\n", button);
    ASSERT(index < window->numButtons, "Failed to remove button %p! The index was unused.\n", button);

    freeButton(window->buttons[index]);
    
    for (unsigned int i = index; i < window->numButtons; i++) {
        window->buttons[i] = window->buttons[i + 1];
    }
    window->buttons[window->numButtons] = NULL;

    window->numButtons--;
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

void drawText(T_Window* window, T_Font* font, T_Color color, const char* text, int x, int y, float sizeRatio)
{
    SDL_Surface* surface = TTF_RenderText_Blended(getTTF(font), text, (SDL_Color){ color.r, color.g, color.b, 255 });
	ASSERT(surface != NULL, "Failed to create surface! TTF error: %s\n", TTF_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
	
    SDL_Rect rect = { 
        x,
        y,
        (int)((float)surface->w * sizeRatio),
        (int)((float)surface->h * sizeRatio)
    };
    
    SDL_RenderCopy(window->renderer, texture, NULL, &rect);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

bool isCursorInButton(int mouseX, int mouseY, T_Button* button, T_Font* font)
{
    int buttonX, buttonY, buttonWidth, buttonHeight;
    getButtonCoordinates(button, &buttonX, &buttonY);
    getTextDimensions(font, getButtonText(button), &buttonWidth, &buttonHeight, 0.5f);

    return (mouseX > buttonX && mouseX < buttonX + buttonWidth) && (mouseY > buttonY && mouseY < buttonY + buttonHeight);
}

#endif
