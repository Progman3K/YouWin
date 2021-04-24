

#include "ywin.h"


DC::DC( IWindow * pFromWnd, Region * pRegion, IBitmap * pixels, Flags uflags ) {

    flags           = uflags;

    /* Text insertion point starts at 0,0 */
    ptPen.x         = 0;
    ptPen.y         = 0;

    uXScroll        = 0;
    uYScroll        = 0;

    pWnd            = pFromWnd;

    hFont           = hSystemFont;

    text.bg         = SysColorWindow.GetColor();
    text.fg         = SysColorWindowText.GetColor();

    iBkMode         = OPAQUE;
    uiTextAlignMode = TA_LEFT | TA_TOP | TA_NOUPDATECP;

    bInDrawText     = false;
    uiDTMode        = 0;

    pPixels         = pixels;

    SetShape( pRegion );

}


int DC::AddIntersection( Region * pRgn ) {

    if ( NULL == pRgn ) {

        intersect.clear();
        return 0;

    }

    for ( unsigned u = 0; u < pRgn->size(); u++ ) {

        intersect.add( pRgn->at( u ) );

    }

    return intersect.size();

}


int DC::AddExclusion( Region * pRgn ) {

    if ( NULL == pRgn ) {

        exclude.reset();
        return 0;

    }

    exclude.x  = pRgn->x;
    exclude.y  = pRgn->y;
    exclude.cx = pRgn->cx;
    exclude.cy = pRgn->cy;

    for ( unsigned u = 0; u < pRgn->size(); u++ ) {

        exclude.add( pRgn->at( u ) );

    }

    return exclude.size();

}


void DC::copy( const POINT & pt, DC * pDC, const RECT & r ) {

    POINT ptSrc;
    POINT ptDest;

    /* Apply the ~ operator */
    for ( int line = 0; line < ( r.bottom - r.top ); line++ ) {

        for ( int column = 0; column < ( r.right - r.left ); column++ ) {

            ptSrc.x = pt.x + column;
            ptSrc.y = pt.y + line;

            COLORREF c;

            if ( GetPixel( ptSrc, c ) ) {

                ptDest.x = r.left + column;
                ptDest.y = r.top  + line;

                if ( pDC->SetPixel( ptDest, c, c ) ) {

                    pDC->paint( ptDest, c );

                }

            }

        }

    }

}


void DC::fill( const RECT & r, COLORREF cFill ) {

    StartPoints();

    POINT pt;

    pt( r.left, r.top );

    for ( pt.y = r.top; pt.y < r.bottom; pt.y++ ) {

        for ( pt.x = r.left; pt.x < r.right; pt.x++ ) {

            if ( pPixels->SetPixel( pt, cFill ) ) {

                paint( pt, cFill );

            }

        }

    }

    EndPoints();

}


void DC::Invert( const RECT & r ) {

    /* Apply the ~ operator */
    POINT pt;

    pt( r.left, r.top );

    for ( pt.y = r.top; pt.y < r.bottom; pt.y++ ) {

        for ( pt.x = r.left; pt.x < r.right; pt.x++ ) {

            COLORREF c;

            if ( pPixels->GetPixel( pt, c ) ) {

                c ^= 0x80;

                if ( pPixels->SetPixel( pt, c ) ) {

                    paint( pt, c );

                }

            }

        }

    }

}


void DC::paint( const POINT & pt, COLORREF c ) {

    // Form onscreen row/collumn.
    // It is SAFE to call GetParentOffset when its instance (pWnd) is NULL.
    POINT ParentOffset = pWnd->GetParentOffset();

    POINT ptScreen;

    ptScreen.x = ParentOffset.x + shape.x + pt.x;
    ptScreen.y = ParentOffset.y + shape.y + pt.y;

    if ( NULL == pWnd ) {

        /* Whole-screen DC */
        Out( ptScreen, c );
        return;

    }

    if ( pWnd->pWndPointObscured( ptScreen ) ) {

        return;

    }

    if ( WS_CHILD & pWnd->dwStyle ) {

        /* Make sure output is clipped to parent's client-area */
        RECT r;

        POINT ptParent;

        ptParent.x = 0;
        ptParent.y = 0;

        ClientToScreen( pWnd->pParentWnd, &ptParent );

        GetClientRect( pWnd->pParentWnd, &r );

        r.left   = ptParent.x;
        r.top    = ptParent.y;
        r.right  = r.left + r.right;
        r.bottom = r.top  + r.bottom;

        if ( ! PtInRect( &r, ptScreen ) ) {

            return;

        }

    }

    // No obscuring window above this one, paint.
    Out( ptScreen, c );

}


bool DC::GetPixel( const POINT & pt, COLORREF & c ) {

    if ( NULL != pPixels ) {

        return pPixels->GetPixel( pt, c );

    }

    /* This can mean a few things */

    if ( NULL == pWnd ) {

        /* This DC is for the entire screen */


    } else {

        /* This DC is for the entire window */
        if ( DC::EntireWindow & flags ) {

            return pWnd->NonClientPixels.GetPixel( pt, c );

        } else {

            return pWnd->ClientPixels.GetPixel( pt, c );

        }

    }

    return false;

}


bool DC::SetPixel( POINT pt, COLORREF c, COLORREF /* pixel */ ) {

    if ( exclude.PtIn( pt ) ) {

        return false;

    }

    if ( DC::Memory & flags ) {

        return pPixels->SetPixel( pt, c );

    }

    if ( DC::EntireWindow & flags ) {

        if ( ( ! pWnd->NonClientPixels.SetPixel( pt, c ) ) && ( ! pWnd->ClientPixels.SetPixel( pt, c ) ) ) {

            return false;

        }

    } else {

        // Client area only.
        if ( ! pPixels->SetPixel( pt, c ) ) {

            return false;

        }

    }

    /* At this point, the pixel is considered written into the DC */
    paint( pt, c );

    return true;

}


void DC::SetSize( unsigned cx, unsigned cy ) {

    pPixels->Create( cx, cy, text.bg );

}


void DC::SetShape( Region * pRegion ) {

    if ( NULL == pRegion ) {

        shape.x  = 0;
        shape.y  = 0;
        shape.cx = 0;
        shape.cy = 0;

        exclude.clear();
        intersect.clear();

    } else {

        shape = *pRegion;

    }

}


bool DC::In( POINT & pt ) const {

    /* Check clipping */
    if ( ! shape.PtIn( pt ) ) {

        return false;

    }

    /* Look in the excluded region list, if the point lies within one of the region rectangles, skip it */
    if ( 0 != exclude.size() ) {

        for ( unsigned u = 0; u < exclude.size(); u++ ) {

            if ( PtInRect( &( exclude.at( u ) ), pt ) ) {

                return false;

            }

        }

    }

    return true;

}
