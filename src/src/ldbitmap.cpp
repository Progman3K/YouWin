

#include "ywin.h"


HBITMAP LoadBitmap( HINSTANCE hInst, LPCTSTR resname ) {

    const UserBitmap * pBitmap = bitmaps.Find( (const ResourceList *)hInst, resname );

    if ( 0 == pBitmap ) {

        pBitmap = bitmaps.open( (const ResourceList *)hInst, resname );

    }

    DBG_MSG( DBG_GRAPHICAL, TEXT( "Loaded bitmap resource 0x%lX from 0x%lX: 0x%lX" ), resname, hInst, pBitmap );

    return (HBITMAP)pBitmap;

}
