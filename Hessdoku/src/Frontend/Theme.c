#include <Frontend/Theme.h>

T_Theme getDraculaTheme()
{
    T_Theme theme;

    theme.backgroudColor       = (T_Color){  40,  42,  54 };
    theme.cellColor            = (T_Color){  68,  71,  90 };
    theme.gridBorderColor      = (T_Color){ 248, 248, 242 };
    theme.gridBorderLightColor = (T_Color){ 255, 121, 198 };
    theme.selectionColor       = (T_Color){  98, 114, 164 };
    theme.buttonColor          = (T_Color){  98, 114, 164 };
    theme.buttonHoveredColor   = (T_Color){  68,  71,  90 };
    theme.buttonClickedColor   = (T_Color){  98, 114, 164 };
    theme.buttonOutlineColor   = (T_Color){  98, 114, 164 };
    theme.textColor            = (T_Color){ 248, 248, 242 };
    theme.validColor           = (T_Color){  80, 250, 123 };
    theme.invalidColor         = (T_Color){ 255,  85,  85 };
    theme.changedColor         = (T_Color){ 189, 147, 249 };

    theme.notesTransparency = 0.7f;

    theme.notesColor = (T_Color){
        theme.textColor.r * theme.notesTransparency,
        theme.textColor.g * theme.notesTransparency,
        theme.textColor.b * theme.notesTransparency
    };

    return theme;
}
