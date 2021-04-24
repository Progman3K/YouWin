

#include "ywin.h"


void Caret::Invert( HWND hWnd ) {

    HDC hDC = GetDC( hWnd );

    TEXTMETRIC tm;
    
    GetTextMetrics( hDC, &tm );

    BitBlt( hDC, pt.x, pt.y, tm.tmAveCharWidth, tm.tmHeight, NULL, 0, 0, DSTINVERT );

    ReleaseDC( hWnd, hDC );

    bVisible = ! bVisible;

#ifdef YOU_WIN_TXT    
    /* Hack to temporarily SEE the focus change */
    POINT ptCaret = (reinterpret_cast<Window *>( hWnd ))->GetParentOffset();

    ptCaret.x += pt.x;
    ptCaret.y += pt.y;

    gotoxy( ptCaret.x, ptCaret.y );
#endif    
    
}
