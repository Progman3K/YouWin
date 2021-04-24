#ifndef YW_EVENTQ_H
#define YW_EVENTQ_H


#ifdef ANDROID
#include <android/looper.h>
#endif /* ANDROID */

#include <sys/socket.h>


#include "timers.h"
#include "handler.h"


class EventQ {

    public:


        int Read( MSG * pMsg );


        int addToQ( HandlerList & Q, Handler * handler ) {

            Q.push_back( handler );
            return 0;

        }


        void RemoveSocket( SOCKET s ) {

            int i;

#ifdef ANDROID
            i = ALooper_removeFd( ALooper_forThread(), s );

            if ( 1 != i ) {

                DBG_MSG( DBG_ERROR, TEXT( "ALooper_removeFd( %lX, %d ) ERROR %d" ), ALooper_forThread(), s, i );

            }
#else

            if ( -1 != ( i = ReadQ.Find( s ) ) ) {

                ReadQ.erase( ReadQ.begin() + i );

            }

            if ( -1 != ( i = WriteQ.Find( s ) ) ) {

                WriteQ.erase( WriteQ.begin() + i );

            }
#endif

        }


        int PostToQ( WindowMsgQ & Q, const MetaMSG * pMsg ) {

            Q.push_back( *pMsg );

            return Q.size();

        }


        int PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

            MetaMSG Msg;

            Msg.Msg.hwnd    = hWnd;
            Msg.Msg.message = uiMsg;
            Msg.Msg.wParam  = wParam;
            Msg.Msg.lParam  = lParam;

            return PostToQ( MsgQ, &Msg );

        }


        int PostMouseMsg( bool bUp, long x, long y, unsigned uVKType, unsigned uMKType );
        int PostMouseMove( long x, long y, unsigned uMKType );

        /* Socket, console queues */
        HandlerList ReadQ;
        HandlerList WriteQ;

        WindowMsgQ MsgQ;
        TimerList  Timers;

};


#endif /* YW_EVENTQ_H */
