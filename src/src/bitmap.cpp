

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


unsigned UserBitmap::getbpp( void ) const {

    switch( fmt ) {

        case BITMAP_FMT_V3:
        case BITMAP_FMT_V4:
        case BITMAP_FMT_V5:

            return ((const BITMAPINFOHEADER *)pInternalBitmap)->biBitCount;

        default:

            return 0;

    }

//    return bpp;

}


long UserBitmap::Width( void ) const {

    switch( fmt ) {

        case BITMAP_FMT_V3:
        case BITMAP_FMT_V4:
        case BITMAP_FMT_V5:

            return ((const BITMAPINFOHEADER *)pInternalBitmap)->biWidth;

        default:

            return 0;

    }

}


long UserBitmap::Height( void ) const {

   switch( fmt ) {

        case BITMAP_FMT_V3:
        case BITMAP_FMT_V4:
        case BITMAP_FMT_V5:

            return ((const BITMAPINFOHEADER *)pInternalBitmap)->biHeight;

        default:

            return 0;

    }

}


size_t UserBitmap::size( void ) const {

   switch( fmt ) {

        case BITMAP_FMT_V3:
        case BITMAP_FMT_V4:
        case BITMAP_FMT_V5:

            return ((const BITMAPINFOHEADER *)pInternalBitmap)->biSizeImage;

        default:

            return 0;

    }

}


const void * UserBitmap::data( void ) const {

   switch( fmt ) {

        case BITMAP_FMT_V3:

            return ((const BITMAPINFO *)pInternalBitmap)->bmiColors;

        default:

            return 0;

    }

}


bool UserBitmap::GetPixel( const POINT & pt, COLORREF & c ) const {

   switch( fmt ) {

        case BITMAP_FMT_V3: {

                /* This code presupposes uncompressed RGB */

                const BITMAPINFO *pBitmap = (const BITMAPINFO *)pInternalBitmap;

                if ( ( pt.x > pBitmap->bmiHeader.biWidth ) || ( pt.y > pBitmap->bmiHeader.biHeight ) ) {

                    return false;

                }

                unsigned stride = ( ( ( ( pBitmap->bmiHeader.biWidth * pBitmap->bmiHeader.biBitCount ) + 31 ) & ~31 ) >> 3 );

                const RGBTRIPLE * pRGB = (const RGBTRIPLE *)( ( (const BYTE *)pBitmap->bmiColors ) + ( ( pBitmap->bmiHeader.biHeight - pt.y ) * stride ) );

                pRGB += pt.x;

                BYTE r,g,b;

                r = pRGB->rgbtRed;
                g = pRGB->rgbtGreen;
                b = pRGB->rgbtBlue;

                c = RGB( r, g, b );

            }
            return true;

        case BITMAP_FMT_V5: {

                /* This code presupposes uncompressed RGB */

                const BITMAPINFO *pBitmap = (const BITMAPINFO *)pInternalBitmap;

                if ( ( pt.x > pBitmap->bmiHeader.biWidth ) || ( pt.y > pBitmap->bmiHeader.biHeight ) ) {

                    return false;

                }

                unsigned stride = ( ( ( ( pBitmap->bmiHeader.biWidth * pBitmap->bmiHeader.biBitCount ) + 31 ) & ~31 ) >> 3 );

                const RGBQUAD * pRGB = (const RGBQUAD *)( ( ((const BYTE *)pBitmap ) + sizeof( BITMAPV5HEADER ) ) + ( ( pBitmap->bmiHeader.biHeight - pt.y ) * stride ) );

                pRGB += pt.x;

                BYTE r,g,b,a;

                r = pRGB->rgbRed;
                g = pRGB->rgbGreen;
                b = pRGB->rgbBlue;
                a = pRGB->rgbReserved;

                c = RGBA( r, g, b, a );

            }
            return true;

        default:

            return false;

    }

}
