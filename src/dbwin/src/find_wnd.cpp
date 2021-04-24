

#include "dbwin.h"


#ifndef _WIN32_WCE
void CMainDlg::FindTheText( HWND /* hEditWnd */, LPCTSTR lpcData, LPFINDREPLACE lpFR ) {

    LPCTSTR lpcTarget;
    DWORD   dwPos;

    // Can't do case-insensitive yet, so if this is the case, fail search.
    lpcTarget = NULL;

    if ( FR_MATCHCASE & lpFR->Flags ) {

        lpcTarget = strstr( lpcData, lpFR->lpstrFindWhat );

    }
    else {

        /* Case insensitive search */

    }

    if ( NULL == lpcTarget ) {

        /* Not found. */
        return;

    }

    /* Calculate offset. */
    dwPos = (DWORD)( lpcTarget - lpcData );

}
#endif /* ! _WIN32_WCE */


#ifndef _WIN32_WCE
void CMainDlg::HandleFindMsg( HWND hDlg, LPFINDREPLACE lpFR ) {

    LPDBWIN_DATA  lpDBWin;
    const TCHAR * pcData;
    DWORD         dwSelStart;
    DWORD         dwSelEnd;

    lpDBWin = (LPDBWIN_DATA)GetWindowLongPtr( hDlg, DWL_USER );

    if ( ! ( FR_FINDNEXT & lpFR->Flags ) ) {

        return;

    }

    if ( NULL == ( pcData = (const TCHAR *)Edit_ClaimTextPtr( lpDBWin->hOutputWnd ) ) ) {

        return;

    }

    /* Establish current position. */
    GetEditSelRange( lpDBWin->hOutputWnd, &dwSelStart, &dwSelEnd );

    FindTheText( lpDBWin->hOutputWnd, pcData, lpFR );

    LocalUnlockPtr( (PVOID)pcData );

}
#endif /* ! _WIN32_WCE */
