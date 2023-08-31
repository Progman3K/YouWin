

#include "ywin.h"


BOOL TranslateMessage( const MSG * pMsg ) {

    return false;

}


static void OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCLBUTTONDOWN( hWnd, bDblClick, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_LBUTTONDOWN( hWnd, bDblClick, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnLButtonUp( HWND hWnd, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCLBUTTONUP( hWnd, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_LBUTTONUP( hWnd, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnMButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCMBUTTONDOWN( hWnd, bDblClick, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_MBUTTONDOWN( hWnd, bDblClick, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnMButtonUp( HWND hWnd, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCMBUTTONUP( hWnd, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_MBUTTONUP( hWnd, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnMouseMove( HWND hWnd, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    /* Ask whether it is in the non-client or not */
    unsigned uHT = FORWARD_WM_NCHITTEST( hWnd, x, y, SendMessage );

    if ( HTCLIENT == uHT ) {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_MOUSEMOVE( hWnd, pt.x, pt.y, uiKeyFlags, SendMessage );

    } else {

        FORWARD_WM_NCMOUSEMOVE( hWnd, x, y, uHT, SendMessage );

    }

}


static void OnRButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCRBUTTONDOWN( hWnd, bDblClick, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_RBUTTONDOWN( hWnd, bDblClick, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnRButtonUp( HWND hWnd, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCRBUTTONUP( hWnd, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_RBUTTONUP( hWnd, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnXButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCXBUTTONDOWN( hWnd, bDblClick, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_XBUTTONDOWN( hWnd, bDblClick, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static void OnXButtonUp( HWND hWnd, int x, int y, UINT uiKeyFlags ) {

    /* Ask whether it is in the non-client or not */
    POINT pt;

    pt.x = x;
    pt.y = y;

    if ( ! ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.IsEmpty() && ( reinterpret_cast<ywWindow *>( hWnd ) )->NonClientArea.PtIn( pt ) ) {

        /* This is a click in the non-client area. */
        FORWARD_WM_NCXBUTTONUP( hWnd, x, y, uiKeyFlags, SendMessage );

    } else {

        pt = pt - ( reinterpret_cast<ywWindow *>( hWnd ) )->GetParentOffset();

        FORWARD_WM_XBUTTONUP( hWnd, pt.x, pt.y, uiKeyFlags, SendMessage );

    }

}


static IWindow * WindowAt( IWindow * pParentWnd, POINT * pPt ) {

    IWindow * pWnd = NULL;

    if ( pParentWnd->bPointInWindow( *pPt ) ) {

        pWnd = pParentWnd;

    }

    /* Check if it's within one of its popups */
    for ( auto child = pParentWnd->children.rbegin(); child != pParentWnd->children.rend(); child++ ) {

        /* Last popup is highest in the Z order */
        IWindow * pChildWnd = WindowAt( *child, pPt );

        if ( ! pChildWnd ) {

            continue;

        }

        pWnd = pChildWnd;
        break;

    }

    return pWnd;

}


LRESULT DispatchMessage( const MSG * pMsg ) {

    switch( pMsg->message ) {

        case WM_TIMER:

            if ( 0 != pMsg->lParam ) {

                /* Call timerproc */
                ((TIMERPROC)(pMsg->lParam))( pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );
                return 0;

            } /* else treat as default: */

    }

    if ( NULL == pMsg->hwnd ) {

        /* Destination for raw mouse input must be resolved here */
        POINT pt;

        pt.x = GET_X_LPARAM( pMsg->lParam );
        pt.y = GET_Y_LPARAM( pMsg->lParam );

        IWindow * pWnd = WindowAt( g.pTopWnd, &pt );

        if ( NULL == pWnd ) {

            // DBG_MSG( DBG_ERROR, TEXT( "Could not find any visible, non-disabled window at (%d,%d), mouse message ignored" ), x, y );
            MessageBeep( MB_BEEP );
            return -1;

        }

        switch ( pMsg->message ) {

            case WM_LBUTTONDOWN: /* Can turn into WM_NCLBUTTONDOWN */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_LBUTTONDOWN( pWnd, pMsg->wParam, pMsg->lParam, OnLButtonDown );
                return 0;

            case WM_LBUTTONUP: /* Can turn into WM_NCLBUTTONUP */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_LBUTTONUP( pWnd, pMsg->wParam, pMsg->lParam, OnLButtonUp );
                return 0;

            case WM_MBUTTONDOWN: /* Can turn into WM_NCMBUTTONDOWN */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_MBUTTONDOWN( pWnd, pMsg->wParam, pMsg->lParam, OnMButtonDown );
                return 0;

            case WM_MBUTTONUP: /* Can turn into WM_NCMBUTTONUP */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_MBUTTONUP( pWnd, pMsg->wParam, pMsg->lParam, OnMButtonUp );
                return 0;

            case WM_MOUSEMOVE: /* Can turn into WM_NCMOUSEMOVE */

                HANDLE_WM_MOUSEMOVE( pWnd, pMsg->wParam, pMsg->lParam, OnMouseMove );
                return 0;

            case WM_RBUTTONDOWN: /* Can turn into WM_NCRBUTTONDOWN  */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_RBUTTONDOWN( pWnd, pMsg->wParam, pMsg->lParam, OnRButtonDown );
                return 0;

            case WM_RBUTTONUP: /* Can turn into WM_NCRBUTTONUP */

                if ( ! IsWindowEnabled( (HWND)pWnd ) ) {

                    return 0;

                }
                HANDLE_WM_RBUTTONUP( pWnd, pMsg->wParam, pMsg->lParam, OnRButtonUp );
                return 0;

            case WM_XBUTTONDOWN:

                HANDLE_WM_XBUTTONDOWN( pWnd, pMsg->wParam, pMsg->lParam, OnXButtonDown );
                return 0;

            case WM_XBUTTONUP:

                HANDLE_WM_XBUTTONUP( pWnd, pMsg->wParam, pMsg->lParam, OnXButtonUp );
                return 0;

            default:
                DBG_MSG( DBG_ERROR, TEXT( "FAILED DELIVERY OF MESSAGE FOR NULL WINDOW" ) );
                TRACE_MESSAGE( DBG_ERROR, pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );
                return 0;

        }

//        DBG_MSG( DBG_ERROR, TEXT( "FAILED DELIVERY OF MESSAGE FOR NULL WINDOW" ) );
//        TRACE_MESSAGE( DBG_ERROR, pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );
//        return 0;

    }

    return SendMessage( pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );

}


int GetMessage( MSG * pMsg, HWND hWnd, UINT uMsgFilterMin, UINT uMsgFilterMax ) {

    if ( g.Q.Quit() ) {

        return 0;

    }

    if ( ( 0 != hWnd ) && ( NULL == IsWnd( hWnd ) ) ) {

        return -1;

    }

    PostRefresh();
    RasterUpdate();

    int iRet = g.Q.Read( pMsg );

    if ( -1 == iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "select returns %d:%s" ), iRet, strerror( errno ) );

    }

    if ( WM_QUIT == pMsg->message ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WM_QUIT code %d" ), iRet );
        return 0;

    }

    return iRet;

}
