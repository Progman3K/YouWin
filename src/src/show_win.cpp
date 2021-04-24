

#include "ywin.h"


BOOL ShowWindow( HWND hWnd, int iShow ) {

    Window * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    if ( ( SW_SHOW == iShow ) && ( ! ( WS_VISIBLE & pWnd->dwStyle ) ) ) {

        // Was INVISIBLE before. Draw it now.
        pWnd->dwStyle |= WS_VISIBLE;

        RedrawWindow( hWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );
        return true;

    }

    if ( ( SW_HIDE == iShow ) && ( WS_VISIBLE & pWnd->dwStyle ) ) {

        // Was VISIBLE before. Repaint everybody that is underneath it.
        pWnd->dwStyle = ( ( ~WS_VISIBLE ) & pWnd->dwStyle );

        /* Get its onscreen placement */
        RECT r;
        r.left   = pWnd->GetParentOffset().x;
        r.top    = pWnd->GetParentOffset().y;
        r.right  = r.left + pWnd->cx;
        r.bottom = r.top  + pWnd->cy;

        repaint( r );
        return true;

    }

    // No change.
    // lpWnd->bIsVisible = ! ( SW_HIDE == iShow );

    return true;

}
