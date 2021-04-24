

#include "ywin.h"


int EventQ::PostMouseMove( long x, long y, unsigned uMKType ) {

    FORWARD_WM_MOUSEMOVE( NULL, x, y, uMKType, PostMessage );

    return 0;

}


int EventQ::PostMouseMsg( bool bUp, long x, long y, unsigned uVKType, unsigned uMKType ) {

    switch( uVKType ) {

        case VK_LBUTTON:

            if ( bUp ) {

                FORWARD_WM_LBUTTONUP( NULL, x, y, MK_LBUTTON, PostMessage );

            } else {

                FORWARD_WM_LBUTTONDOWN( NULL, false, x, y, MK_LBUTTON, PostMessage );

            }
            break;

        case VK_RBUTTON:

            if ( bUp ) {

                FORWARD_WM_RBUTTONUP( NULL, x, y, MK_RBUTTON, PostMessage );

            } else {

                    FORWARD_WM_RBUTTONDOWN( NULL, false, x, y, MK_RBUTTON, PostMessage );

            }
            break;

        case VK_MBUTTON:

            if ( bUp ) {

                FORWARD_WM_MBUTTONUP( NULL, x, y, MK_MBUTTON, PostMessage );

            } else {

                FORWARD_WM_MBUTTONDOWN( NULL, false, x, y, MK_MBUTTON, PostMessage );

            }
            break;

        case VK_XBUTTON1:

            if ( bUp ) {

                FORWARD_WM_XBUTTONUP( NULL, x, y, MK_XBUTTON1, PostMessage );

            } else {

                FORWARD_WM_XBUTTONDOWN( NULL, false, x, y, MK_XBUTTON1, PostMessage );

            }
            break;

        case VK_XBUTTON2:

            if ( bUp ) {

                FORWARD_WM_XBUTTONUP( NULL, x, y, MK_XBUTTON2, PostMessage );

            } else {

                FORWARD_WM_XBUTTONDOWN( NULL, false, x, y, MK_XBUTTON2, PostMessage );

            }
            break;

        default:

            return -1;

    }

    return 0;

}


int EventQ::Read( MSG * pMsg ) {

    struct timeval   timeout;
    struct timeval * ptimeout = NULL;

    unsigned long    now;

    for( ;; ) {

        /* Check window message queue */

        if ( MsgQ.RemoveMessage( pMsg ) ) {

            return 1;

        }

        /* No messages in the queue, prime timers. */
        MetaMSG * pNearestTimerMsg = Timers.GetNearestTimer();

        if ( NULL != pNearestTimerMsg ) {

            now = GetTickCount();

            if ( now >= pNearestTimerMsg->lFresh ) {

                /* Copy to delivery queue. */
                PostToQ( MsgQ, pNearestTimerMsg );

                /* Set its next expiry NOW in case the user deletes it during the callback */
                pNearestTimerMsg->lFresh = GetTickCount() + pNearestTimerMsg->ulInterval;

                continue;

            }

            /* it's before the time, default to blocking until it is time. */

            timeout.tv_sec  = ( pNearestTimerMsg->lFresh - now ) / 1000;

            timeout.tv_usec = ( ( pNearestTimerMsg->lFresh - now ) % 1000 ) * 1000;   /* microseconds */

            ptimeout = &timeout;

        } else {

            /* No timer are in effect. */
            ptimeout = NULL;

        }

#if defined( ANDROID ) && defined( YOU_WIN_GRAPHICAL )

        int iRet = droidSelect( ptimeout );

        if ( 0 > iRet ) {

            return -1;

        }

#else
#if defined( YOU_WIN_GRAPHICAL_OSX ) && defined( YOU_WIN_GRAPHICAL )

        OSXGetMessage( this, ptimeout );

#else

        fd_set   fdreadlist;
        fd_set * pfdreadlist;

        fd_set   fdwritelist;
        fd_set * pfdwritelist;

        // Establish file descriptor lists for stdin and server reading.  
        FD_ZERO( &fdreadlist );
        pfdreadlist = NULL;

        FD_ZERO( &fdwritelist );
        pfdwritelist = NULL;

        int iHighestFD = -1;

        if ( 0 < ReadQ.size() ) {

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Evaluating %u socket read queue members" ), ReadQ.size() );

            pfdreadlist = &fdreadlist;

            iHighestFD = ReadQ.SetFDs( fdreadlist );

        }

        if ( 0 < WriteQ.size() ) {

            pfdwritelist = &fdwritelist;

            int iTemp = WriteQ.SetFDs( fdwritelist );

            if ( iTemp > iHighestFD ) {

                iHighestFD = iTemp;

            }

        }


#ifdef DEBUG
//        TCHAR   szMsg[1024];

        if ( ptimeout ) {

//            sprintf( szMsg, "%lu seconds, %lu ucseconds", (long unsigned)ptimeout->tv_sec, (long unsigned)ptimeout->tv_usec );

        } else {

//            sprintf( szMsg, "no timers" );

        }

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "select( %d, %s, %s, NULL, %s" ), iHighestFD + 1, pfdreadlist ? "readers" : "NO_READERS", pfdwritelist ? "writers" : "NO_WRITERS", szMsg );
#endif /* DEBUG */


        int iRet = select( iHighestFD + 1, pfdreadlist, pfdwritelist, NULL, ptimeout );

        if ( 0 > iRet ) {

            if ( EINTR == errno ) {

                // select was interrupted by asynchronous signal. Any significant interaction will have generated a message
                continue;

            }

            DBG_MSG( DBG_ERROR, TEXT( "select error %d" ), errno );
            return -1;

        }

        if ( 0 == iRet ) {

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "process timers (%d selectors)" ), iHighestFD + 1 );
            continue;

        }

//        DBG_MSG( DBG_ERROR, TEXT( "select returns %d, check selectors" ), iRet );

        if ( NULL != pfdreadlist ) {

            ReadQ.HandleEvents( fdreadlist );

        }

        if ( NULL != pfdwritelist ) {

            WriteQ.HandleEvents( fdwritelist );

        }
#endif
#endif

    }

}
