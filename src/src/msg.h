#ifndef YW_MSG_H
#define YW_MSG_H


#include <vector>
#include <ctime>


#include <wtypes.h>


class MetaMSG  {

    public:

        unsigned long   lFresh;
        unsigned long   ulInterval; /* In milliseconds */
        MSG             Msg;
        bool            raw;

        MetaMSG() {

            raw         = false;
            lFresh      = clock();
            ulInterval  = 0;
            Msg.hwnd    = 0;
            Msg.message = 0;
            Msg.wParam  = 0;
            Msg.lParam  = 0;

        }


};


class WindowMsgQ : public std::vector<MetaMSG> {

    public:

        int PostTo( MetaMSG * pMsg ) {

            push_back( *pMsg );

            return 0;

        }


        bool RemoveMessage( MSG * pMsg ) {

            /* Process window message queue */

            for ( iterator i = begin(); i != end(); ++i ) {

                *pMsg = (*i ).Msg;

                erase( i );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Message 0x%04lX removed from queue, %d left in queue" ), pMsg->message, size() );

                return true;

            }

            return false;

        }

};


#endif /* YW_MSG_H */
