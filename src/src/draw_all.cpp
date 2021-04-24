

#include "ywin.h"


BOOLEAN bPaintAll( IWindow * pWnd, LPARAM lParam ) {

//    RECT * pr = (RECT *)lParam;

    POINT pt = pWnd->GetParentOffset();
    RECT  r;

    r.left   = pt.x;
    r.top    = pt.y;
    r.right  = r.left + pWnd->cx;
    r.bottom = r.top  + pWnd->cy;

    RedrawWindow( (HWND)pWnd, &r, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_ERASENOW | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

//  DrawWindow( lpWnd );
    return true;

}


void RedrawDesktop( RECT * pr ) {

    iEnumWindows( bPaintAll, false, NULL, (LPARAM)pr );

}
