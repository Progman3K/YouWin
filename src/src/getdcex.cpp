

#include "ywin.h"


extern "C" HDC GetDC( HWND hWnd ) {

    /* Returns a copy of the client area */
    Window * pWnd;

    if ( NULL == hWnd ) {

        /* Requesting DC to the entire screen */
        pWnd = NULL;

    } else {

        pWnd = IsWnd( hWnd );

        if ( NULL == pWnd ) {

            return NULL;

        }

    }

    if ( NULL == pWnd ) {

        Region region( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );

        DC * pDC = new DC( pWnd, &region, NULL, DC::EntireScreen );

        if ( NULL == pDC ) {

            return NULL;

        }

        return (HDC)pDC;

    }

//    pDC = new DC( pWnd, &pWnd->ClientArea, &pWnd->ClientPixels, 0 );

    return (HDC)&pWnd->ClientDC;

}


extern "C" HDC GetDCEx( HWND hWnd, HRGN hRgn, DWORD flags ) {

    Window * pWnd;
    DC *     pDC   = NULL;
    Region * pRgn  = reinterpret_cast<Region *>( hRgn );

    if ( NULL == hWnd ) {

        /* Requesting DC to the entire screen */
        pWnd = NULL;

    } else {

        pWnd = IsWnd( hWnd );

        if ( NULL == pWnd ) {

            return NULL;

        }

    }

    if ( DCX_WINDOW & flags ) {

        if ( NULL == pWnd ) {

            Region region( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );

            pDC = new DC( pWnd, &region, NULL, DC::EntireScreen );

            if ( NULL == pDC ) {

                return NULL;

            }

        } else {

            Region region( 0, 0, pWnd->cx, pWnd->cy );

            pDC = new DC( pWnd, &region, NULL, DC::EntireWindow );

            if ( NULL == pDC ) {

                return NULL;

            }

        }

    } else {

        pDC = &pWnd->ClientDC;

    }

    if ( DCX_INTERSECTRGN & flags ) {

        pDC->AddIntersection( pRgn );

    }

    if ( DCX_EXCLUDERGN & flags ) {

        pDC->AddExclusion( pRgn );

    }

#if 0
    DCX_CACHE
    DCX_PARENTCLIP
    DCX_CLIPSIBLINGS
    DCX_CLIPCHILDREN
    DCX_NORESETATTRS
    DCX_INTERSECTUPDATE
    DCX_LOCKWINDOWUPDATE
    DCX_VALIDATE
#endif

    return (HDC)pDC;

}


HDC CreateCompatibleDC( HDC hDC ) {

    IBitmap * pBMP = Bitmap::alloc( 1, 1, 1, 1, NULL );

    DC * pDC = new DC( NULL, NULL, pBMP, DC::Memory );

    if ( NULL == pDC ) {

        return NULL;

    }

    return pDC;

}


BOOL DeleteDC( HDC hDC ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL == pDC ) {

        return false;

    }

    /* If it's a memory DC, discard the selected bitmap, if any */
    if ( pDC->pPixels ) {

        DeleteObject( (HGDIOBJ)pDC->pPixels );
        pDC->pPixels = 0;

    }

    delete pDC;

    return true;

}


int ReleaseDC( HWND, HDC hDC ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL == pDC ) {

        return 0;

    }

    if ( DC::StaticToWindow & pDC->flags ) {

        return 1;

    }

    delete pDC;

    return 1;

}
