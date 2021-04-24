

#include "dbwin.h"


void CSettingsDlg::OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT /* uiNotifyCode */ ) {

    LPDBWIN_DATA lpDBWin;
    BOOL         bWordWrap;

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    switch( iID ) {

        case IDCANCEL:

            EndDialog( hDlg, 0 );
            break;

        case IDRB_WORDWRAP:

            bWordWrap = Button_GetCheck( hCtlWnd );
            CMainDlg::ToggleWordWrap( lpDBWin->hOutputWnd, bWordWrap );
            // SetAppProfileBool( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_WORDWRAP ), bWordWrap, g_szIniFile );
            break;

        case IDB_CHOOSE_FONT: {

#if ! defined( _WIN32_WCE ) && defined( _WIN32 )

                HFONT      hFont;
                CHOOSEFONT cf;
                LOGFONT    lf;

                ZeroMemory( &cf, sizeof( cf ) );

                GetObject( (HGDIOBJ)lpDBWin->hFont, sizeof( lf ), &lf );

                cf.lStructSize = sizeof( cf );
                cf.hwndOwner   = hDlg;
                cf.lpLogFont   = &lf;
                cf.Flags       = CF_SCREENFONTS | CF_FORCEFONTEXIST | CF_INITTOLOGFONTSTRUCT;
                cf.rgbColors   = GetSysColor( COLOR_WINDOWTEXT );

                if ( ! ChooseFont( &cf ) ) {

                    break;
                }

                /* Replace current font with the new one. */
                if ( NULL == ( hFont = CreateFontIndirect( &lf ) ) ) {

                    break;

                }

                SetWindowFont( lpDBWin->hOutputWnd, hFont, true );

                if ( NULL != lpDBWin->hFont ) {

                    DeleteFont( lpDBWin->hFont );

                }

                lpDBWin->hFont = hFont;

                // SetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_NAME ), lf.lfFaceName, g_szIniFile );
                // SetAppProfileLong( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_POINT ), lf.lfHeight, g_szIniFile, TRUE );
                // SetAppProfileLong( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_WIDTH ), lf.lfWidth, g_szIniFile, TRUE );

#endif /* ! _WIN32_WCE */

            }
            break;

    }

}


BOOL CSettingsDlg::bOnInit( HWND hDlg, HWND /* hFocusWnd */, LPARAM lParam ) {

    LPDBWIN_DATA lpDBWin;
    HWND         hCtlWnd;
    BOOL         bWordWrap;

    lpDBWin = (LPDBWIN_DATA)lParam;

    SetWindowLong( hDlg, DWL_USER, (LPARAM)lpDBWin );

    if ( NULL == ( hCtlWnd = GetDlgItem( hDlg, IDRB_WORDWRAP ) ) ) {

        return false;

    }

    bWordWrap = ( 0 != ( GetWindowLong( lpDBWin->hOutputWnd, GWL_STYLE ) & ( ES_AUTOHSCROLL | WS_HSCROLL ) ) );
    Button_SetCheck( hCtlWnd, bWordWrap );

    return true;

}


BOOL CSettingsDlg::bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    BOOL	bRet;

    switch( uiMsg ) {

    case WM_COMMAND:

        HANDLE_WM_COMMAND( hDlg, wParam, lParam, OnCommand );
        break;

    case WM_INITDIALOG:

        bRet = (BOOL)HANDLE_WM_INITDIALOG( hDlg, wParam, lParam, bOnInit );

        if ( ! bRet ) {

            EndDialog( hDlg, -1 );

        }
        break;

        default:

            return false;

    }

    return true;

}
