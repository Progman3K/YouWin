

#include "ywin.h"


BOOL StretchBlt( HDC hdcDst, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop ) {

    DC * pSrcDC = (DC *)hdcSrc;
    DC * pDstDC = (DC *)hdcDst;

    POINT ptSrc;
    POINT ptDst;
    COLORREF c;

    StartPoints();

    for( int x = 0, y = 0; y < hDest; ) {

        ptSrc.x = xSrc + x;
        ptSrc.y = ySrc + y;

        ptDst.x = xDest + x;
        ptDst.y = yDest + y;

        if ( pSrcDC->pPixels->GetPixel( ptSrc, c ) ) {

            switch( pSrcDC->pPixels->getfmt() ) {

                case IBitmap::BITMAP_FMT_V4:
                case IBitmap::BITMAP_FMT_V5:

                    /* Handle transparency */

                    if ( 255 == GetAValue( c ) ) {

                        pDstDC->SetPixel( ptDst, c, 0 );

                    }
                    break;

                default:

                    pDstDC->SetPixel( ptDst, c, 0 );

            }

        }

        x++;

        if ( x > wDest ) {

            x = 0;
            y++;

        }

    }

    EndPoints();

    return true;

}
