#include <Game.h>
#include <Frontend/Frontend.h>

int main(int argc, char* argv[])
{
    T_Game* game = createGame(GRID_SIZE, GRID_SIZE);
    T_Frontend* frontend = createFrontend(game);

    runFrontend(frontend);

    freeFrontend(frontend);
    destroyGame(game);

    return 0;
}