#ifndef THEME_H
#define THEME_H

#include <Frontend/Color.h>

typedef enum
{
    THEME_DRACULA
} T_ThemeType;

typedef struct T_Theme 
{
    T_Color backgroudColor;
    T_Color cellColor;
    T_Color gridBorderColor;
    T_Color gridBorderLightColor;
    T_Color selectionColor;
    T_Color buttonColor;
    T_Color textColor;
    T_Color notesColor;
    T_Color validColor;
    T_Color invalidColor;
    T_Color changedColor;

    float notesTransparency;
} T_Theme;

T_Theme getDraculaTheme();

#endif
