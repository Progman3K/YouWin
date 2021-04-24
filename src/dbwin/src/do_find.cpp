

#include "dbwin.h"


#ifndef	_WIN32_WCE
void CMainDlg::DoFind( HWND hDlg, LPFINDREPLACE lpFR, LPCTSTR lpszInitialText, WORD wInitialTextBufferSize, LPFRHOOKPROC lpfnHook, LPARAM lParam ) {

	static	HWND	hFindDlg	=	NULL;

	if ( IsWindow( hFindDlg ) ) {

		SetFocus( hFindDlg );
		return;

	}

	ZeroMemory( lpFR, sizeof( FINDREPLACE ) );

	lpFR->lStructSize	=	sizeof( FINDREPLACE );
	lpFR->hwndOwner		=	hDlg;
	lpFR->lpstrFindWhat	=	(LPTSTR)lpszInitialText;
	lpFR->wFindWhatLen	=	wInitialTextBufferSize;
	lpFR->Flags			=	FR_DOWN;
	lpFR->lpfnHook		=	lpfnHook;
	lpFR->lCustData		=	lParam;

	hFindDlg = FindText( lpFR );

}
#endif	/* ! _WIN32_WCE */
