#ifndef __IOSKEYMOUSE_H__
#define __IOSKEYMOUSE_H__


#include "eventq.h"
#include "regions.h"


class iOSKeyMouse : public Handler {

    public:

        Region updates;

        bool SendUpdates( void );

        iOSKeyMouse( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) {

        }


        bool EventHandler();

    private:

        RawInput input;

};


#endif  /* __IOSKEYMOUSE_H__ */
