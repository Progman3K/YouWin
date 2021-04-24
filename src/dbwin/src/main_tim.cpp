

#include "dbwin.h"


BOOL DoEdit_ScrollCaret( HWND hEditWnd ) {

    int iLen = GetWindowTextLength( hEditWnd );
    Edit_SetSel( hEditWnd, iLen, iLen );

#if defined( _WIN32 ) || defined( _WIN32_WCE )
    Edit_ScrollCaret( hEditWnd );
#endif

    return true;

}


void CMainDlg::OnTimer( HWND hDlg, UINT uiTimerID ) {

    LPDBWIN_DATA	lpDBWin;

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    switch( uiTimerID ) {

        case ID_UPDATE_OUTPUT_TIMER:

            // KillTimer( hDlg, ID_UPDATE_OUTPUT_TIMER );

            DoEdit_ScrollCaret( lpDBWin->hOutputWnd );
            SetWindowRedraw( lpDBWin->hOutputWnd, true );
            UpdateWindow( lpDBWin->hOutputWnd );
            SetWindowRedraw( lpDBWin->hOutputWnd, false );
            break;

    }

}
