

#include "ywin.h"


static void makepath( TSTRING * pPath, LPCTSTR pDir, LPCTSTR pFname ) {

    if ( NULL != pDir ) {

        pPath->append( pDir );

    }

    if ( NULL != pFname ) {

        if ( '/' != pPath->at( pPath->size() - 1 ) ) {

            pPath->append( TEXT( "/" ) );

        }

        pPath->append( pFname );

    }

}


int GetOpenFileNameDlg::SetToFolder( HWND hDlg, LPCTSTR pszFolder ) {

    TCHAR szPath[PATH_MAX + 1];

    ZeroMemory( szPath, sizeof( szPath ) );

    GetDlgItemText( hDlg, IDST_FOLDER, szPath, Dim( szPath ) - 1 );

    if ( 0 == _tcscmp( TEXT( "" ), pszFolder ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "BLANK PATH" ) );
        return -1;

    }

    if ( ( 0 == _tcscmp( TEXT( ".." ), pszFolder ) ) && ( 0 != _tcscmp( TEXT( "/" ), szPath ) ) && ( 0 != _tcscmp( TEXT( "" ), szPath ) ) ) {

        /* Lop off last folder */
        TCHAR * pszSlash = _tcsrchr( szPath, '/' );

        if ( NULL == pszSlash ) {

            return -1;

        }

        *pszSlash = '\0';

        if ( 0 == _tcscmp( TEXT( "" ), szPath ) ) {

            return SetToFolder( hDlg, TEXT( "/" ) );

        }

        return SetToFolder( hDlg, szPath );

    }

    DIR * pUserDir;

    if ( NULL == ( pUserDir = opendir( ( (TSTRING)pszFolder ).charz_str() ) ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "UNABLE TO OPEN DIR '%s'" ), pszFolder );
        return -1;

    }

    SetDlgItemText( hDlg, IDST_FOLDER, pszFolder );

    HWND hLBFolders = GetDlgItem( hDlg, IDLB_FOLDERS );
    HWND hLBFiles   = GetDlgItem( hDlg, IDLB_FILES );
    HWND hEFile     = GetDlgItem( hDlg, IDE_FILENAME );
    HWND hOK        = GetDlgItem( hDlg, IDOK );

    BOOL bRet = ListBox_ResetContent( hLBFolders );

    if ( LB_ERR == bRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "UNABLE TO RESET LISTBOX" ) );

    }

    bRet = ListBox_ResetContent( hLBFiles );

    if ( LB_ERR == bRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "UNABLE TO RESET LISTBOX" ) );

    }

    SetWindowText( hEFile, TEXT( "" ) );

    if ( GetFocus() == hOK ) {

        SetFocus( hLBFiles );

    }

    Button_Enable( hOK, false );

//    struct dirent   entry;
    struct dirent * pEntry;
    struct stat     Stat;

    for ( ;; ) {

        pEntry = readdir( pUserDir );

        if ( NULL == pEntry ) {

            break;

        }


        if ( 0 == strcmp( ".", pEntry->d_name ) ) {

            /* Filter out the . entry */
            continue;

        }

        if ( ( 0 == strcmp( "..", pEntry->d_name ) ) && ( 0 == strcmp( "/", ( (TSTRING)pszFolder ).charz_str() ) ) ) {

            /* Already at top of the tree, filter out the .. entry */
            continue;

        }

        if ( ( 0 != strcmp( "..", pEntry->d_name ) ) && ( 0 == strncmp( ".", pEntry->d_name, 1 ) ) && ( ! ( OFN_FORCESHOWHIDDEN & pofn->Flags ) ) ) {

            /* Filter out hidden entries */
            continue;

        }

        TSTRING File;

        const TCHAR * pszEntry;

#ifdef UNICODE
        TSTRING Entry;
        Entry.absorb( entry.d_name );
        pszEntry = Entry.c_str();
#else
        pszEntry = pEntry->d_name;
#endif

        makepath( &File, pszFolder, pszEntry );

        int iRet = stat( File.charz_str(), &Stat );

        if ( 0 != iRet ) {

            continue;

        }

        if ( S_ISDIR( Stat.st_mode ) ) {

            iRet = ListBox_AddString( hLBFolders, pEntry->d_name );

        } else if ( S_ISREG( Stat.st_mode ) ) {

            iRet = ListBox_AddString( hLBFiles, pEntry->d_name );

        }

    }

    closedir( pUserDir );

    return 0;

}


void GetOpenFileNameDlg::HandleOpen( HWND hDlg ) {

    /* If the contents of the edit is a fully-qualified path-name, and it exists, accept it. Done */
    HWND hWnd = GetDlgItem( hDlg, IDE_FILENAME );

    int iLen = GetWindowTextLength( hWnd );

    TSTRING Name;

    Name.resize( iLen + 1 );

    GetWindowText( hWnd, (TCHAR *)Name.c_str(), iLen );

    struct stat Stat;
    int iRet;

#ifdef UNICODE
    iRet = stat( Name.charz_str(), &Stat );
#else
    iRet = stat( Name.c_str(), &Stat );
#endif

    if ( 0 == iRet ) {

        if ( S_ISDIR( Stat.st_mode ) ) {

            /* It's a fully qualified path. */
            SetToFolder( hDlg, Name.c_str() );
            return;

        }

        if ( S_ISREG( Stat.st_mode ) ) {

            /* It's a fully-qualified filename. */
            _tcsncpy( pofn->lpstrFile, Name.c_str(), pofn->nMaxFile );
            EndDialog( hDlg, IDOK );
            return;

        }

    }

    /* If the contents of the edit and the current folder form an existing filename, accept it. Done */

    TSTRING File;

    TCHAR szPath[PATH_MAX + 1];

    ZeroMemory( szPath, sizeof( szPath ) );

    /* Get the contents of the edit. */
    GetDlgItemText( hDlg, IDST_FOLDER, szPath, Dim( szPath ) - 1 );

    /* If the contents of the edit and the current folder form an existing path, set the current folder to it, break. */

    makepath( &File, szPath, Name.c_str() );

    iRet = stat( File.charz_str(), &Stat );

    if ( 0 == iRet ) {

        if ( S_ISDIR( Stat.st_mode ) ) {

            /* It's a fully qualified path. */
            SetToFolder( hDlg, File.c_str() );
            return;

        }

        if ( S_ISREG( Stat.st_mode ) ) {

            /* It's a fully-qualified filename. */
            _tcsncpy( pofn->lpstrFile, File.c_str(), pofn->nMaxFile );
            EndDialog( hDlg, IDOK );
            return;

        }

    }

    if ( OFN_FILEMUSTEXIST & pofn->Flags ) {

        MessageBox( hDlg, TEXT( "File must exist" ), NULL, MB_OK );
        return;

    }

    _tcsncpy( pofn->lpstrFile, File.c_str(), pofn->nMaxFile );
    EndDialog( hDlg, IDOK );

}


void GetOpenFileNameDlg::OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

    switch( iID ) {

        case IDE_FILENAME:

            if ( EN_CHANGE == uiNotifyCode ) {

                /* There is no text, disable send. Done */
                Button_Enable( GetDlgItem( hDlg, IDOK ), 0 != Edit_GetTextLength( hCtlWnd ) );

            }
            break;

        case IDLB_FOLDERS:

            if ( LBN_DBLCLK == uiNotifyCode ) {

                int iIndex = ListBox_GetCurSel( hCtlWnd );

                TCHAR szName[NAME_MAX + 1];

                ZeroMemory( szName, sizeof( szName ) );

                int iLen = ListBox_GetText( hCtlWnd, iIndex, szName );

                if ( ( LB_ERR == iLen ) || ( 0 == iLen ) ) {

                    DBG_MSG( DBG_ERROR, TEXT( "ERROR: COULDN'T RETRIEVE TEXT" ) );
                    break;

                }

                if ( 0 == _tcscmp( TEXT( ".." ), szName ) ) {

                    SetToFolder( hDlg, szName );
                    break;

                }

                HWND hWnd = GetDlgItem( hDlg, IDST_FOLDER );

                TCHAR szPath[PATH_MAX + 1];

                ZeroMemory( szPath, sizeof( szPath ) );

                Static_GetText( hWnd, szPath, Dim( szPath ) - 1 );

                TSTRING Path;

                makepath( &Path, szPath, szName );

                SetToFolder( hDlg, Path.c_str() );

            }
            break;

        case IDLB_FILES:

            switch( uiNotifyCode ) {

                case LBN_SELCHANGE: {

                    TCHAR szName[NAME_MAX + 1];

                    ZeroMemory( szName, sizeof( szName ) );

                    int iIndex = ListBox_GetCurSel( hCtlWnd );

                    if ( LB_ERR == iIndex ) {

                        DBG_MSG( DBG_ERROR, TEXT( "ERROR: COULDN'T GET CURRENT SELECTION" ) );
                        break;

                    }

                    int iLen = ListBox_GetText( hCtlWnd, iIndex, szName );

                    if ( LB_ERR != iLen ) {

                        SetDlgItemText( hDlg, IDE_FILENAME, szName );

                        Button_Enable( GetDlgItem( hDlg, IDOK ), true );

                    }
                    break;

                }

                case LBN_DBLCLK:

                    HandleOpen( hDlg );
                    break;

            }
            break;

        case IDOK:

            HandleOpen( hDlg );
            break;

        case IDCANCEL:

            EndDialog( hDlg, iID );
            break;

    }

}


BOOL GetOpenFileNameDlg::OnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam ) {

#ifdef YOU_WIN_TXT
    portrait.Record( hYouWinModule, MAKEINTRESOURCE( IDD_OPENFILENAME_TEXT_PORTRAIT ), HWND_DESKTOP );
    landscape.Record( hYouWinModule, MAKEINTRESOURCE( IDD_OPENFILENAME_TEXT ), HWND_DESKTOP );
#else
    portrait.Record( hYouWinModule, MAKEINTRESOURCE( IDD_OPENFILENAME_FOR_ANDROID_PORTRAIT ), HWND_DESKTOP );
    landscape.Record( hYouWinModule, MAKEINTRESOURCE( IDD_OPENFILENAME_FOR_ANDROID_LANDSCAPE ), HWND_DESKTOP );
#endif

    pofn = (OPENFILENAME *)lParam;

    if ( OFN_HIDEREADONLY & pofn->Flags ) {

        HWND hWnd = GetDlgItem( hDlg, IDRB_OPEN_AS_READ_ONLY );

        if ( NULL != hWnd ) {

            ShowWindow( hWnd, SW_HIDE );

        }

    }

    if ( NULL != pofn->lpstrTitle ) {

        SetWindowText( hDlg, pofn->lpstrTitle );

    }

    int iRet = SetToFolder( hDlg, ( NULL == pofn->lpstrInitialDir ) ? TEXT( "/" ) : pofn->lpstrInitialDir );

    if ( 0 != iRet ) {

        iRet = SetToFolder( hDlg, TEXT( "/sdcard" ) );

        if ( 0 != iRet ) {

            iRet = SetToFolder( hDlg, TEXT( "/" ) );

            if ( 0 != iRet ) {

                EndDialog( hDlg, -1 );
                return false;

            }

        }

    }

    SetDlgItemText( hDlg, IDE_FILENAME, pofn->lpstrFile );

    FORWARD_WM_COMMAND( hDlg, IDE_FILENAME, GetDlgItem( hDlg, IDE_FILENAME ), EN_CHANGE, SendMessage );

    return true;

}


void GetOpenFileNameDlg::OnDisplayChange( HWND hWnd, UINT uiBitsPerPixel, UINT cx, UINT cy ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "GetOpenFileName resized to %ux%u" ), cx, cy );

    RECT r;

    GetWindowRect( hWnd, &r );

    if ( cy > cx ) {

        /* Portrait */
        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Dialog set to portrait mode (%ux%u) [%d,%d,%d,%d]" ), portrait.cx, portrait.cy, r.left, r.top, r.left + portrait.cx, r.top + portrait.cy );
        portrait.MoveTo( hWnd, r.left, r.top );

    } else {

        /* Landscape */
        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Dialog set to landscape mode (%ux%u) [%d,%d,%d,%d]" ), landscape.cx, landscape.cy, r.left, r.top, r.left + landscape.cx, r.top + landscape.cy );
        landscape.MoveTo( hWnd, r.left, r.top );

    }

}


INT_PTR GetOpenFileNameDlg::bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
            break;

        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hWnd, wParam, lParam, OnDisplayChange );
            break;

        case WM_INITDIALOG:

            return HANDLE_WM_INITDIALOG( hWnd, wParam, lParam, OnInit );

        default:

            return false;

    }

    return true;

}


BOOL GetOpenFileName( LPOPENFILENAME lpofn ) {

    HINSTANCE hInst = hYouWinModule;

    int iDlgID;

    int iPortraitDlgID;
    int iLandscapeDlgID;

#ifdef YOU_WIN_TXT
    iPortraitDlgID  = IDD_OPENFILENAME_TEXT_PORTRAIT;
    iLandscapeDlgID = IDD_OPENFILENAME_TEXT;
#else
    iPortraitDlgID  = IDD_OPENFILENAME_FOR_ANDROID_PORTRAIT;
    iLandscapeDlgID = IDD_OPENFILENAME_FOR_ANDROID_LANDSCAPE;
#endif

    if ( GetSystemMetrics( SM_CYSCREEN ) > GetSystemMetrics( SM_CXSCREEN ) ) {

        iDlgID = iPortraitDlgID;

    } else {

        iDlgID = iLandscapeDlgID;

    }

    LPCTSTR pDlgID = MAKEINTRESOURCE( iDlgID );

    if ( OFN_ENABLETEMPLATE & lpofn->Flags ) {

        hInst  = lpofn->hInstance;
        pDlgID = lpofn->lpTemplateName;

    }

    int iRet = DialogBoxParam( hInst, pDlgID, lpofn->hwndOwner, (DLGPROC)GetOpenFileNameDlg::bDlgProc, (LPARAM)lpofn );

    if ( IDOK != iRet ) {

        return false;

    }

    return true;

}
