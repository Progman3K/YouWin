

#include "ywin.h"


BOOL PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Window * pWnd;
    BOOL     bRet;

    if ( HWND_BROADCAST == hWnd ) {

        /* TODO Add proper support for broadcast */
        return false;

    }

    if ( NULL == hWnd ) {

        /* TODO Implement proper thread-posting */
        return false;

    }

    pWnd = IsWnd( hWnd );

    if ( 0 == pWnd ) {

        /* Invalid handle TODO set error code */
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

    return g.Q.PostToQ( g.Q.MsgQ, &Msg );

}
