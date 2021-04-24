

#include "dbglog.h"


void ProcessUserData( COPYDATASTRUCT * pCD ) {

    char * pszCursor;
    char * pEOL;

    pszCursor = (char *)pCD->lpData;

    for( ;; ) {

        if ( NULL == ( pEOL = strchr( pszCursor, '\n' ) ) ) {

            /* Single line of text, send to output and end. */

            if ( '\0' == ( *pszCursor ) ) {

                /* Blank line. */
                break;

            }

            printf( "%s\n", pszCursor );
            break;

        } else {

            /* Multiple lines of text. */

            /* Split this line off from the rest. */
            *pEOL = '\0';

            printf( "%s\n", pszCursor );

            /* Point past null to next line of text. */
            pszCursor = pEOL;
            pszCursor++;

        }

    }

}


void HandleSelect( SOCKET s ) {

    int       iRet;
    socklen_t iLen;

    union {

        sockaddr sa;
        sockaddr_in sin;

    };

    union {

        DEBUGMSGDATASTRUCT UNCD;
        char               cBuffer[MAXIMUM_MTU_SIZE];

    } Read;

    bzero( &Read, sizeof( Read ) );

    iLen = sizeof( sa );
    iRet = recvfrom( s, Read.cBuffer, sizeof( Read.cBuffer ), 0, &sa, &iLen );

    if ( 0 < iRet ) {

        COPYDATASTRUCT CD;

        CD.cbData = Read.UNCD.cbData;
        CD.dwData = Read.UNCD.dwData;
        CD.lpData = Read.UNCD.cData;

        printf( "%15s:%05d - ", inet_ntoa( sin.sin_addr ), ntohs( sin.sin_port ) );
        ProcessUserData( &CD );

    }

}


SOCKET PrepSocket( void ) {

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

    int TraceSocket = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( -1 == TraceSocket ) {

        return -1;

    }

    bzero( &sin, sizeof( sin ) );

    sin.sin_family = AF_INET;
    sin.sin_port   = htons( ID_DBGDLL_DATAGRAM_BROADCAST_PORT );

    if ( 0 != bind( TraceSocket, &sa, sizeof( sa ) ) ) {

        printf( "ERROR binding port %u\n", ID_DBGDLL_DATAGRAM_BROADCAST_PORT );
        return -1;

    }

    return TraceSocket;

}


int main( int iArgC, char * argv[] ) {

    fd_set fdreadlist;

    SOCKET s = PrepSocket();

    if ( -1 == s ) {

        return -1;

    }

    FD_ZERO( &fdreadlist );
    FD_SET( s, &fdreadlist );

    int iRet;

    for( ;; ) {

        iRet = select( s + 1, &fdreadlist, NULL, NULL, NULL );

        if ( 0 > iRet ) {

            printf( "ERROR on select\n" );
            break;

        }

        /* Dump message */
        HandleSelect( s );

    }

    return iRet;

}
