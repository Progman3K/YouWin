

#include "ywin.h"


BOOL BitBlt( HDC hDestDC, int x, int y, int cx, int cy, HDC hSrcDC, int nXSrc, int nYSrc, DWORD dwRop ) {

    DC * pDestDC = reinterpret_cast<DC *>( hDestDC );

    DC * pSrcDC  = reinterpret_cast<DC *>( hSrcDC );

    StartPoints();

    RECT  r;
    POINT pt;

    switch( dwRop ) {

        case DSTINVERT:

            r( x, y, x + cx, y + cy );

            pDestDC->Invert( r );
            break;

        case SRCCOPY:

            pt( nXSrc, nYSrc );
            r( x, y, x + cx, y + cy );

            pSrcDC->copy( pt, pDestDC, r );
            break;

    }

    EndPoints();

    return true;

}

