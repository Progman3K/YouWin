

#include "dbwin.h"


BOOL CAboutDlg::bOnInit( HWND hDlg, HWND /* hFocusWnd */, LPARAM /* lParam */ ) {

    HWND  hParentWnd;
    TCHAR szVersion[128];
    TCHAR szTemp[1024];

    if ( NULL != ( hParentWnd = GetParent( hDlg ) ) ) {

        // bCenterWindow( hDlg, hParentWnd, FALSE );

    }

    ZeroMemory( szVersion, sizeof( szVersion ) );
    // GetVersionInfo( g_hInst, hDlg, (LPTSTR)ID( IDST_ABOUT_APP_NAME ), szVersion, (LPTSTR)ID( IDST_ABOUT_APP_COPYRIGHT ) );

    sprintf( szTemp, TEXT( "Version %s" ), (LPCTSTR)szVersion );

    SetDlgItemText( hDlg, IDST_ABOUT_APP_VERSION, szTemp );

    return true;

}


void CAboutDlg::OnCommand( HWND hDlg, int iID, HWND /* hCtlWnd */, UINT /* uiNotifyCode */ ) {

    switch ( iID ) {

        case IDCANCEL:
        case IDOK:

            EndDialog( hDlg, 0 );
            break;

    }

}


extern "C" BOOL CAboutDlg::bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    BOOL bRet;

    switch( uiMsg ) {

        case WM_INITDIALOG:

            bRet = (BOOL)HANDLE_WM_INITDIALOG( hDlg, wParam, lParam, bOnInit );

            if ( ! bRet ) {

                EndDialog( hDlg, 0 );

            }
            break;

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hDlg, wParam, lParam, OnCommand );
            return false;
            break;

        default:

            return false;

    }

    return true;

}


void CMainDlg::DoAbout( HWND hParentWnd ) {

    DialogBox( g_hInst, MAKEINTRESOURCE( IDD_ABOUT ), hParentWnd, (DLGPROC)CAboutDlg::bDlgProc );

}
