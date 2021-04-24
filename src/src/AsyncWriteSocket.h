#ifndef YW_ASYNCWRITESOCKET_H
#define YW_ASYNCWRITESOCKET_H


#include "AsyncSocket.h"


class AsyncWriteSocket : public AsyncSocket {

    public:

        AsyncWriteSocket( EventQ * pThreadEventQ, HWND hNotifyWnd, UINT uiNotifyMsg, SOCKET session, long lEventMask ) : AsyncSocket( pThreadEventQ, hNotifyWnd, uiNotifyMsg, session, lEventMask ) {

            Freshen( hNotifyWnd, uiNotifyMsg, lEventMask );

        }

        bool EventHandler() override {

            if ( FD_CONNECT & lEvents ) {

                /* Can only receive this notification once */
                lEvents = ( ~FD_CONNECT & lEvents );

                DBG_MSG( DBG_NETWORK_INFO, TEXT( "FD_CONNECT on socket %d, HWND %lX, Msg %u" ), s, hWnd, uiMsg );
                FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, FD_CONNECT, 0, SendMessage );

            } else {

                DBG_MSG( DBG_NETWORK_INFO, TEXT( "FD_WRITE on socket %d, HWND %lX, Msg %u" ), s, hWnd, uiMsg );
                FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, FD_WRITE, 0, SendMessage );

            }

            return true;

        }

};


#endif /* YW_ASYNCWRITESOCKET_H */
