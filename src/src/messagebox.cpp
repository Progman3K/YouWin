

//#include "ywin.h"
#include "messagebox.h"
#include "defines.h"


extern HMODULE hYouWinModule;


void MessageBoxDlg::OnCommand( HWND hDlg, int iID, HWND /* hCtlWnd */, UINT /* uiNotifyCode */ ) {

    switch( iID ) {

        case IDCANCEL:

            if ( ! ( ( MB_CANCELTRYCONTINUE == ( MB_CANCELTRYCONTINUE & Params.uType ) ) || ( MB_OKCANCEL == ( MB_OKCANCEL & Params.uType ) ) || ( MB_RETRYCANCEL == ( MB_RETRYCANCEL & Params.uType ) ) || ( MB_YESNOCANCEL == ( MB_YESNOCANCEL & Params.uType ) ) ) ) {

                /* Pressing ESC is NOT a valid choice, ignore it */
                break;

            }

            /* FALL THROUGH */

        case IDABORT:
        case IDCONTINUE:
        case IDIGNORE:
        case IDNO:
        case IDOK:
        case IDRETRY:
        case IDTRYAGAIN:
        case IDYES:

            EndDialog( hDlg, iID );
            break;

    }

}


static HWND makecontrol( HWND hParentWnd, int x, int y, utf16string * pText, unsigned short uCtlType, unsigned short uID, int iStringID, unsigned uFlags, LPCTSTR lpszText, const TCHAR * pParam ) {

    utf16string text;

    if ( pText ) {

        pText->LoadString( hYouWinModule, iStringID );

        lpszText = pText->tcharz_str();

    } else if ( iStringID ) {

        text.LoadString( hYouWinModule, iStringID );
        lpszText = text.tcharz_str();

    }

    HWND hWnd = CreateWindowEx( 0, MAKEINTRESOURCE( uCtlType ), lpszText, WS_CHILD | WS_VISIBLE | uFlags, x, y, 0, 0, hParentWnd, (HMENU)MAKEINTRESOURCE( uID ), hYouWinModule /* GetWindowInstance( hParentWnd ) */, (LPVOID)pParam );

    return hWnd;

}


HWND MessageBoxDlg::makebutton( HWND hParentWnd, unsigned short uCtlType, unsigned short uID, int iStringID, unsigned uFlags, LPCTSTR lpszText, const TCHAR * pParam ) {

    HWND hButtonWnd = makecontrol( hParentWnd, 0, 0, NULL, uCtlType, uID, iStringID, uFlags, lpszText, pParam );

    if ( hButtonWnd ) {

        buttons.push_back( hButtonWnd );

    }

    return hButtonWnd;

}


void MessageBoxDlg::buttonselect( unsigned uButtonIndex ) {

    if ( uButtonIndex >= buttons.size() ) {

        return;

    }

    SetFocus( buttons.at( uButtonIndex ) );

}


void MessageBoxDlg::init( HWND hWnd, HDC hDC, MsgBoxParams & UserParams ) {

    Title = UserParams.lpszTitle; 
    Text = UserParams.lpszText;

    r.left   = 0;
    r.top    = 0;
    r.right  = 0;
    r.bottom = 0;

    DrawText( hDC, Text.c_str(), Text.size(), &r, DT_LEFT | DT_CALCRECT );

    hMessageWnd = makecontrol( hWnd, 0, 0, NULL, ATOM_STATIC, (unsigned short)-1, 0, 0, UserParams.lpszText, 0 );

    switch( LONIBBLE( LOBYTE( LOWORD( UserParams.uType ) ) ) ) {

        case MB_OK:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDOK,       IDS_OK, WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_OKCANCEL:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDOK,       IDS_OK,     WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDCANCEL,   IDS_CANCEL, WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_ABORTRETRYIGNORE:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDABORT,    IDS_ABORT,  WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDRETRY,    IDS_RETRY,  WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDIGNORE,   IDS_IGNORE, WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_YESNOCANCEL:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDYES,      IDS_YES,    WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDNO,       IDS_NO,     WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDCANCEL,   IDS_CANCEL, WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_YESNO:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDYES,      IDS_YES, WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDNO,       IDS_NO,  WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_RETRYCANCEL:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDRETRY,    IDS_RETRY,  WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDCANCEL,   IDS_CANCEL, WS_TABSTOP, NULL, 0 )
            } );
            break;

        case MB_CANCELTRYCONTINUE:

            makebuttons( {
                button_def( hWnd, ATOM_BUTTON, IDCANCEL,   IDS_CANCEL,   WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDTRYAGAIN, IDS_TRYAGAIN, WS_TABSTOP, NULL, 0 ),
                button_def( hWnd, ATOM_BUTTON, IDCONTINUE, IDS_CONTINUE, WS_TABSTOP, NULL, 0 )
            } );
            break;

        default:

            break;

    }

    hIconWnd = 0;

    int x = GetSystemMetrics( SM_CXEDGE );
    int y = GetSystemMetrics( SM_CYEDGE );

    switch( HINIBBLE( LOBYTE( LOWORD( UserParams.uType ) ) ) ) {

        case MB_ICONHAND /* aka MB_ICONERROR, MB_ICONSTOP */:

            hIconWnd = makecontrol( hWnd, x, y, NULL, ATOM_STATIC, IDST_ICON, 0, SS_ICON, NULL, MAKEINTRESOURCE( IDI_HAND ) );
            break;

        case MB_ICONQUESTION:

            hIconWnd = makecontrol( hWnd, x, y, NULL, ATOM_STATIC, IDST_ICON, 0, SS_ICON, NULL, MAKEINTRESOURCE( IDI_QUESTION ) );
            break;

        case MB_ICONEXCLAMATION /* aka MB_ICONWARNING */:

            hIconWnd = makecontrol( hWnd, x, y, NULL, ATOM_STATIC, IDST_ICON, 0, SS_ICON, NULL, MAKEINTRESOURCE( IDI_EXCLAMATION ) );
            break;

        case MB_ICONASTERISK /* aka MB_ICONINFORMATION */:

            hIconWnd = makecontrol( hWnd, x, y, NULL, ATOM_STATIC, IDST_ICON, 0, SS_ICON, NULL, MAKEINTRESOURCE( IDI_ASTERISK ) );
            break;

        default:

            break;

    }

    if ( hIconWnd ) {

        RECT r = {0};

        GetClientRect( hIconWnd, &r );

        Icon.cx = r.right;
        Icon.cy = r.bottom;

    }

    u_int16_t uButtonSelection = LOWORD( Params.uType ) & 0xFF00;

    switch( uButtonSelection ) {

        case MB_DEFBUTTON2:

            buttonselect( 1 );
            break;

        case MB_DEFBUTTON3:

            buttonselect( 2 );
            break;

        case MB_DEFBUTTON4:

            buttonselect( 3 );
            break;

        case MB_DEFBUTTON1:
        default:

            buttonselect( 0 );
            break;

    }

}


SIZE GetWidestButton( HDC hDC, std::vector<HWND> & buttons ) {

    SIZE s = {};

    for( auto button : buttons ) {

        auto Len = GetWindowTextLength( button );

        if ( ! Len ) {

            continue;

        }

        TCHAR windowtext[128] = {};

        auto LenRead = GetWindowText( button, windowtext, ( sizeof( windowtext ) / sizeof( windowtext[0] ) ) - 1 );

        if ( ! LenRead ) {

            continue;

        }

        SIZE b = {};

        GetTextExtentPoint32( hDC, windowtext, LenRead, &b );

        s.cx = std::max( s.cx, b.cx );

    }

    return s;

}


void MessageBoxDlg::Layout( HWND hWnd, HDC hDC ) {

    SIZE sTitleSize = {0,0};
    GetTextExtentPoint32( hDC, Title.c_str(), Title.size(), &sTitleSize );

    iButtonCY   = ( sTitleSize.cy * 2 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 );

    lButtonMaxLabelCX = GetWidestButton( hDC, buttons ).cx;

    SIZE sSPC = {0,0};

    TSTRING SPC = TEXT( " " );

    GetTextExtentPoint32( hDC, SPC.c_str(), SPC.size(), &sSPC );

    lButtonMaxLabelCX += ( sSPC.cx * 2 ) + ( GetSystemMetrics( SM_CXBORDER ) * 2 );

    iMaxCXLine = std::max( sTitleSize.cx, r.right + ( sSPC.cx * 2 ) );

    iMaxCXLine = std::max( iMaxCXLine, (LONG)( ( buttons.size() * ( sSPC.cx * 2 ) ) + ( buttons.size() * lButtonMaxLabelCX ) ) );

    iMaxCXLine = std::min( iMaxCXLine, (LONG)GetSystemMetrics( SM_CXSCREEN ) - ( (LONG)GetSystemMetrics( SM_CXFIXEDFRAME ) * 2 ) );

    RECT rIcon = {0};

    if ( hIconWnd ) {

        GetClientRect( hIconWnd, &rIcon );

    }

    int iDlgCX = rIcon.right + iMaxCXLine + ( GetSystemMetrics( SM_CXFIXEDFRAME ) * 2 ) /* + ( sSPC.cx * 2 ) */;
    int iDlgCY = rIcon.bottom + r.bottom + GetSystemMetrics( SM_CYCAPTION ) + ( GetSystemMetrics( SM_CYFIXEDFRAME ) * 2 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 ) + ( sTitleSize.cy * 3 ) /* + ( sSPC.cy * 2 ) */;

    LONG lPadDlgCX = 0;
    LONG lPadDlgCY = 0;

    if ( iDlgCX < GetSystemMetrics( SM_CXSCREEN ) ) {

        lPadDlgCX = GetSystemMetrics( SM_CXSCREEN ) - iDlgCX;
        lPadDlgCX /= 2;
        lPadDlgCX += ( sSPC.cx / 2 );

    }

    if ( iDlgCY < GetSystemMetrics( SM_CYSCREEN ) ) {

        lPadDlgCY = GetSystemMetrics( SM_CYSCREEN ) - iDlgCY;
        lPadDlgCY /= 2;
        lPadDlgCY += ( sSPC.cy / 2 );

    }

    MoveWindow( hWnd,
                lPadDlgCX,
                lPadDlgCY,
                iDlgCX,
                iDlgCY,
                true );

    RECT rClient;

    GetClientRect( hWnd, &rClient );

    LONG lPad = 0;

    if ( r.right < rClient.right ) {

        lPad += rClient.right - r.right;
        lPad /= 2;
        lPad += ( rIcon.right / 4 );

    }

    MoveWindow( hMessageWnd, 0 + lPad, 0 + ( sSPC.cy / 4 ) + ( rIcon.bottom / 4 ), r.right, r.bottom, false );

    int iButtonYpos = r.bottom + GetSystemMetrics( SM_CYFIXEDFRAME ) + ( sSPC.cy / 2 ) + ( rIcon.bottom / 2 );

    if ( ! buttons.size() ) {

        return;

    }

    LONG lSegment = rClient.right / buttons.size();

    lPad = 0;

    if ( lSegment > lButtonMaxLabelCX ) {

        lPad = lSegment - lButtonMaxLabelCX;
        lPad /= 2;

    }

    for( unsigned u = 0; u < buttons.size(); u++ ) {

        MoveWindow( buttons.at( u ), ( lSegment * u ) + lPad, iButtonYpos, lButtonMaxLabelCX,  iButtonCY, false );

    }

}


BOOL MessageBoxDlg::OnInit( HWND hWnd, HWND /* hFocusWnd */, LPARAM lParam ) {

    Params = *( (MsgBoxParams *)lParam );

    SetWindowText( hWnd, ( NULL == Params.lpszTitle ) ? TEXT( "Error" ) : Params.lpszTitle );

    HDC hDC = GetDC( hWnd );

    init( hWnd, hDC, Params );

    Layout( hWnd, hDC );

    ReleaseDC( hWnd, hDC );

    /* Focus was set manually */
    return false;

}


void MessageBoxDlg::OnDisplayChange( HWND hWnd, UINT, UINT, UINT ) {

    HDC hDC = GetDC( hWnd );

    Layout( hWnd, hDC );

    ReleaseDC( hWnd, hDC );

}


INT_PTR MessageBoxDlg::bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CLOSE:

            // This will prevent de dialog closing except by explicit command from the user
            break;

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
            break;

        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hWnd, wParam, lParam, OnDisplayChange );
            return false;
            break;

        case WM_INITDIALOG:

            return HANDLE_WM_INITDIALOG( hWnd, wParam, lParam, OnInit );

        default:

            return false;

    }

    return true;

}


int MessageBox( HWND hWnd, LPCTSTR lpszText, LPCTSTR lpszTitle, UINT uType ) {

    MsgBoxParams Params;

    ZeroMemory( &Params, sizeof( Params ) );

    Params.lpszText   = lpszText;
    Params.lpszTitle  = ( NULL == lpszTitle ) ? TEXT( "Error" ) : lpszTitle;
    Params.uType      = uType;

    union {

        DLGTEMPLATE Header;
        char        cData[sizeof( DLGTEMPLATE ) + ( sizeof( WORD ) * 8 ) ];

    } Dialog;

    ZeroMemory( &Dialog, sizeof( Dialog ) );

    Dialog.Header.style           = WS_POPUP | WS_CAPTION | WS_DLGFRAME;

    return DialogBoxIndirectParam( NULL, (LPCDLGTEMPLATE)&Dialog, hWnd, MessageBoxDlg::bDlgProc, (LPARAM)&Params );

}
