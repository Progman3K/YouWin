

#include "dbwin.h"


HINSTANCE   g_hInst     = NULL;
UINT        g_uiFindMsg = 0;
HWND        g_hMainDlg  = NULL;


/* File storage */
TCHAR       g_szIniFile[1024] = TEXT( IDSZ_INIFILE );


extern "C" int _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow ) {

    int         iRet;
    DBWIN_DATA  DBWin;

    g_hInst = hInst;

    // ZeroMemory( &DBWin, sizeof( DBWin ) );

    DBWin.nCmdShow		=	nCmdShow;
    DBWin.hOutputFile	=	0;

    DBWin.sCmdLine.assign( lpszCmdLine );

    if ( 0 == ( iRet = CApp::iInit( hInst, hPrevInst ) ) ) {

        iRet = DialogBoxParam( hInst, MAKEINTRESOURCE( IDD_MAIN ), HWND_DESKTOP, (DLGPROC)CMainDlg::bDlgProc, (LPARAM)(LPDBWIN_DATA)&DBWin );

    }

    if ( 0 != DBWin.hOutputFile ) {

        fclose( DBWin.hOutputFile );
        DBWin.hOutputFile = 0;

    }

    CApp::CleanUp();

    return iRet;

}
