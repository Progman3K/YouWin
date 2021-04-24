#ifndef YW_TRACKBAR_H
#define YW_TRACKBAR_H


#include "genericwindow.h"


class Trackbar : public Window {

    public:

        Trackbar( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

//            Animate * pWnd = (Animate *)hWnd;

            return DefWindowProc( hWnd, uiMsg, wParam, lParam );

        }

    private:

//        void     OnPaint( HWND hWnd, PAINTSTRUCT * pPS );

};


class TrackbarClass : public WindowClass {

    public:

        TrackbarClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Trackbar( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Trackbar *>( pThis );

        }

};


#endif /* YW_TRACKBAR_H */
