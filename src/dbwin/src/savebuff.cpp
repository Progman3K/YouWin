

#include "dbwin.h"


int CMainDlg::WriteEditToFile( HWND hDlg, FILE * hFile, LPARAM /* lParam */ ) {

    HWND          hEditWnd;
    TCHAR const * pcData;
    UINT          uiLen;

    if ( NULL == ( hEditWnd = GetDlgItem( hDlg, IDE_OUTPUT ) ) ) {

        return -1;

    }

    if ( 0 == ( uiLen = (UINT)Edit_GetTextLength( hEditWnd ) ) ) {

        return -1;

    }

#if defined( _WIN32_WCE ) || defined( _WIN32 )
    if ( NULL == ( pcData = (LPTSTR)GlobalAllocPtr( GHND, sizeof( TCHAR ) * ( uiLen + 1 ) ) ) ) {

        return -1;

    }

    GetWindowText( hEditWnd, (LPTSTR)pcData, uiLen );

    uiLen = lstrlen( pcData );
#else
    if ( NULL == ( pcData = (LPCTSTR)Edit_ClaimTextPtr( hEditWnd ) ) ) {

        return -1;

    }
#endif /* ! _WIN32_WCE || _WIN32 */

    fwrite( (LPVOID)pcData, sizeof( TCHAR ) * uiLen, 1, hFile );

#if defined( _WIN32_WCE ) || defined( _WIN32 )
    GlobalFreePtr( (PVOID)pcData );
#else
    LocalUnlockPtr( (PVOID)pcData );
#endif /* ! _WIN32_WCE || _WIN32 */

    return 0;

}



        typedef LRESULT (* FNOPENFNAMEHOOK)(HWND, UINT, WPARAM, LPARAM);

        typedef int (* WRITEFILEPROC)( HWND hParentWnd, FILE * hFile, LPARAM lParam );

        static int iSaveTo( HWND hParentWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, WRITEFILEPROC lpfnWriteFileProc, LPARAM lParam, HINSTANCE hInst ) {

            FILE * hFile;
            int         iRet = IDOK;

            {

//                TCHAR   szFileName[4096];

//                ZeroMemory( szFileName, sizeof ( szFileName ) );

//                _tcsncpy( szFileName, lpszRet, Dim( szFileName ) - 1 );

                if ( ! bFind( hParentWnd, uFileFilter, cSeparator, lpszDialogTitle, lpszRet, uszRetBufSize, dwFlags, lpszInitialDir, lpfnDlgHookProc, hInst ) ) {

                    return IDCANCEL;

                }

//                if ( NULL != lpszRet ) {

//                    _tcsncpy( lpszRet, szFileName, uszRetBufSize );

//                }

                {

                    if ( INVALID_HANDLE_VALUE == ( hFile = fopen( lpszRet, "w" ) ) ) {

                        return -1;

                    }

                }


            }   /* Reclaim stack-frame space. */

            if ( NULL != lpfnWriteFileProc ) {

                iRet = lpfnWriteFileProc( hParentWnd, hFile, lParam );

            }

            fclose( hFile );

            return iRet;

        }





void CMainDlg::DoSaveDebugBuffer( HWND hDlg ) {

    iSaveTo(

        hDlg,
        IDS_SAVE_BUFFER_AS_TYPES,
        '|',
        MAKEINTRESOURCE( IDS_SAVE_BUFFER_AS ),
        NULL,
        0,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
#ifdef _WIN32
        | OFN_EXPLORER | OFN_NOREADONLYRETURN | OFN_NOCHANGEDIR
#endif
        ,
        NULL,
        NULL,
        WriteEditToFile, 0,
        g_hInst

    );

}
