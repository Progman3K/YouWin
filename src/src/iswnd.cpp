

#include "ywin.h"


Window * Window::ToWnd( HWND hWnd, const char * pszFile, unsigned uLine ) {

    Window * pWnd;

    if ( ! hWnd ) {

        DBG_MSG( DBG_ERROR, TEXT( "NULL WINDOW passed in from %s, line %u" ), pszFile, uLine );
        return NULL;

    }

    pWnd = reinterpret_cast<Window *>( hWnd );

    // Verify signature.
    if ( 0 != pWnd->SigGood() ) {

        DBG_MSG( DBG_ERROR, TEXT( "BAD WINDOW SIGNATURE on %lX, passed in from %s, line %u" ), pWnd, pszFile, uLine );
        return NULL;

    }

    return pWnd;

}


BOOL IsWindow( HWND hWnd ) {

    return NULL != IsWnd( hWnd );

}
