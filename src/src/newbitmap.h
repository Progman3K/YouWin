

#ifndef __NEWBITMAP_H__
#define __NEWBITMAP_H__


#include <vector>


#include "resource.h"


#ifndef RT_BITMAP_VAL
#define RT_BITMAP_VAL                     2
#endif


#define ptinrect( pr, pt ) ( ( pt.x >= pr->left ) && ( pt.x <  pr->right ) && ( pt.y >= pr->top ) && ( pt.y <  pr->bottom ) )


class bitmap : public Resource {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */
    
    public:

        
        RECT r;    


        bitmap() : Resource( RT_BITMAP_VAL ) {

            r.left   = 0;
            r.top    = 0;
            r.right  = 0;
            r.bottom = 0;

        }


        unsigned long getWidth( void ) {

            return r.right;

        }


        unsigned long getHeight( void ) {

            return r.bottom;

        }


};


template <class T> class Bitmap : public bitmap {

    /* After the bitmap has been created,
     * you can change its size,
     * but not its number of color planes,
     * or number of bits required to identify the color.
     */
    
    public:

        
        std::vector<T> pixels;


        bool Create( unsigned cx, unsigned cy, T c ) {

            pixels.resize( cx * cy, c );

            r.left   = 0;
            r.top    = 0;
            r.right  = cx;
            r.bottom = cy;

            return true;

        }


        bool SetPixel( const POINT & pt, T c ) {

            if ( NULL == this ) {

                return false;

            }

            if ( ! ptinrect( (&r), pt ) ) {

                return false;

            }

            pixels.at( ( r.right * pt.y ) + pt.x ) = c;

            return true;

        }


        bool GetPixel( const POINT & pt, T & c ) {

            if ( ! ptinrect( (&r), pt ) ) {

                return false;

            }

            c = *( pixels.at( ( r.right * pt.y ) + pt.x ) );

            return true;

        }


};


#endif /* __NEWBITMAP_H__ */
