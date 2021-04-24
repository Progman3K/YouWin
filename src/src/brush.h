#ifndef YW_BRUSH_H
#define YW_BRUSH_H


#include "gdi.h"


class SolidBrush : public GDIObject {

        COLORREF cr;

    public:

        SolidBrush() : GDIObject( solid_brush, true ) { cr = 0; }

        virtual ~SolidBrush() override {}

        SolidBrush( COLORREF c, bool bSystem ) : GDIObject( solid_brush, bSystem ) {

            cr = c;

        }

        COLORREF GetColor( void ) const {

            // DBG_MSG( DBG_GRAPHICAL, TEXT( "Color %s (%08lX) retrieved, instance %08lX" ), Name.c_str(), cr, this );
            return cr;

        }

        void SetColor( COLORREF c ) {

            cr   = c;

        }

};


extern SolidBrush  brDesktop;
extern SolidBrush  br3DFace;
extern SolidBrush  brWindow;

extern SolidBrush  brBlack;


#endif /* YW_BRUSH_H */
