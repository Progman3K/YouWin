

#include "dbwin.h"


void CMainDlg::ToggleWordWrap( HWND hEditWnd, BOOL bWordWrap ) {

    DWORD dwStyles;

    dwStyles = GetWindowLong( hEditWnd, GWL_STYLE );

    if ( bWordWrap ) {

        dwStyles = dwStyles & ( ~( ES_AUTOHSCROLL | WS_HSCROLL ) );
        SetWindowLong( hEditWnd, GWL_STYLE, dwStyles );

    } else {

        SetWindowLong( hEditWnd, GWL_STYLE, ( ES_AUTOHSCROLL | WS_HSCROLL | dwStyles ) );

    }

}
