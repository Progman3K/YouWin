

#include "ywin.h"


ULONG_PTR SetClassLongPtr( HWND hWnd, int iIndex, LONG_PTR lVal ) {

    ywWindow * pWnd;
    ULONG_PTR lOldVal;

    if ( ( pWnd = IsWnd( hWnd ) ) == NULL ) {

        errno = EBADF;
        return 0;

    }

    switch( iIndex ) {

        case GCL_STYLE:

            lOldVal = (ULONG_PTR)pWnd->bDlgProc;

            pWnd->bDlgProc = (DLGPROC)lVal;

            return lOldVal;

        case GCLP_HICON:

            lOldVal = (ULONG_PTR)pWnd->pClass->SetClassIcon( (HICON)lVal );
            return lOldVal;

        case GCLP_WNDPROC:

            lOldVal = (ULONG_PTR)( ( reinterpret_cast<Dialog *>( pWnd ) )->dwMsgResult );

            ( reinterpret_cast<Dialog *>( pWnd ) )->dwMsgResult = (DWORD)lVal;

            return lOldVal;

        case GCLP_HBRBACKGROUND:

            lOldVal = (ULONG_PTR)pWnd->lUserData;

            pWnd->lUserData = lVal;

            return lOldVal;

    }

    return 0;

}


ULONG_PTR GetClassLongPtr( HWND hWnd, int iIndex ) {

    ywWindow * pWnd;

    if ( ( pWnd = IsWnd( hWnd ) ) == NULL ) {

        errno = EBADF;
        return 0;

    }

    WindowClass * pClass = pWnd->pClass;

    UserWindow * pUserWnd = reinterpret_cast<UserWindow *>( pWnd );

    UserWindowClass * pUserClass = reinterpret_cast<UserWindowClass *>( pWnd->pClass );

    switch( iIndex ) {

//        case GCW_ATOM:

//            return (ULONG_PTR)pClass->;

        case GCL_CBCLSEXTRA:

            return (ULONG_PTR)pUserClass->ClsExtra.size();

        case GCL_CBWNDEXTRA:

            return (ULONG_PTR)pUserWnd->WndExtra.size();

        case GCLP_HBRBACKGROUND:

            return (ULONG_PTR)pClass->GetBackgroundBrush();

//        case GCLP_HCURSOR:

        case GCLP_HICON:

            return (ULONG_PTR)pClass->GetClassIcon();

//        case GCLP_HMODULE:

//        case GCLP_MENUNAME:

        case GCL_STYLE:

            return (ULONG_PTR)(long)pClass->GetClassStyles();

        case GCLP_WNDPROC:

            return (ULONG_PTR)pClass->GetWindowProc();

    }

    return 0;

}
