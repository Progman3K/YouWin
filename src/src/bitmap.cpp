

#include "ywin.h"


HBITMAP CreateBitmap( int cx, int cy, UINT cPlanes, UINT uBPP, const void * lpvBits ) {

    IBitmap * p = Bitmap::alloc( cx, cy, cPlanes, uBPP, lpvBits );

    return p;

}


HBITMAP CreateCompatibleBitmap( HDC hDC, int cx, int cy ) {

    IBitmap * p;
    
    if ( NULL == hDC ) {
        
        p = Bitmap::alloc( cx, cy, 1, 1, NULL );
        
    } else {
        
        p = Bitmap::alloc( cx, cy, 1, 32, NULL );

    }

    return p;

}
