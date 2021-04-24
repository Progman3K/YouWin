

#include "ywin.h"


AsyncSelectList SocketInputs;


extern "C" int readsocket( int s, char * buff, int len ) {

    return read( s, buff, len );

}


extern "C" int closesocket( SOCKET s ) {

    g.Q.RemoveSocket( s );

    /* Find if s has any WSA functions active */
    AsyncSelectList::iterator i = SocketInputs.find( s );

    if( SocketInputs.end() != i ) {

        delete (*i).second;
        SocketInputs.erase( i );

    }

    return close( s );

}


#if defined( YOU_WIN_GRAPHICAL ) && defined( ANDROID )
#ifdef DEBUG
LPCTSTR GetEventString( LPTSTR lpszEvents, int iEvent, int iMaxLen ) {

    ZeroMemory( lpszEvents, iMaxLen );

    if ( ALOOPER_EVENT_INPUT & iEvent ) {

        strcat( lpszEvents, TEXT( "ALOOPER_EVENT_INPUT " ) );

    }

    if ( ALOOPER_EVENT_OUTPUT & iEvent ) {

        strcat( lpszEvents, TEXT( "ALOOPER_EVENT_OUTPUT " ) );

    }

    if ( ALOOPER_EVENT_ERROR & iEvent ) {

        strcat( lpszEvents, TEXT( "ALOOPER_EVENT_ERROR " ) );

    }

    if ( ALOOPER_EVENT_HANGUP & iEvent ) {

        strcat( lpszEvents, TEXT( "ALOOPER_EVENT_HANGUP " ) );

    }

    if ( ALOOPER_EVENT_INVALID & iEvent ) {

        strcat( lpszEvents, TEXT( "ALOOPER_EVENT_INVALID" ) );

    }

    return lpszEvents;

}
#endif


static int android_socketevent( int s, int iEvents, AsyncSocket * pInput ) {

#ifdef DEBUG
    TCHAR szEvents[256];

    ZeroMemory( szEvents, sizeof( szEvents ) );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android_socketevent: socket %d, event mask %X '%s'" ), s, iEvents, GetEventString( szEvents, iEvents, Dim( szEvents ) - 1 ) );
#endif

    if ( ( ALOOPER_EVENT_INPUT & iEvents ) || ( ALOOPER_EVENT_HANGUP & iEvents ) ) {

        ( reinterpret_cast<AsyncReadSocket *>( pInput ) )->EventHandler();
        return 1;

    }

    if ( ALOOPER_EVENT_OUTPUT & iEvents ) {

        ( reinterpret_cast<AsyncWriteSocket *>( pInput ) )->EventHandler();
        return 1;

    }

    if ( ALOOPER_EVENT_ERROR & iEvents ) {

        DBG_MSG( DBG_ERROR, TEXT( "SOCKET %d IN ERROR" ) );
        return 1;

    }

    if ( ALOOPER_EVENT_INVALID & iEvents ) {

        DBG_MSG( DBG_ERROR, TEXT( "SOCKET %d INVALID" ) );
        return 1;

    }

    return 1;

}
#endif


extern "C" int WSAAsyncSelect( SOCKET s, HWND hWnd, unsigned int uiMsg, long lEvent ) {

    /* Put socket in non-blocking mode */
    int flags;

    if ( -1 == ( flags = fcntl( s, F_GETFL, 0 ) ) ) flags = 0;

    int iRet = fcntl( s, F_SETFL, flags | O_NONBLOCK );

    DBG_MSG( DBG_NETWORK_INFO, TEXT( "fcntl( %d, F_SETFL, %X | O_NONBLOCK ) returned %d" ), s, flags, iRet );

//    int opt = 1;
//    ioctl( s, FIONBIO, &opt );

    g.Q.RemoveSocket( s );

    AsyncSocket * pInput = NULL;

    AsyncSelectList::iterator i = SocketInputs.find( s );

    if( SocketInputs.end() != i ) {

        pInput = (*i).second;

        delete pInput;

        SocketInputs.erase( i );
//        pInput->Freshen( hWnd, uiMsg, lEvent );

    }

    if ( 0 == lEvent ) {

#if defined( YOU_WIN_GRAPHICAL ) && defined( YOU_WIN_GRAPHICAL_OSX )

        OSXAddAsyncSelectSocket( s, 0 );

#endif
        return 0;

    }

    /* Now create it */

    if ( ( FD_CONNECT & lEvent ) || ( FD_WRITE & lEvent ) ) {

        pInput = new AsyncWriteSocket( &g.Q, hWnd, uiMsg, s, lEvent );

    } else {

        // FD_ACCEPT FD_READ

        pInput = new AsyncReadSocket( &g.Q, hWnd, uiMsg, s, lEvent );

    }

    if ( NULL == pInput ) {

        return -1;

    }

    SocketInputs.insert( AsyncSelectPair( s, pInput ) );

#if defined( YOU_WIN_GRAPHICAL ) && defined( YOU_WIN_GRAPHICAL_OSX )

    OSXAddAsyncSelectSocket( s, lEvent );

#else

#if defined( YOU_WIN_GRAPHICAL ) && defined( ANDROID )
    int iEvents = 0;

    if ( ( FD_ACCEPT & lEvent ) || ( FD_CLOSE & lEvent ) || ( FD_READ & lEvent ) ) {

        iEvents |= ALOOPER_EVENT_INPUT;

    }

    if ( ( FD_CONNECT & lEvent ) || ( FD_WRITE & lEvent ) ) {

        iEvents |= ALOOPER_EVENT_OUTPUT;

    }

    if ( FD_CLOSE & lEvent ) {

        iEvents |= ALOOPER_EVENT_HANGUP;

    }

    iRet = ALooper_addFd( ALooper_forThread(), s, ALOOPER_POLL_CALLBACK, iEvents, (ALooper_callbackFunc)android_socketevent, pInput );

    if ( 1 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "ALooper_addFd ERROR %d" ), iRet );

    }

#else /* All text-based and generic OpenGL solutions have this in common; a standard select/socket architecture */

    if ( ( FD_CONNECT & lEvent ) || ( FD_WRITE & lEvent ) ) {

        g.Q.addToQ( g.Q.WriteQ, pInput );

    }

    if ( ( FD_ACCEPT & lEvent ) || ( FD_CLOSE & lEvent ) || ( FD_READ & lEvent ) ) {

        g.Q.addToQ( g.Q.ReadQ, pInput );

    }

#endif

#endif

    return 0;

}


int ioctlsocket( SOCKET s, long cmd, unsigned long * argp ) {

    int flags;

    int iBytes = 0;

    switch( cmd ) {

        case FIONBIO:

            flags = fcntl( s, F_GETFL, 0 );

            if ( -1 == flags ) {

                return -1;

            }

            if ( 0 == *argp ) {

                /* Make socket blocking */
                flags = fcntl( s, F_SETFL, flags & ( ~O_NONBLOCK ) );

            } else {

                /* Make socket non-blocking */
                flags = fcntl( s, F_SETFL, flags | O_NONBLOCK );

            }

            if ( -1 == flags ) {

                return -1;

            }

            break;

        case FIONREAD:

            flags = ioctl( s, FIONREAD, &iBytes );

            if ( -1 == flags ) {

                return -1;

            }

            break;

        default:

            return -1;

    }

    return 0;

}


int WSAStartup( WORD /* wVersionRequested */, LPWSADATA /* lpWSAData */ ) {

    return 0;

}
