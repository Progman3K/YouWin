

#include "dbwin.h"


#if 0	/* This code superseded by OnInitMenuPopup because of WindowsCE. */
void CMainDlg::OnInitMenu( HWND hDlg, HMENU hMenu ) {

	DWORD			dwStyles;
	LPDBWIN_DATA	lpDBWin;

	lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

	if ( 0 == GetWindowTextLength( lpDBWin->hOutputWnd ) ) {

		EnableMenuItem( hMenu, IDM_COPY,			MF_BYCOMMAND | MF_GRAYED );
		EnableMenuItem( hMenu, IDM_CLEAR_OUTPUT,	MF_BYCOMMAND | MF_GRAYED );
		EnableMenuItem( hMenu, IDM_SELECT_ALL,		MF_BYCOMMAND | MF_GRAYED );
		EnableMenuItem( hMenu, IDM_SAVE_BUFFER_AS,	MF_BYCOMMAND | MF_GRAYED );
		EnableMenuItem( hMenu, IDM_FIND,			MF_BYCOMMAND | MF_GRAYED );

	}
	else {

		EnableMenuItem( hMenu, IDM_COPY,			MF_BYCOMMAND | MF_ENABLED );
		EnableMenuItem( hMenu, IDM_CLEAR_OUTPUT,	MF_BYCOMMAND | MF_ENABLED );
		EnableMenuItem( hMenu, IDM_SELECT_ALL,		MF_BYCOMMAND | MF_ENABLED );
		EnableMenuItem( hMenu, IDM_SAVE_BUFFER_AS,	MF_BYCOMMAND | MF_ENABLED );
		EnableMenuItem( hMenu, IDM_FIND,			MF_BYCOMMAND | MF_ENABLED );

	}

	dwStyles = GetWindowLong( hDlg, GWL_EXSTYLE );

	if ( WS_EX_TOPMOST & dwStyles ) {

		CheckMenuItem( hMenu, IDM_ALWAYS_ON_TOP_TOGGLE, MF_BYCOMMAND | MF_CHECKED );

	}
	else {

		CheckMenuItem( hMenu, IDM_ALWAYS_ON_TOP_TOGGLE, MF_BYCOMMAND | MF_UNCHECKED );

	}
	
	DrawMenuBar( hDlg );

}
#endif
