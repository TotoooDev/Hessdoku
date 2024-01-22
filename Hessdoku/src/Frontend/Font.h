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

/**
 * Calculates the total size of the text.
 * @param font The font that is used when calculating the size of the text.
 * @param text The text to calculate the size of.
 * @param width A pointer to the emplacement of the width.
 * @param height A pointer to the emplacement of the height.
 * @param sizeRatio The size ratio of the font.
 * @note `width` and `height` can be NULL.
*/
void getTextDimensions(T_Font* font, const char* text, int* width, int* height, float sizeRatio);

#endif
