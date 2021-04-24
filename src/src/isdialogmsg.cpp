

#include "ywin.h"


BOOL IsDialogMessage( HWND hDlg, const MSG * pMsg ) {

    if ( NULL == hDlg ) {

        return false;

    }

    /* This switch might be used by TranslateMessage too.. */

    switch( pMsg->message ) {

        default:

            return false;

        case WM_CHAR:
        case WM_KEYDOWN:
        case WM_KEYUP:

            /* Let the dialog decide who reads it*/
            ;

    }

    /* Message from the console driver */

    /* Direct it to dialog if no window currently has focus */
    SendMessage( ( NULL == pMsg->hwnd ) ? hDlg : pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );

    return true;

}
