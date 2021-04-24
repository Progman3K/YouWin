

#include "ywin.h"


HANDLE CreateEvent( struct SECURITY_ATTRIBUTES * pEventAttributes, BOOL bManualReset, BOOL bInitialState, const TCHAR * pszName ) {

    CEvent * pEvent = new CEvent;

    return pEvent;

}


BOOL SetEvent( HANDLE hEvent ) {

    CEvent * pEvent = reinterpret_cast<CEvent *>( hEvent );

    int iRet =
#ifdef __MACH__
    0;
    dispatch_semaphore_signal( pEvent->semaphore );
#else /* Other unices */
    sem_post( &pEvent->semaphore );
#endif

    if ( 0 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "BAD EVENT HANDLE %lX\n" ), (long)hEvent );
        return false;

    }

    return true;

}


DWORD WaitForSingleObject( HANDLE h, DWORD dwMilliseconds ) {

    CEvent * pEvent = reinterpret_cast<CEvent *>( h );

    if ( INFINITE == dwMilliseconds ) {

#ifdef __MACH__
        if ( 0 != dispatch_semaphore_wait( pEvent->semaphore, DISPATCH_TIME_FOREVER ) ) {

            return WAIT_TIMEOUT;

        }
#else /* Other unices */
        if ( 0 != sem_wait( &pEvent->semaphore ) ) {

            if ( ETIMEDOUT == errno ) {

                return WAIT_TIMEOUT;

            }

            return WAIT_FAILED;

        }
#endif
        return WAIT_OBJECT_0;

    }

#ifdef __MACH__
    dispatch_time_t ts = dispatch_time( DISPATCH_TIME_NOW, dwMilliseconds * 1000 );

    if ( 0 != dispatch_semaphore_wait( pEvent->semaphore, ts ) ) {

        return WAIT_TIMEOUT;

    }
#else /* Other unices */
    struct timespec ts;
    ts.tv_sec = dwMilliseconds / 1000;
    ts.tv_nsec = dwMilliseconds * 1000;

    int iRet = sem_timedwait( &pEvent->semaphore, &ts );

    if ( -1 == iRet ) {

        if ( ETIMEDOUT == errno ) {

            return WAIT_TIMEOUT;

        }

        return WAIT_FAILED;

    }
#endif

    return WAIT_OBJECT_0;

}
