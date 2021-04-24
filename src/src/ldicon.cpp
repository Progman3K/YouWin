

#include "ywin.h"



HICON LoadIcon( HINSTANCE hInst, LPCTSTR resname ) {

    if ( ( NULL == hInst ) && ( 0 == HIWORD( resname ) ) ) {

        // return code as actual stock object for now
        return (HICON)(unsigned long)LOWORD( resname );

    }

    HICON h = (HICON)icons.open( hInst, resname );

    return h; // pIcon;

}


BOOL DestroyIcon( HICON h ) {

    if ( NULL == h ) {

        return false;

    }

    if ( 0 == HIWORD( h ) ) {

        // Destroying stock object not permitted
        return false;

    }

//    Icon * pIcon = (Icon *)h;

//    pIcon->close();

//    delete pIcon;

    return true;

}
