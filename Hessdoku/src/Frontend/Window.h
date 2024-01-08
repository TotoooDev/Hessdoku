#ifndef WINDOW_H
#define WINDOW_H

typedef struct T_Window T_Window;

T_Window* createWindow(const char* title, int width, int height);
void freeWindow(T_Window* window);

#endif
