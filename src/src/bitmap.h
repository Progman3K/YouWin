

#ifndef YW_BITMAP_H
#define YW_BITMAP_H


#include <vector>


#include <gdi.h>


#include "resource.h"


#ifndef RT_BITMAP_VAL
#define RT_BITMAP_VAL                     2
#endif


#define ptinrect( pr, pt ) ( ( pt.x >= pr->left ) && ( pt.x <  pr->right ) && ( pt.y >= pr->top ) && ( pt.y <  pr->bottom ) )


class bitmap {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */

    public:


        RECT r;
        unsigned bpp;


        bitmap() {

            r.left   = 0;
            r.top    = 0;
            r.right  = 0;
            r.bottom = 0;

            bpp = 0;

        }


};


class IBitmap : public Object {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */

    public:

        typedef enum {

            BITMAP_FMT_NONE,
            BITMAP_FMT_FONT,
            BITMAP_FMT_V3,
            BITMAP_FMT_V4,
            BITMAP_FMT_V5

        } BITMAP_FMT;

//        IBitmap() : Object( OBJECT_TYPE_BITMAP ) {}


//        unsigned bpp;

        virtual BITMAP_FMT getfmt( void ) const = 0;

        virtual unsigned getbpp( void ) const = 0;


        virtual void setbpp( unsigned ) {} /* = 0; */


        virtual bool Create( unsigned /* cx */, unsigned /* cy */, COLORREF /* c */ ) { return false; } /* = 0; */


        virtual bool SetPixel( const POINT & /* pt */, COLORREF /* c */ ) { return false; } /* = 0; */


        virtual bool GetPixel( const POINT & pt, COLORREF & c ) const = 0;


        virtual long Width( void ) const = 0;


        virtual long Height( void ) const = 0;


        virtual const void * data( void ) const = 0;


        virtual void append( COLORREF /* c */ ) {} /* = 0; */


        virtual size_t size( void ) const = 0;


};


template <class T> class protoBitmap : /* public Object, */ public bitmap, public IBitmap {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */

    public:

        protoBitmap() {

            setType( OBJECT_TYPE_USERBITMAP );

        }

        virtual ~protoBitmap() {}

        std::vector<T> pixels;


        BITMAP_FMT getfmt( void ) const override {

            return BITMAP_FMT_NONE;

        }


        unsigned getbpp( void ) const override { return bpp; }


        void setbpp( unsigned nbpp ) override { bpp = nbpp; }


        bool Create( unsigned cx, unsigned cy, COLORREF c ) override {

            pixels.resize( cx * cy, c );

            r.left   = 0;
            r.top    = 0;
            r.right  = cx;
            r.bottom = cy;

            return true;

        }


        bool SetPixel( const POINT & pt, COLORREF c ) override {

            if ( ! ptinrect( (&r), pt ) ) {

                return false;

            }

            pixels.at( ( r.right * pt.y ) + pt.x ) = c;

            return true;

        }


        bool GetPixel( const POINT & pt, COLORREF & c ) const override {

            if ( ! ptinrect( (&r), pt ) ) {

                return false;

            }

            c = pixels.at( ( r.right * pt.y ) + pt.x );

            return true;

        }


        long Width( void ) const override {

            return r.right;

        }


        long Height( void ) const override {

            return r.bottom;

        }


        const void * data( void ) const override {

            return pixels.data();

        }


        void append( COLORREF c ) override {

            return pixels.push_back( c );

        }


        size_t size( void ) const override {

            return pixels.size();

        }


};


class Bitmap {

    public:

        static IBitmap * alloc( int cx, int cy, UINT /* cPlanes */, UINT uBPP, const void * /* lpvBits */ ) {

            IBitmap * p;

            switch( uBPP ) {

                case 1:

                    p = new protoBitmap<char>;
                    p->setbpp( 1 );
//                    p->bpp = 1;
                    break;

                case 32:

                    p = new protoBitmap<COLORREF>;
                    p->setbpp( 32 );
//                    p->bpp = 32;
                    break;

                default:

                    return NULL;

            }

            p->Create( cx, cy, 0 );

            return p;

        }


        static void discard( IBitmap * pThis ) {

            switch( pThis->getbpp() ) {

                case 1:

                    delete reinterpret_cast<protoBitmap<char> *>( pThis );
                    break;

                case 32:

                    delete reinterpret_cast<protoBitmap<COLORREF> *>( pThis );
                    break;

            }

        }


};


/* This is what a HBITMAP can map to directly */
class UserBitmap : public IBitmap /* , public Object */ {

    public:

        BITMAP_FMT fmt;


        BITMAP_FMT getfmt( void ) const override {

            return fmt;

        }


        UserBitmap( const BITMAPINFOHEADER * pBitmap ) {

            setType( OBJECT_TYPE_RESOURCEBITMAP );

            pInternalBitmap = (VOID *)pBitmap;

            const TCHAR * bmptype;

            switch( pBitmap->biSize ) {

                case sizeof( BITMAPINFOHEADER ):

                    fmt = BITMAP_FMT_V3;
                    bmptype = TEXT( "v3" );
                    break;

                case sizeof( BITMAPV4HEADER ):

                    fmt = BITMAP_FMT_V4;
                    bmptype = TEXT( "v4" );
                    break;

                case sizeof( BITMAPV5HEADER ):

                    fmt = BITMAP_FMT_V5;
                    bmptype = TEXT( "v5" );
                    break;

                default:

                    fmt = BITMAP_FMT_NONE;
                    bmptype = TEXT( "UNKNOWN" );
                    break;

            }

            DBG_MSG( DBG_DATA_DUMPS, TEXT( 
                     "Windows bitmap %s loaded:\n"
                     "Size of header: in code %u, on disk: %u\n"
                     "Dimensions: %ux%u\n"
                     "planes: %u\n"
                     "bits per pixel: %u\n"
                     "compression: %u\n"
                     "size in bytes: %u\n"
                     "colors used: %u\n"
                     "color important: %u\n"
                    ),
                     bmptype,
                     (unsigned)sizeof( BITMAPINFOHEADER ),
                     (unsigned)pBitmap->biSize,
                     (unsigned)pBitmap->biWidth,
                     (unsigned)pBitmap->biHeight,
                     (unsigned)pBitmap->biPlanes,
                     (unsigned)pBitmap->biBitCount,
                     (unsigned)pBitmap->biCompression,
                     (unsigned)pBitmap->biSizeImage,
                     (unsigned)pBitmap->biClrUsed,
                     (unsigned)pBitmap->biClrImportant
            );

        }

        VOID * pInternalBitmap; /* This might point to storage of BITMAP_FMT type */

        /* IBitmap API */
        unsigned getbpp( void ) const override;
        long Width( void ) const override;
        long Height( void ) const override;
        size_t size( void ) const override;
        const void * data( void ) const override;
        bool GetPixel( const POINT & pt, COLORREF & c ) const override;

};


typedef std::pair <const Resource *, UserBitmap> BmpPair;


class BmpList : public std::map <const Resource *, UserBitmap> {

    public:

        const UserBitmap * open( const ResourceList * resources, LPCTSTR resname ) {

            HINSTANCE hInst = (HINSTANCE)resources;
            HRSRC hRes = FindResource( hInst, resname, RT_BITMAP );

            if ( 0 == hRes ) {

                DBG_MSG( DBG_ERROR, TEXT( "Could not load bitmap resource %lX from %lX" ), resname, hInst );
                return NULL;

            }

            HGLOBAL h = LoadResource( hInst, hRes );

            const BITMAPINFOHEADER * pBitmap = (const BITMAPINFOHEADER *)LockResource( h );

            DBG_MSG( DBG_GRAPHICAL, TEXT( "Loaded bitmap resource %lX from %lX: %lX" ), resname, hInst, pBitmap );

            UserBitmap bitmap( pBitmap );

            auto f = emplace( (const Resource *)hRes, bitmap );

            DBG_MSG( DBG_ERROR, TEXT( "Make bitmap: %s" ), f.second ? "Success" : "Failed" );

            if ( false == f.second ) {

                return 0;

            }

            return &f.first->second;

        }

        const UserBitmap * Find( const ResourceList * resources, LPCTSTR resname ) {

            /*
             * Perform a for over the list and check each bitmap resource record for a matching name.
             * If found, return the record, otherwise scan the resources for a matching bitmap.
             * If found, create a UserBitmap object wrapping the bitmap resource, insert it in the list, and then return its pointer
             * Otherwise return NULL.
             */

            for ( auto const & [resource,bmp] : *this ) {

//                if ( resources != resource )

                if ( 0 == HIWORD( resname ) ) {

                    // Name must be numerical
                    if ( 0 == resource->Id.uName ) continue; // Name not numerical

                    if ( LOWORD( resname ) != resource->Id.uName ) continue; // Not right name

                } else {

                    // Name must be alphanumerical
                    if ( 0 != resource->Id.uName ) continue; // Name not alphanumerical

                    TSTRING tName( resource->Id.pszName );

//                    if ( 0 != _tcscmp( resname, resource.Id.pszName ) ) continue; // Not right name
                    if ( 0 != tName.comparei( resname ) ) continue; // Not right name

                }

                return &bmp;

            }

            return NULL;

        }


};


extern  BmpList bitmaps;


#endif /* YW_BITMAP_H */
