

#include "ywin.h"


static Click rightclick;


typedef struct {

    IWindow * pParentWnd;
    IWindow * pWnd;

} NextChild;


static BOOLEAN EnumChildren( IWindow * pWnd, LPARAM lParam ) {

    NextChild * pNext = (NextChild *)lParam;

    if ( pWnd->pParentWnd != pNext->pParentWnd ) {

        return true;

    }

    pNext->pWnd = pWnd;

    return false;


}


static void RemoveNode( Window * pWnd ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Removing window %lX from linked-list" ), pWnd );

    if ( pWnd->pPrevSiblingWnd ) {

        // NOT the topmost window. Change IT'S next pointer to MY next pointer.
        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "NOT the topmost window. Change IT'S next pointer to MY next pointer %lX" ), pWnd->pNextSiblingWnd );
        pWnd->pPrevSiblingWnd->pNextSiblingWnd = pWnd->pNextSiblingWnd;

    }

    if ( pWnd->pNextSiblingWnd ) {

        // NOT the bottommost window. Change IT'S previous pointer to MY previous pointer.
        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "NOT the bottommost window. Change IT'S previous pointer to MY previous pointer %lX" ), pWnd->pPrevSiblingWnd );
        pWnd->pNextSiblingWnd->pPrevSiblingWnd = pWnd->pPrevSiblingWnd;

    }

}


void Window::OnDestroy( HWND hWnd ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Window %lX: delete child controls..." ), hWnd );

    bNoRedraw = true;

    int iEnum;

    NextChild   Child;

    Child.pParentWnd = reinterpret_cast<LPWindow>( hWnd );

    // Remove it from the linked list.
    RemoveNode( this );

    for ( ;; ) {

        Child.pWnd = NULL;

        iEnum = iEnumWindows( EnumChildren, true, reinterpret_cast<IWindow *>( hWnd ), (LPARAM)&Child );

        if ( NULL == Child.pWnd ) {

            break;

        }

        /* Since we are NOT in an enumeration the list is NOT being walked and cannot go bad, process the deletetions synchronously. */
        FORWARD_WM_DESTROY( (HWND)Child.pWnd, SendMessage );

//        DestroyWindow( (HWND)Child.lpWnd ); 

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Window %lX: delete child controls ended code %d" ), hWnd, iEnum );

//    ShowWindow( hWnd, SW_HIDE );


    if ( GetFocus() == this ) {

        DBG_MSG( DBG_ERROR, TEXT( "FOCUS LOST" ) );
        g.pFocusWnd = NULL;

    }

    if ( NULL != pbClosed ) {

        *pbClosed = true;

    }

    pClass->Discard( this );

}


void Window::OnEnable( HWND hWnd, BOOL bEnable ) {

    if ( bEnable ) {

        /* Turn off WS_DISABLED */

        if ( ! ( WS_DISABLED & dwStyle ) ) {

            /* Already enabled, done. */
            return;

        }

        dwStyle &= ( ~ WS_DISABLED );

    } else {

        /* Turn on WS_DISABLED */

        if ( WS_DISABLED & dwStyle ) {

            /* Already disabled, done. */
            return;

        }

        dwStyle |= WS_DISABLED;

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

}


void Window::OnSetText( HWND hWnd, LPCTSTR lpszText ) {

    Text.assign( lpszText );

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

}


void Window::OnMouseClicks( HWND hWnd, BOOLEAN bDblClick, int userx, int usery, UINT uiKeyFlags ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Mouse %sclick at (%d,%d) flags %X" ), bDblClick ? "double" : "", userx, usery, uiKeyFlags );

    if ( bDblClick ) {

        return;

    }

    DWORD dwWhen = GetTickCount();

    POINT pt;

    pt.x = userx;
    pt.y = usery;

    /* For those with the class style CS_DBLCLCK, check if we received a click within the timeout period. */
    if ( CS_DBLCLKS & pClass->GetClassStyles() ) {

        if ( ( rightclick.hWnd == hWnd ) && ( dwWhen <= rightclick.dwWhen + GetDoubleClickTime() ) ) {

            RECT r;

            r.left   = rightclick.pt.x - ( GetSystemMetrics( SM_CXDOUBLECLK ) / 2 );
            r.right  = rightclick.pt.x + ( GetSystemMetrics( SM_CXDOUBLECLK ) / 2 );
            r.top    = rightclick.pt.y - ( GetSystemMetrics( SM_CYDOUBLECLK ) / 2 );
            r.bottom = rightclick.pt.y + ( GetSystemMetrics( SM_CYDOUBLECLK ) / 2 );

            if ( PtInRect( &r, pt ) ) {

                rightclick.reset();

                /* User double-clicked, generate notification */
                FORWARD_WM_LBUTTONDOWN( hWnd, true, userx, usery, uiKeyFlags, SendMessage );

            } else {

                rightclick.hWnd   = hWnd;
                rightclick.dwWhen = dwWhen;
                rightclick.pt     = pt;

            }

        } else {

            rightclick.hWnd   = hWnd;
            rightclick.dwWhen = dwWhen;
            rightclick.pt     = pt;

        }

    } else {

        rightclick.hWnd   = hWnd;
        rightclick.dwWhen = dwWhen;
        rightclick.pt     = pt;

    }

    if ( ! CanAcceptFocus() ) {

        DBG_MSG( DBG_ERROR, TEXT( "Can't accept focus" ) );
        return;

    }

    if ( GetFocus() != hWnd ) {

        SetFocus( hWnd );

    }

}


void Window::OnNCMouseClicks( HWND hWnd, BOOLEAN bDblClick, int userx, int usery, UINT uiKeyFlags ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Non-client mouse %sclick at (%d,%d) flags %X" ), bDblClick ? "double" : "", userx, usery, uiKeyFlags );

//    DWORD dwWhen = GetTickCount();

    POINT pt;

    pt( userx, usery );

    pt = pt - GetParentOffset();

    /* This is a click in the non-client area. */

    if ( PtInRect( &vscrollArea, pt ) ) {

        // It's in the vertical scrollbar
        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "vertical scrollbar hit" ) );

        if ( PtInRect( &vscrollThumbTop, pt ) ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_VSCROLL SB_LINEUP" ) );
            FORWARD_WM_VSCROLL( hWnd, NULL, SB_LINEUP, 0, SendMessage );

        } else if ( PtInRect( &vscrollThumbBottom, pt ) ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_VSCROLL SB_LINEDOWN" ) );
            FORWARD_WM_VSCROLL( hWnd, NULL, SB_LINEDOWN, 0, SendMessage );

        } else {

            /* Somewhere in the middle */
            long range = vscrollMiddle.bottom - vscrollMiddle.top;
            long pos   = pt.y - vscrollMiddle.top;

            if ( pos > ( range / 2 ) ) {

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_VSCROLL SB_PAGEDOWN" ) );
                FORWARD_WM_VSCROLL( hWnd, NULL, SB_PAGEDOWN, 0, SendMessage );

            } else {

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_VSCROLL SB_PAGEUP" ) );
                FORWARD_WM_VSCROLL( hWnd, NULL, SB_PAGEUP, 0, SendMessage );

            }

        }

    } else if ( PtInRect( &hscrollArea, pt ) ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "horizontal scrollbar hit" ) );

        if ( PtInRect( &hscrollThumbLeft, pt ) ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_HSCROLL SB_LINELEFT" ) );
            FORWARD_WM_HSCROLL( hWnd, NULL, SB_LINELEFT, 0, SendMessage );

        } else if ( PtInRect( &hscrollThumbRight, pt ) ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_HSCROLL SB_LINERIGHT" ) );
            FORWARD_WM_HSCROLL( hWnd, NULL, SB_LINERIGHT, 0, SendMessage );

        } else {

            /* Somewhere in the middle */
            long range = hscrollMiddle.right - hscrollMiddle.left;
            long pos   = pt.x - hscrollMiddle.left;

            if ( pos > ( range / 2 ) ) {

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_HSCROLL SB_PAGERIGHT" ) );
                FORWARD_WM_HSCROLL( hWnd, NULL, SB_PAGERIGHT, 0, SendMessage );

            } else {

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_HSCROLL SB_PAGELEFT" ) );
                FORWARD_WM_HSCROLL( hWnd, NULL, SB_PAGELEFT, 0, SendMessage );

            }

        }

    }

}


typedef enum {

    triangle_point_up,
    triangle_point_right,
    triangle_point_down,
    triangle_point_left

} triangle_orientation;


void DrawTriangle( HDC hDC, triangle_orientation orientation, const RECT & r2, HBRUSH hBR ) {

    RECT rLine;
    RECT r;

    r = r2;

    long ColCount = r.right - r.left;
    long LinCount = r.bottom - r.top;

    switch( orientation ) {

        case triangle_point_right:

            r.left   += ( ( GetSystemMetrics( SM_CXHTHUMB ) / 4 ) + ( GetSystemMetrics( SM_CXBORDER ) * 2 ) );
            r.top    += GetSystemMetrics( SM_CYBORDER ) * 2;
            r.bottom -= GetSystemMetrics( SM_CYBORDER ) * 2;

            for ( long y = 0; y < ColCount; y++ ) {

                rLine.left   = r.left     + y;
                rLine.right  = rLine.left + 1;

                rLine.top    = r.top    + y;
                rLine.bottom = r.bottom - y;

                FillRect( hDC, &rLine, hBR );

            }
            break;

        case triangle_point_left:

            r.right  -= ( ( GetSystemMetrics( SM_CXHTHUMB ) / 4 ) + ( GetSystemMetrics( SM_CXBORDER ) * 2 ) );
            r.top    += GetSystemMetrics( SM_CYBORDER ) * 2;
            r.bottom -= GetSystemMetrics( SM_CYBORDER ) * 2;

            for ( long y = 0; y < ColCount; y++ ) {

                rLine.right  = r.right     - y;
                rLine.left   = rLine.right - 1;

                rLine.top    = r.top    + y;
                rLine.bottom = r.bottom - y;

                FillRect( hDC, &rLine, hBR );

            }
            break;

        case triangle_point_up:

            r.bottom -= ( ( GetSystemMetrics( SM_CYVTHUMB ) / 4 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 ) );
            r.left   += GetSystemMetrics( SM_CXBORDER ) * 2;
            r.right  -= GetSystemMetrics( SM_CXBORDER ) * 2;

            for ( long y = 0; y < LinCount; y++ ) {

                rLine.left   = r.left    + y;
                rLine.right  = r.right   - y;

                rLine.top    = r.bottom  - y;
                rLine.bottom = rLine.top + 1;

                FillRect( hDC, &rLine, hBR );

            }
            break;

        case triangle_point_down:

            r.top   += ( ( GetSystemMetrics( SM_CYVTHUMB ) / 4 ) + ( GetSystemMetrics( SM_CXBORDER ) * 2 ) ) ;
            r.left  += GetSystemMetrics( SM_CXBORDER ) * 2;
            r.right -= GetSystemMetrics( SM_CXBORDER ) * 2;

            for ( long y = 0; y < LinCount; y++ ) {

                rLine.left   = r.left    + y;
                rLine.right  = r.right   - y;

                rLine.top    = r.top     + y;
                rLine.bottom = rLine.top + 1;

                FillRect( hDC, &rLine, hBR );

            }
            break;

    }

}


void Window::DrawScrollBar( HDC hDC, bool bHorizontal, SCROLLBARINFO * pSBInfo ) {

    SolidBrush brScrollbar( SysColorScrollbar.GetColor(), true );
    SolidBrush brArrow( SysColorBtnText.GetColor(), true );

    if ( bHorizontal ) {

        /* Left */
        FillRect( hDC, &hscrollThumbLeft, (HBRUSH)&brScrollbar );
        DrawTriangle( hDC, triangle_point_left, hscrollThumbLeft, (HBRUSH)&brArrow );
        DrawEdge( hDC, &hscrollThumbLeft, BDR_RAISEDOUTER, BF_RECT );

        /* Right */
        FillRect( hDC, &hscrollThumbRight, (HBRUSH)&brScrollbar );
        DrawTriangle( hDC, triangle_point_right, hscrollThumbRight, (HBRUSH)&brArrow );
        DrawEdge( hDC, &hscrollThumbRight, BDR_RAISEDOUTER, BF_RECT );

        /* Middle */
        FillRect( hDC, &hscrollMiddle, (HBRUSH)&brScrollbar );
        DrawEdge( hDC, &hscrollMiddle, BDR_SUNKENINNER, BF_RECT );

    } else { /* vertical */

        /* Top */
        FillRect( hDC, &vscrollThumbTop, (HBRUSH)&brScrollbar );
        DrawTriangle( hDC, triangle_point_up, vscrollThumbTop, (HBRUSH)&brArrow );
        DrawEdge( hDC, &vscrollThumbTop, BDR_RAISEDOUTER, BF_RECT );

        /* Bottom */
        FillRect( hDC, &vscrollThumbBottom, (HBRUSH)&brScrollbar );
        DrawTriangle( hDC, triangle_point_down, vscrollThumbBottom, (HBRUSH)&brArrow );
        DrawEdge( hDC, &vscrollThumbBottom, BDR_RAISEDOUTER, BF_RECT );

        /* Middle section */
        FillRect( hDC, &vscrollMiddle, (HBRUSH)&brScrollbar );
        DrawEdge( hDC, &vscrollMiddle, BDR_SUNKENINNER, BF_RECT );

    }

}


void Window::OnNCPaint( HWND hWnd, HRGN hRgn ) {

    HDC hDC = GetDCEx( hWnd, hRgn, DCX_WINDOW | DCX_INTERSECTRGN );

    if ( NULL == hDC ) {

        return;

    }

    RECT r = {0,0,0,0};

    int iXthickframe = 0;
    int iYthickframe = 0;

    if ( WS_THICKFRAME & dwStyle ) {

        iXthickframe = GetSystemMetrics( SM_CXSIZEFRAME );
        iYthickframe = GetSystemMetrics( SM_CYSIZEFRAME );

    }

    if ( WS_BORDER & dwStyle ) {

        SolidBrush br3DShadow( SysColor3DShadow.GetColor(), true ), br3DHiLight( SysColor3DHighLight.GetColor(), true );

        // Left side line
        r.left   = 0;
        r.top    = 0;

        r.right  = iXthickframe + GetSystemMetrics( SM_CXBORDER );
        r.bottom = cy;

        FillRect( hDC, &r, (HBRUSH)&br3DHiLight /* br3DShadow */ );

        // Top line
        r.left   = 0;
        r.top    = 0;

        r.right  = cx;
        r.bottom = iYthickframe + GetSystemMetrics( SM_CYBORDER );

        FillRect( hDC, &r, (HBRUSH)&br3DHiLight /* br3DShadow */ );

        // Right side line
        r.left   = cx - ( iXthickframe + GetSystemMetrics( SM_CXBORDER ) ) ;
        r.top    = iYthickframe + GetSystemMetrics( SM_CYBORDER );

        r.right  = cx;
        r.bottom = cy;

        FillRect( hDC, &r, (HBRUSH)&br3DShadow /* br3DHiLight */ );

        // Bottom line
        r.left   = iXthickframe + GetSystemMetrics( SM_CXBORDER );
        r.top    = cy - ( iYthickframe + GetSystemMetrics( SM_CYBORDER ) );

        r.right  = cx;
        r.bottom = cy;

        FillRect( hDC, &r, (HBRUSH)&br3DShadow /* br3DHiLight */ );

        /* Final edge */
        r.left   = 0;
        r.top    = 0;
        r.right  = cx;
        r.bottom = cy;

        DrawEdge( hDC, &r, BDR_RAISEDOUTER /* BDR_SUNKENOUTER */, BF_RECT );

    }

    if ( ( WS_CAPTION & dwStyle ) == WS_CAPTION ) {

        COLORREF cCaption;
        bool     bActive;

        if ( ( NULL != GetFocus() ) && ( GetPopup( reinterpret_cast<Window *>( GetFocus() ) ) == this ) ) {

            bActive  = true;
            cCaption = SysColorActiveCaption.GetColor();

        } else {

            bActive  = false;
            cCaption = SysColorInactiveCaption.GetColor();

        }

        SolidBrush brCaption( cCaption, true );

        FillRect( hDC, &rCaption, (HBRUSH)&brCaption );

        COLORREF oldbkcr = SetBkColor( hDC, bActive ? GetSysColor( COLOR_ACTIVECAPTION ) : GetSysColor( COLOR_INACTIVECAPTION ) );
        COLORREF oldfgcr = SetTextColor( hDC, GetSysColor( COLOR_CAPTIONTEXT ) );
        int iOldBkMode   = SetBkMode( hDC, TRANSPARENT );

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Draw caption in rect (%d,%d,%d,%d)" ), r.left, r.top, r.right, r.bottom );

        DrawText( hDC, Text.c_str(), Text.size(), &rCaption, DT_CENTER | DT_SINGLELINE );

        SetBkMode( hDC, iOldBkMode );
        SetBkColor( hDC, oldbkcr );
        SetTextColor( hDC, oldfgcr );

    }

    if ( WS_HSCROLL & dwStyle ) {

        DrawScrollBar( hDC, true, NULL );

        if ( WS_VSCROLL & dwStyle ) {

            SolidBrush brScrollbar( SysColorScrollbar.GetColor(), true );

            FillRect( hDC, &rthumb, (HBRUSH)&brScrollbar );

        }

    }

    if ( WS_VSCROLL & dwStyle ) {

        DrawScrollBar( hDC, false, NULL );

    }

    ReleaseDC( hWnd, hDC );

}


/* THIS FUNCTION IS A STOP-GAP METHOD AS EACH CLASS DEFINES ITS DRAWING METHOD; NO ONE IS EVER EXPECTED TO CALL THIS */
static bool OnPaint( HWND hWnd ) {

    PAINTSTRUCT ps;

    ZeroMemory( &ps, sizeof( ps ) );

    BeginPaint( hWnd, &ps );

    EndPaint( hWnd, &ps );

    // TEMPORARY
    return true;

}


bool Window::OnEraseBackground( HWND hWnd, HDC hDC ) {

    HBRUSH  hbr;

    if ( NULL == ( hbr = pClass->GetBackgroundBrush() ) ) {

        /* Transparent background */
        return true;

    }

    RECT r;

    if ( GetClientRect( hWnd, &r ) ) {

        FillRect( hDC, &r, hbr );

    }

    return true;

}


#ifdef YOU_WIN_TXT
static void OnSetfocus( HWND hWnd, HWND hOldfocuswnd ) {

    Window * pWnd = reinterpret_cast<LPWindow>( hWnd );

    /* Hack to temporarily SEE the focus change */
    POINT pt = pWnd->GetParentOffset();

    gotoxy( pt.x + 1, pt.y + 1 );

}
#endif


void Window::OnSetRedraw( HWND hWnd, BOOL bRedraw ) {

    bNoRedraw = ! bRedraw;

    if ( bRedraw && ( ! ( WS_VISIBLE & dwStyle ) ) ) {

        dwStyle |= WS_VISIBLE;

//        RedrawWindow( hWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    }

}


UINT Window::OnNCHitTest( HWND hWnd, int absx, int absy ) {

    // x and y are relative to upper-left of the screen, not relative to the window

    POINT pt;

    pt.x = absx;
    pt.y = absy;

    pt = pt - GetParentOffset();

    if ( ClientArea.PtIn( pt ) ) {

        return HTCLIENT;

    }

    if ( ! NonClientArea.PtIn( pt ) ) {

        return HTNOWHERE;

    }

    if ( PtInRect( &rCaption, pt ) ) {

        return HTCAPTION;

    }

    if ( PtInRect( &vscrollArea, pt ) ) {

        return HTVSCROLL;

    }

    if ( PtInRect( &hscrollArea, pt ) ) {

        return HTHSCROLL;

    }

    return HTBORDER; // HTERROR;

}


LRESULT Window::DefWndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CHARTOITEM:

            return -1;

        case WM_CLOSE:

            FORWARD_WM_DESTROY( hWnd, PostMessage );
            break;

        case WM_DESTROY:

            HANDLE_WM_DESTROY( hWnd, wParam, lParam, OnDestroy );
            break;

        case WM_DISPLAYCHANGE:

            RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );
            break;

        case WM_ENABLE:

            HANDLE_WM_ENABLE( hWnd, wParam, lParam, OnEnable );
            break;

        case WM_ERASEBKGND:

            return HANDLE_WM_ERASEBKGND( hWnd, wParam, lParam, OnEraseBackground );

        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:

            if ( ! IsWindowEnabled( hWnd ) ) {

                DBG_MSG( DBG_ERROR, TEXT( "Window disabled" ) );
                MessageBeep( MB_BEEP );
                break;

            }

            HANDLE_WM_LBUTTONDOWN( hWnd, wParam, lParam, OnMouseClicks );
            break;

        case WM_NCLBUTTONDBLCLK:
        case WM_NCLBUTTONDOWN:
        case WM_NCMBUTTONDOWN:
        case WM_NCRBUTTONDOWN:

            HANDLE_WM_NCLBUTTONDOWN( hWnd, wParam, lParam, OnNCMouseClicks );
            break;

        case WM_NCCREATE:

            return true;

        case WM_NCHITTEST:

            return HANDLE_WM_NCHITTEST( hWnd, wParam, lParam, OnNCHitTest );

        case WM_NCPAINT:

            HANDLE_WM_NCPAINT( hWnd, wParam, lParam, OnNCPaint );
            break;

        case WM_PAINT:

            return OnPaint( hWnd );

#ifdef YOU_WIN_TXT
        case WM_SETFOCUS:

            HANDLE_WM_SETFOCUS( hWnd, wParam, lParam, OnSetfocus );
            break;
#endif

        case WM_SETREDRAW:

            HANDLE_WM_SETREDRAW( hWnd, wParam, lParam, OnSetRedraw );
            break;

        case WM_SETTEXT:

            HANDLE_WM_SETTEXT( hWnd, wParam, lParam, OnSetText );
            return true;

        case WM_VKEYTOITEM:

            return -1;

    }

    return 0;

}


LRESULT DefWindowProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    return (reinterpret_cast<Window *>( hWnd ))->DefWndProc( hWnd, uiMsg, wParam, lParam );

}
