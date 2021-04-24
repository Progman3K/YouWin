

#include "dbwin.h"


void PrepOutputFile( FILE * hFile, DWORD dwMaxFileSize ) {

#if 0
    DWORD dwFileSize;
    DWORD dwFilePos;
    DWORD dwCharPos;
    DWORD dwRead;
    TCHAR cData[1024];

    /* Read how big the file IS. */
#ifdef _WIN32
    if ( (DWORD)-1 == ( dwFileSize = GetFileSize( hFile, NULL ) ) ) {

        return;

    }
#else
    if ( (DWORD)-1 == ( dwFileSize = _filelength( hFile ) ) ) {

        return;

    }
#endif

    /* If the file is smaller, change its size to the proper length, simply jump to the end of it. */
    if ( dwFileSize < ( dwMaxFileSize * 1024 ) ) {

#ifdef _WIN32
        NativeFile::Seek( hFile, ( dwMaxFileSize * 1024 ), NativeFile::FROM_BEGINNING );
        SetEndOfFile( hFile );
#else
        _chsize( hFile, dwMaxFileSize * 1024 );
#endif
        NativeFile::Seek( hFile, dwFileSize, NativeFile::FROM_BEGINNING );
        return;

    }

    /* If the file is larger, change its size to the proper length, then find where the eof is. */
    if ( dwFileSize >= ( dwMaxFileSize * 1024 ) ) {

#ifdef _WIN32
        NativeFile::Seek( hFile, ( dwMaxFileSize * 1024 ), NativeFile::FROM_BEGINNING );
        SetEndOfFile( hFile );
#else
        _chsize( hFile, dwMaxFileSize * 1024 );
#endif

        /* Comb the file block by block looking for our EOF marker. */		
        NativeFile::Seek( hFile, 0, NativeFile::FROM_BEGINNING );

        for( dwFilePos = 0; dwFilePos < ( dwMaxFileSize * 1024 ); ) {

            ZeroMemory( cData, sizeof( cData ) );

            dwRead = NativeFile::Read( hFile, cData, sizeof( cData ) );

            if ( (DWORD)-1 == dwRead ) {

                break;

            }

            /* Look for EOF character */
            for( dwCharPos = 0; dwCharPos < Dim( cData ); dwCharPos++ ) {

                if ( EOFMARKER == cData[dwCharPos] ) {

                    dwFilePos += dwCharPos * sizeof( TCHAR );

                    /* Found it! Back up the file pointer to here. */
                    NativeFile::Seek( hFile, dwFilePos, NativeFile::FROM_BEGINNING );
                    return;

                }

            }

            dwFilePos += dwRead;			

        }

        /* Couldn't find the EOF marker, so start at the beginning of the file. */
        NativeFile::Seek( hFile, 0, NativeFile::FROM_BEGINNING );

    }
#endif

}


BOOL AddMenu( HWND hWnd, HINSTANCE hResourceInst, WORD wMenuResourceID, int iIDCmdBar ) {

    HMENU	hMenu;

    if ( NULL == ( hMenu = LoadMenu( hResourceInst, MAKEINTRESOURCE( wMenuResourceID ) ) ) ) {

        return false;

    }

#ifdef _WIN32_WCE
    {

        HWND	hCommandBarWnd;

        if ( NULL == ( hCommandBarWnd = CommandBar_Create( hResourceInst, hWnd, iIDCmdBar ) ) ) {

            return false;

        }

        if ( ! CommandBar_InsertMenubar( hCommandBarWnd, hResourceInst, wMenuResourceID, 1 ) ) {

            return false;

        }

        CommandBar_Show( hCommandBarWnd, true );

    }
#else
    SetMenu( hWnd, hMenu );
#endif /* ! _WIN32_WCE */

    return true;

}


BOOL CMainDlg::bOnInit( HWND hDlg, HWND /* hFocusWnd */, LPARAM lParam ) {

    LPDBWIN_DATA lpDBWin;
    BOOL         bWordWrap;
    BOOL         bUseUDP;
    RECT         r;
    TCHAR        szPath[1024];
    TCHAR        szTemp[1024];
    TCHAR        szStringEntry[1024];

    lpDBWin = (LPDBWIN_DATA)lParam;

    SetWindowLong( hDlg, DWL_USER, (LPARAM)lpDBWin );

    if ( ! AddMenu( hDlg, g_hInst, IDM_MAIN, IDCMDBAR_MENU ) ) {

        return false;

    }

    if ( NULL == ( lpDBWin->hOutputWnd = GetDlgItem( hDlg, IDE_OUTPUT ) ) ) {

        return false;

    }

    // Edit_LimitText( lpDBWin->hOutputWnd, 0 );

    // bWordWrap = GetAppProfileBool( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_WORDWRAP ), FALSE, g_szIniFile, TRUE );
    bWordWrap = false;

    ToggleWordWrap( lpDBWin->hOutputWnd, bWordWrap );

    GetClientRect( hDlg, &r );
    FORWARD_WM_SIZE( hDlg, SIZE_RESTORED, r.right, r.bottom, SendMessage );

#ifndef _WIN32_WCE
//    BOOL bAlwaysOnTop = GetAppProfileBool( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_ALWAYS_ON_TOP ), FALSE, g_szIniFile, TRUE );
    BOOL bAlwaysOnTop = false;

    if ( bAlwaysOnTop ) {

//        SetWindowPos( hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );

    }
#endif /* ! _WIN32_WCE */

    ZeroMemory( szTemp, sizeof( szTemp ) );

    /* Read how big the file is supposed to be. */
    // lpDBWin->dwMaxFileSize = GetAppProfileLong( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_MAX_TRACEFILESIZE ), DEFAULT_TRACEFILE_SIZE, g_szIniFile, TRUE, FALSE );
    lpDBWin->dwMaxFileSize = DEFAULT_TRACEFILE_SIZE;

    if ( lpDBWin->dwMaxFileSize < MINIMUM_TRACEFILE_SIZE ) {

        lpDBWin->dwMaxFileSize = MINIMUM_TRACEFILE_SIZE;

    }

    ZeroMemory( szTemp, sizeof( szTemp ) );
    // GetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_OUTPUT_TO ), TEXT( "" ), szTemp, Dim( szTemp ) - 1, g_szIniFile, TRUE );

    if ( 0 == strlen( szTemp ) ) {

        /* empty entry, so select window output */
        // SetAppProfileString( g_hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_OUTPUT_TO ), ID( IDS_WINDOW ), g_szIniFile );

        lpDBWin->bNoOutput = false;

    }
    else {

        /* no output ? */

        ZeroMemory( szStringEntry, sizeof( szStringEntry ) );

        LoadString( g_hInst, IDS_NONE, szStringEntry, Dim( szStringEntry ) - 1 );

        if ( 0 == strcmp ( szTemp, szStringEntry ) ) {

            /* no output */
            lpDBWin->bNoOutput = true;

        }
        else {

            /* file or window ouput ? */


            /* will output to window in all cases */
            lpDBWin->bNoOutput = false;


            /* file output also? */
            ZeroMemory( szStringEntry, sizeof( szStringEntry ) );

            LoadString( g_hInst, IDS_WINDOW, szStringEntry, Dim( szStringEntry ) - 1 );

            if ( 0 != strcmp( szTemp, szStringEntry ) ) {

                if ( 0 != ( lpDBWin->hOutputFile = OpenOutputFile( szTemp ) ) ) {

                    PrepOutputFile( lpDBWin->hOutputFile, lpDBWin->dwMaxFileSize );

                }

                /* do not care if open fails */

            }

        }

    }

#ifdef _WIN32
    lpDBWin->hFont = hCreateFont( g_hInst );
#endif

//    SetWindowFont( lpDBWin->hOutputWnd, lpDBWin->hFont, true );

    ShowWindow( hDlg, lpDBWin->nCmdShow );

    // bUseUDP =  GetAppProfileBool( g_hInst, ID( IDS_UDP_SETTINGS_SECTION ), ID( IDS_ENABLE_UDP ), FALSE, g_szIniFile, TRUE );
    bUseUDP = true;

    ZeroMemory( szPath, sizeof( szPath ) );
    //	GetAppProfileString( g_hInst, ID( IDS_UDP_SETTINGS_SECTION ), ID( IDS_WINSOCK_PATH ), ID( IDS_WINSOCK ), szPath, Dim( szPath ) - 1, g_szIniFile, TRUE );

    if ( bUseUDP ) {

        if ( ! lpDBWin->UDP.bInit( hDlg ) ) {

            MessageBox( hDlg, "UDP receiver init failed", "Error", MB_OK );

        }

    }


#ifdef _WIN32_WCE
// MoveWindow( hDlg, 0, 0, GetSystemMetrics( SM_CXMAXIMIZED ), GetSystemMetrics( SM_CYMAXIMIZED ), FALSE );
#endif /* _WIN32_WCE */
    return true;

}
