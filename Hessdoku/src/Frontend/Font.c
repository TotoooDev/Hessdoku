#include <Frontend/Font.h>
#include <Log.h>

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
