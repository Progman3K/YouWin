

#include "test.h"
#include <dbgtrace.cpp>
//#include <traceMSG.cpp>


#define WM_WSAASYNCTCPXFER WM_USER + 100


int testDialog( HINSTANCE hInst ) {

    LONG lBaseUnits = GetDialogBaseUnits();

    int iDlgID = IDD_MAIN;

    if ( ( 1 == HIWORD( lBaseUnits ) ) && ( 1 == LOWORD( lBaseUnits ) ) ) {

        iDlgID = IDD_MAIN_TEXT;

    }

    MSG Msg;

    Msg.wParam = DialogBoxParam( hInst, MAKEINTRESOURCE( iDlgID ), HWND_DESKTOP, (DLGPROC)CMainWnd::bDlgProc, (LPARAM)0 );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Exiting: %d" ), Msg.wParam );

    return Msg.wParam;

}


int _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR pszCmdLine, int nCmdShow ) {

//    INITCOMMONCONTROLSEX InitCtrlEx;

//    InitCtrlEx.dwSize = sizeof( INITCOMMONCONTROLSEX );
//    InitCtrlEx.dwICC  = ICC_PROGRESS_CLASS;

//    InitCommonControlsEx( &InitCtrlEx );

//    return MessageBox( HWND_DESKTOP, TEXT( "Starting test" ), TEXT( "Test App" ), MB_OK | MB_ICONINFORMATION );

    return testDialog( hInst );

}
