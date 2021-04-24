

#include "ywin.h"


HPEN CreatePenIndirect( const LOGPEN * plgpn ) {

    Pen * pPen = new Pen();

    return pPen;

}


HPEN CreatePen( int fnPenStyle, int nWidth, COLORREF crColor ) {

    LOGPEN lp;

    return CreatePenIndirect( &lp );

}
