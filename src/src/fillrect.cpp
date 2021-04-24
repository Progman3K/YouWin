

#include "ywin.h"


HBRUSH CreateSolidBrush( COLORREF cr ) {

    return (HBRUSH) new SolidBrush( cr, false );

}


BOOL DrawEdge( HDC hDC, LPRECT prc, UINT uiEdge, UINT uFlags ) {

    SolidBrush brLeft,brTop,brRight,brBottom;

    if ( BDR_RAISEDOUTER & uiEdge ) {

        brLeft.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
        brTop.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

        if ( BF_FLAT & uFlags ) {

            brRight.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
            brBottom.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

        } else {

            brRight.SetColor( GetSysColor( COLOR_3DSHADOW ) );
            brBottom.SetColor( GetSysColor( COLOR_3DSHADOW ) );

        }

    }

    if ( BDR_SUNKENOUTER & uiEdge ) {

        if ( BF_FLAT & uFlags ) {

            brLeft.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
            brTop.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

        } else {

            brLeft.SetColor( GetSysColor( COLOR_3DSHADOW ) );
            brTop.SetColor( GetSysColor( COLOR_3DSHADOW ) );

        }

        brRight.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
        brBottom.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

    }

    if ( BDR_SUNKENINNER & uiEdge ) {

        if ( BF_FLAT & uFlags ) {

            brLeft.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
            brTop.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

        } else {

            brLeft.SetColor( GetSysColor( COLOR_3DDKSHADOW ) );
            brTop.SetColor( GetSysColor( COLOR_3DDKSHADOW ) );

        }

        brRight.SetColor( GetSysColor( COLOR_3DHILIGHT ) );
        brBottom.SetColor( GetSysColor( COLOR_3DHILIGHT ) );

    }

    RECT r;

    if ( uFlags & BF_LEFT ) {

        // Left side line
        r.left   = prc->left;
        r.top    = prc->top;

        r.right  = r.left + GetSystemMetrics( SM_CXBORDER );
        r.bottom = prc->bottom;

        FillRect( hDC, &r, (HBRUSH)&brLeft );

    }

    if ( uFlags & BF_TOP ) {

        // Top line
        r.left   = prc->left;
        r.top    = prc->top;

        r.right  = prc->right;
        r.bottom = r.top + GetSystemMetrics( SM_CYBORDER );

        FillRect( hDC, &r, (HBRUSH)&brTop );

    }

    if ( uFlags & BF_RIGHT ) {

        // Right side line
        r.left   = prc->right - GetSystemMetrics( SM_CXBORDER );
        r.top    = prc->top;

        r.right  = prc->right;
        r.bottom = prc->bottom;

        FillRect( hDC, &r, (HBRUSH)&brRight );

    }

    if ( uFlags & BF_BOTTOM ) {

        // Bottom line
        r.left   = prc->left;
        r.top    = prc->bottom - GetSystemMetrics( SM_CYBORDER );

        r.right  = prc->right;
        r.bottom = prc->bottom;

        FillRect( hDC, &r, (HBRUSH)&brBottom );

    }

    return true;

}


BOOL DrawFocusRect( HDC hDC, const RECT * pr ) {

    return InvertRect( hDC, pr );

}


int FillRect( HDC hDC, const RECT * prc, HBRUSH hbr ) {

    COLORREF c;

    if ( 0 == HIWORD( hbr ) ) {

        /* System solid color brush */
        c = GetSysColor( LOWORD( hbr ) - 1 );

    } else {

        SolidBrush * pBR = reinterpret_cast<SolidBrush *>( hbr );
        c = pBR->GetColor();

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

#ifdef YOU_WIN_TXT
    POINT ptOldCaret = getxy();
#endif

    StartPoints();

    // Draw inside the rectangle in the background colour with clipping.
    POINT pt;

    for ( pt.y = prc->top; pt.y < prc->bottom; pt.y++ ) {

        for ( pt.x = prc->left; pt.x < prc->right; pt.x++ ) {

            /* Check clipping */
            pDC->SetPixel( pt, c, c );

        }

    }

    EndPoints();

#ifdef YOU_WIN_TXT
    gotoxy( ptOldCaret.x, ptOldCaret.y );
#endif

    return true;

}
