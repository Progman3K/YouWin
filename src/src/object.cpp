

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


BOOL DeleteObject( HGDIOBJ h ) {

    if ( NULL == h ) {

        DBG_MSG( DBG_ERROR, TEXT( "DeleteObject NULL OBJECT %u" ), h );
        return false;

    }

    IObject * pObject = reinterpret_cast<IObject *>( h );

    GDIObject * pObj;

    switch( pObject->type() ) {

        case OBJECT_TYPE_USERBITMAP:

            DBG_MSG( DBG_WIN32API, TEXT( "Deleting USERBITMAP handle %lX\n" ), h );
            Bitmap::discard( (IBitmap *)pObject );
            break;

        case OBJECT_TYPE_RESOURCEBITMAP:

            DBG_MSG( DBG_WIN32API, TEXT( "Deleting RESOURCEBITMAP handle %lX\n" ), h );
            break;

        case OBJECT_TYPE_FONT:

            DBG_MSG( DBG_WIN32API, TEXT( "Deleting FONT handle %lX\n" ), h );
            break;

        case OBJECT_TYPE_GDI:

            pObj = reinterpret_cast<GDIObject *>( h );

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

        case OBJECT_TYPE_ICON:

            delete reinterpret_cast<Resource *>( h );
            break;

        case OBJECT_TYPE_REGION:

            delete reinterpret_cast<ywRegion *>( h );
            return true;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN OBJECT TYPE %u" ), pObject->type() );
            return false;

    }

    return false;

}


HGDIOBJ SelectObject( HDC hDC, HGDIOBJ hObj ) {

    DBG_MSG( DBG_GRAPHICAL, TEXT( "SelectObject( HDC %lX Object %lX )" ), hDC, hObj );

    DC * pDC = reinterpret_cast<DC *>( hDC );

    if ( NULL == pDC ) {

        DBG_MSG( DBG_ERROR, TEXT( "SelectObject - INVALID DC %lX" ), pDC );
        return HGDI_ERROR;

    }

    IObject * pObject = reinterpret_cast<IObject *>( hObj );

    if ( NULL == pObject ) {

        DBG_MSG( DBG_ERROR, TEXT( "SelectObject - INVALID OBJECT %lX" ), pObject );
        return HGDI_ERROR;

    }

    HGDIOBJ hOldObj;

    switch( pObject->type() ) {

        case OBJECT_TYPE_USERBITMAP:
        case OBJECT_TYPE_RESOURCEBITMAP:

            hOldObj = pDC->pPixels;

            pDC->pPixels = reinterpret_cast<IBitmap *>( hObj );

            return hOldObj;

        case OBJECT_TYPE_FONT:

            hOldObj = pDC->hFont;

            pDC->hFont = (HFONT)hObj;

            return hOldObj;

        case OBJECT_TYPE_GDI:

            break;

        case OBJECT_TYPE_REGION: {

            int iRet = pDC->AddExclusion( reinterpret_cast<ywRegion *>( hObj ) );

            return (HGDIOBJ)(long)iRet; }

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN OBJECT TYPE %u" ), pObject->type() );
            return NULL;

    }

    return NULL;

}


int GetObject( HANDLE h, int c, LPVOID pv ) {

    return 0;

}
