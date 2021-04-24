

#include "dbwin.h"


void CMainDlg::OnSize( HWND hDlg, UINT /* uiState */, int iCX, int iCY ) {

    HWND hOutputWnd;
    HWND hCmdBar;
    int  iOffset;

    if ( NULL == ( hOutputWnd = GetDlgItem( hDlg, IDE_OUTPUT ) ) ) {

        return;

    }

    iOffset = 0;

    if ( NULL != ( hCmdBar = GetDlgItem( hDlg, IDCMDBAR_MENU ) ) ) {

        iOffset = GetSystemMetrics( SM_CYMENU );

    }

    MoveWindow( hOutputWnd, 0, iOffset, iCX, iCY - iOffset, true );

}
