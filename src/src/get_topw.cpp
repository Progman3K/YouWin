

#include "ywin.h"


HWND GetActiveWindow( void ) {

    IWindow * pWnd;

    if ( NULL != ( pWnd = reinterpret_cast<IWindow *>( GetFocus() ) ) ) {

        pWnd = pWnd->GetPopup( pWnd );

        if ( NULL != pWnd ) {

            return pWnd;

        }

    }

    /* Fallback to old method */
    return NULL;

}
