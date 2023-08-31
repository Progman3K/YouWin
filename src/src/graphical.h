

#ifndef YW_H_GRAPHICAL_H
#define YW_H_GRAPHICAL_H


#include <windows.h>
#include "eventq.h"


#if ! defined(  YOU_WIN_TXT )
#define AVG_CHARACTER_WIDTH     8
#define AVG_CHARACTER_HEIGHT    16


#define COLORREF_COLOR_BLUE          RGB(  58, 110, 165 )
#define COLORREF_COLOR_WHITE         RGB( 255, 255, 255 )
#define COLORREF_COLOR_GRAY          RGB( 212, 208, 200 )
#endif


#if 0
#define COLORREF_LIGHTBLUE           RGB(   0, 255, 255 )
#define COLORREF_COLOR_YELLOW        RGB( 255, 255,   0 )
#define COLORREF_COLOR_BLACK         RGB(   0,   0,   0 )
#define COLORREF_COLOR_LIGHTGRAY     RGB( 153, 153, 153 )
#define COLORREF_COLOR_RED           RGB( 255,   0,   0 )
#define COLORREF_COLOR_GREEN         RGB( 0,   255,   0 )
#define COLORREF_COLOR_COLOR_MAGENTA RGB( 255,   0, 255 )
#define COLORREF_COLOR_CYAN          RGB(   0, 127, 127 )
#define COLORREF_COLOR_DARKGRAY      RGB(  51,  51,  51 )
#define COLORREF_COLOR_BROWN         RGB( 130, 127,   0 )
#define COLORREF_COLOR_LIGHTGREEN    RGB( 127, 255, 127 )
#define COLORREF_COLOR_LIGHTCYAN     RGB( 127, 255, 255 )
#define COLORREF_COLOR_LIGHTRED      RGB( 255, 127, 127 )
#define COLORREF_COLOR_LIGHTMAGENTA  RGB( 255, 127, 255 )
#define COLORREF_COLOR_NONE          RGB( 255, 255, 255 )
#endif


namespace ywDisplay {

    int Init( int cx, int cy, EventQ & Q, int argc, char * argv[], LPARAM lParam );

    void Destroy( void );

    void drawscreen( void );

}




#endif /* YW_H_GRAPHICAL_H */
