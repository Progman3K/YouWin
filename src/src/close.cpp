

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

#ifdef YOU_WIN_GRAPHICAL

    // Free the fonts?
    for ( FontList::iterator i = fonts.begin(); i != fonts.end(); ++i ) {

//        Font * pFont = i->second;

    }




#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iRet = iOSDestroy( app );
#else
#ifdef ANDROID
    droidDestroy( g.app );
#else
    GL::glDestroy();
#endif
#endif

#endif /* YOU_WIN_GRAPHICAL */

    return 0;

}
