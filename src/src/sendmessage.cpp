

#include "ywin.h"


#ifndef NDEBUG
#include <traceMSG.cpp>
#include <dump_buff.cpp>
#endif
#include <dbgtrace.cpp>


static
#ifndef __APPLE_CC__
__thread
#endif
int iInSendMessage = 0;


BOOL InSendMessage( void ) {

    return iInSendMessage;

}


void OutputDebugString( LPCTSTR pszString ) {

#if defined( DEBUG ) || defined( _DEBUG )
    dbgtrace( 0, NULL, -1, TEXT( "%s" ), pszString );
#endif

    _ftprintf( stderr, TEXT( "%s\n" ), pszString );

}


LRESULT SendMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    if ( ( 0 == hWnd ) || ( HWND_DESKTOP == hWnd ) ) {


        DBG_MSG( DBG_WINDOW_MESSAGES, "SendMessage called with handle %lX", hWnd );
        hWnd = g.pTopWnd;

    }

#ifndef NDEBUG
    TCHAR szPrefix[1024];

    ZeroMemory( szPrefix, sizeof( szPrefix ) );

    LPCTSTR lpszClassname = ( reinterpret_cast<ywWindow *>( hWnd ) )->pClass->GetClassName();

    long lID = (long)( reinterpret_cast<ywWindow *>( hWnd ) )->hMenu;

    _sntprintf( szPrefix, Dim( szPrefix ) - 1, TEXT( "%s %ld " ), lpszClassname, lID );

    TRACE_MESSAGE_NESTED( DBG_WINDOW_MESSAGES, iInSendMessage, szPrefix, hWnd, uiMsg, wParam, lParam );
#endif

    iInSendMessage++;

    DLGPROC DlgProc = (DLGPROC)GetWindowLongPtr( hWnd, DWL_DLGPROC );
    WNDPROC WndProc = (WNDPROC)GetWindowLongPtr( hWnd, GWL_WNDPROC );

    LRESULT lVal;

    if ( ( WM_CREATE != uiMsg ) && ( NULL != DlgProc ) ) {

        lVal = DlgProc( hWnd, uiMsg, wParam, lParam );

        if ( ( WM_DESTROY != uiMsg ) && ( 0 != lVal ) ) {

            /* Dialog procedure DID handle the message */
            goto fin;

        }

    }

    if ( NULL != WndProc ) {

        lVal = (LRESULT)WndProc( hWnd, uiMsg, wParam, lParam );

        goto fin;

    }

    lVal = (LRESULT)DefWindowProc( hWnd, uiMsg, wParam, lParam );

    goto fin;

fin:

    iInSendMessage--;

    TRACE_MESSAGE_NESTED( DBG_WINDOW_MESSAGES, iInSendMessage, szPrefix, hWnd, uiMsg, 0, lVal );

    switch( uiMsg ) {

        case WM_ERASEBKGND:

            ( reinterpret_cast<ywWindow *>( hWnd ) )->fErase = ! (bool)lVal;
            break;

        case WM_NCPAINT:

            ( reinterpret_cast<ywWindow *>( hWnd ) )->bDrawFramePending = false;
            break;

    }

    return lVal;

}
