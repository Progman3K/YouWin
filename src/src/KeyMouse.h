#ifndef __KEYMOUSE_H__
#define __KEYMOUSE_H__


#include "eventq.h"
#include "console_input.h"


#if 0

// Top-left (0,0)     5B 4D 20 21 21                [M !!
// Bottom-right       5B 4D 20 DD 52                [M ÝR

// NORTHWEST ARROW    5B 31 7E                      [1~
// SOUTHWEST ARROW    5B 34 7E                      [4~

#endif


class KeyMouse : public Handler {

    public:

        KeyMouse( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) {

        }


        bool EventHandler() override {

            bool bRet = readconsoleinput( getsocket(), pQ );

            if ( ! bRet ) {

                DBG_MSG( DBG_ERROR, TEXT( "Error reading console" ) );
                return false;

            }

            return true;

        }

};


#endif  /* __KEYMOUSE_H__ */
