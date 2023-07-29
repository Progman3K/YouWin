

#include "ywin.h"


HWND GetNextDlgTabItem( HWND hDlg, HWND hCtlWnd, BOOL bPrevious ) {

    if ( ( NULL == hDlg ) || ( NULL == hCtlWnd ) ) {

        return NULL;

    }

    return (HWND)IWindow::GetNextTabstop( reinterpret_cast<IWindow *>( hDlg ), reinterpret_cast<IWindow *>( hCtlWnd ), ! bPrevious );

}


void Dialog::OnChar( HWND hDlg, UINT ch, int cRepeat ) {

    if ( NULL != g.pFocusWnd ) {

        FORWARD_WM_CHAR( (HWND)g.pFocusWnd, ch, cRepeat, SendMessage );

    } else {

        DBG_MSG( DBG_ERROR, TEXT( "INPUT LOST" ) );

    }

}


//     void Cls_OnKey( HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags );
void Dialog::OnKeydown( HWND hDlg, UINT vk, BOOL fDown, int cRepeat, UINT flags ) {

    /* Check for special keys */
    switch( vk ) {

        HWND hCtlWnd;

        case VK_ESCAPE: /* User pressed ESC */

            hCtlWnd = GetDlgItem( hDlg, IDCANCEL );

            FORWARD_WM_COMMAND( hDlg, IDCANCEL, hCtlWnd, BN_CLICKED, SendMessage );
            break;

        case VK_BACKTAB: /* User pressed SHIFT-TAB */
        case VK_TAB: /* User pressed TAB */

            if (

            ( NULL != ( hCtlWnd = (HWND)GetNextTabstop( reinterpret_cast<LPWindow>( hDlg ), g.pFocusWnd, VK_TAB == vk ) ) ) ||
            ( NULL != ( hCtlWnd = (HWND)GetTabstop( reinterpret_cast<LPWindow>( hDlg ), VK_TAB == vk ) ) )

            ) {

                SetFocus( hCtlWnd );

            }
            break;

        case VK_RETURN: {

                Window * pWnd;

                pWnd = reinterpret_cast<Window *>( GetFocus() );

                if ( NULL != pWnd ) {

                    if ( Button::WndProc == pWnd->pClass->GetWindowProc() ) {

                        /* Send a click message. */
                        FORWARD_WM_COMMAND( hDlg, (unsigned long)pWnd->hMenu, (HWND)pWnd, BN_CLICKED, SendMessage );
                        return;

                    }

#if 0
                    if ( ! ( ( Edit::WndProc == pWnd->pClass->GetWindowProc() ) && ( ES_WANTRETURN & pWnd->dwStyle ) ) ) {

                        /* Find the default pushbutton and send a click message. */
                        return;

                    }
                    /* It's an edit and has the ES_WANTRETURN style, do nothing. */
#endif

                }

            }

            /* FALLS THROUGH HERE */

        default:

            /* Not a special key */

            if ( ( NULL != g.pFocusWnd ) && ( hDlg != g.pFocusWnd ) ) {

                FORWARD_WM_KEYDOWN( (HWND)g.pFocusWnd, vk, cRepeat, flags, SendMessage );

            } else {

                DBG_MSG( DBG_ERROR, TEXT( "INPUT LOST" ) );

            }

    }

}


LRESULT Dialog::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CHAR:

            HANDLE_WM_CHAR( hWnd, wParam, lParam, OnChar );
            break;

        case WM_KEYDOWN:

            HANDLE_WM_KEYDOWN( hWnd, wParam, lParam, OnKeydown );
            return 0;

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}


LRESULT DefDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    return (reinterpret_cast<Dialog *>( hWnd ))->WndProc( hWnd, uiMsg, wParam, lParam );

}
