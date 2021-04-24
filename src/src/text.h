#ifndef __H_TEXT_H__
#define __H_TEXT_H__


#include <termios.h>
#include <signal.h>

#include <colors.h>

#include "KeyMouse.h"


#define AVG_CHARACTER_WIDTH     1
#define AVG_CHARACTER_HEIGHT    1


#define COLORREF_LIGHTBLUE           (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_LIGHTBLUE, COLOR_LIGHTBLUE )
#define COLORREF_COLOR_BLUE          (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_BLUE,      COLOR_BLUE      )
#define COLORREF_COLOR_YELLOW        (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_YELLOW,    COLOR_YELLOW    )
#define COLORREF_COLOR_BLACK         (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_BLACK,     COLOR_BLACK     )
#define COLORREF_COLOR_LIGHTGRAY     (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_LIGHTGRAY, COLOR_LIGHTGRAY )
#define COLORREF_COLOR_WHITE         (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_WHITE,     COLOR_WHITE     )
#define COLORREF_COLOR_GRAY          (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_GRAY,      COLOR_GRAY      )
#define COLORREF_COLOR_NONE          (COLORREF)MAKE_TEXT_COLORREF( ' ', COLOR_NONE,      COLOR_NONE      )


int TerminalInit( void );
void TerminalCleanup( void );


/*
 *  Used to type a character to the display.
 */
void gotoxy( unsigned uX, unsigned uY );
POINT getxy( void );


void underline_on( void );
void underline_off( void );


#define StartPoints()
#define EndPoints()
#define PostRefresh()
#define RasterUpdate()


#endif /* __H_TEXT_H__ */
