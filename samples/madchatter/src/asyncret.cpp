

#include "chatter.h"


void CChatterMainWnd::OnWSAAsyncNotification( HWND hDlg, SOCKET s, WORD wEventCode, WORD wErrorCode ) {

    int       iLen;
    socklen_t socklen;
    int       iListID;
    CWho *    pYou;

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

    union {

        Exchange_t  et;
        char        cBuffer[ sizeof( Exchange_t ) + MAX_DATA_LENGTH];

    };

    switch( wEventCode ) {

        case FD_READ:

//            for ( ;; ) {

                ZeroMemory( cBuffer, sizeof( cBuffer ) );
                ZeroMemory( &sa, sizeof( sa ) );
                socklen = sizeof( sa );

                iLen = recvfrom( s, cBuffer, sizeof( cBuffer ), 0, &sa, &socklen );

                if ( ( iLen <= 0 ) || ( sizeof( et ) > (unsigned)iLen ) ) {

//                    DBG_MSG( DBG_ERROR, TEXT( "Receive error: size %d %s" ), iLen, lpszMapErrorCode( WSAGetLastError() ) );
                    break;

                }

                if ( pMe->GetEntity() == et.Header.entity ) {

//                    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "loopback detected, discarding" ) );
                    break;

                }

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Msg from socket %d peer %s:%u, size %d" ), s, INet_NToT( sin.sin_addr ), (unsigned)ntohs( sin.sin_port ), iLen );
        //            DBG_DMP( DBG_GENERAL_INFORMATION, cBuffer, iLen );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Check for peer" ) );
                if ( NULL == ( pYou = GetYou( et.Header.entity, sin, &iListID ) ) ) {

//                    DBG_MSG( DBG_ERROR, TEXT( "Couldn't create a new one!" ) );
                    break;

                }

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Associate peer" ) );
                pYou->SetSocket( s );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Freshen presence" ) );
                pYou->SetTimeLastSeen( now() );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Process packet" ) );
                pYou->RecvData( hDlg, pMe, *this, &et, iLen );

//            }
            break;

    }

}
