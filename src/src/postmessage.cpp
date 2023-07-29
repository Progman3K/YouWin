

#include "ywin.h"


BOOL PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Window * pWnd;
    BOOL     bRet;

    if ( HWND_BROADCAST == hWnd ) {

        /* TODO Add proper support for broadcast */
        DBG_MSG( DBG_ERROR, TEXT( "Broadcast post failed" ) );
        return false;

    }

    if ( NULL == hWnd ) {

        /* TODO Implement proper thread-posting */
        DBG_MSG( DBG_ERROR, TEXT( "Thread post failed" ) );
        return false;

    }

    pWnd = IsWnd( hWnd );

    if ( 0 == pWnd ) {

        /* Invalid handle TODO set error code */
        DBG_MSG( DBG_ERROR, TEXT( "Post failed: Bad window" ) );
        return false;

    }

    MetaMSG  Msg;

    Msg.Msg.hwnd    = hWnd;
    Msg.Msg.message = uiMsg;
    Msg.Msg.wParam  = wParam;
    Msg.Msg.lParam  = lParam;

    switch( uiMsg ) {

        case WM_NCPAINT:

            if ( pWnd->bDrawFramePending ) {

                return true;

            }

            bRet = g.Q.PostToQ( g.Q.MsgQ, &Msg );

            if ( bRet ) {

                pWnd->bDrawFramePending = true;

            }

            return bRet;


        case WM_PAINT:

            if ( pWnd->bDirty ) {

                return true;

            }

            bRet = g.Q.PostToQ( g.Q.MsgQ, &Msg );

            if ( bRet ) {

                pWnd->bDirty = true;

            }

            return bRet;

        case WM_ERASEBKGND:

            if ( pWnd->fErase ) {

                return true;

            }

            bRet = g.Q.PostToQ( g.Q.MsgQ, &Msg );

            if ( bRet ) {

                pWnd->fErase = true;

            }

            return bRet;

    }

    DBG_MSG( DBG_ERROR, TEXT( "Post message %u to loop" ), Msg.Msg.message );
    return g.Q.PostToQ( g.Q.MsgQ, &Msg );

}
