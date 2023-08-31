

#include "ywin.h"


/*
void ScreenToClient( LPWindow lpWnd, POINT ptScreen ) {

    // Convert this coordinate to client coords.
    ptScreen.uiX = ptScreen.uiX - lpWnd->pt.uiX;
    ptScreen.uiY = ptScreen.uiY - lpWnd->pt.uiY;

}
*/
#define	ScreenToClient( lpWnd, ptScreen ) ptScreen.x = ptScreen.x - lpWnd->GetParentOffset().x; ptScreen.y = ptScreen.y - lpWnd->GetParentOffset().y


bool bWindowsIntersect( IWindow * pTopWnd, IWindow * pWnd ) {

    bool bIntersectX = false;
    bool bIntersectY = false; /* Intersection detected on the X,Y */

    if ( pTopWnd->x < pWnd->x ) {

        if ( pWnd->x < ( pTopWnd->x + pTopWnd->cx ) ) {

            bIntersectX = true;

            if ( pTopWnd->y < pWnd->y ) {

                if ( pWnd->y < ( pTopWnd->y + pTopWnd->cy ) ) {

                    bIntersectY = true;

                }

            } else {

                // pTopWnd->y >= pWnd->y
                if ( pTopWnd->y < ( pWnd->y + pWnd->cy ) ) {

                    bIntersectY = true;

                }

            }

        }

    } else {

        // pTopWnd->x >= pWnd->x
        if ( pTopWnd->x < ( pWnd->x + pWnd->cx ) ) {

            /* Intersection detected on the X */
            bIntersectX = true;

            if ( pTopWnd->y < pWnd->y ) {

                if ( pWnd->y < ( pTopWnd->y + pTopWnd->cy ) ) {

                    bIntersectY = true;

                }

            } else {

                // pTopWnd->y >= pWnd->y
                if ( pTopWnd->y < ( pWnd->y + pWnd->cy ) ) {

                    bIntersectY = true;

                }

            }

        }

    }

    return bIntersectX && bIntersectY;

}


BOOLEAN bEnumRepaintWndProc( IWindow * pWnd, LPARAM lParam ) {

    ywWindow * pTopWnd = reinterpret_cast<ywWindow *>( lParam );

//    RECT r;

    /*
     * If the rectangle of the window
     * is over any part of the rectangle
     * of any other window underneath it,
     * the intersection must be added to
     * the lower window's list of invalid regions.
     *
    */

    if ( bWindowsIntersect( pTopWnd, pWnd ) ) {

        RedrawWindow( pWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    }

    return true;

}


// Repaint all the windows under this one.
void RepaintWindowsUnder( ywWindow * pWnd ) {

    /* Enumerate all windows from this one in descending order */
    iEnumWindows( bEnumRepaintWndProc, false, pWnd, (LPARAM)pWnd );

}
