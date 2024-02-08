#include <Frontend/Theme.h>

T_Theme getDraculaTheme()
{
    // From https://draculatheme.com/contribute

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

T_Theme getNeoBrutalismTheme()
{
    T_Theme theme;

    theme.backgroudColor       = (T_Color){ 128, 128, 128 };
    theme.cellColor            = (T_Color){ 255, 255, 255 };
    theme.gridBorderColor      = (T_Color){   0,   0,   0 };
    theme.gridBorderLightColor = (T_Color){ 127, 127, 127 };
    theme.selectionColor       = (T_Color){ 200, 200, 200 };
    theme.buttonColor          = (T_Color){ 220, 220, 220 };
    theme.buttonHoveredColor   = (T_Color){ 240, 240, 240 };
    theme.buttonClickedColor   = (T_Color){ 200, 200, 200 };
    theme.buttonOutlineColor   = (T_Color){  60,  60,  60 };
    theme.textColor            = (T_Color){   0,   0,   0 };
    theme.validColor           = (T_Color){   0, 255,   0 };
    theme.invalidColor         = (T_Color){ 255,   0,   0 };
    theme.changedColor         = (T_Color){   0,   0, 255 };

    theme.notesTransparency = 0.7f;

    theme.notesColor = (T_Color){
        theme.textColor.r * theme.notesTransparency,
        theme.textColor.g * theme.notesTransparency,
        theme.textColor.b * theme.notesTransparency
    };

    return theme;
}
