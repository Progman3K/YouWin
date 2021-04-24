#ifndef __GL_EVENTS_H__
#define __GL_EVENTS_H__


#include "handler.h"


class GLEvents : public Handler {

    public:

        GLEvents() : Handler( -1, NULL ) {}

        GLEvents( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) {}

#ifndef ANDROID
        bool EventHandler() override {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "OpenGL update" ) );
            RasterUpdate();
            return true;

        }
#endif

};


#endif  /* __GL_EVENTS_H__ */
