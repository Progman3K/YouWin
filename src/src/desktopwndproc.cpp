

#include "ywin.h"


static BOOL InformDisplayChanged( HWND hWnd, LPARAM lParam ) {

    HWND hMyselfWnd = (HWND)lParam;

    if ( hWnd == hMyselfWnd ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Skipping circular notification" ) );
        return true;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Top-level window %lX informed of resize" ), hWnd );

    Window * pWnd = reinterpret_cast<Window *>( hWnd );

    if ( WS_CHILD & pWnd->dwStyle ) {

        FORWARD_WM_DISPLAYCHANGE( hWnd, 24, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), PostMessage );

    } else {

        FORWARD_WM_DISPLAYCHANGE( hWnd, 24, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), SendMessage );

    }

    EnumChildWindows( hWnd, InformDisplayChanged, (LPARAM)hWnd );

    return true;

}


void Desktop::OnDisplayChange( HWND hWnd, UINT uiBitsPerPixel, UINT usercx, UINT usercy ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Desktop resized to %ux%u" ), usercx, usercy );

    g.iCX = usercx;
    g.iCY = usercy;

    MoveWindow( hWnd, 0, 0, usercx, usercy, false );

    EnumChildWindows( NULL, InformDisplayChanged, (LPARAM)hWnd );

}


LRESULT Desktop::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Desktop * pWnd = reinterpret_cast<Desktop *>( hWnd );

    switch( uiMsg ) {

        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hWnd, wParam, lParam, pWnd->OnDisplayChange );
            break;

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}
