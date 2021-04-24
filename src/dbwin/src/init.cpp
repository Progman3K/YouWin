

#include "dbwin.h"


int CApp::iInit( HINSTANCE hInst, HINSTANCE hPrevInst ) {

    WSADATA	WSAData;
    ZeroMemory( &WSAData, sizeof( WSAData ) );

    if ( 0 != WSAStartup( MAKEWORD( 1, 1 ), &WSAData ) ) {

        return -1;

    }

#ifndef _WIN32_WCE
    if ( 0 == ( g_uiFindMsg = RegisterWindowMessage( FINDMSGSTRING ) ) ) {

        return -1;

    }
#endif /* ! _WIN32_WCE */

    if ( NULL == hPrevInst ) {

        if ( ! bRegisterClasses( hInst ) ) {

            return -1;

        }

    }

    return 0;

}
