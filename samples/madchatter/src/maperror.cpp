

#include "chatter.h"


const TCHAR * lpszMapErrorCode( unsigned short uError ) {

    switch( uError ) {

        case EINTR:
        case EBADF:
        case EACCES:
        case EFAULT:
        case EINVAL:
        case EMFILE:
        case ENAMETOOLONG:
        case ENOTEMPTY:
#ifdef WIN32
        case WSAEWOULDBLOCK:
        case WSAHOST_NOT_FOUND:
        case WSATRY_AGAIN:
        case WSANO_RECOVERY:
        case WSAEINPROGRESS:
        case WSAEALREADY:
        case WSAENOTSOCK:
        case WSAEDESTADDRREQ:
        case WSAEMSGSIZE:
        case WSAEPROTOTYPE:
        case WSAENOPROTOOPT:
        case WSAEPROTONOSUPPORT:
        case WSAESOCKTNOSUPPORT:
        case WSAEOPNOTSUPP:
        case WSAEPFNOSUPPORT:
        case WSAEAFNOSUPPORT:
        case WSAEADDRINUSE:
        case WSAEADDRNOTAVAIL:
        case WSAENETDOWN:
        case WSAENETUNREACH:
        case WSAENETRESET:
        case WSAECONNABORTED:
        case WSAECONNRESET:
        case WSAENOBUFS:
        case WSAEISCONN:
        case WSAENOTCONN:
        case WSAESHUTDOWN:
        case WSAETOOMANYREFS:
        case WSAETIMEDOUT:
        case WSAECONNREFUSED:
        case WSAELOOP:
        case WSAEHOSTDOWN:
        case WSAEHOSTUNREACH:
        case WSAEUSERS:
        case WSAEDQUOT:
        case WSAESTALE:
        case WSAEREMOTE:
#endif /* WIN32 */
//        case NO_DATA:
//        case EPROCLIM:
//        case EDISCON:
//        case SYSNOTREADY:
//        case VERNOTSUPPORTED:
//        case NOTINITIALISED:
        
        break;
           
    }
    
    return TEXT( "unknown" );
    
}

