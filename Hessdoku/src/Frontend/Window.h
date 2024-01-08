#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

typedef struct T_Window T_Window;

T_Window* createWindow(const char* title, int width, int height);
void freeWindow(T_Window* window);
void updateWindow(T_Window* window);
void clearWindow(T_Window* window, unsigned char r, unsigned char g, unsigned char b);
void presentWindow(T_Window* window);
bool isWindowOpen(T_Window* window);

#endif
