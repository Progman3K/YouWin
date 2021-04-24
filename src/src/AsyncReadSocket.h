#ifndef YW_ASYNCREADSOCKET_H
#define YW_ASYNCREADSOCKET_H


#include <sys/ioctl.h>

#ifdef sun
#include <sys/filio.h>
#endif /* sun */

#include "AsyncSocket.h"


class AsyncReadSocket : public AsyncSocket /* Handler */ {

    public:

        AsyncReadSocket( EventQ * pThreadEventQ, HWND hNotifyWnd, UINT uiNotifyMsg, SOCKET session, long lEventMask ) : AsyncSocket( pThreadEventQ, hNotifyWnd, uiNotifyMsg, session, lEventMask ) /* Handler ( session, pThreadEventQ ) */ {

            Freshen( hNotifyWnd, uiNotifyMsg, lEventMask );

        }

        bool EventHandler() override {

            if ( FD_ACCEPT & lEvents ) {

                DBG_MSG( DBG_NETWORK_INFO, TEXT( "FD_ACCEPT on socket %d, HWND %lX, Msg %u" ), s, hWnd, uiMsg );
                FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, FD_ACCEPT, 0, SendMessage );
                return true;

            } else {

#ifdef WIN32
                ULONG iLen = 0;
                int iRet = ioctlsocket( s, FIONREAD, &iLen );
#else
                int iLen = 0;
                int iRet = ioctl( s, FIONREAD, &iLen );
#endif

                if ( ( -1 == iRet ) || ( 0 == iLen ) ) {

                    DBG_MSG( DBG_ERROR, TEXT( "READ QUEUE CHECK=%d, LEN=%lu ERRNO (%d) ON SOCKET %d, SENDING FD_CLOSE" ), iRet, (unsigned long)iLen, errno, s );
                    FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, FD_CLOSE, 0, SendMessage );
                    return true;

                }

                DBG_MSG( DBG_NETWORK_INFO, TEXT( "FD_READ on socket %d, HWND %lX, Msg %u" ), s, hWnd, uiMsg );
                FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, FD_READ, 0, SendMessage );
                return true;

            }

        }

};


#endif /* YW_ASYNCREADSOCKET_H */
