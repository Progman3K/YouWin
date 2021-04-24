

#include "ywin.h"


HMENU LoadMenu( HINSTANCE hInst, LPCTSTR lpszName ) {

    if ( ( NULL == hInst ) && ( 0 == HIWORD( lpszName ) ) ) {

        // return code as actual stock object for now
        return (HMENU)(unsigned long)LOWORD( lpszName );

    }

//    Resource * h;
// = new Object( OBJECT_TYPE_MENU );
// TODO: CONNECT MENU RESOURCE
//    BOOL bLoaded = Resource::bLoad( hInst, RT_MENU, lpszName, h );

//    if ( ! bLoaded ) {

//        delete h;
//        return NULL;

//    }

//    MENU_RESOURCE * pMenu = (MENU_RESOURCE *)h->data();

    return 0;

}


BOOL DestroyMenu( HMENU h ) {

    if ( NULL == h ) {

        return false;

    }

    if ( 0 == HIWORD( h ) ) {

        // Destroying stock object not permitted
        return false;

    }

    delete reinterpret_cast<Resource *>( h );

    return true;

}


HMENU GetSubMenu( HMENU hMenu, int nIndex ) {

    if ( NULL == hMenu ){

        return NULL;

    }

//    Resource * h = (Resource *)hMenu;

// TODO: CONNECT SUB-MENU
//    MENU_RESOURCE * pMenu = (MENU_RESOURCE *)h->data();

//    if ( pMenu->items[0].fItemFlags ) {
//    }
    return NULL;

}


BOOL TrackPopupMenuEx( HMENU hMenu, UINT uFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm ) {

    return 0;

}
