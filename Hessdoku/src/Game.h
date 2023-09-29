#ifndef GAME_H
#define GAME_H

#include <Grid.h>
#include <Solver.h>

/**
 * A structure to represent the game
 *
 * @member grid The grid of the game, usually 9x9 cells
 */

typedef struct Game
{
    T_Grid grid;
} T_Game;

/**
 * Allocates a game structure with its grid.
 *
 * @returns The newly created game
 * @author Toto
 */
T_Game* createGame(int sizeX, int sizeY);

/**
 * Destroys a game structure.
 *
 * @author Toto
 */
void destroyGame(T_Game* game, T_Grid grid);

#endif