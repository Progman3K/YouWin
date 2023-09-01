#ifndef YOUWIN_WINSOCK_H
#define YOUWIN_WINSOCK_H


#include <windows.h>
#include <iptypes.h>


#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>


#include "wsanotif.h"


#define MAXGETHOSTSTRUCT        1024
#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

#define WSAGetLastError()         errno

#define WSACleanup()              0


#ifndef INVALID_SOCKET
#define INVALID_SOCKET            (SOCKET)(-1)
#endif


#ifndef IPPROTO_TCP
#define IPPROTO_TCP                6
#endif /* IPPROTO_TCP */


#ifndef WSAGETASYNCBUFLEN
#define WSAGETASYNCBUFLEN(lParam) LOWORD(lParam)
#endif /* WSAGETASYNCBUFLEN */


#ifndef WSAGETASYNCERROR
#define WSAGETASYNCERROR(lParam)  HIWORD(lParam)
#endif /* WSAGETASYNCERROR */


#ifndef WSAGETSELECTEVENT
#define WSAGETSELECTEVENT(lParam) LOWORD(lParam)
#endif /* WSAGETSELECTEVENT */


typedef struct WSAData {

    WORD           wVersion;
    WORD           wHighVersion;
    char           szDescription[WSADESCRIPTION_LEN+1];
    char           szSystemStatus[WSASYS_STATUS_LEN+1];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *         lpVendorInfo;

} WSADATA;
typedef WSADATA *LPWSADATA;


#ifdef __cplusplus
extern "C" {
#endif


int WSAAsyncSelect( SOCKET s, HWND hWnd, unsigned int uiMsg, LONG lEvent );
HANDLE WSAAsyncGetHostByName( HWND hWnd, unsigned int uiMsg, const char * name, char * buf, int buflen );
int WSAStartup( WORD wVersionRequested, LPWSADATA lpWSAData );


int closesocket( SOCKET s );


int readsocket( int s, char * buf, int buflen );


#ifdef __cplusplus
}
#endif


#endif /* YOUWIN_WINSOCK_H */
