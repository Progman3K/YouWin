

#include "dbwin.h"


BOOL CMainDlg::GetEditSelRange( HWND hEditWnd, LPDWORD lpdwSelStart, LPDWORD lpdwSelEnd ) {

#ifdef _WIN32

	SendMessage( hEditWnd, EM_GETSEL, (WPARAM)lpdwSelStart, (LPARAM)lpdwSelEnd );

#else	/* ! _WIN32 */

	DWORD	dwSel;

	dwSel = Edit_GetSel( hEditWnd );

	if ( NULL != lpdwSelStart ) {

		*lpdwSelStart	=	LOWORD( dwSel );

	}
	
	if ( NULL != lpdwSelEnd ) {

		*lpdwSelEnd		=	HIWORD( dwSel );

	}

#endif	/* ! _WIN32 */

	return true;

}
