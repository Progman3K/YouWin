

#include "ywin.h"


BOOL EnableScrollBar( HWND hWnd, UINT uiSBflags, UINT uiArrows ) {

    return true;

}


BOOL GetCurrentPositionEx( HDC hDC, LPPOINT lpPt ) {

    if ( ( NULL == hDC ) || ( NULL == lpPt ) ) {

        return false;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    *lpPt = pDC->ptPen;

    return true;

}


HWND GetDesktopWindow( void ) {

    return g.pTopWnd;

}


DWORD GetLastError( void ) {

    return errno;

}


HGDIOBJ GetStockObject( int nIndex ) {

    switch ( nIndex ) {

        case BLACK_BRUSH:

            return &brBlack;

    }

    return NULL;

}


#if defined( TARGET_OS_MAC )
DWORD GetTickCount( void ) {

    static mach_timebase_info_data_t s_timebase_info;

    if ( 0 == s_timebase_info.denom ) {

        (void)mach_timebase_info( &s_timebase_info );

    }

    // mach_absolute_time() returns billionth of seconds,
    // so divide by one million to get milliseconds
    return ( ( mach_absolute_time() * s_timebase_info.numer ) / ( ( 1000 * 1000 ) * s_timebase_info.denom ) );

}
#else
DWORD GetTickCount( void ) {

    struct timespec ts;

    clock_gettime( CLOCK_MONOTONIC, &ts );

    DWORD   dwTick = ( ts.tv_sec * 1000 ) + ( ts.tv_nsec / 1000000 );

    return dwTick;

}
#endif


BOOL KillTimer( HWND hWnd, UINT_PTR uID ) {

    if ( 0 == uID ) {

        return false;

    }

    timer_key key;

    key.hWnd = hWnd;
    key.uID  = uID;

    TimerList::iterator ret = g.Q.Timers.find( key );

    if ( g.Q.Timers.end() == ret ) {

        DBG_MSG( DBG_ERROR, TEXT( "ATTEMPT TO KILL INEXISTANT TIMER: KillTimer( %lX, %u )" ), hWnd, uID );
        return false;

    }

    g.Q.Timers.erase( ret );

    return true;

}


COLORREF GetPixel( HDC hDC, int iX, int iY ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    POINT pt;

    pt( iX, iY );

    COLORREF c;

    if ( pDC->GetPixel( pt, c ) ) {

        return c;

    }

    return CLR_INVALID;

}


BOOL GetScrollBarInfo( HWND hWnd, LONG lObjectID, PSCROLLBARINFO pSBI ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( NULL == pSBI ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR - BAD PARAMS GetScrollBarInfo( HWND: %lX, LONG: %lX, PSCROLLBARINFO %lX )" ), hWnd, lObjectID, pSBI );
        return false;

    }

    return true;

}


COLORREF SetPixel( HDC hDC, int iX, int iY, COLORREF c ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    POINT pt;

    pt.x = iX;
    pt.y = iY;

    StartPoints();

    if ( pDC->SetPixel( pt, c, c ) ) {

        EndPoints();
        return c;

    }

    EndPoints();

    return -1;

}


BOOL GetTextMetrics( HDC hDC, TEXTMETRIC * pTM ) {

    if ( ( NULL == hDC ) || ( NULL == pTM ) ) {

        return false;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    ZeroMemory( pTM, sizeof( TEXTMETRIC ) );

    if ( NULL == pDC->hFont ) {

        ( reinterpret_cast<ywFont *>( hSystemFont ) )->GetMetrics( pTM );

    } else {

        ( reinterpret_cast<ywFont *>( pDC->hFont ) )->GetMetrics( pTM );

    }

    return true;

}


UINT_PTR SetTimer( HWND hWnd, UINT_PTR uID, UINT uiTimerRefresh, TIMERPROC timerfunc ) {

    UINT_PTR uiRet = 0;

    if ( 0 == uID ) {

        return uiRet;

    }

    MetaMSG Msg;

    Msg.Msg.hwnd    = hWnd;
    Msg.Msg.message = WM_TIMER;
    Msg.Msg.wParam  = uID;
    Msg.Msg.lParam  = (LPARAM)timerfunc;
    Msg.ulInterval  = uiTimerRefresh;
    Msg.lFresh      = GetTickCount() + uiTimerRefresh;

    if ( NULL == hWnd ) {

        /* Create anonymous timer */

        uiRet = g.Q.Timers.GetAnonymousTimerID();

        if ( 0 == uiRet ) {

            /* No more timers */
            return uiRet;

        }

        Msg.Msg.wParam  = uiRet;

        g.Q.Timers.PostTo( hWnd, uiRet, &Msg );

        return uiRet;

    }

    timer_key key;

    key.hWnd = hWnd;
    key.uID  = uID;

    TimerList::iterator ret = g.Q.Timers.find( key );

    if ( g.Q.Timers.end() != ret ) {

        g.Q.Timers.erase( ret );

    }

    g.Q.Timers.PostTo( hWnd, uID, &Msg );

    return uID;

}


BOOL GetClientRect( HWND hWnd, LPRECT pr ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( NULL == pr ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR - BAD PARAMS GetClientRect( %lX, %lX)" ), hWnd, pr );
        return false;

    }

    pr->left   = 0;
    pr->top    = 0;

    pr->right  = pWnd->ClientArea.cx;
    pr->bottom = pWnd->ClientArea.cy;

    return true;

}


BOOL GetWindowRect( HWND hWnd, LPRECT pr ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( NULL == pr ) ) {

        return false;

    }

    POINT pt = pWnd->GetParentOffset();

    pr->left   = pt.x;
    pr->top    = pt.y;

    pr->right  = pr->left + pWnd->cx;
    pr->bottom = pr->top  + pWnd->cy;

    return true;

}


BOOL ScreenToClient( HWND hWnd, LPPOINT pPt ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( NULL == pPt ) ) {

        return false;

    }

    POINT ptClientArea;
    ptClientArea.x = pWnd->ClientArea.x;
    ptClientArea.y = pWnd->ClientArea.y;

    *pPt = *pPt - ( pWnd->GetParentOffset() + ptClientArea );

    return true;

}


BOOL ClientToScreen( HWND hWnd, LPPOINT lpPt ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( NULL == lpPt ) ) {

        return false;

    }

    POINT pt = pWnd->GetParentOffset();

    lpPt->x = lpPt->x + pt.x + pWnd->ClientArea.x;
    lpPt->y = lpPt->y + pt.y + pWnd->ClientArea.y;

    return true;

}


int GetDlgCtrlID( HWND hWnd ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return 0;

    }

    return (int)(long)pWnd->hMenu;

}


HWND GetDlgItem( HWND hDlg, int iCtrlID ) {

    if ( NULL == hDlg ) {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR: GetDlgItem( NULL, %d )" ), iCtrlID );
        return NULL;

    }

    ywWindow * pParentWnd = (ywWindow *)hDlg;
    ywWindow * pWnd = NULL;

    /* Walk the list and for all children of hDlg, return the one ( iCtrlID == hMenu ) */
    for ( auto i = pParentWnd->children.begin(); i != pParentWnd->children.end(); i++ ) {

        if ( ! ( ( (*i)->pParentWnd == hDlg ) && (  reinterpret_cast<long>( ((ywWindow *)(*i))->hMenu ) == iCtrlID ) ) ) {

            continue;

        }

        pWnd = (ywWindow *)(*i);
        break;

    }

    return pWnd;

}


UINT GetDlgItemInt( HWND hDlg, int iCtrlID, BOOL * lpTranslated, BOOL /* bSigned */ ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( GetDlgItem( hDlg, iCtrlID ) );

    if ( ( NULL == pWnd ) || ( 0 == pWnd->Text.size() ) ) {

        if ( NULL != lpTranslated ) {

            *lpTranslated = false;

        }

        return 0;

    }

    TCHAR * pErrChar;

    long lResult = _tcstol( pWnd->Text.c_str(), &pErrChar, 0 );

    if ( pErrChar == pWnd->Text.c_str() ) {

        if ( NULL != lpTranslated ) {

            *lpTranslated = false;

        }

        return 0;

    }

    if ( NULL != lpTranslated ) {

        *lpTranslated = true;

    }

    return (UINT)lResult;

}


BOOL SetDlgItemInt( HWND hDlg, int iCtrlID, UINT uValue, BOOL bSigned ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( GetDlgItem( hDlg, iCtrlID ) );

    if ( NULL == pWnd ) {

        return false;

    }

    TCHAR szNum[128];

    ZeroMemory( szNum, sizeof( szNum ) );

    _sntprintf( szNum, Dim( szNum ) - 1, bSigned ? TEXT( "%d" ) : TEXT( "%u" ), uValue );

    return SetWindowText( (pWnd), szNum );

}


UINT GetDlgItemText( HWND hDlg, int iCtrlID, LPTSTR lpString, int nMaxCount ) {

    HWND hWnd = GetDlgItem( hDlg, iCtrlID );

    if ( NULL == hWnd ) {

        return 0;

    }

    return GetWindowText( hWnd, lpString, nMaxCount );

}


LRESULT SendDlgItemMessage( HWND hDlg, int iCtrlID, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    HWND hWnd = GetDlgItem( hDlg, iCtrlID );

    if ( NULL == hWnd ) {

        return 0;

    }

    return SendMessage( hWnd, uiMsg, wParam, lParam );

}


HWND GetParent( HWND hWnd ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return NULL;

    }

    return pWnd->pParentWnd;

}


BOOL SetDlgItemText( HWND hDlg, int iCtrlID, LPCTSTR lpString ) {

    HWND hChildWnd = GetDlgItem( hDlg, iCtrlID );

    if ( NULL == hChildWnd ) {

        return false;

    }

    return SetWindowText( hChildWnd, lpString );

}


HWND GetFocus( void ) {

    return (HWND)g.pFocusWnd;

}


DWORD CheckMenuItem( HMENU hMenu, UINT uItem, UINT uCheck ) {

    return 0;

}


BOOL DrawMenuBar( HWND hWnd ) {

    return true;

}


BOOL EnableMenuItem( HMENU hMenu, UINT uItem, UINT uEnable ) {

    return true;

}


BOOL SetMenu( HWND hWnd, HMENU hMenu ) {

    return true;

}


HWND FindText( LPFINDREPLACE lpfr ) {

    return NULL;

}


BOOL EnableWindow( HWND hWnd, BOOL bEnable ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    BOOL bRet = ( WS_DISABLED & pWnd->dwStyle );

    FORWARD_WM_ENABLE( hWnd, bEnable, SendMessage );

    return bRet;

}


int EndDialog( HWND hDlg, int iCode ) {

    ywWindow * pWnd = IsWnd( hDlg );

    if ( NULL == pWnd ) {

        return -1;

    }

    if ( NULL != pWnd->piDlgRetCode ) {

        *pWnd->piDlgRetCode = iCode;

    }

    if ( NULL != pWnd->pbClosed ) {

        *pWnd->pbClosed = true;

    }

    //    DestroyWindow( hDlg );

    return 0;

}


HDC BeginPaint( HWND hWnd, PAINTSTRUCT * pPaint ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( hWnd );

    pPaint->rcPaint.left   = 0;
    pPaint->rcPaint.top    = 0;
    pPaint->rcPaint.right  = pWnd->ClientArea.cx;
    pPaint->rcPaint.bottom = pWnd->ClientArea.cy;
    pPaint->hdc            = (HDC)&pWnd->ClientDC;

    if ( pWnd->fErase ) {

        /* Clear the background erase flag */
        pWnd->fErase = FORWARD_WM_ERASEBKGND( hWnd, (HDC)&pWnd->ClientDC, SendMessage );

    }

    pPaint->fErase         = pWnd->fErase;

//  pPaint->fIncUpdate
//  pPaint->fRestore
//  pPaint->rgbReserved

    return (HDC)&pWnd->ClientDC;

}


BOOL EndPaint( HWND hWnd, const PAINTSTRUCT * pPaint ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    pWnd->bDirty = false;

    pWnd->ClientDC.AddExclusion( NULL );
    pWnd->ClientDC.AddIntersection( NULL );

    RasterUpdate();

    return true;

}


COLORREF GetBkColor( HDC hDC ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    return pDC->text.bg;

}


COLORREF SetBkColor( HDC hDC, COLORREF cr ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    COLORREF PreviousValue = pDC->text.bg;

    pDC->text.bg = cr;

    return PreviousValue;

}


int GetBkMode( HDC hDC ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    return pDC->iBkMode;

}


int SetBkMode( HDC hDC, int iMode ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    int iRet = pDC->iBkMode;

    pDC->iBkMode = iMode;

    return iRet;

}


COLORREF SetTextColor( HDC hDC, COLORREF cr ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    COLORREF PreviousValue = pDC->text.fg;

    pDC->text.fg = cr;

    return PreviousValue;

}


COLORREF GetTextColor( HDC hDC ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    return pDC->text.fg;

}


BOOL GetClassInfo( HINSTANCE hInst, LPCTSTR pClassName, WNDCLASS * pWndClass ) {

    WindowClass * pClass = classes.Find( pClassName );

    if ( NULL == pClass ) {

        return false;

    }

    pWndClass->cbClsExtra    = 0;
    pWndClass->cbWndExtra    = 0;
    pWndClass->hbrBackground = pClass->GetBackgroundBrush();
    pWndClass->hCursor       = NULL;
    pWndClass->hIcon         = NULL;
    pWndClass->hInstance     = hInst;
    pWndClass->lpfnWndProc   = pClass->GetWindowProc();
    pWndClass->lpszClassName = pClass->GetClassName();
    pWndClass->lpszMenuName  = NULL;
    pWndClass->style         = pClass->GetClassStyles();

    return true;

}


BOOL IsIconic( HWND hWnd ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    return WS_MINIMIZE & pWnd->dwStyle;

}


int GetClassName( HWND hWnd, LPTSTR lpClassName, int nMaxCount ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( ( NULL == pWnd ) || ( 2 > nMaxCount ) ) {

        return 0;

    }

    return _tcslen( _tcsncpy( lpClassName, pWnd->pClass->GetClassName(), nMaxCount ) );

}


BOOL IsWindowVisible( HWND hWnd ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    for( ;; ) {

        if ( ! ( pWnd->dwStyle & WS_VISIBLE ) ) {

            return false;

        }

        if ( pWnd->bNoRedraw ) {

            return false;

        }

        if ( ( NULL == pWnd->pParentWnd ) || ( HWND_DESKTOP == pWnd->pParentWnd ) ) {

            return true;

        }

        pWnd = reinterpret_cast<ywWindow *>( pWnd->pParentWnd );

    }

}


BOOL IsWindowEnabled( HWND hWnd ) {

    if ( ! IsWindowVisible( hWnd ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "Window not enabled: NOT visible" ) );
        return false;

    }

    IWindow * pWnd = reinterpret_cast<IWindow *>( hWnd );

    IWindow * pPopupOwner = IWindow::GetPopup( pWnd );

    if ( ( NULL != pPopupOwner ) && pPopupOwner->bPopupDisabled ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Window is disabled by popup" ) );
        return false;

    }

    for( ;; ) {

        if ( WS_DISABLED & pWnd->dwStyle ) {

            DBG_MSG( DBG_ERROR, TEXT( "Window is disabled" ) );
            return false;

        }

        if ( ( NULL == pWnd->pParentWnd ) || ( HWND_DESKTOP == pWnd->pParentWnd ) ) {

            return true;

        }

        pWnd = reinterpret_cast<ywWindow *>( pWnd->pParentWnd );

    }

}


BOOL InvertRect( HDC hDC, const RECT * pr ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    StartPoints();

    pDC->Invert( *pr );

    EndPoints();

    return true;

}


BOOL EnumChildWindows( HWND hParentWnd, WNDENUMPROC pEnumFunc, LPARAM lParam ) {

    if ( ! pEnumFunc ) {

        return false;

    }

    IWindow * pWnd;

    if ( 0 == hParentWnd ) {

        pWnd = g.pTopWnd;

    } else {

        pWnd = (IWindow *)hParentWnd;

    }

    for ( auto child = pWnd->children.begin(); child != pWnd->children.end(); child++ ) {

        if ( ! pEnumFunc( *child, lParam ) ) {

            return false;

        }

        /* If the child window has children, enumerate them too */
        if ( ! EnumChildWindows( *child, pEnumFunc, lParam ) ) {

            return false;

        }

    }

    return true;

}


BOOL EnumWindows( WNDENUMPROC pEnumFunc, LPARAM lParam ) {

    BOOL bEnum = false;

    if ( pEnumFunc ) {

        for ( auto popup = g.pTopWnd->children.begin(); popup != g.pTopWnd->children.end(); popup++ ) {

            bEnum = pEnumFunc( *popup, lParam );

            if ( ! bEnum ) {

                return 0;

            }

        }

    }

    return bEnum;

}


BOOL MapDialogRect( HWND hDlg, LPRECT pr ) {

    if ( NULL == pr ) {

        return false;

    }

    if ( ( NULL == hDlg ) || ( HWND_DESKTOP == hDlg ) ) {

//        return false;

    }

    LONG lBaseUnits = GetDialogBaseUnits();

    int iXBaseunit = LOWORD( lBaseUnits );
    int iYBaseunit = HIWORD( lBaseUnits );

    if ( ( 1 == iXBaseunit ) && ( 1 == iYBaseunit ) ) {

        /* Text mode, 1 pixel equals 1 character */
        return true;

    }

    pr->left   = MulDiv( pr->left,   iXBaseunit, 4 );
    pr->right  = MulDiv( pr->right,  iXBaseunit, 4 );
    pr->top    = MulDiv( pr->top,    iYBaseunit, 8 );
    pr->bottom = MulDiv( pr->bottom, iYBaseunit, 8 );

    return true;

}


BOOL InitCommonControlsEx( const LPINITCOMMONCONTROLSEX /* lpInitCtrls */ ) {

    return true;

}


BOOL MessageBeep( UINT /* uType */ ) {

#ifdef YOU_WIN_TXT
    char bell = BEL;
    return g.pTerminal( g.lClientData, &bell, sizeof( bell ) );
#endif

    return true;

}


BOOL LineTo( HDC hDC, int DestX, int DestY ) {

    if ( NULL == hDC ) {

        return false;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    float x = pDC->ptPen.x;
    float y = pDC->ptPen.y;

    float xstep;
    float ystep;

    float cx = ( DestX > x ) ? ( xstep = 1, DestX - x ) : ( xstep = -1, x - DestX );

    float cy = ( DestY > y ) ? ( ystep = 1, DestY - y ) : ( ystep = -1, y - DestY );

    float step;

    if ( cx > cy )  {

        step = ( cy / cx );

        if ( DestY < y ) {

            step = step * -1.0;

        }

        for ( ; xstep > 0 ? x < DestX : x > DestX;  ) {

            SetPixel( hDC, x, y, RGB( 0, 0, 0 ) );

            y += step;

            x += xstep;

        }

    } else {

        step = ( cx / cy );

        if ( DestX < x ) {

            step = step * -1.0;

        }

        for ( ; ystep > 0 ? y < DestY : y > DestY;  ) {

            SetPixel( hDC, x, y, RGB( 0, 0, 0 ) );

            x += step;

            y += ystep;

        }

    }

    /* Update the current pen position */
    pDC->ptPen.x = x;
    pDC->ptPen.y = y;

    return true;

}


BOOL MoveToEx( HDC hDC, int x, int y, LPPOINT lpPt ) {

    if ( NULL == hDC ) {

        return false;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL != lpPt ) {

        *lpPt = pDC->ptPen;

    }

    pDC->ptPen.x = x;
    pDC->ptPen.y = y;

//    if ( ! pDC->In( pt ) ) {

//        return false;

//    }

    return true;

}


BOOL MoveWindow( HWND hWnd, int x, int y, int cx, int cy, BOOL bRepaint ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( hWnd );

    if ( NULL == pWnd ) {

        DBG_MSG( DBG_ERROR, TEXT( "MoveWindow - ERROR: NULL WINDOW HANDLE" ) );
        return false;

    }

    DBG_MSG( DBG_WIN32API, TEXT( "MoveWindow( %s %lX:%ld, %d, %d, %d, %d, %s )" ), pWnd->pClass->GetClassName(), pWnd, pWnd->hMenu, x, y, cx, cy, bRepaint ? "repaint" : "no_repaint" );

    RECT rOldPosition;
    GetWindowRect( hWnd, &rOldPosition );

    pWnd->x  = x;
    pWnd->y  = y;
    pWnd->cx = cx;
    pWnd->cy = cy;

    pWnd->CalculateRegions();

    if ( bRepaint ) {

        UpdateWindow( hWnd );

    }

    /* In any case, repaint what was under the window originally */
    repaint( rOldPosition );

    return true;

}


int MulDiv( int nNumber, int nNumerator, int nDenominator ) {

    long long lResult = nNumber * nNumerator;

    return lResult / nDenominator;

}


HWND SetFocus( HWND hWnd ) {

    if ( g.pFocusWnd == reinterpret_cast<LPWindow>( hWnd ) ) {

        return hWnd;

    }

    if ( ( NULL != hWnd ) && ( ! IsWindow( hWnd ) ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "SetFocus( %lX ) invalid handle" ), hWnd );
        return NULL;

    }

    /* Swap them */
    HWND hOldFocusWnd = (HWND)g.pFocusWnd;
    HWND hOldPopupWnd = IWindow::GetPopup( g.pFocusWnd );

    g.pFocusWnd       = reinterpret_cast<ywWindow *>( hWnd );

    HWND hNewPopupWnd = IWindow::GetPopup( g.pFocusWnd );

    if ( ( NULL != hOldFocusWnd ) && IsWindow( hOldFocusWnd ) ) {

        FORWARD_WM_KILLFOCUS( hOldFocusWnd, hWnd, SendMessage );

        if ( ( NULL != hOldPopupWnd ) && ( hOldPopupWnd != hNewPopupWnd ) ) {

//            RedrawWindow( hOldPopupWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

        }

    }

    if ( NULL != hWnd ) {

        FORWARD_WM_SETFOCUS( hWnd, hOldFocusWnd, SendMessage );

        if ( NULL != hNewPopupWnd ) {

//            RedrawWindow( hNewPopupWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

        }

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Old focus %lX ---> SetFocus( %lX ) - %s, ID - %lu" ), hOldFocusWnd, hWnd, ( reinterpret_cast<LPWindow>( hWnd ) )->pClass->GetClassName(), (unsigned long)( reinterpret_cast<LPWindow>( hWnd ) )->hMenu );

    }

    return hOldFocusWnd;

}


UINT SetTextAlign( HDC hDC, UINT uMode ) {

    if ( NULL == hDC ) {

        return GDI_ERROR;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    UINT uOldMode = pDC->uiTextAlignMode;

    pDC->uiTextAlignMode = uMode;

    return uOldMode;

}


BOOL ShowScrollBar( HWND hWnd, int wBar, BOOL bShow ) {

    ywWindow * pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    switch( wBar ) {

        case SB_BOTH:

            return ShowScrollBar( hWnd, SB_HORZ, bShow ) && ShowScrollBar( hWnd, SB_VERT, bShow );

        case SB_CTL:

            if ( bShow ) {

                ShowWindow( hWnd, SW_SHOW );

            } else {

                ShowWindow( hWnd, SW_HIDE );

            }
            break;

        case SB_HORZ:

            if ( ( bShow && ( pWnd->dwStyle & WS_HSCROLL ) ) || ( ( ! bShow ) && ( 0 == ( pWnd->dwStyle & WS_HSCROLL ) ) ) ) {

                /* Already in the requested state */
                return true;

            }

            if ( bShow ) {

                pWnd->dwStyle |= WS_HSCROLL;

            } else {

                pWnd->dwStyle &= ( ~ WS_HSCROLL );

            }
            break;

        case SB_VERT:

            if ( ( bShow && ( WS_VSCROLL & pWnd->dwStyle ) ) || ( ( ! bShow ) && ( 0 == ( WS_VSCROLL & pWnd->dwStyle ) ) ) ) {

                /* Already in the requested state */
                return true;

            }

            if ( bShow ) {

                pWnd->dwStyle |= WS_VSCROLL;

            } else {

                pWnd->dwStyle &= ( ~ WS_VSCROLL );

            }
            break;

        default:

            return false;


    }

    pWnd->CalculateRegions();

    RedrawWindow( hWnd, NULL, NULL,  RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );
    return true;

}


void PostQuitMessage( int nExitCode ) {

    MetaMSG Msg;

    Msg.Msg.hwnd    = NULL;
    Msg.Msg.message = WM_QUIT;
    Msg.Msg.wParam  = nExitCode;
    Msg.Msg.lParam  = 0;

    g.Q.PostToQ( g.Q.MsgQ, &Msg );

}


BOOL UpdateWindow( HWND hWnd ) {

    return RedrawWindow( hWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

}


void ZeroMemory( void * p, unsigned long size ) {

    memset( p, '\0', size );

}


int ImageList_ReplaceIcon( HIMAGELIST hImages, int i, HICON hicon ) {

    return -1;

}


HIMAGELIST ImageList_Create( int cx, int cy, UINT flags, int cInitial, int cGrow ) {

    return NULL;

}


BOOL GdiGradientFill( HDC hDC, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nMesh, ULONG ulMode ) {

    return false;

}
