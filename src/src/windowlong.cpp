

#include "ywin.h"


LONG_PTR SetWindowLongPtr( HWND hWnd, int iIndex, LONG_PTR lVal ) {

    Window * pWnd;
    LONG_PTR lOldVal;

    if ( ( pWnd = IsWnd( hWnd ) ) == NULL ) {

        errno = EBADF;
        return 0;

    }

    switch( iIndex ) {

        case GWL_STYLE:

            lOldVal = (LONG_PTR)pWnd->dwStyle;

            pWnd->dwStyle = (DWORD)lVal;

            return lOldVal;

        case DWL_DLGPROC:

            lOldVal = (LONG_PTR)pWnd->bDlgProc;

            pWnd->bDlgProc = (DLGPROC)lVal;

            return lOldVal;

        case DWL_MSGRESULT:

            lOldVal = (LONG_PTR)( ( reinterpret_cast<Dialog *>( pWnd ) )->dwMsgResult );

            ( reinterpret_cast<Dialog *>( pWnd ) )->dwMsgResult = (DWORD)lVal;

            return lOldVal;

        case DWL_USER:

            lOldVal = (LONG_PTR)( ( reinterpret_cast<Dialog *>( pWnd ) )->dwUser );

            ( reinterpret_cast<Dialog *>( pWnd ) )->dwUser = (DWORD)lVal;

            return lOldVal;

        case GWL_USERDATA:

            lOldVal = pWnd->lUserData;

            pWnd->lUserData = lVal;

            return lOldVal;

    }

    return 0;

}


LONG_PTR GetWindowLongPtr( HWND hWnd, int iIndex ) {

    Window * pWnd;

    if ( ( pWnd = IsWnd( hWnd ) ) == NULL ) {

        errno = EBADF;
        return 0;

    }

    switch( iIndex ) {

        case DWL_DLGPROC:

            return (LONG_PTR)pWnd->bDlgProc;

        case DWL_MSGRESULT:

            return (LONG_PTR)( ( reinterpret_cast<Dialog *>( pWnd ) )->dwMsgResult );

        case DWL_USER:

            return (LONG_PTR)( ( reinterpret_cast<Dialog *>( pWnd ) )->dwUser );

        case GWL_EXSTYLE:

            return (LONG_PTR)pWnd->dwExStyle;

        case GWL_STYLE:

            return (LONG_PTR)pWnd->dwStyle;

        case GWL_USERDATA:

            return pWnd->lUserData;

        case GWL_WNDPROC:

            return (LONG_PTR)pWnd->WndProc;

        case GWLP_HINSTANCE:

            return (LONG_PTR)pWnd->hInst;

    }

    return 0;

}
