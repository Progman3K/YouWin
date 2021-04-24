

#ifndef YW_BITMAP_H
#define YW_BITMAP_H


#include <vector>


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


class IBitmap /* : public Object */ {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */

    public:

//        IBitmap() : Object( OBJECT_TYPE_BITMAP ) {}


//        unsigned bpp;


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


template <class T> class protoBitmap : public bitmap, public IBitmap {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */

    public:

        virtual ~protoBitmap() {}

        std::vector<T> pixels;


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


#endif /* YW_BITMAP_H */
