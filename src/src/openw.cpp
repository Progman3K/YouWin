

#include "ywin.h"


static DefWindowClass DefWndClass( TEXT( "" ), DefWindowProc, (HBRUSH)&brWindow, CS_SYSTEM, NULL );


Window * Window::Create( DWORD ExtStyle, const TCHAR * pClassName, LPCTSTR pWindowName, DWORD style, int ix, int iy, unsigned int cx, unsigned int cy, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, LPVOID pParam ) {

    WindowClass * pClass = NULL;

    if ( NULL == pClassName ) {

        DBG_MSG( DBG_ERROR, TEXT( "WARNING: Requested NULL window class" ) );
        pClass = &DefWndClass;

    } else {

        if ( 0 == HIWORD( pClassName ) ) {

            switch( LOWORD( pClassName ) ) {

                case ATOM_BUTTON:

                    pClass = &CButton;
                    break;

                case ATOM_EDITTEXT:

                    pClass = &CEdit;
                    break;

                case ATOM_STATIC:

                    pClass = &CStatic;
                    break;

                case ATOM_LISTBOX:

                    pClass = &CListbox;
                    break;

                case ATOM_SCROLLBAR:

//                    pClass = ;
                    break;

                case ATOM_COMBOBOX:

                    pClass = &CCombobox;
                    break;

                default:

                    break;

            }

        } else {

            pClass = classes.Find( pClassName );

        }

        if ( NULL == pClass ) {

            return NULL;

        }

    }

    // Allocate the new window handle and
    Window * pWnd = pClass->Allocate( hParentWnd, pWindowName, ix, iy, cx, cy, hMenu, style, ExtStyle, pClass->GetWindowProc(), hInst, pParam );

    if ( NULL == pWnd ) {

        return NULL;

    }

    CREATESTRUCT cs;

    cs.x              = ix;
    cs.y              = iy;
    cs.cx             = cx;
    cs.cy             = cy;
    cs.dwExStyle      = ExtStyle;
    cs.style          = style;
    cs.hInstance      = hInst;
    cs.hMenu          = hMenu;
    cs.hwndParent     = hParentWnd;
    cs.lpszClass      = pClassName;
    cs.lpszName       = pWindowName;
    cs.lpCreateParams = pParam;

    if ( ! SendMessage( (HWND)pWnd, WM_NCCREATE, 0, (LPARAM)&cs ) ) {

        pClass->Discard( pWnd );
        return NULL;

    }

    if ( -1 == SendMessage( (HWND)pWnd, WM_CREATE, 0, (LPARAM)&cs ) ) {

        pClass->Discard( pWnd );
        return NULL;

    }

    return pWnd;

}


HWND CreateWindowEx( DWORD dwExStyle, LPCTSTR pClassName, LPCTSTR pWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, LPVOID pParam ) {

    Window * pWnd;
    IWindow * pTopWnd;

    /* Rule out the obvious */
    if ( WS_CHILD & dwStyle ) {

        if ( ( NULL == hParentWnd ) || ( HWND_DESKTOP == hParentWnd ) ) {

            return NULL;

        }

    }

    // Allocate the new window handle and
    if ( ( pWnd = Window::Create( dwExStyle, pClassName, pWindowName, dwStyle, x, y, cx, cy, hParentWnd, hMenu, hInst, pParam ) ) == NULL ) {

        return (HWND)NULL;

    }

    // insert it on TOP of the window list
    if ( ( pTopWnd = IWindow::TopmostWindow() ) == NULL ) {

        if ( NULL == g.pTopWnd ) {

            g.pTopWnd = pWnd;

        } else {

            // First child. Link directly onto desktop.
            if ( g.pTopWnd->pPrevSiblingWnd ) {

                // Internal error. List is corrupt.
                return NULL;

            }

            g.pTopWnd->pPrevSiblingWnd = pWnd;

            // Relink window with others below it.
            pWnd->pNextSiblingWnd = g.pTopWnd;

        }

    } else {

        // Not the first child.
        pTopWnd->pPrevSiblingWnd = pWnd;
        // Relink window with others below it.
        pWnd->pNextSiblingWnd = pTopWnd;

    }

    if ( NULL != pWindowName ) {

        pWnd->Text.assign( pWindowName );
        //. FORWARD_WM_SETTEXT( (HWND)pWnd, pWindowName, SendMessage );

    }

    return (HWND)pWnd;

}


HWND CreateWindow( const TCHAR * pClassName, const TCHAR * pWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, void * pParam ) {

    return CreateWindowEx( 0, pClassName, pWindowName, dwStyle, x, y, cx, cy, hParentWnd, hMenu, hInst, pParam );

}
