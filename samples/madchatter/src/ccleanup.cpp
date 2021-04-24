

#include "chatter.h"


void CleanUp( HINSTANCE hInst, CWho & me ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Chatter cleanup" ) );

    SOCKET s;

    if ( INVALID_SOCKET != ( s = me.GetSocket() ) ) {

        closesocket( s );

    }

    UnregisterClass( TEXT( IDSZ_CHATTER_WINDOW_CLASS ), hInst );

#ifdef WIN32
    WSACleanup();
#endif

}

