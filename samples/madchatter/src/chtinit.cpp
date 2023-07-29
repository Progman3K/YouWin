

#include "chatter.h"


/* Any return value other than ZERO means an error. */
int iInit( CWho & me ) {

	TCHAR szError[1024];
		
//  GetAppProfileString( hInst, ID( IDS_REGISTRATION ), ID( IDS_USERNAME ), TEXT( "" ), g_szChatterUserName, Dim( g_szChatterUserName ), g_szChatterIni, TRUE );

//  TCHAR   szString[MAX_TEMPSTRING_SIZE];
//  GetAppProfileString( hInst, ID( IDS_REGISTRATION ), ID( IDS_REGISTRATION_KEY ), TEXT( "" ), szString, Dim( szString ), g_szChatterIni, TRUE );

//  g_bMute = GetAppProfileBool( hInst, ID( IDS_INITIALIZATION_SECTION ), ID( IDS_MUTE_SOUND ), FALSE, g_szChatterIni, TRUE );

//  g_uiTimerTimeout = GetAppProfileInt( hInst, ID( IDS_INITIALIZATION_SECTION ), ID( IDS_TIMER_INTERVAL ), ID_TIMER_DEFAULT_INTERVAL, g_szChatterIni, TRUE, FALSE );

    SOCKET s = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    if ( INVALID_SOCKET == s ) {

//        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Host socket creation failed" ) );
        return -1;

    }

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

    ZeroMemory( &sa, sizeof( sa ) );

    sin = me.GetSin();

    int iLen = sizeof( sa );
    int iRet = bind( s, &sa, iLen );

    if ( 0 != iRet ) {

        closesocket( s );
        short sError = WSAGetLastError();
		_stprintf( szError, TEXT( "Init: FATAL - Error binding: %d '%s'" ), (int)sError, lpszMapErrorCode( sError ) );
		MessageBox( HWND_DESKTOP, szError, ERROR_APP_TITLE, MB_OK | MB_ICONERROR );
        return -1;

    }

    union {

        int     iOpt;
        char    cOpt[0];

    };

    iOpt = true;
    iLen = sizeof( iOpt );

    iRet = setsockopt( s, SOL_SOCKET, SO_BROADCAST, cOpt, iLen );

    if ( 0 != iRet ) {

        short   sError = WSAGetLastError();
        _stprintf( szError, TEXT( "FATAL - Setting broadcast option: %d '%s'" ), (int)sError, lpszMapErrorCode( sError ) );
        closesocket( s );
		MessageBox( HWND_DESKTOP, szError, ERROR_APP_TITLE, MB_OK | MB_ICONERROR );
        return -1;

    }
#if 0
    union {

        in_addr     sin_addr;
        char        cAddress[0];

    };

    ZeroMemory( &sin_addr, sizeof( sin_addr ) );

    sin_addr.s_addr = htonl( INADDR_LOOPBACK );

    hostent * pHost = gethostbyaddr( cAddress, sizeof( sin_addr ), AF_INET );

    if ( NULL == pHost ) {

        short   sError = WSAGetLastError();
        _stprintf( szError, TEXT( "FATAL - Error %d getting host info: '%s'" ), (int)sError, lpszMapErrorCode( sError ) );
        closesocket( s );
		MessageBox( HWND_DESKTOP, szError, ERROR_APP_TITLE, MB_OK | MB_ICONERROR );
        return -1;

    }
#endif
    if ( ! me.SetSocket( s ) ) {

        closesocket( s );
        return -1;

    }

    return 0;

}
