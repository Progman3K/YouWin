

#include "dbwin.h"


void CMainDlg::ProcessUserData( LPDBWIN_DATA lpDBWin, COPYDATASTRUCT * lpCD ) {

    LPTSTR lpszCursor;
    LPTSTR lpEOL;

    lpszCursor = (LPTSTR)lpCD->lpData;

    for( ;; ) {

        if ( NULL == ( lpEOL = strchr( lpszCursor, '\n' ) ) ) {

            /* Single line of text, send to output and end. */

            if ( '\0' == (*lpszCursor) ) {

                /* Blank line. */
                break;

            }

            EditText::AppendTextEx( g_hInst, lpDBWin->hOutputWnd, lpszCursor, strlen( lpszCursor ), false, false );
            EditText::AppendTextEx( g_hInst, lpDBWin->hOutputWnd, TEXT( "" ), 0, true, false );
            break;

        }
        else {

            /* Multiple lines of text. */

            /* Split this line off from the rest. */
            *lpEOL = '\0';

            EditText::AppendTextEx( g_hInst, lpDBWin->hOutputWnd, lpszCursor, strlen( lpszCursor ), false, false );
            EditText::AppendTextEx( g_hInst, lpDBWin->hOutputWnd, TEXT( "" ), 0, true, false );

            /* Point past null to next line of text. */
            lpszCursor = lpEOL;
            lpszCursor++;

        }

    }

}


void WriteLogFile( FILE * hFile, DWORD dwMaxFileSize, LPVOID lpData, DWORD dwNumBytes ) {

    DWORD dwSpaceLeft;
    DWORD dwCurrentPosition;
    DWORD dwBytesWritten;
    TCHAR cEOT;

    cEOT = EOFMARKER;

    for( ;; ) {

        dwCurrentPosition = ftell( hFile );

        if ( (DWORD)-1 == dwCurrentPosition ) {

            break;

        }

        /* Check that there is NO wraparound. */	
        if ( ( dwCurrentPosition + dwNumBytes + sizeof( cEOT ) ) <= ( dwMaxFileSize * 1024 ) ) {

            /* Dump data to disk. */
            fwrite( lpData, (int)dwNumBytes, 1, hFile );

            /* Save true END OF DATA position. */
            dwCurrentPosition = ftell( hFile );

            if ( (DWORD)-1 == dwCurrentPosition ) {

                break;

            }

            /* Append EOF. */
            fwrite( &cEOT, sizeof( cEOT ), 1, hFile );

            /* Restore write pointer to overwrite EOF on next ouput. */
            fseek( hFile, dwCurrentPosition, SEEK_SET );
            return;

        }

        /* Calculate just how much space IS left. */
        dwSpaceLeft = ( dwMaxFileSize * 1024 ) - dwCurrentPosition;

        if ( 0 == dwSpaceLeft ) {

            fseek( hFile, 0, SEEK_SET );
            dwCurrentPosition = 0;

        }

        dwBytesWritten = std::min( dwSpaceLeft, dwNumBytes );

        fwrite( lpData, (int)dwBytesWritten, 1, hFile );
        fseek( hFile, 0, SEEK_SET );

        lpData = ( (LPBYTE)lpData + dwBytesWritten );
        dwNumBytes -= dwBytesWritten;

    }

}


LPVOID MemDup( LPVOID lpSource, DWORD dwLen ) {

    LPVOID lpv;

    lpv = malloc( (UINT)dwLen );

    if ( NULL == lpv ) {

        return NULL;

    }

    memcpy( lpv, lpSource, (UINT)dwLen );

    return lpv;

}


BOOL CMainDlg::bOnCopyData( HWND hDlg, HWND /* hFromWnd */, COPYDATASTRUCT * lpCD ) {

    LPDBWIN_DATA   lpDBWin;
    COPYDATASTRUCT CD;

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    if ( lpDBWin->bNoOutput ) {

        return true;

    }

    /* Copy most of the information */
    CD = *lpCD;

    /* Allocate private copy of the data. */
    if ( NULL == ( CD.lpData = MemDup( lpCD->lpData, lpCD->cbData ) ) ) {

        return false;

    }

#if ! defined( _WIN32_WCE ) && defined( _WIN32 )

    /* Release caller. */
    ReplyMessage( true );

#endif	/* ! _WIN32_WCE && WIN32 */

    if ( 0 != lpDBWin->hOutputFile ) {

        if ( sizeof( TCHAR ) < CD.cbData ) {

            WriteLogFile( lpDBWin->hOutputFile, lpDBWin->dwMaxFileSize, CD.lpData, CD.cbData - sizeof( TCHAR ) );

        }

    }

    ProcessUserData( lpDBWin, &CD );

    free( CD.lpData );

    /* Repaint soon because we have new text. */
    SetTimer( hDlg, ID_UPDATE_OUTPUT_TIMER, 5000, NULL );

    return true;

}
