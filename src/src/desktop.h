#ifndef YW_DESKTOP_H
#define YW_DESKTOP_H


#include "genericwindow.h"


class Desktop : public ywWindow {

    public:

        Desktop( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : ywWindow( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {}

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        void OnDisplayChange( HWND hWnd, UINT uiBitsPerPixel, UINT cxScreen, UINT cyScreen );

};


class DesktopClass : public WindowClass {

    public:

        DesktopClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Desktop( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class ywWindow * pThis ) override {

            delete reinterpret_cast<Desktop *>( pThis );

        }

};


#endif /* YW_DESKTOP_H */
