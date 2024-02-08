#ifndef THEME_H
#define THEME_H

#include <Frontend/Color.h>

/**
 * An enum to enumerate the different themes.
*/
typedef enum
{
    THEME_DRACULA,
    THEME_NEO_BRUTALISM
} T_ThemeType;

/**
 * A structure containing information about a color theme.
*/
typedef struct T_Theme 
{
    T_Color backgroudColor;
    T_Color cellColor;
    T_Color gridBorderColor;
    T_Color gridBorderLightColor;
    T_Color selectionColor;
    T_Color buttonColor;
    T_Color buttonHoveredColor;
    T_Color buttonClickedColor;
    T_Color buttonOutlineColor;
    T_Color textColor;
    T_Color notesColor;
    T_Color validColor;
    T_Color invalidColor;
    T_Color changedColor;

    float notesTransparency;
} T_Theme;

/**
 * Get the dracula color palette defined at https://draculatheme.com/contribute.
 * @return The dracula theme.
*/
T_Theme getDraculaTheme();

/**
 * Get the custom neo-brutalism color palette.
 * @return The neo-brutalism theme.
*/
T_Theme getNeoBrutalismTheme();

#endif
