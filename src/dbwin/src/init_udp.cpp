

#include "dbwin.h"


BOOL CUDPTrace::bPrepSocket( HWND hWnd ) {

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

    TraceSocket = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( INVALID_SOCKET == TraceSocket ) {

        return false;

    }

    ZeroMemory( &sin, sizeof( sin ) );
    sin.sin_family = AF_INET;
    sin.sin_port   = htons( ID_DBGDLL_DATAGRAM_BROADCAST_PORT );

    if ( 0 != bind( TraceSocket, &sa, sizeof( sa ) ) ) {

        Close();
        return false;

    }

    if ( 0 != WSAAsyncSelect( TraceSocket, hWnd, WM_WSAASYNCSELECT, FD_READ ) ) {

        Close();
        return false;

    }

    return true;

}
