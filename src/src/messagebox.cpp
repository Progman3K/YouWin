

//#include "ywin.h"
#include "messagebox.h"
#include "defines.h"

extern HMODULE hYouWinModule;

void MessageBoxDlg::OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

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


static HWND makecontrol( HWND hParentWnd, utf16string * pText, unsigned short uCtlType, unsigned short uID, int iStringID, unsigned uFlags, LPCTSTR lpszText ) {

    if ( pText ) {

        pText->LoadString( hYouWinModule, iStringID );

        lpszText = pText->tcharz_str();

    }

    HWND hWnd = CreateWindowEx( 0, MAKEINTRESOURCE( uCtlType ), lpszText, WS_CHILD | WS_VISIBLE | uFlags, 0, 0, 0, 0, hParentWnd, (HMENU)MAKEINTRESOURCE( uID ), GetWindowInstance( hParentWnd ), 0 );

    return hWnd;

}


void MessageBoxDlg::init( HWND hWnd, HDC hDC, MsgBoxParams & UserParams ) {

    Title = UserParams.lpszTitle; 
    Text = UserParams.lpszText;

    r.left   = 0;
    r.top    = 0;
    r.right  = 0;
    r.bottom = 0;

    DrawText( hDC, Text.c_str(), Text.size(), &r, DT_LEFT | DT_CALCRECT );

    hMessageWnd = makecontrol( hWnd, NULL, ATOM_STATIC, (unsigned short)-1, 0, 0, UserParams.lpszText );

    switch( LONIBBLE( LOBYTE( LOWORD( UserParams.uType ) ) ) ) {

        case MB_OK:

            hOKButtonWnd = makecontrol( hWnd, &OK, ATOM_BUTTON, IDOK, IDS_OK, BS_DEFPUSHBUTTON | WS_TABSTOP, NULL );
            break;

        case MB_OKCANCEL:

            hOKButtonWnd     = makecontrol( hWnd, &OK,     ATOM_BUTTON, IDOK,     IDS_OK,     BS_DEFPUSHBUTTON | WS_TABSTOP, NULL );
            hCancelButtonWnd = makecontrol( hWnd, &Cancel, ATOM_BUTTON, IDCANCEL, IDS_CANCEL, WS_TABSTOP,                    NULL );
            break;

        case MB_YESNO:

            hYesButtonWnd = makecontrol( hWnd, &Yes, ATOM_BUTTON, IDYES, IDS_YES, WS_TABSTOP, NULL );
            hNoButtonWnd  = makecontrol( hWnd, &No,  ATOM_BUTTON, IDNO,  IDS_NO,  WS_TABSTOP, NULL );
            break;

        case MB_YESNOCANCEL:

            hYesButtonWnd    = makecontrol( hWnd, &Yes,    ATOM_BUTTON, IDYES,    IDS_YES,    WS_TABSTOP, NULL );
            hNoButtonWnd     = makecontrol( hWnd, &No,     ATOM_BUTTON, IDNO,     IDS_NO,     WS_TABSTOP, NULL );
            hCancelButtonWnd = makecontrol( hWnd, &Cancel, ATOM_BUTTON, IDCANCEL, IDS_CANCEL, WS_TABSTOP, NULL );
            break;

        default:

            break;

    }

}


void MessageBoxDlg::Layout( HWND hWnd, HDC hDC ) {

    SIZE sTitleSize = {0,0};
    GetTextExtentPoint32( hDC, Title.c_str(), Title.size(), &sTitleSize );

    iButtonCY   = ( sTitleSize.cy * 2 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 );

    SIZE sOK = {0,0};
    GetTextExtentPoint32( hDC, OK.tcharz_str(), OK.tcharz.size(), &sOK );

    SIZE sCancel = {0,0};
    GetTextExtentPoint32( hDC, Cancel.tcharz_str(), Cancel.tcharz.size(), &sCancel );

    SIZE sYes = {0,0};
    GetTextExtentPoint32( hDC, Yes.tcharz_str(), Yes.tcharz.size(), &sYes );

    SIZE sNo = {0,0};
    GetTextExtentPoint32( hDC, No.tcharz_str(), No.tcharz.size(), &sNo );

    SIZE sSPC = {0,0};

    TSTRING SPC = TEXT( " " );

    GetTextExtentPoint32( hDC, SPC.c_str(), SPC.size(), &sSPC );

    lButtonMaxLabelCX = std::max( sOK.cx, sCancel.cx );

    lButtonMaxLabelCX = std::max( lButtonMaxLabelCX, sYes.cx );

    lButtonMaxLabelCX = std::max( lButtonMaxLabelCX, sNo.cx );

    lButtonMaxLabelCX += ( sSPC.cx * 2 ) + ( GetSystemMetrics( SM_CXBORDER ) * 2 );

    iMaxCXLine = std::max( sTitleSize.cx, r.right + ( sSPC.cx * 2 ) );

    switch( LONIBBLE( LOBYTE( LOWORD( Params.uType ) ) ) ) {

        case MB_OK:

            iMaxCXLine = std::max( iMaxCXLine, sSPC.cx + lButtonMaxLabelCX + sSPC.cx );
            break;

        case MB_OKCANCEL:

            iMaxCXLine = std::max( iMaxCXLine, sSPC.cx + lButtonMaxLabelCX + sSPC.cx + lButtonMaxLabelCX + sSPC.cx );
            break;

        case MB_YESNO:

            iMaxCXLine = std::max( iMaxCXLine, sSPC.cx + lButtonMaxLabelCX + sSPC.cx + lButtonMaxLabelCX + sSPC.cx );
            break;

        case MB_YESNOCANCEL:

            iMaxCXLine = std::max( iMaxCXLine, sSPC.cx + lButtonMaxLabelCX + sSPC.cx + lButtonMaxLabelCX + sSPC.cx + lButtonMaxLabelCX + sSPC.cx );
            break;

        default:

            /* INCORRECT FLAGS */
            break;

    }

    iMaxCXLine = std::min( iMaxCXLine, (LONG)GetSystemMetrics( SM_CXSCREEN ) - ( (LONG)GetSystemMetrics( SM_CXFIXEDFRAME ) * 2 ) );

    int iDlgCX = iMaxCXLine + ( GetSystemMetrics( SM_CXFIXEDFRAME ) * 2 ) /* + ( sSPC.cx * 2 ) */;
    int iDlgCY = r.bottom + GetSystemMetrics( SM_CYCAPTION ) + ( GetSystemMetrics( SM_CYFIXEDFRAME ) * 2 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 ) + ( sTitleSize.cy * 3 ) /* + ( sSPC.cy * 2 ) */;

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
                false ); /* No redraw necessary */

    RECT rClient;

    GetClientRect( hWnd, &rClient );

    LONG lPad = 0;

    if ( r.right < rClient.right ) {

        lPad = rClient.right - r.right;
        lPad /= 2;

    }

    MoveWindow( hMessageWnd, 0 + lPad, 0 + ( sSPC.cy / 4 ), r.right, r.bottom, false );

    int iButtonYpos = r.bottom + GetSystemMetrics( SM_CYFIXEDFRAME ) + ( sSPC.cy / 2 );
//    int iButtonYpos = rClient.bottom - ( ( TitleSize.cy * 2 ) + ( GetSystemMetrics( SM_CYBORDER ) * 2 ) );

    switch( LONIBBLE( LOBYTE( LOWORD( Params.uType ) ) ) ) {

        case MB_OK:

            MoveWindow( hOKButtonWnd, ( rClient.right / 2 ) - ( lButtonMaxLabelCX / 2 ), iButtonYpos, lButtonMaxLabelCX, iButtonCY,false );
            break;

        case MB_OKCANCEL: {

                LONG lSegment = rClient.right / 2;

                lPad = 0;

                if ( lSegment > lButtonMaxLabelCX ) {

                    lPad = lSegment - lButtonMaxLabelCX;
                    lPad /= 2;

                }

                MoveWindow( hOKButtonWnd, lPad, iButtonYpos, lButtonMaxLabelCX, iButtonCY, false );
                MoveWindow( hCancelButtonWnd, lSegment + lPad, iButtonYpos, lButtonMaxLabelCX,  iButtonCY, false );

            }
            break;

        case MB_YESNO: {

                LONG lSegment = rClient.right / 2;

                lPad = 0;

                if ( lSegment > lButtonMaxLabelCX ) {

                    lPad = lSegment - lButtonMaxLabelCX;
                    lPad /= 2;

                }

                MoveWindow( hYesButtonWnd, lPad, iButtonYpos, lButtonMaxLabelCX, iButtonCY, false );
                MoveWindow( hNoButtonWnd, lSegment + lPad, iButtonYpos, lButtonMaxLabelCX,  iButtonCY, false );

            }
            break;

        case MB_YESNOCANCEL: {

                LONG lSegment = rClient.right / 3;

                lPad = 0;

                if ( lSegment > lButtonMaxLabelCX ) {

                    lPad = lSegment - lButtonMaxLabelCX;
                    lPad /= 2;

                }

                MoveWindow( hYesButtonWnd, lPad, iButtonYpos, lButtonMaxLabelCX, iButtonCY, false );
                MoveWindow( hNoButtonWnd, lSegment + lPad, iButtonYpos, lButtonMaxLabelCX,  iButtonCY, false );
                MoveWindow( hCancelButtonWnd, ( lSegment * 2 ) + lPad, iButtonYpos, lButtonMaxLabelCX,  iButtonCY, false );

            }
            break;

        default:

            break;

    }

}


BOOL MessageBoxDlg::OnInit( HWND hWnd, HWND hFocusWnd, LPARAM lParam ) {

    Params = *( (MsgBoxParams *)lParam );

    SetWindowText( hWnd, ( NULL == Params.lpszTitle ) ? TEXT( "Error" ) : Params.lpszTitle );

    HDC hDC = GetDC( hWnd );

    init( hWnd, hDC, Params );

    Layout( hWnd, hDC );

    ReleaseDC( hWnd, hDC );

    return true;

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
