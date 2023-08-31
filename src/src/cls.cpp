

#include "ywin.h"


void Cls( HWND hWnd ) {

    IWindow * pWnd = reinterpret_cast<IWindow *>( hWnd );

    // Check if request to clear the screen.
    if ( ( NULL == hWnd ) || ( HWND_DESKTOP == hWnd ) ) {

        pWnd = g.pTopWnd;

    }

    if ( NULL == ( pWnd = IsWnd( pWnd ) ) ) {

        return;

    }

    RedrawWindow( (HWND)pWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW );

}
