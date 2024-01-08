#ifndef WINDOW_H
#define WINDOW_H

typedef struct Window Window;

Window* createWindow(const char* title, int width, int height);
void freeWindow(Window* window);

#endif
