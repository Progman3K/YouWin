

#include "ywin.h"


BOOL CloseHandle( HANDLE h ) {

    class Object * p = (class Object *)h;

    switch( p->type() ) {

        case OBJECT_TYPE_EVENT:

//            DEBUG_PRINTF( TEXT( "Deleting EVENT handle %lX\n" ), h );
            delete reinterpret_cast<CEvent *>( p );
            break;

        case OBJECT_TYPE_IO:

            DBG_MSG( DBG_WIN32API, TEXT( "Deleting COMM handle %lX\n" ), h );
//            CloseCommPort( h );
            break;

        case OBJECT_TYPE_FF:

            DBG_MSG( DBG_WIN32API, TEXT( "Deleting FINDFIRST handle %lX\n" ), h );
            delete reinterpret_cast<CFindFirst *>( p );
            break;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN HANDLE %lX, type %u\n" ), h, p->type() );
            return false;

    }

    return true;

}


BOOL DeleteObject( HGDIOBJ hObj ) {

    if ( NULL == hObj ) {

        return false;

    }

    IObject * pObject = reinterpret_cast<IObject *>( hObj );

    GDIObject * pObj;

    switch( pObject->type() ) {

        case RT_BITMAP_VAL:

            break;

        case RT_FONT_VAL:

            break;

        case RT_GDI_VAL:

            pObj = reinterpret_cast<GDIObject *>( hObj );

            if ( pObj->bStatic ) {

                return false;

            }

            switch( pObj->GDIObjType ) {

                case GDIObject::solid_brush:

                    delete reinterpret_cast<SolidBrush *>( pObj );
                    return true;

                case GDIObject::pen:

                    delete reinterpret_cast<Pen *>( pObj );
                    return true;

                default:

                    DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN GDI OBJECT TYPE %u" ), pObj->GDIObjType );
                    return false;

            }

            return false;

        case RT_ICON_VAL:

            delete reinterpret_cast<Resource *>( hObj );
            break;

        case RT_REGION_VAL:

            delete reinterpret_cast<Region *>( hObj );
            return true;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN OBJECT TYPE %u" ), pObject->type() );
            return false;

    }

    return false;

}


HGDIOBJ SelectObject( HDC hDC, HGDIOBJ hObj ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    IObject * pObject = reinterpret_cast<IObject *>( hObj );

    if ( ( NULL == pDC ) || ( NULL == pObject ) ) {

        return HGDI_ERROR;

    }

    HGDIOBJ hOldObj;

    switch( pObject->type() ) {

        case RT_BITMAP_VAL:

            hOldObj = pDC->pPixels;

            pDC->pPixels = reinterpret_cast<IBitmap *>( hObj );

            return hOldObj;

        case RT_FONT_VAL:

            hOldObj = pDC->hFont;

            pDC->hFont = (HFONT)hObj;

            return hOldObj;

        case RT_GDI_VAL:

            break;

        case RT_REGION_VAL: {

            int iRet = pDC->AddExclusion( reinterpret_cast<Region *>( hObj ) );

            return (HGDIOBJ)(long)iRet; }

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN OBJECT TYPE %u" ), pObject->type() );
            return NULL;

    }

    return NULL;

}
