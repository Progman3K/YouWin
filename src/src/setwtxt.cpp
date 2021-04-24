

#include "ywin.h"


BOOL SetWindowText( HWND hWnd, LPCTSTR psz ) {

    FORWARD_WM_SETTEXT( hWnd, psz, SendMessage );

    return true;

}
