

#include "dbwin.h"


static void DoSetOnTop( HWND hDlg, BOOL bOnTop ) {

#if ! defined( _WIN32_WCE ) && defined( _WIN32 )
    SetWindowPos( hDlg, bOnTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
#endif /* ! _WIN32_WCE && WIN32  */
// SetAppProfileBool( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_ALWAYS_ON_TOP ), bOnTop, g_szIniFile );

}


FILE * CMainDlg::OpenOutputFile( LPCTSTR lpszFileName ) {

    FILE * hFile;

    if ( 0 == ( hFile = fopen( lpszFileName, "a" ) ) ) {

        return 0;

    }

    return hFile;

}


BOOL bFind( HWND hWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, HINSTANCE hInst ) {

            OPENFILENAME    ofn;
            BOOL            bRet = false;
            TCHAR           szFilter[1024];
            TCHAR           szTitle[1024];

            if ( ( lpszRet == NULL ) || ( uszRetBufSize == 0 ) ) {

                /* Parameter error. */
                return false;

            }

            ZeroMemory( &ofn, sizeof( ofn ) );

            ofn.lStructSize      = sizeof( OPENFILENAME );

            /* Load filtering string from resource table. */
            if ( NULL != hInst ) {

                unsigned uCB;
                ZeroMemory( szFilter, sizeof( szFilter ) );
                if ( ( uCB = LoadString( hInst, uFileFilter, szFilter, Dim( szFilter ) - 1 ) ) == 0 ) {

                    return false;

                }

                /* Replace all occurances of separator char with null. */
                while ( 0 != ( --uCB ) ) {

                    if ( szFilter[ uCB ] == cSeparator ) {

                        szFilter[ uCB ] = 0;

                    }

                }

                ofn.lpstrFilter      = szFilter;

                ofn.nFilterIndex     = 1;

                /* Load dialog title string. */
                if ( 0 == HIWORD( (uintptr_t)lpszDialogTitle ) ) {

                    ZeroMemory( szTitle, sizeof( szTitle ) );

                    if ( ! LoadString( hInst, LOWORD( (uintptr_t)lpszDialogTitle ), szTitle, Dim( szTitle ) - 1 ) ) {

                        return false;

                    }

                    lpszDialogTitle = szTitle;

                }

            }

            ofn.hwndOwner        = hWnd;

            ofn.lpstrTitle       = lpszDialogTitle;

            ofn.lpstrFile        = lpszRet;

            ofn.nMaxFile         = uszRetBufSize;

            ofn.lpstrInitialDir  = lpszInitialDir;

            ofn.Flags            = dwFlags;

            ofn.lpfnHook         = lpfnDlgHookProc;

            bRet = GetOpenFileName( &ofn );

            /* Return the user's choice. */
            return bRet;

        }


void CMainDlg::OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

    LPDBWIN_DATA lpDBWin;
    TCHAR        szOutputFileName[1024];

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    switch( iID ) {

        /* ------------------------------- CONTROLS -------------------------------- */

        case IDE_OUTPUT:

            switch( uiNotifyCode ) {

                case EN_MAXTEXT:
                case EN_ERRSPACE:

                    MessageBeep(0);

                    /* Delete one eighth of the text. Too bad... */
                    DeleteText( hCtlWnd, 8 );
                    break;

            }

            break;

        /* ------------------------------ FILE menu -------------------------------- */

        case IDM_SAVE_BUFFER_AS:

            DoSaveDebugBuffer( hDlg );
            break;

        case IDM_EXIT:

            if ( ! Sure( g_hInst, hDlg, MAKEINTRESOURCE( IDS_DBWIN_MSG ), MAKEINTRESOURCE( IDS_EXIT ), 0, NULL ) ) {

                break;

            }

            EndDialog( hDlg, 0 );
            break;

        /* ------------------------------ EDIT menu -------------------------------- */

        case IDM_COPY:

#ifdef _WIN32
            SendDlgItemMessage( hDlg, IDE_OUTPUT, WM_COPY, 0, 0 );
#endif
            break;

        case IDM_FIND:

#ifndef _WIN32_WCE
            ZeroMemory( lpDBWin->szFindData, sizeof( lpDBWin->szFindData ) );
            DoFind( hDlg, &lpDBWin->FR, lpDBWin->szFindData, Dim( lpDBWin->szFindData ) - 1, NULL, 0 );
#endif /* ! _WIN32_WCE */
            break;

        case IDM_SELECT_ALL:

            SendDlgItemMessage( hDlg, IDE_OUTPUT, EM_SETSEL, 0, -1 );
            break;

        case IDM_CLEAR_OUTPUT:

            SetDlgItemText( hDlg, IDE_OUTPUT, TEXT( "" ) );
            break;

        /* --------------------------- OPTIONS menu -------------------------------- */

        case IDM_SETTINGS:

            DialogBoxParam( g_hInst, MAKEINTRESOURCE( IDD_SETTINGS ), hDlg, (DLGPROC)CSettingsDlg::bDlgProc, (LPARAM)lpDBWin );
            break;

        case IDM_OUTPUT_TO_FILE:

            if ( 0 == lpDBWin->hOutputFile ) {

                /* Open a file for output. */
                ZeroMemory( szOutputFileName, sizeof( szOutputFileName ) );
                if ( ! bFind( hDlg, IDS_LOG_FILE_TYPES, '|', MAKEINTRESOURCE( IDS_OUTPUT_LOGFILE ), szOutputFileName, Dim( szOutputFileName ) - 1, OFN_CREATEPROMPT | OFN_HIDEREADONLY, NULL, NULL, g_hInst ) ) {

                    break;

                }

                lpDBWin->hOutputFile = OpenOutputFile( szOutputFileName );

                // SetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_OUTPUT_TO ), szOutputFileName, g_szIniFile );

            } else {

                /* Close the output file. */
                fclose( lpDBWin->hOutputFile );
                lpDBWin->hOutputFile = 0;

            }
            break;

        case IDM_OUTPUT_TO_WINDOW:

            lpDBWin->bNoOutput = false;
            // SetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_OUTPUT_TO ), ID( IDS_WINDOW ), g_szIniFile );
            break;

        case IDM_OUTPUT_DISABLE:

            lpDBWin->bNoOutput = true;
            // SetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_OUTPUT_TO ), ID( IDS_NONE ), g_szIniFile );
            break;

        case IDM_ALWAYS_ON_TOP_TOGGLE:

#ifndef _WIN32_WCE
            DoSetOnTop( hDlg, 0 == ( WS_EX_TOPMOST & GetWindowLong( hDlg, GWL_EXSTYLE ) ) );
#endif /* ! _WIN32_WCE */
            break;

        /* ------------------------------ HELP menu -------------------------------- */

        case IDM_ABOUT:

            DoAbout( hDlg );
            break;

    }

}
