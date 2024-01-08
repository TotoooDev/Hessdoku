#ifndef FRONTEND_H
#define FRONTEND_H

#include <Game.h>

typedef struct T_Frontend T_Frontend;

T_Frontend* createFrontend(T_Game* game);
void runFrontend(T_Frontend* frontend);
void freeFrontend(T_Frontend* frontend);

#endif
