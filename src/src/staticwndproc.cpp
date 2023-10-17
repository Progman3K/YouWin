

#include "ywin.h"


void Static::DrawIcon( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS ) {

    if ( NULL != hIcon ) {

//        FillRect( pPS->hdc, pr, GetSysColorBrush( COLOR_3DFACE ) );
        ::DrawIcon( pPS->hdc, pr->left, pr->top, hIcon );

    } else {

        DrawEdge( pPS->hdc, pr, BDR_SUNKENINNER, BF_RECT );

    }

}


void Static::DrawFrame( HDC hDC, RECT & r ) {

    if ( SS_BLACKFRAME == LOWORD( dwStyle ) ) {

        DrawEdge( hDC, &r, BDR_SUNKENINNER, BF_RECT );
        return;

    }

    if ( SS_GRAYFRAME == LOWORD( dwStyle ) ) {

        DrawEdge( hDC, &r, BDR_SUNKENINNER, BF_RECT );
        return;

    }

    if ( SS_WHITEFRAME == LOWORD( dwStyle ) ) {

        DrawEdge( hDC, &r, BDR_SUNKENINNER, BF_RECT );
        return;

    }

    DrawEdge( hDC, &r, BDR_SUNKENINNER, BF_RECT );

}


void Static::OnPaint( HWND hWnd, PAINTSTRUCT * pPS ) {

    COLORREF oldbkcr = GetBkColor( pPS->hdc );
    COLORREF oldfgcr = GetTextColor( pPS->hdc );
    int iOldBkMode   = SetBkMode( pPS->hdc, TRANSPARENT );

    SetTextColor( pPS->hdc, IsWindowEnabled( hWnd ) ? SysColorBtnText.GetColor() : SysColorGrayText.GetColor() );

    RECT r;
    GetClientRect( hWnd, &r );

    if ( SS_ICON == LOWORD( dwStyle ) ) {

        DrawIcon( hWnd, &r, pPS );
        return;

    }

    if ( SS_BLACKRECT == LOWORD( dwStyle ) ) {

        FillRect( pPS->hdc, &r, GetSysColorBrush( COLOR_3DDKSHADOW ) );
        return;

    }

    if ( SS_GRAYRECT == LOWORD( dwStyle ) ) {

        FillRect( pPS->hdc, &r, GetSysColorBrush( COLOR_3DSHADOW ) );
        return;

    }

    if ( SS_WHITERECT == LOWORD( dwStyle ) ) {

        FillRect( pPS->hdc, &r, GetSysColorBrush( COLOR_3DHILIGHT ) );
        return;

    }

    // Before drawing the frame, clip out the area the text label will appear in.
    SIZE s;
    s.cx = 0;
    s.cy = 0;

    GetTextExtentPoint32( pPS->hdc, Text.c_str(), Text.size(), &s );

    HRGN hClip = CreateRectRgn( 0, 0, s.cx, s.cy );
    SelectClipRegion( pPS->hdc, hClip );
    DeleteObject( hClip );

//    DrawFrame( pPS->hdc, r );

    SelectClipRegion( pPS->hdc, NULL );

#ifdef YOU_WIN_TXT
//    COLORREF bkcr = SysColor3DFace.GetColor();
    SolidBrush br( COLORREF_COLOR_GRAY, true );
    FillRect( pPS->hdc, &r, (HBRUSH)&br );
//    bkcr = COLORREF_COLOR_GRAY;
#endif

//    SetBkColor( ps.hdc, bkcr );

    UINT uFormat = 0; //DT_SINGLELINE; // Assuming DT_LEFT

    if ( SS_NOPREFIX & LOWORD( dwStyle ) ) {

        uFormat |= DT_NOPREFIX;

    }

    if ( SS_RIGHT & LOWORD( dwStyle ) ) {

        uFormat |= DT_RIGHT;

    }

    if ( SS_CENTER & LOWORD( dwStyle ) ) {

        uFormat |= ( DT_CENTER | DT_VCENTER );

    }

    DrawText( pPS->hdc, Text.c_str(), Text.size(), &r, uFormat );

    SetBkMode( pPS->hdc, iOldBkMode );
    SetBkColor( pPS->hdc, oldbkcr );
    SetTextColor( pPS->hdc, oldfgcr );

}


HICON Static::OnSetIcon( HWND hWnd, unsigned /* uType */, HICON hNewIcon ) {

    HICON hOldIcon = hIcon;

    hIcon = hNewIcon;

    if ( NULL == hIcon ) {

    } else {

    }

    CalculateRegions();

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    return hOldIcon;

}


void Static::OnNCPaint( HWND hWnd, HRGN hRgn ) {

    HDC hDC = GetDCEx( hWnd, hRgn, DCX_WINDOW | DCX_INTERSECTRGN );

    if ( NULL == hDC ) {

        return;

    }

    RECT r = {0,0,0,0};

    GetWindowRect( hWnd, &r );

    /* Convert from global screen-coordinates to local window-coordinates */
    r.right  = r.right - r.left;
    r.bottom = r.bottom - r.top;
    r.left   = 0;
    r.top    = 0;

    DrawFrame( hDC, r );

    ReleaseDC( hWnd, hDC );

}


LRESULT Static::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Static * pWnd = reinterpret_cast<Static *>( hWnd );

    switch( uiMsg ) {

        case STM_GETICON:

            return (LRESULT)pWnd->hIcon;

        case STM_SETICON:

            return (LRESULT)HANDLE_STM_SETICON( hWnd, wParam, lParam, pWnd->OnSetIcon );

        case WM_NCPAINT:

            HANDLE_WM_NCPAINT( hWnd, wParam, lParam, pWnd->OnNCPaint );
            return 0;

        case WM_PAINT: {

                PAINTSTRUCT ps;

                ZeroMemory( &ps, sizeof( ps ) );

                BeginPaint( hWnd, &ps );

                pWnd->OnPaint( hWnd, &ps );

                EndPaint( hWnd, &ps );

            }
            return 0;

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}


Static::Static( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hInst, LPVOID pParam ) : ywWindow( pWindowClass, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hInst, pParam ) {

    hIcon = NULL;

    if ( NULL == pParam ) {

        return;

    }

    if ( ! (  SS_ICON & Style ) ) {

        return;

    }

    if ( 0 == cx ) {

        /* Set to system default */
        cx = GetSystemMetrics( SM_CXICON );

    }

    if ( 0 == cy ) {

        /* Set to system default */
        cy = GetSystemMetrics( SM_CYICON );

    }

    if ( 0 == HIWORD( pParam ) ) {

        /* Load icon by ordinal */
        hIcon = LoadIcon( hInst, MAKEINTRESOURCE( LOWORD( pParam ) ) );

    } else {

        /* Load icon by dialog template reference */
        hIcon = LoadIcon( hInst, MAKEINTRESOURCE( I386PE_INT16_TO_HOST( pParam ) ) );

    }

    if ( NULL != hIcon ) {

        HICON hOldIcon = Static_SetIcon( this, hIcon );
        DBG_MSG( DBG_GRAPHICAL, TEXT( "New icon set, old icon was %lX" ), hOldIcon );

    }

}
