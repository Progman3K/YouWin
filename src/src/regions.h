#ifndef YW_REGION_H
#define YW_REGION_H


#include <vector>
#include "object.h"


class ywRegion : public std::vector<RECT>, public Object {


    public:


        int       x;
        int       y;
        unsigned cx;
        unsigned cy;


        ywRegion() /* : Object( OBJECT_TYPE_REGION ) */ {

            setType( OBJECT_TYPE_REGION );
            reset();

        }


        virtual ~ywRegion() override {}


        ywRegion( int X, int Y, unsigned CX, unsigned CY ) /* : Object( OBJECT_TYPE_REGION ) */ {

            setType( OBJECT_TYPE_REGION );
            x  = X;
            y  = Y;
            cx = CX;
            cy = CY;

        }


        void reset( void ) {

            x  = 0;
            y  = 0;
            cx = 0;
            cy = 0;

            clear();

        }


        bool add( RECT r ) {

#if 0
            if ( r.left < pt.x ) {

                pt.x = r.left;

            }

            if ( r.top < pt.y ) {

                pt.y = r.top;

            }

            if ( r.right > cx ) {

                cx = r.right;

            }

            if ( r.bottom > cy ) {

                cy = r.bottom;

            }
#endif

            // If r is either the same as another rectangle in the set or fits completely inside of another rectangle in the set, do nothing.

            // No match was found.

            // If any of the set fit completely inside of this rectangle, discard any that do, and add this rectangle to the set.

            // No match was found.

            // Add this rectangle to the set.
            push_back( r );
            return true;

        }


        /* True if the DC's extent is nothing */
        bool IsEmpty() const {

            if ( ( 0 == x ) && ( 0 == y ) && ( 0 == cx ) && ( 0 == cy ) ) {

                return true;

            }

            for ( size_t u = 0; u < size(); u++ ) {

                const RECT & r = at( u );

                if ( ( 0 == r.left ) && ( 0 == r.top ) && ( 0 == r.right ) && ( 0 == r.bottom ) ) {

                    continue;

                }

                return false;

            }

            return true;

        }


        bool PtIn( POINT & pt ) const {

            if ( ! (
                ( pt.x           >= x      ) && // Within
                ( (unsigned)pt.x <  x + cx ) && // all
                ( pt.y           >= y      ) && // figure's
                ( (unsigned)pt.y <  y + cy )    // sides?
            ) ) {

                return false;

            }

            if ( size() > 0 ) {

                for ( size_t u = 0; u < size(); u++ ) {

                    if ( PtInRect( &( at( u ) ), pt ) ) {

                        return true;

                    }

                }

                return false;

            }

            return true;

        }


        bool remove( const RECT & /* r */ ) {

            // If r is either the same as another rectangle in the set or completely surrounds another rectangle in the set, remove it.
            return true;

        }


};


#endif /* YW_REGION_H */
