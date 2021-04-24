#ifndef YW_ASYNCSOCKET_H
#define YW_ASYNCSOCKET_H


#include <map>

#include <ws2x.h>


#include "eventq.h"


class AsyncSocket : public Handler {

    public:

        HWND hWnd;
        UINT uiMsg;
        long lEvents;

        virtual ~AsyncSocket() override {}

        AsyncSocket( EventQ * pThreadEventQ, HWND hNotifyWnd, UINT uiNotifyMsg, SOCKET session, long lEventMask ) : Handler( session, pThreadEventQ ) {

            Freshen( hNotifyWnd, uiNotifyMsg, lEventMask );

        }

        void Freshen( HWND hNotifyWnd, UINT uiNotifyMsg, long lEventMask ) {

            lEvents = lEventMask;
            uiMsg   = uiNotifyMsg;
            hWnd    = hNotifyWnd;

        }

};


typedef std::pair <SOCKET, AsyncSocket *> AsyncSelectPair;
typedef std::map <SOCKET, AsyncSocket *> AsyncSelectList;


extern AsyncSelectList SocketInputs;


#endif /* YW_ASYNCSOCKET_H */
