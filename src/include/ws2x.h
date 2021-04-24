

#ifndef YW_WS2X_H
#define YW_WS2X_H


#include <winsock2.h>

#ifdef WIN32
typedef int socklen_t;
#endif /* ! WIN32 */


/*___________________________________________________________________________

    WinSock Message Crackers
___________________________________________________________________________*/
#ifndef HANDLE_WM_WSAASYNCSELECT
/* OnWsaAsyncSelect( HWND hWnd, SOCKET s, unsigned uFDEvent, unsigned uErrorCode ); */
#define HANDLE_WM_WSAASYNCSELECT( hWnd, wParam, lParam, fn ) ( (fn)( (hWnd), (SOCKET)( wParam ), (WSAGETSELECTEVENT( lParam )), (WSAGETASYNCERROR( lParam )) ), 0L )
#endif /* HANDLE_WM_WSAASYNCSELECT */

#ifndef FORWARD_WM_WSAASYNCSELECT
#define FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, Event, Error, fn ) ( (fn)( (hWnd), (uiMsg), (WPARAM)( s ), (MAKELPARAM( ( Event ), ( Error ) )) ) )
#endif /* FORWARD_WM_WSAASYNCSELECT */

#ifndef HANDLE_WM_WSAASYNCGETHOSTBYNAME
/* OnWsaAsyncGethost( HWND hWnd, HANDLE hAsyncRequest, unsigned uBufferLen, unsigned uErrorCode ); */
#define HANDLE_WM_WSAASYNCGETHOSTBYNAME( hWnd, wParam, lParam, fn ) ( (fn)( (hWnd), (HANDLE)( wParam ), (WSAGETASYNCBUFLEN( lParam )), (WSAGETASYNCERROR( lParam )) ), 0L )
#endif /* HANDLE_WM_WSAASYNCGETHOSTBYNAME */

#endif /* YW_WS2X_H */
