

#include "chatter.h"


BOOL CChatterMainWnd::OnInit( HWND hDlg, HWND /* hFocusWnd */, LPARAM lParam ) {

    LPSTARTUP_INFO lpsi;

    lpsi = (LPSTARTUP_INFO)lParam;

    pMe = lpsi->me;

#if 0 // ndef NDEBUG

    RECT r;

    r.right  = 0;
    r.top    = 0;
    r.left   = 10;
    r.bottom = 10;
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Rectangle transforms %d,%d,%d,%d to" ), r.right, r.top, r.left, r.bottom );
    MapDialogRect( hDlg, &r );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "                     %d,%d,%d,%d\n" ), r.right, r.top, r.left, r.bottom );

    r.right  = 1;
    r.top    = 1;
    r.left   = 10;
    r.bottom = 10;
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Rectangle transforms %d,%d,%d,%d to" ), r.right, r.top, r.left, r.bottom );
    MapDialogRect( hDlg, &r );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "                     %d,%d,%d,%d\n" ), r.right, r.top, r.left, r.bottom );

    r.right  = 10;
    r.top    = 10;
    r.left   = 100;
    r.bottom = 100;
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Rectangle transforms %d,%d,%d,%d to" ), r.right, r.top, r.left, r.bottom );
    MapDialogRect( hDlg, &r );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "                     %d,%d,%d,%d" ), r.right, r.top, r.left, r.bottom );

#endif

    HINSTANCE hInst = GetWindowInstance( hDlg );

//  Ctl3dSubclassDlgEx( hDlg, CTL3D_ALL );

    TCHAR szString[MAX_TEMPSTRING_SIZE];

    char szHost[128];

    ZeroMemory( szHost, sizeof( szHost ) );

    gethostname( szHost, Dim( szHost ) - 1 );

	textstring Host;

	Host.absorb( szHost );

    _stprintf( szString, TEXT( "%s on %s" ), (LPTSTR)TEXT( IDSZ_APPNAME ), Host.c_str() );

#ifndef _WIN32_WCE
    SetWindowText( hDlg, szString );
#endif

    if ( bIsTextMode() ) {

        portrait.Record( hInst, MAKEINTRESOURCE( IDD_CHATTER_MAIN_TEXT_PORTRAIT ), hDlg );
        landscape.Record( hInst, MAKEINTRESOURCE( IDD_CHATTER_MAIN_TEXT ), hDlg );

    } else {

        portrait.Record( hInst, MAKEINTRESOURCE( IDD_CHATTER_MAIN_FOR_ANDROID_PORTRAIT ), hDlg );
        landscape.Record( hInst, MAKEINTRESOURCE( IDD_CHATTER_MAIN_FOR_ANDROID_LANDSCAPE ), hDlg );

    }

    if ( NULL == ( hAppIcon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN ) ) ) ) {

        return false;

    }

    if ( NULL == ( hHatAnimIcon[0] = LoadIcon( hInst, MAKEINTRESOURCE( IDI_BLINK1 ) ) ) ) {

        return false;

    }

    if ( NULL == ( hHatAnimIcon[1] = LoadIcon( hInst, MAKEINTRESOURCE( IDI_BLINK2 ) ) ) ) {

        return false;

    }

    if ( NULL == ( hHatAnimIcon[2] = LoadIcon( hInst, MAKEINTRESOURCE( IDI_BLINK3 ) ) ) ) {

        return false;

    }

    if ( NULL == ( hHatAnimIcon[3] = LoadIcon( hInst, MAKEINTRESOURCE( IDI_BLINK4 ) ) ) ) {

        return false;

    }

//  if ( NULL == ( hHatAnimIcon[4] = LoadIcon( hInst, MAKEINTRESOURCE( IDI_BLINK5 ) ) ) ) {

//      return FALSE;

//  }

    if ( NULL == ( hFileXfer = GetDlgItem( hDlg, IDPB_FILEXFER ) ) ) {

        return false;

    }

    if ( NULL == ( hUserListWnd = GetDlgItem( hDlg, IDLB_USERLIST ) ) ) {

        return false;

    }

    if ( NULL == ( hOutputWnd = GetDlgItem( hDlg, IDE_OUTPUT ) ) ) {

        return false;

    }

    if ( NULL == ( hInputWnd = GetDlgItem( hDlg, IDE_USER_INPUT ) ) ) {

        return false;

    }

    Edit_LimitText( hInputWnd, MAX_DATA_LENGTH - 1 );

    //  Button_SetCheck( GetDlgItem( hDlg, IDB_MUTE ), g_bMute ? BST_CHECKED : BST_UNCHECKED );

    /* Announce every two minutes */
    if ( 0 == SetTimer( hDlg, ID_CHATTER_BROADCAST_TIMER, ( BROADCAST_TIMER_INTERVAL_SECONDS * 1000 ), NULL ) ) {

        return false;

    }

    WSAAsyncSelect( pMe->GetSocket(), hDlg, WM_WSAASYNCSELECT, FD_READ );

    /* Introduce yourself */
    FORWARD_WM_TIMER( hDlg, ID_CHATTER_BROADCAST_TIMER, PostMessage );

    SetFocus( hInputWnd );

    HandleSendButtons( hDlg );

    return true;

}
