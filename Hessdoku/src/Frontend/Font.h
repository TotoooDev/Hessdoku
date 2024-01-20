#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

/**
 * A wrapper around a font.
 */
typedef struct T_Font T_Font;

/**
 * Load a new font.
 * @param filename The file name of the font.
 * @param size The point size of the font.
 * @returns The new font.
 */
T_Font* loadFont(const char* filename, int size);

/**
 * Frees a font.
 * @param font The font to free.
 */
void freeFont(T_Font* font);

void getTextDimensions(T_Font* font, const char* text, int* width, int* height, float sizeRatio);

#endif
