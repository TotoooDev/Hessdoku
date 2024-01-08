#include <Game.h>
#include <Frontend/Frontend.h>

int main(int argc, char* argv[])
{
    T_Game* game = createGame(GRID_SIZE, GRID_SIZE);
    T_Frontend* frontend = createFrontend(game);

    freeFrontend(frontend);
    destroyGame(game);

    return 0;
}