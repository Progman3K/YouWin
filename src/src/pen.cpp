

#include "ywin.h"


HPEN CreatePenIndirect( const LOGPEN * plgpn ) {

    Pen * pPen = new Pen();

    if ( 0 == pPen ) {

        return 0;

    }

    pPen->set( plgpn );

    return pPen;

}


HPEN CreatePen( int fnPenStyle, int nWidth, COLORREF crColor ) {

    LOGPEN lp;
    POINT pt;

    pt.y = 0; /* The y member in the POINT structure for lopnWidth isn't used */
    pt.x = nWidth;

    lp.lopnStyle = fnPenStyle;
    lp.lopnWidth = pt;
    lp.lopnColor = crColor;

    return CreatePenIndirect( &lp );

}
