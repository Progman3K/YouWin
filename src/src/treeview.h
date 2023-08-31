#ifndef YW_TREEVIEW_H
#define YW_TREEVIEW_H


#include "genericwindow.h"


class Treeview : public ywWindow {

    public:

        Treeview( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : ywWindow( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

//            Animate * pWnd = (Animate *)hWnd;

            return DefWindowProc( hWnd, uiMsg, wParam, lParam );

        }

    private:

//        void     OnPaint( HWND hWnd, PAINTSTRUCT * pPS );

};


class TreeviewClass : public WindowClass {

    public:

        TreeviewClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hUserInst, LPVOID pParam ) override {

           return new Treeview( this, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hUserInst, pParam );

        }

        void Discard( class ywWindow * pThis ) override {

            delete reinterpret_cast<Treeview *>( pThis );

        }

};


#endif /* YW_TREEVIEW_H */
