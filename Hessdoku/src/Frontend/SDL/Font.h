#ifndef SDL_FONT_H
#define SDL_FONT_H

#include <Frontend/Font.h>
#include <SDL2/SDL_ttf.h>

/**
 * Returns the SDL_ttf font handler.
 * @param font The font to get the handler from.
 * @returns The handler of the font.
*/
TTF_Font* getTTF(T_Font* font);

#endif
