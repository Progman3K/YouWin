

#include "ywin.h"


HWND WindowFromPoint( POINT pt ) {

//    if ( NULL == g.pTopWnd ) {

//        return NULL;

//    }
#if 0
    for ( auto const x : children ) {

        foo(x);

    }

    IWindow * pHighestWindowAboveMe = NULL;

    IWindow * pWindowAboveMe;

    for ( pWindowAboveMe = g.pTopWnd; pWindowAboveMe; pWindowAboveMe = pWindowAboveMe->pPrevSiblingWnd ) {

        if ( ! ( WS_VISIBLE & pWindowAboveMe->dwStyle ) ) {

            continue;

        }

        if ( ! pWindowAboveMe->bPointInWindow( pt ) ) {

            continue;

        }

        // The point falls within it's extents.
        pHighestWindowAboveMe = pWindowAboveMe;

        // Check the window above that one.

    }

    // No visible windows above me obscuring the point.
    return pHighestWindowAboveMe;
#endif

    return 0;

}


unsigned long repaint( RECT & r ) {

    ywWindow * pWnd;
    POINT    ptScreen;
    std::unordered_set<HWND> repaint;

    ptScreen( r.left, r.top );

    unsigned long ulMissedPixels = 0;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "repaint screen rectangle %d,%d,%d,%d" ), r.left, r.top, r.right, r.bottom );

    for ( ptScreen.y = r.top; ptScreen.y < r.bottom; ptScreen.y++ ) {

        for ( ptScreen.x = r.left; ptScreen.x < r.right; ptScreen.x++ ) {

            if ( NULL == ( pWnd = reinterpret_cast<ywWindow *>( WindowFromPoint( ptScreen ) ) ) ) {

                ulMissedPixels++;
                continue;

            }

            /* If this window is already in the list, keep going */

            /* If not, add it */
            repaint.emplace( (HWND)pWnd );

        }

    }

    for ( const auto & i : repaint ) {

        /* Make the windows paint */
        RedrawWindow( i, 0, 0, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_INTERNALPAINT | RDW_NOCHILDREN );

    }


//    EndPoints();

    if ( 0 != ulMissedPixels ) {

        DBG_MSG( DBG_ERROR, TEXT( "repaint screen missed %lu pixels" ), ulMissedPixels );

    }

    PostRefresh();
    RasterUpdate();

    return ulMissedPixels;

}


BOOL DestroyWindow( HWND hWnd ) {

    if ( NULL == hWnd ) {

        return false;

    }

    IWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    /* Memorize its onscreen placement */
    RECT r;
    GetWindowRect( hWnd, &r );

    /* Reverse-delete child controls first */
    for ( auto i = pWnd->children.rbegin(); i != pWnd->children.rend(); i++ ) {

        DestroyWindow( *i );

    }

    FORWARD_WM_DESTROY( hWnd, SendMessage );

    /* Now walk entire window list and for every window intersecting, internal repaint r */
    repaint( r );

    return true;

}
