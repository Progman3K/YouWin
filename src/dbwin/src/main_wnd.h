

class CMainDlg {

    public:

        static LRESULT     lDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );
        static BOOL        bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

        static void        OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        static void        OnSize( HWND hDlg, UINT uiState, int iCX, int iCY );
        static void        OnTimer( HWND hDlg, UINT uiTimerID );
        static BOOL        bOnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );
        static BOOL        bOnCopyData( HWND hDlg, HWND hFromWnd, COPYDATASTRUCT * lpCD );
        static void        OnInitMenu( HWND hDlg, HMENU hMenu );
        static void        OnInitMenuPopup( HWND hDlg, HMENU hMenu, UINT uiItem, BOOL bSystemMenu );
        static void        OnDestroy( HWND hDlg );
        static void        OnWSAAsyncSelect( HWND hDlg, SOCKET s, unsigned uEvent, unsigned uError );

        static void        ToggleWordWrap( HWND hEditWnd, BOOL bWordWrap );

    private:

        static int         WriteEditToFile( HWND hDlg, FILE * hFile, LPARAM lParam );
        static void        DoSaveDebugBuffer( HWND hDlg );

#ifndef _WIN32_WCE
        static void        DoFind( HWND hDlg, LPFINDREPLACE lpFR, LPCTSTR lpszInitialText, WORD wInitialTextBufferSize, LPFRHOOKPROC lpfnHook, LPARAM lParam );
        static void        HandleFindMsg( HWND hDlg, LPFINDREPLACE lpFR );
        static void        FindTheText( HWND /* hEditWnd */, LPCTSTR lpcData, LPFINDREPLACE lpFR );
#endif /* ! _WIN32_WCE */

        static HFONT       hCreateFont( HINSTANCE hInst );
        static BOOL        GetEditSelRange( HWND hEditWnd, DWORD * pdwSelStart, DWORD * pdwSelEnd );

        static void *      Edit_ClaimTextPtr( HWND hEditWnd );
        static BOOL        LocalUnlockPtr( void * lpData );

        static void        ProcessUserData( LPDBWIN_DATA lpDBWin, COPYDATASTRUCT * lpCD );

        static FILE *      OpenOutputFile( LPCTSTR lpszFileName );

        static void        DoAbout( HWND hParentWnd );

};
