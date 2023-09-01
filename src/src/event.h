#ifndef YW_EVENT_H
#define YW_EVENT_H


#include "object.h"


class CEvent : public ywObject {

    public:

#ifdef __MACH__
        dispatch_semaphore_t
#else /* Other unices */
        sem_t
#endif
        semaphore;


        CEvent() {

            setType( OBJECT_TYPE_EVENT );

#ifdef __MACH__
            semaphore = dispatch_semaphore_create( 0 );
#else /* Other unices */
            sem_init( &semaphore, 0, 0 );
#endif

        }


        virtual ~CEvent() override {

#ifdef __MACH__
#else /* Other unices */
            sem_destroy( &semaphore );
#endif

        }


};


#endif /* YW_EVENT_H */
