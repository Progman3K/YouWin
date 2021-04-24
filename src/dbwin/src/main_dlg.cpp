

#include "dbwin.h"


extern "C" BOOL CMainDlg::bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    BOOL bRet;

    switch( uiMsg ) {

    case WM_COMMAND:

        HANDLE_WM_COMMAND( hDlg, wParam, lParam, OnCommand );
        break;

    case WM_COPYDATA:

        bRet = HANDLE_WM_COPYDATA( hDlg, wParam, lParam, bOnCopyData );
        return bRet;

    case WM_DESTROY:

        HANDLE_WM_DESTROY( hDlg, wParam, lParam, OnDestroy );
        break;

#ifdef _WIN32_WCE
    case WM_GETICON:

        SetDlgMsgResult( hDlg, WM_GETICON, (HICON)LoadImage( g_hInst, ID( IDI_MAIN ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR ) );
        break;
#endif /* _WIN32_WCE */

    case WM_INITDIALOG:

        bRet = (BOOL)HANDLE_WM_INITDIALOG( hDlg, wParam, lParam, bOnInit );

        if ( ! bRet ) {

            EndDialog( hDlg, -1 );

        }
        break;

    case WM_INITMENUPOPUP:

        HANDLE_WM_INITMENUPOPUP( hDlg, wParam, lParam, OnInitMenuPopup );
        break;

    case WM_SIZE:

        HANDLE_WM_SIZE( hDlg, wParam, lParam, OnSize );
        break;

    case WM_TIMER:

        HANDLE_WM_TIMER( hDlg, wParam, lParam, OnTimer );
        break;

#ifndef _WIN32_WCE
    case WM_WSAASYNCSELECT:

        HANDLE_WM_WSAASYNCSELECT( hDlg, wParam, lParam, OnWSAAsyncSelect );
        break;
#endif /* ! _WIN32_WCE */

        default:

            return false;

    }

    return true;

}
