

#include "chatter.h"


INT_PTR CChatterMainWnd::bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CLOSE:

            HANDLE_WM_CLOSE( hDlg, wParam, lParam, OnClose );
            break;

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hDlg, wParam, lParam, OnCommand );
            break;

        case WM_DESTROY:

            HANDLE_WM_DESTROY( hDlg, wParam, lParam, OnDestroy );
            break;

        case WM_DELETEITEM:

            HANDLE_WM_DELETEITEM(  hDlg, wParam, lParam, OnDeleteItem );
            break;

        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hDlg, wParam, lParam, OnDisplayChange );
            break;

        case WM_GETICON:

            SetWindowLongPtr( hDlg, DWLP_MSGRESULT, (LONG_PTR)(LRESULT)hAppIcon );
            break;

        case WM_INITDIALOG: {

            BOOL bRet = (BOOL)HANDLE_WM_INITDIALOG( hDlg, wParam, lParam, OnInit );

            if ( ! bRet ) {

				OutputDebugString( TEXT( "Main dialog failed init" ) );
                EndDialog( hDlg, -1 );

            }

            /* Indicate our init handler has already set the focus */
            return false;

        }

        case WM_SIZE:

            HANDLE_WM_SIZE( hDlg, wParam, lParam, OnSize );
            break;

        case WM_TIMER:

            HANDLE_WM_TIMER( hDlg, wParam, lParam, OnTimer );
            break;

#ifdef WIN32
        case WM_WSAASYNCGETHOSTBYNAME:

            HANDLE_WM_WSAASYNCGETHOSTBYNAME( hDlg, wParam, lParam, OnWSAAsyncGetHostByName );
            break;
#endif

        case WM_WSAASYNCSELECT:

            HANDLE_WM_WSAASYNCSELECT( hDlg, wParam, lParam, OnWSAAsyncNotification );
            break;

        case WM_WSAASYNCTCPXFER:

            HANDLE_WM_WSAASYNCSELECT( hDlg, wParam, lParam, OnWSAAsyncTCPXfer );
            break;

        default:

            return false;

    }

    return true;

}
