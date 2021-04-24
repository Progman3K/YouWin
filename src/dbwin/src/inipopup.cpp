

#include "dbwin.h"


void CMainDlg::OnInitMenuPopup( HWND hDlg, HMENU hMenu, UINT uiItem, BOOL /* bSystemMenu */ ) {

    DWORD        dwTextLength;
    LPDBWIN_DATA lpDBWin;

    lpDBWin = (LPDBWIN_DATA)GetWindowLongPtr( hDlg, DWL_USER );

    dwTextLength = GetWindowTextLength( lpDBWin->hOutputWnd );

    switch( uiItem ) {

        case MENU_POPUP_FILE:

            if( 0 == dwTextLength ) {

                EnableMenuItem( hMenu, IDM_SAVE_BUFFER_AS,	MF_BYCOMMAND | MF_GRAYED );
            }
            else {

                EnableMenuItem( hMenu, IDM_SAVE_BUFFER_AS,	MF_BYCOMMAND | MF_ENABLED );

            }
            break;

        case MENU_POPUP_EDIT:

            if( 0 == dwTextLength ) {

                EnableMenuItem( hMenu, IDM_COPY,			MF_BYCOMMAND | MF_GRAYED );
                EnableMenuItem( hMenu, IDM_CLEAR_OUTPUT,	MF_BYCOMMAND | MF_GRAYED );
                EnableMenuItem( hMenu, IDM_SELECT_ALL,		MF_BYCOMMAND | MF_GRAYED );
                EnableMenuItem( hMenu, IDM_FIND,			MF_BYCOMMAND | MF_GRAYED );
            }
            else {

                EnableMenuItem( hMenu, IDM_COPY,			MF_BYCOMMAND | MF_ENABLED );
                EnableMenuItem( hMenu, IDM_CLEAR_OUTPUT,	MF_BYCOMMAND | MF_ENABLED );
                EnableMenuItem( hMenu, IDM_SELECT_ALL,		MF_BYCOMMAND | MF_ENABLED );
                EnableMenuItem( hMenu, IDM_FIND,			MF_BYCOMMAND | MF_ENABLED );

            }
            break;

        case MENU_POPUP_OPTIONS:

            if ( lpDBWin->bNoOutput ) {

                CheckMenuItem( hMenu, IDM_OUTPUT_DISABLE,	MF_BYCOMMAND | MF_CHECKED	);
                CheckMenuItem( hMenu, IDM_OUTPUT_TO_WINDOW,	MF_BYCOMMAND | MF_UNCHECKED	);

            }
            else {

                CheckMenuItem( hMenu, IDM_OUTPUT_DISABLE,	MF_BYCOMMAND | MF_UNCHECKED	);
                CheckMenuItem( hMenu, IDM_OUTPUT_TO_WINDOW,	MF_BYCOMMAND | MF_CHECKED	);

            }

            if ( 0 == lpDBWin->hOutputFile ) {

                CheckMenuItem( hMenu, IDM_OUTPUT_TO_FILE,	MF_BYCOMMAND | MF_UNCHECKED	);

            }
            else {

                CheckMenuItem( hMenu, IDM_OUTPUT_TO_FILE,	MF_BYCOMMAND | MF_CHECKED	);

            }

#ifndef _WIN32_WCE
            {

                DWORD	dwStyles;

                dwStyles = GetWindowLong( hDlg, GWL_EXSTYLE );

                if ( WS_EX_TOPMOST & dwStyles ) {

                    CheckMenuItem( hMenu, IDM_ALWAYS_ON_TOP_TOGGLE, MF_BYCOMMAND | MF_CHECKED );

                }
                else {

                    CheckMenuItem( hMenu, IDM_ALWAYS_ON_TOP_TOGGLE, MF_BYCOMMAND | MF_UNCHECKED );

                }

            }
#endif /* ! _WIN32_WCE */
            break;

        case MENU_POPUP_CLEAR:

            break;

        case MENU_POPUP_HELP:

            break;

    }

#ifndef _WIN32_WCE
    DrawMenuBar( hDlg );
#endif /* ! _WIN32_WCE */

}
