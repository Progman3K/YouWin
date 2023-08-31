

#include "ywin.h"

#if 0
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

    Window * pWnd = NULL;

    for ( auto popup = g.pTopWnd->children.rbegin(); popup != g.pTopWnd->children.rend(); popup++ ) {

        /* Last popup is highest in the Z order */
        if ( ! (*popup)->bPointInWindow( *pPt ) ) {

            continue;

        }

        pWnd = (Window *)*popup;

        /* But if one of its children fits, supersede */
        for ( auto child = pWnd->children.rbegin(); child != pWnd->children.rend(); child++ ) {

            if ( (*child)->bPointInWindow( *pPt ) ) {

                /* This is the first window encountered from the top-down */

                if ( ! IsWindowVisible( (HWND)*child ) ) {

                    /* Not visible, ignore it */
                    continue;

                }

                /* MUST not have any disabled parent */
//                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

//                    continue;

//                }

                pWnd = (Window *)*child;
                break;

            }

        }

        if ( pWnd ) {

            break;

        }

    }

    if ( NULL == pWnd ) {

        return NULL;

    }

    /* Translate from absolute to window-relative coordinates */
    *pPt = *pPt - pWnd->GetParentOffset();

    DBG_MSG( DBG_GENERAL_INFORMATION, 
    TEXT(
        "%8s"
        " %8X"
        " %5d"
        " (%4d,%4d)"
        "%s%s%s%s%s%s%s%s%s%s%s%s"
    ),
    pWnd->pClass->GetClassName(), pWnd, (unsigned long)( pWnd->hMenu ), pWnd->cx, pWnd->cy,
    ( WS_BORDER      & pWnd->dwStyle ) ? " WS_BORDER"      : "",
    ( WS_CAPTION     & pWnd->dwStyle ) ? " WS_CAPTION"     : "",
    ( WS_CHILD       & pWnd->dwStyle ) ? " WS_CHILD"       : "",
    ( WS_DISABLED    & pWnd->dwStyle ) ? " WS_DISABLED"    : "",
    ( WS_GROUP       & pWnd->dwStyle ) ? " WS_GROUP"       : "",
    ( WS_MINIMIZEBOX & pWnd->dwStyle ) ? " WS_MINIMIZEBOX" : "",
    ( WS_OVERLAPPED  & pWnd->dwStyle ) ? " WS_OVERLAPPED"  : "",
    ( WS_SYSMENU     & pWnd->dwStyle ) ? " WS_SYSMENU"     : "",
    ( WS_TABSTOP     & pWnd->dwStyle ) ? " WS_TABSTOP"     : "",
    ( WS_THICKFRAME  & pWnd->dwStyle ) ? " WS_THICKFRAME"  : "",
    ( WS_VISIBLE     & pWnd->dwStyle ) ? " WS_VISIBLE"     : "",
    ( WS_VSCROLL     & pWnd->dwStyle ) ? " WS_VSCROLL"     : "" );

    return pWnd;

}
#endif
