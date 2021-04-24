#ifndef YW_TIMERS_H
#define YW_TIMERS_H


#include <map>


#include "msg.h"


typedef struct tag_timer_key {

    HWND     hWnd;
    UINT_PTR uID;

    bool operator < ( const tag_timer_key & n ) const {

        if ( hWnd == n.hWnd ) {

            return uID < n.uID;

        }

        return hWnd < n.hWnd;

    }

} timer_key;


class TimerList : public std::map<timer_key,MetaMSG> {

    typedef std::pair<timer_key,MetaMSG> item;

    UINT_PTR uAutoTimerID;

    typedef enum {

        MAX_ANONYMOUS_TIMER_ID = 0x7FFF

    } Constants;

    public:

        TimerList() {

            uAutoTimerID = MAX_ANONYMOUS_TIMER_ID;

        }

        UINT_PTR GetAnonymousTimerID( void ) {

            bool bWraparound = false;

            timer_key key;

            key.hWnd = (HWND)0;

            walktimerspace:

            for ( ; uAutoTimerID > 0; uAutoTimerID-- ) {

                key.uID  = uAutoTimerID;

                const iterator found = find( key );

                if ( end() == found ) {

                    /* Timer ID is available, return it. */
                    return uAutoTimerID--;

                }

            }

            if ( ! bWraparound ) {

                bWraparound = true;

                uAutoTimerID = MAX_ANONYMOUS_TIMER_ID;

                goto walktimerspace;

            }

            return 0;

        }


        MetaMSG * GetNearestTimer() {

            if ( 0 == size() ) {

                return nullptr;

            }

            iterator Lowest = begin();

            for ( iterator i = begin(); i != end(); ++i ) {

                if ( (*i).second.lFresh < (*Lowest).second.lFresh ) {

                    Lowest = i;

                }

            }

            return &(*Lowest).second;

        }


        int PostTo( HWND hWnd, UINT_PTR uID, const MetaMSG * pMsg ) {

            timer_key key;

            key.hWnd   = hWnd;
            key.uID    = uID;

            item timer;

            timer.first  = key;
            timer.second = *pMsg;

            // std::pair<iterator,bool> ret = 
            insert( timer );

            return 0;

        }

};


#endif /* YW_TIMERS_H */
