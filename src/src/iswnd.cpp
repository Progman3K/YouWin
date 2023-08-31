

#include "ywin.h"


ywWindow * ywWindow::ToWnd( HWND hWnd, const char * pszFile, unsigned uLine ) {

    ywWindow * pWnd;

    if ( ! hWnd ) {

        DBG_MSG( DBG_ERROR, TEXT( "NULL WINDOW passed in from %s, line %u" ), pszFile, uLine );
        return NULL;

    }

    if ( HWND_DESKTOP == hWnd ) {

        hWnd = g.pTopWnd;

    }

    pWnd = reinterpret_cast<ywWindow *>( hWnd );

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
