

class CSettingsDlg {

    public:

        static BOOL bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

        static BOOL bOnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );
        static void OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );

};
