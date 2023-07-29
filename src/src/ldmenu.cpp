

#include "ywin.h"


HMENU LoadMenu( HINSTANCE hInst, LPCTSTR resname ) {

    if ( NULL == hInst ) {

        /* As commonly-understood, this means to load the menu from the application's default resources */
        hInst = GetModuleHandle( NULL );

    }

    HMENU hMenu = (HMENU)menus.open( hInst, resname );

    return hMenu;

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
