

#if defined( YOU_WIN_TXT )


#include "ywin.h"
#include "console_input.h"


#ifndef __APPLE_CC__
__thread
#endif
POINT _pt;


static struct sigaction sa;


KeyMouse    Input( &g.Q, fileno( stdin ) );



/*
         ESC[#;#;....;#m                Set display attributes where # is
                                            0 for normal display
                                            1 for bold on
                                            4 underline (mono only)
                                            5 blink on
                                            7 reverse video on
                                            8 nondisplayed (invisible)

                                            40 black background
                                            41 red background
                                            42 green background
                                            43 yellow background
                                            44 blue background
                                            45 magenta background
                                            46 cyan background
                                            47 white background

*/

// Establish mapping from our API to the ANSI API.
static void MapToANSI( COLOR_PAIR cp ) {

    unsigned    iAttr1;
    unsigned    iAttr2;
    unsigned    uMode = 3;

    // Foreground 
    switch( cp.fg ) {

        case COLOR_BLACK:
            iAttr1 = 30; break;

        case COLOR_RED:
            iAttr1 = 31; break;

        case COLOR_GREEN:
            iAttr1 = 32; break;

        case COLOR_YELLOW:
            iAttr1 = 33; break;

        case COLOR_BLUE:
            iAttr1 = 34; break;

        case COLOR_MAGENTA:
            iAttr1 = 35; break;

        case COLOR_CYAN:
            iAttr1 = 36; break;

        case COLOR_LIGHTGRAY:
        case COLOR_GRAY:
            iAttr1 = 37; break;

        case COLOR_WHITE:
            iAttr1 = 107; break;

        case COLOR_BROWN:
            iAttr1 = 33; break;

        case COLOR_DARKGRAY:
            iAttr1 = 90; break;

        case COLOR_LIGHTBLUE:
            iAttr1 = 94; break;

        case COLOR_LIGHTGREEN:
            iAttr1 = 92; break;

        case COLOR_LIGHTCYAN:
            iAttr1 = 96; break;

        case COLOR_LIGHTRED:
            iAttr1 = 91; break;

        case COLOR_LIGHTMAGENTA:
            iAttr1 = 95; break;

        default:

            iAttr1 = 30;    // Black text

    }

    // Background
    switch( cp.bg ) {

        case COLOR_BLACK:
            iAttr2 = 40; break;

        case COLOR_RED:
            iAttr2 = 41; break;

        case COLOR_GREEN:
            iAttr2 = 42; break;

        case COLOR_YELLOW:
            iAttr2 = 93; break;

        case COLOR_BLUE:
            iAttr2 = 44; break;

        case COLOR_MAGENTA:
            iAttr2 = 45; break;

        case COLOR_CYAN:
            iAttr2 = 46; break;

        case COLOR_GRAY:
            iAttr2 = 47; break;

        case COLOR_WHITE:
            iAttr2 = 107; break;

        case COLOR_BROWN:
            iAttr2 = 43; break;

        case COLOR_LIGHTGRAY:
        case COLOR_DARKGRAY:
        case COLOR_LIGHTBLUE:
        case COLOR_LIGHTGREEN:
        case COLOR_LIGHTCYAN:
        case COLOR_LIGHTRED:
        case COLOR_LIGHTMAGENTA:

        default:

            iAttr2 = 0;

    }

    char    szTmp[128];
    sprintf( szTmp, "\x1B[%u;%u;%um", uMode, iAttr1, iAttr2 );

    g.pTerminal( g.lClientData, szTmp, strlen( szTmp ) );

}


static int Terminal( intptr_t lParam, const char * pszString, int iLen ) {

    if ( 0 >= iLen ) {

        return iLen;

    }

    int iRet = write( fileno( stdout ), pszString, iLen );

    return iRet;

}


static void SignalHandler( int sig ) {

    struct winsize ws;

    DBG_MSG( DBG_CONSOLE, TEXT( "Signal %d received" ), sig );

    switch( sig ) {

        case SIGWINCH:

            if ( ioctl( STDIN_FILENO, TIOCGWINSZ, &ws ) == -1 ) {

                DBG_MSG( DBG_ERROR, TEXT( "Error getting new terminal window-size" ) );

            } else {

                DBG_MSG( DBG_CONSOLE, TEXT( "Teminal window size changed" ) );

                ywDisplay::resize( ws.ws_col, ws.ws_row );

            }
            break;

    }

}


static int InstallSignalHandler( void ) {

    sigemptyset( &sa.sa_mask );

    sa.sa_flags   = 0;
    sa.sa_handler = SignalHandler;

    if ( -1 == sigaction( SIGWINCH, &sa, 0 ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "Error installing signal-handler" ) );
        return -1;

    }

    return 0;

}


int ywDisplay::Init( int cx, int cy, EventQ & Q, int argc, char * argv[], LPARAM ) {

    DBG_MSG( DBG_CONSOLE, TEXT( "Init terminal" ) );

    set_console_input_mode();

    struct winsize ws;
    if ( 0 == ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws ) ) {

        DBG_MSG( DBG_CONSOLE, TEXT( "Terminal setting size to %dx%d" ), ws.ws_col, ws.ws_row );
        g.iCX = ws.ws_col;
        g.iCY = ws.ws_row;

    } else {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR GETTING TERMINAL SIZE" ) );

    }

    g.Q.addToQ( g.Q.ReadQ, &Input );

    /* Enable mouse reporting */

#define IDSZ_MOUSE_REPORTING    "\e[?9h"
    g.pTerminal = Terminal;

    g.pTerminal( g.lClientData, IDSZ_MOUSE_REPORTING, strlen( IDSZ_MOUSE_REPORTING ) );

    /* register cleanup handler, and set the new terminal mode */
    atexit( reset_console_input_mode );

    InstallSignalHandler();

    return 0;

}


void ywDisplay::Destroy( void ) {

    DBG_MSG( DBG_CONSOLE, TEXT( "Cleanup resets terminal" ) );
    reset_console_input_mode();

}


void underline_on( void ) {

    char    szTmp[128];
    sprintf( szTmp, "\x1B[4m" );

    g.pTerminal( g.lClientData, szTmp, strlen( szTmp ) );

}


void underline_off( void ) {

    char    szTmp[128];
    sprintf( szTmp, "\x1B[24m" );

    g.pTerminal( g.lClientData, szTmp, strlen( szTmp ) );

}


void SetTextAttributes( COLOR_PAIR cp ) {

    static COLOR_PAIR Oldcp = { COLOR_NONE, COLOR_NONE };

    if ( memcmp( &cp, &Oldcp, sizeof( Oldcp ) ) == 0 ) {

        // Already using these colors.	
        return;

    }

    // Set current colors.
    Oldcp.fg = cp.fg;
    Oldcp.bg = cp.bg;

    MapToANSI( cp );

}


void gotoxy( unsigned uX, unsigned uY ) {

    char    szTmp[128];

    // Change from a ZERO-based coordinate system to ONE-based.
    sprintf( szTmp, "\x1B[%u;%uH", uY + 1, uX + 1 );

    // Send position command to console
    g.pTerminal( g.lClientData, szTmp, strlen( szTmp ) );

    /* Save cursor position */
    _pt.x = uX;
    _pt.y = uY;

}


POINT getxy( void ) {

    return _pt;

}


int putch( char c ) {

    // Write to console
    return g.pTerminal( g.lClientData, &c, sizeof( c ) );

}


void DC::Out( const POINT & pt, COLORREF cStorage ) {

    gotoxy( pt.x, pt.y );

    COLOR_PAIR cp;

    /* Unpack character into it's colour and character representation. */
    cp.fg   = GET_TEXT_COLORREF_FG( cStorage );
    cp.bg   = GET_TEXT_COLORREF_BG( cStorage );
    TCHAR c = GET_TEXT_COLORREF_CHAR( cStorage );

    // Set to text attributes.
    SetTextAttributes( cp );

    if ( ' ' > c ) {

        c = ' ';

    }

    putch( (char)c );

}


// Used to type a character to the display.
int DC::TypeByteAt( HFONT, POINT pt, UINT /* uFlags */, UINT uFormat, TCHAR c, const RECT * pr ) {

    if ( DT_CALCRECT & uFormat ) {

        return 1;

    }

//    if ( ( ! In( pt ) ) || ( ( NULL != pr ) && ( ! PtInRect( pr, pt ) ) ) ) {

    if ( ! ( ( NULL == pr ) || PtInRect( pr, pt ) ) ) {

        return 1;

    }

    COLORREF cStorage;

    if ( OPAQUE == iBkMode ) {

        /* Pack character into it's colour and character representation so that it may be repainted easily later. */
        cStorage = MAKE_TEXT_COLORREF( c, text.fg, text.bg );

    } else {

        COLORREF cOldStorage;

        GetPixel( pt, cOldStorage );

        cStorage = MAKE_TEXT_COLORREF( c, text.fg, GET_TEXT_COLORREF_BG( cOldStorage ) );

    }

    /* Store new contents even if occulted. */
    SetPixel( pt, cStorage, cStorage );

    /* Calculate where on the screen this should go. */
    POINT ParentOffset = pWnd->GetParentOffset();

    POINT ptScreen;

    ptScreen.x = ParentOffset.x + shape.x + pt.x;
    ptScreen.y = ParentOffset.y + shape.y + pt.y;

#if 0
    if ( pWnd->pWndPointObscured( ptScreen ) ) {

        /* Window ABOVE this one obscuring it, do not paint. */

        return 1;

    }
#endif

    Out( ptScreen, cStorage );

    return 1;

}


#endif /* YOU_WIN_TXT */
