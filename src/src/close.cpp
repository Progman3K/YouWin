

#include "ywin.h"


int CloseWindowLib( void ) {

    if ( ! g.bInit ) {

        // Function called BEFORE init.	
        return -1;

    }

    // Walk the window list and clean up everything.
    if ( NULL != g.pTopWnd ) {

        // Destroy the desktop.
        HWND hDesktopWnd = (HWND)g.pTopWnd;
        g.pTopWnd = NULL;

        DestroyWindow( hDesktopWnd );

    }

    for ( auto j = classes.rbegin() ; j != classes.rend(); ++j ) {

        UnregisterClass( j->second->ClassName.c_str(), 0 );

    }

#ifdef YOU_WIN_GRAPHICAL

    // Free the fonts?
    for ( FontList::iterator i = fonts.begin(); i != fonts.end(); ++i ) {

//        Font * pFont = i->second;

    }

#endif /* YOU_WIN_GRAPHICAL */

    return 0;

}
