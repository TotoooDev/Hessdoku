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

void getTextDimensions(T_Font* font, const char* text, int* width, int* height)
{
    int textWidth = 0;
    int textHeight = 0;
    for (unsigned int i = 0; i < strlen(text); i++)
    {
        int minY, maxY, advance;
        TTF_GlyphMetrics32(font->font, text[i], NULL, NULL, &minY, &maxY, &advance);
        int charHeight = maxY - minY;

        textWidth += advance;
        textHeight = charHeight > textHeight ? charHeight : textHeight;
    }

    *width = textWidth;
    *height = textHeight;
}

#endif
