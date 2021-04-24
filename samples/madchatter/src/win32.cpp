

#include "chatter.h"


BOOL bRegisterClasses( HINSTANCE hInst, HICON hClassIcon ) {

    WNDCLASS wc;

    ZeroMemory( &wc, sizeof( wc ) );

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = DefDlgProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInst;
    wc.hIcon         = hClassIcon;

#ifdef _WIN32_WCE
    wc.hCursor       = NULL;
#else
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
#endif /* _WIN32_WCE */

    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = TEXT( IDSZ_CHATTER_WINDOW_CLASS );

    if ( 0 == RegisterClass( &wc ) ) {

        return false;

    }

    return true;

}


HICON WinInit( HINSTANCE hInst, HINSTANCE hPrevInst ) {

    WSADATA WSAData;

    if ( 0 != WSAStartup( MAKEWORD( 1, 1 ), &WSAData ) ) {

        OutputDebugString( TEXT( "FATAL - Network layer init failed" ) );
        return NULL;

    }

    INITCOMMONCONTROLSEX InitCtrlEx;

    InitCtrlEx.dwSize = sizeof( INITCOMMONCONTROLSEX );
    InitCtrlEx.dwICC  = ICC_PROGRESS_CLASS;

    InitCommonControlsEx( &InitCtrlEx );

    HICON   hIcon;

    if ( NULL == ( hIcon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN ) ) ) ) {

        OutputDebugString( TEXT( "FATAL - Main icon not found" ) );
        return NULL;

    }

    if ( ! bRegisterClasses( hInst, hIcon ) ) {

        OutputDebugString( TEXT( "FATAL - Main windows class registration failed" ) );
        DestroyIcon( hIcon );
        return NULL;

    }

    return hIcon;

}
