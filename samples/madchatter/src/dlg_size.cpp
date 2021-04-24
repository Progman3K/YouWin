

#include "chatter.h"


void CChatterMainWnd::OnSize( HWND hDlg, UINT uiState, int /* iCX */, int /* iCY */ ) {

    switch( uiState ) {

        case SIZE_MAXIMIZED:
        case SIZE_RESTORED:

            bNewCommunications = false;


#if defined( WIN32 ) && ! defined( _WIN32_WCE )
            {

                SetClassIcon( hDlg, hMainIcon );
                UpdateWindow( hDlg );

                DWORD dwStyle = GetWindowExStyle( hDlg );
                SetWindowLong( hDlg, GWL_EXSTYLE, dwStyle & ( ~WS_EX_TOPMOST ) );
                SetWindowPos( hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW );

            }
#endif /* ! _WIN32_WCE */
            break;

        case SIZE_MINIMIZED:

            bNewCommunications = false;
            break;

    }

}
