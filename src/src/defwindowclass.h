#ifndef YW_DEFWINDOWCLASS_H
#define YW_DEFWINDOWCLASS_H


#include "genericwindow.h"


class DefWindowClass : public WindowClass {

    public:

        DefWindowClass( const TCHAR * pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Styles, DWORD ExtStyles, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Window( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Styles, ExtStyles, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Window *>( pThis );

        }

};


#endif /* YW_DEFWINDOWCLASS_H */
