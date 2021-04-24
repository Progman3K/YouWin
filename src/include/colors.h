#ifndef __H_COLORS_H__
#define __H_COLORS_H__


typedef enum /* : unsigned char */ {

    // Dark colors
    COLOR_NONE,
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_GRAY,

    COLOR_BROWN,            // Doesn't work???
    COLOR_DARKGRAY,         // Doesn't work???

    // Light colors
    COLOR_LIGHTGRAY,        // Doesn't work???
    COLOR_LIGHTBLUE,        // Doesn't work???
    COLOR_LIGHTGREEN,       // Doesn't work???
    COLOR_LIGHTCYAN,        // Doesn't work???
    COLOR_LIGHTRED,         // Doesn't work???
    COLOR_LIGHTMAGENTA,     // Doesn't work???

    COLOR_WHITE = 107,

    COLOR_NUM_COLORS

} COLOR;


#define MAKE_TEXT_COLORREF( c, fg, bg ) MAKELONG( c, MAKEWORD( (BYTE)fg, (BYTE)bg ) )
#define GET_TEXT_COLORREF_FG( c )       LOBYTE( HIWORD( c ) )
#define GET_TEXT_COLORREF_BG( c )       HIBYTE( HIWORD( c ) )
#define GET_TEXT_COLORREF_CHAR( c )     LOWORD( c )


#endif  /* __H_COLORS_H__ */
