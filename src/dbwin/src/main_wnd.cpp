

#include "dbwin.h"


extern "C" LRESULT CMainDlg::lDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

#ifndef _WIN32_WCE
    if ( uiMsg == g_uiFindMsg ) {

        HandleFindMsg( hDlg, (LPFINDREPLACE)lParam );
        return 0;

    }
#endif /* ! _WIN32_WCE */

    switch( uiMsg ) {

        case WM_ERASEBKGND:

            return true;

        default:

            break;

    }

    return DefDlgProc( hDlg, uiMsg, wParam, lParam );

}
