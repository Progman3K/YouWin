

#include "dbwin.h"


void CMainDlg::OnDestroy( HWND hDlg ) {

    LPDBWIN_DATA	lpDBWin;

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    if ( NULL == lpDBWin ) {

        return;

    }

    SetWindowLongPtr( hDlg, DWL_USER, 0 );

    if ( NULL != lpDBWin->hFont ) {

#ifdef _WIN32
        DeleteFont( lpDBWin->hFont );
#endif
        lpDBWin->hFont = NULL;

    }

    lpDBWin->UDP.Close();

}
