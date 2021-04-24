#if ! defined( WIN32) && defined( linux )
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif


static SOCKET PrepUDP( void ) {

#ifdef WIN32

    WORD    wVersion;

    int     iRet;

    WSADATA WSAData;

    wVersion = MAKEWORD( 1, 1 );

    ZeroMemory( &WSAData, sizeof( WSAData ) );

    iRet = WSAStartup( wVersion, &WSAData );

    if ( 0 != iRet ) {

        return (SOCKET)-1;

    }

    #endif /* WIN32 */

    SOCKET s = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( (SOCKET)-1 == s ) {

        return s;

    }

    union {

        int     iOpt;
        char    cOpt[1];

    };

    iOpt = true;

    if ( 0 != setsockopt( s, SOL_SOCKET, SO_BROADCAST, cOpt, sizeof( iOpt ) ) ) {

#ifdef WIN32
        closesocket( s );
#else
        close( s );
#endif

        return (SOCKET)-1;

    }

    return s;

}


inline static size_t UDPOutput( unsigned long tid, const char * pszMsg, size_t Len ) {

    static bool   bInit = false;

    static SOCKET s     = (SOCKET)-1;

    if ( ( 0 == Len ) || ( (size_t)-1 == Len ) ) {

        return (size_t)-1;

    }

    if ( ! bInit ) {

        bInit = true;

        s = PrepUDP();

    }

    if ( (SOCKET)-1 == s ) {

        return (SOCKET)-1;

    }

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

    memset( &sa, 0, sizeof( sa ) );

    sin.sin_family      = AF_INET;
    sin.sin_port        = htons( ID_DBGDLL_DATAGRAM_BROADCAST_PORT );
    sin.sin_addr.s_addr = htonl( INADDR_BROADCAST );

    union {

        DEBUGMSGDATASTRUCT UNCD;
        char               cBuffer[MAXIMUM_MTU_SIZE];

    };

    memset( cBuffer, 0, sizeof( cBuffer ) );

	Len = std::min( (size_t)Len, (size_t)( ( sizeof( cBuffer ) - 1 ) - sizeof( UNCD ) ) );

    UNCD.dwData = htonl( tid );

    UNCD.cbData = htons( (unsigned short)Len );

    memcpy( UNCD.cData, pszMsg, Len );

    size_t Ret = sendto( s, cBuffer, (int)( sizeof( DEBUGMSGDATASTRUCT ) + Len + 1 ), 0, &sa, sizeof( sa ) );

    return Ret;

}
