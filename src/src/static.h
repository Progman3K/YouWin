#ifndef YW_STATIC_H
#define YW_STATIC_H


#include "genericwindow.h"

#define HANDLE_STM_SETICON(hwnd,wParam,lParam,fn) ((fn)((hwnd),(unsigned)(wParam),(HICON)(lParam)))

class Static : public ywWindow {

    public:

        Static( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hInst, LPVOID pParam );

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        HICON hIcon;

        void OnNCPaint( HWND hWnd, HRGN hRgn );
        void OnPaint( HWND hWnd, PAINTSTRUCT * pPS );

        HICON OnSetIcon( HWND hWnd, unsigned uType, HICON hIcon );

        /* Utility */
        void DrawIcon( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );
        void DrawFrame( HDC hDC, RECT & r );

};


class StaticClass : public WindowClass {

    public:

        StaticClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Static( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class ywWindow * pThis ) override {

            delete reinterpret_cast<Static *>( pThis );

        }

};


#endif /* YW_STATIC_H */
