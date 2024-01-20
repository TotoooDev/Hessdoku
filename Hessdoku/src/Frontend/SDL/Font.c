#include <Frontend/Config.h>

#ifdef FRONTEND_SDL

#include <Frontend/Font.h>
#include <Log.h>
#include <string.h>

typedef struct T_Font 
{
    TTF_Font* font;
}
T_Font;

T_Font* loadFont(const char* filename, int size)
{
    T_Font* font = (T_Font*)malloc(sizeof(T_Font));

    font->font = TTF_OpenFont(filename, size);
    ASSERT(font->font != NULL, "Failed to load font %s! TTF error: %s", filename, TTF_GetError());
    
    return font;
}

void freeFont(T_Font* font)
{
    TTF_CloseFont(font->font);
    free(font);
}

TTF_Font* getTTF(T_Font* font)
{
    return font->font;
}

void getTextDimensions(T_Font* font, const char* text, int* width, int* height, float sizeRatio)
{
    int textWidth = 0;
    int textHeight = 0;
    TTF_SizeUTF8(font->font, text, &textWidth, &textHeight);
    *width = textWidth * sizeRatio;
    *height = textHeight * sizeRatio;
}

#endif
