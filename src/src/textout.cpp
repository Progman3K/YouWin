

#include "ywin.h"


BOOL TextOut( HDC hDC, int x, int y, LPCTSTR lpString, int nCount ) {

    return ExtTextOut( hDC, x, y, 0, NULL, lpString, nCount, NULL );

}
