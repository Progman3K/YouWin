

#include "ywin.h"


IWindow * IWindow::TopmostWindow( void ) {

    // Walk the window list UP from the desktop and return the topmost window
    IWindow * pWindowAboveMe;

    if ( ( ! g.pTopWnd ) || ( ! g.pTopWnd->pPrevSiblingWnd ) ) {

        // Not initialized yet or no children have been created..
        return NULL;

    }

    pWindowAboveMe = g.pTopWnd->pPrevSiblingWnd;

    // There IS a window above me.
    do {

        if ( ! pWindowAboveMe->pPrevSiblingWnd ) {

            // No more windows above this one.
            return pWindowAboveMe;

        }

        // Reiterate from new level.
        pWindowAboveMe = pWindowAboveMe->pPrevSiblingWnd;

    } while( true );

}


int iEnumWindows( FPBENUMTEXTWINDOWSPROC fpbEnumWndProc, BOOLEAN bAscending, IWindow * pWnd, LPARAM lParam ) {

    // Walk the window list up OR down
    IWindow * pNextWnd;
    int       iCountWnd = 0;

    if ( pWnd ) {

        // Start the enumeration from the root window's PREVIOUS/NEXT sibling.
        if ( ! ( pNextWnd = bAscending ? pWnd->pPrevSiblingWnd : pWnd->pNextSiblingWnd ) ) {

            // No more windows.
            return 0;

        }

        // Start iteration with the NEXT member.
        pWnd = reinterpret_cast<Window *>( pNextWnd );

    } else {

        if ( ! ( pWnd = ( bAscending ? g.pTopWnd : IWindow::TopmostWindow() ) ) ) {

            // No windows in chain.
            return 0;

        }

    }

    // There IS a window above me.
    do {

        iCountWnd++;

        // Call back user.
        if ( ! fpbEnumWndProc( pWnd, lParam ) ) {

            // User has signaled to stop enum.
            break;

        }

        if ( ! ( pNextWnd = bAscending ? pWnd->pPrevSiblingWnd : pWnd->pNextSiblingWnd ) ) {

            // No more windows.
            break;

        }

        // Reiterate from new level.
        pWnd = reinterpret_cast<Window *>( pNextWnd );

    } while( true );

    return iCountWnd;

}


typedef struct {

    POINT    pt;
    Window * pWnd;

} EnumFWaS;


BOOLEAN bEnumFindWindowAtSpot( IWindow * pWnd, LPARAM lParam ) {

    EnumFWaS * pFWaS = (EnumFWaS *)lParam;

    if ( pWnd->bPointInWindow( pFWaS->pt ) ) {

        /* This is the first window encountered from the top-down */

        if ( ! IsWindowVisible( (HWND)pWnd ) ) {

            /* Not visible, ignore it */
            return true;

        }

        /* MUST not have any disabled parent */
//        if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

//            return true;

//        }

        pFWaS->pWnd = reinterpret_cast<Window *>( pWnd );

    }

    return true;

}


Window * Window::At( POINT * pPt ) {

    /* Find out which window is here, */
    EnumFWaS    eFWaS;

    eFWaS.pWnd = NULL;
    eFWaS.pt   = *pPt;

    /* Find which window is at x,y and send to it directly. */
    iEnumWindows( bEnumFindWindowAtSpot, true, NULL, (LPARAM)&eFWaS );

    if ( NULL == eFWaS.pWnd ) {

        return NULL;

    }

    /* Translate from absolute to window-relative coordinates */
    eFWaS.pt = eFWaS.pt - eFWaS.pWnd->GetParentOffset();

    *pPt = eFWaS.pt;

    DBG_MSG( DBG_GENERAL_INFORMATION, 
    TEXT(
        "%8s"
        " %8X"
        " %5d"
        " (%4d,%4d)"
        "%s%s%s%s%s%s%s%s%s%s%s%s"
    ),
    eFWaS.pWnd->pClass->GetClassName(), eFWaS.pWnd, (unsigned long)( eFWaS.pWnd->hMenu ), eFWaS.pWnd->cx, eFWaS.pWnd->cy,
    ( WS_BORDER      & eFWaS.pWnd->dwStyle ) ? " WS_BORDER"      : "",
    ( WS_CAPTION     & eFWaS.pWnd->dwStyle ) ? " WS_CAPTION"     : "",
    ( WS_CHILD       & eFWaS.pWnd->dwStyle ) ? " WS_CHILD"       : "",
    ( WS_DISABLED    & eFWaS.pWnd->dwStyle ) ? " WS_DISABLED"    : "",
    ( WS_GROUP       & eFWaS.pWnd->dwStyle ) ? " WS_GROUP"       : "",
    ( WS_MINIMIZEBOX & eFWaS.pWnd->dwStyle ) ? " WS_MINIMIZEBOX" : "",
    ( WS_OVERLAPPED  & eFWaS.pWnd->dwStyle ) ? " WS_OVERLAPPED"  : "",
    ( WS_SYSMENU     & eFWaS.pWnd->dwStyle ) ? " WS_SYSMENU"     : "",
    ( WS_TABSTOP     & eFWaS.pWnd->dwStyle ) ? " WS_TABSTOP"     : "",
    ( WS_THICKFRAME  & eFWaS.pWnd->dwStyle ) ? " WS_THICKFRAME"  : "",
    ( WS_VISIBLE     & eFWaS.pWnd->dwStyle ) ? " WS_VISIBLE"     : "",
    ( WS_VSCROLL     & eFWaS.pWnd->dwStyle ) ? " WS_VSCROLL"     : "" );

    return eFWaS.pWnd;

}
