

class CAboutDlg {

    public:

        static BOOL bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

        static void OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        static BOOL bOnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );

};


void DoAbout( HWND hParentWnd );
