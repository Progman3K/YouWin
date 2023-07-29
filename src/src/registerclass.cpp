

#include "ywin.h"


ATOM RegisterClass( const WNDCLASS * pWndClass ) {

    if ( CS_SYSTEM & pWndClass->style ) {

        /* System classes cannot be unregistered */
        return 0;

    }

    WindowClass * pExistingClass = classes.Find( pWndClass->lpszClassName );

    if ( NULL != pExistingClass ) {

        DBG_MSG( DBG_ERROR, TEXT( "Error - RegisterClass: class '%s' already exists" ), pExistingClass->GetClassName() );

        return 0;

    }

    UserWindowClass * pClass = new UserWindowClass( pWndClass->lpszClassName, pWndClass->lpfnWndProc, pWndClass->hbrBackground, pWndClass->style, pWndClass->hIcon, pWndClass->cbWndExtra );

    if ( NULL == pClass ) {

        return 0;

    }

    if ( 0 < pWndClass->cbClsExtra ) {

        pClass->ClsExtra.resize( pWndClass->cbClsExtra, 0 );

    }

    ClassPair   pair;

    pair.first  = pClass->GetClassName();
    pair.second = pClass;

    ClassList::iterator ii = classes.insert( classes.end(), pair );

    ATOM wndclass = std::distance( classes.begin(), ii );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "RegisterClass: class '%s' registered" ), pClass->GetClassName() );

    return wndclass;

#if 0
    // Not processed
    hInstance;
    hCursor;
    lpszMenuName;
#endif

}
