

#include "ywin.h"


void ywWindow::CalculateRegions() {

    // Client area starts off taking up the entire window.
    ClientArea.reset();

    NonClientArea.reset();

    unsigned uCaptionAreaY = 0;
//    bool     bBorder       = false;

    rCaption( 0, 0, 0, 0 );

    vscrollArea( 0, 0, 0, 0 );
    vscrollThumbTop( 0, 0, 0, 0 );
    vscrollMiddle( 0, 0, 0, 0 );
    vscrollThumbBottom( 0, 0, 0, 0 );

    hscrollArea( 0, 0, 0, 0 );
    hscrollThumbLeft( 0, 0, 0, 0 );
    hscrollMiddle( 0, 0, 0, 0 );
    hscrollThumbRight( 0, 0, 0, 0 );

    rthumb( 0, 0, 0, 0 );

    if ( WS_BORDER & dwStyle ) {

        ClientArea.x += GetSystemMetrics( SM_CXBORDER );
        ClientArea.y += GetSystemMetrics( SM_CYBORDER );

//        bBorder = true;

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "border - %d,%d" ), ClientArea.x, ClientArea.y );

    }

    if ( WS_THICKFRAME & dwStyle ) {

        ClientArea.x += GetSystemMetrics( SM_CXSIZEFRAME );
        ClientArea.y += GetSystemMetrics( SM_CYSIZEFRAME );

//        bBorder = true;

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "thickframe - %d,%d" ), ClientArea.x, ClientArea.y );

    }

    if ( ( WS_CAPTION & dwStyle ) == WS_CAPTION ) {

        uCaptionAreaY += GetSystemMetrics( SM_CYCAPTION );

        rCaption.left   = ClientArea.x;
        rCaption.top    = ClientArea.y;
        rCaption.bottom = rCaption.top + uCaptionAreaY;

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "caption thickness - %d" ), uCaptionAreaY );

    }

    // Calculate the areas

    if ( (unsigned)( ClientArea.x * 2 ) < cx ) {

        ClientArea.cx = cx - ( ClientArea.x * 2 );

    }

    if ( ( WS_CAPTION & dwStyle ) == WS_CAPTION ) {

        rCaption.right = rCaption.left + ClientArea.cx;

    }

    if ( ( uCaptionAreaY + ( ClientArea.y * 2 ) ) < cy ) {

        ClientArea.cy = cy - ( uCaptionAreaY + ( ClientArea.y * 2 ) );

        ClientArea.y += uCaptionAreaY;

    }

    if ( 0 != HIWORD( hMenu ) ) {

        ClientArea.cy -= GetSystemMetrics( SM_CYMENU );

        ClientArea.y += GetSystemMetrics( SM_CYMENU );

    }

    if ( WS_HSCROLL & dwStyle ) {

        ClientArea.cy -= GetSystemMetrics( SM_CYHSCROLL );

        hscrollArea.left   = ClientArea.x;
        hscrollArea.top    = ClientArea.y + ClientArea.cy;
        hscrollArea.bottom = hscrollArea.top + GetSystemMetrics( SM_CYHSCROLL );

        if ( WS_VSCROLL & dwStyle ) {

            hscrollArea.right = hscrollArea.left + ( ClientArea.cx - GetSystemMetrics( SM_CXVSCROLL ) );

            rthumb.left   = hscrollArea.right;
            rthumb.top    = hscrollArea.top;
            rthumb.right  = rthumb.left + GetSystemMetrics( SM_CXVSCROLL );
            rthumb.bottom = rthumb.top + GetSystemMetrics( SM_CYHSCROLL );

        } else {

            hscrollArea.right = hscrollArea.left + ClientArea.cx;

        }

        hscrollThumbLeft.left    = hscrollArea.left;
        hscrollThumbLeft.top     = hscrollArea.top;
        hscrollThumbLeft.bottom  = hscrollArea.bottom;
        hscrollThumbLeft.right   = hscrollArea.left + GetSystemMetrics( SM_CXHTHUMB );

        hscrollThumbRight.left   = hscrollArea.right - GetSystemMetrics( SM_CXHTHUMB );
        hscrollThumbRight.top    = hscrollArea.top;
        hscrollThumbRight.bottom = hscrollArea.bottom;
        hscrollThumbRight.right  = hscrollArea.right;

        hscrollMiddle.left       = hscrollArea.left + GetSystemMetrics( SM_CXHTHUMB );
        hscrollMiddle.top        = hscrollArea.top;
        hscrollMiddle.bottom     = hscrollArea.bottom;
        hscrollMiddle.right      = hscrollArea.right - GetSystemMetrics( SM_CXHTHUMB );

    }

    if ( WS_VSCROLL & dwStyle ) {

        ClientArea.cx -= GetSystemMetrics( SM_CXVSCROLL );

        vscrollArea.left          = ClientArea.x + ClientArea.cx;
        vscrollArea.top           = ClientArea.y;
        vscrollArea.right         = vscrollArea.left + GetSystemMetrics( SM_CXVSCROLL );
        vscrollArea.bottom        = vscrollArea.top + ClientArea.cy;

        vscrollThumbTop.left      = vscrollArea.left;
        vscrollThumbTop.top       = vscrollArea.top;
        vscrollThumbTop.bottom    = vscrollArea.top + GetSystemMetrics( SM_CYVTHUMB );
        vscrollThumbTop.right     = vscrollArea.right;

        vscrollThumbBottom.left   = vscrollArea.left;
        vscrollThumbBottom.top    = vscrollArea.bottom - GetSystemMetrics( SM_CYVTHUMB );
        vscrollThumbBottom.bottom = vscrollArea.bottom;
        vscrollThumbBottom.right  = vscrollArea.right;

        vscrollMiddle.left        = vscrollArea.left;
        vscrollMiddle.top         = vscrollArea.top + GetSystemMetrics( SM_CYVTHUMB );
        vscrollMiddle.bottom      = vscrollArea.bottom - GetSystemMetrics( SM_CYVTHUMB );
        vscrollMiddle.right       = vscrollArea.right;

    }

    if ( ( 0 == ClientArea.x ) && ( 0 == ClientArea.y ) && ( cx == ClientArea.cx ) && ( cy == ClientArea.cy ) ) {

        /* There is no non-client area on this window */

    } else {

        /* Include only the non-client areas */
        RECT r;

        NonClientArea.cx = cx;
        NonClientArea.cy = cy /* ClientArea.pt.y */;

        if ( 0 <  ClientArea.y ) {

            // Add top side
            r.left   = 0;
            r.top    = 0;
            r.right  = cx;
            r.bottom = ClientArea.y;

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Non-client: Add caption/top (%d,%d) (%d,%d)" ), r.left, r.top, r.right, r.bottom );
            NonClientArea.add( r );

        }

        if ( 0 < ClientArea.x ) {

            // Add left side
            r.left   = 0;
            r.top    = ClientArea.y;
            r.right  = ClientArea.x;
            r.bottom = cy;

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Non-client: Add left side (%d,%d) (%d,%d)" ), r.left, r.top, r.right, r.bottom );
            NonClientArea.add( r );

        }

        if ( ClientArea.x + ClientArea.cx < cx ) {

            // Add right side
            r.left   = ClientArea.x + ClientArea.cx;
            r.top    = ClientArea.y;
            r.right  = cx;
            r.bottom = cy;

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Non-client: Add right side (%d,%d) (%d,%d)" ), r.left, r.top, r.right, r.bottom );
            NonClientArea.add( r );

        }

        if ( ClientArea.y + ClientArea.cy < cy ) {

            // Add bottom side
            r.left   = 0;
            r.top    = ClientArea.y + ClientArea.cy;
            r.right  = cx;
            r.bottom = cy;

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Non-client: Add bottom side (%d,%d) (%d,%d)" ), r.left, r.top, r.right, r.bottom );
            NonClientArea.add( r );

        }

    }

    /* Update the windows's DCs */

    ClientDC.SetShape( &ClientArea );
    ClientPixels.Create( ClientArea.cx, ClientArea.cy, RGBA( 0, 0, 0, 255 ) );

    NonClientDC.SetShape( &NonClientArea );
    NonClientPixels.Create( NonClientArea.cx, NonClientArea.cy, RGBA( 0, 0, 0, 255 ) );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Window at (%d,%d) sized %d,%d, client area at (%d,%d), sized %d, %d, non-client area at (%d,%d), sized %d, %d." ), x, y, cx, cy, ClientArea.x, ClientArea.y, ClientArea.cx, ClientArea.cy, NonClientArea.x, NonClientArea.y, NonClientArea.cx, NonClientArea.cy );

}


int ExcludeClipRect( HDC hDC, int left, int top, int right, int bottom ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL == pDC ) {

        return ERROR;

    }

    ywRegion Rgn( left, top, right - left, bottom - top );
    RECT   r;

    r.left   = left;
    r.top    = top;
    r.right  = right;
    r.bottom = bottom;

    Rgn.add( r );

    int iCount = pDC->AddExclusion( &Rgn );

    if ( 0 == iCount ) {

        return NULLREGION;

    }

    if ( 1 == iCount ) {

        return SIMPLEREGION;

    }

    return COMPLEXREGION;

}


DWORD GetRegionData( HRGN hRgn, DWORD dwCount, RGNDATA * pRgnData ) {

    if ( NULL == hRgn ) {

        return 0;

    }

    ywRegion * pRgn = reinterpret_cast<ywRegion *>( hRgn );

    if ( NULL == pRgnData ) {

        /* Calculate size */
        return sizeof( RGNDATA ) + ( pRgn->size() * sizeof( RECT ) );

    }

    if ( sizeof( RGNDATA ) > dwCount ) {

        return 0;

    }

    pRgnData->rdh.rcBound.left   = pRgn->x;
    pRgnData->rdh.rcBound.top    = pRgn->y;
    pRgnData->rdh.rcBound.right  = pRgn->x + pRgn->cx;
    pRgnData->rdh.rcBound.bottom = pRgn->y + pRgn->cy;

    pRgnData->rdh.dwSize   = sizeof( RGNDATA ); 
    pRgnData->rdh.iType    = RDH_RECTANGLES;
    pRgnData->rdh.nRgnSize = sizeof( RECT );
    pRgnData->rdh.nCount   = 0;

    dwCount -= sizeof( RGNDATA );

    for ( RECT * pr = (RECT *)pRgnData->Buffer; ( pRgnData->rdh.nCount < pRgn->size() ) && ( sizeof( RECT ) <= dwCount ); pRgnData->rdh.nCount++, pr++ ) {

        *pr = pRgn->at( pRgnData->rdh.nCount );

        dwCount -= sizeof( RECT );

    }

    return sizeof( RGNDATA ) + ( pRgnData->rdh.nCount * sizeof( RECT ) );

}


int SelectClipRegion( HDC hDC, HRGN hRgn ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL == pDC ) {

        return ERROR;

    }

    int iCount = pDC->AddExclusion( reinterpret_cast<ywRegion *>( hRgn ) );

    if ( 0 == iCount ) {

        return NULLREGION;

    }

    if ( 1 == iCount ) {

        return SIMPLEREGION;

    }

    return COMPLEXREGION;

}


HRGN CreateRectRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect ) {

    ywRegion * pRgn = new ywRegion( nLeftRect, nTopRect, nRightRect, nBottomRect );

    return pRgn;

}
