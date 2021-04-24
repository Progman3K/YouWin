

#include "dbwin.h"


BOOL CApp::bRegisterClasses( HINSTANCE hInst ) {

    WNDCLASS wc;

    ZeroMemory( &wc, sizeof( wc ) );

//    wc.style            = 0;
    wc.style            = DS_SETFONT;
    wc.lpfnWndProc      = (WNDPROC)CMainDlg::lDlgProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = DLGWINDOWEXTRA;
    wc.hInstance        = hInst;
#ifdef _WIN32_WCE
    wc.hIcon            = (HICON)LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
    wc.hCursor          = NULL;
#else
    wc.hIcon            = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN ) );
    wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
#endif /* ! _WIN32_WCE */
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT( IDSZ_DBWIN_WINDOW_CLASS );

    if ( 0 == RegisterClass( &wc ) ) {

        return false;

    }

    return true;

}
