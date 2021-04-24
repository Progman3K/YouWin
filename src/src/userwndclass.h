#ifndef YW_USER_WNDCLASS_H
#define YW_USER_WNDCLASS_H


#include "genericwindow.h"


class UserWindow : public Window {

    public:

        UserWindow( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam, int cbWndExtra ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {}

        std::vector<BYTE>   WndExtra;

};


class UserWindowClass : public WindowClass {

    public:

        UserWindowClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco, int iWndExtra ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {

            cbWndExtra = iWndExtra;

        }

        virtual ~UserWindowClass() {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hUserInst, LPVOID pParam ) override {

           UserWindow * pWnd = new UserWindow( this, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hUserInst, pParam, cbWndExtra );

           if ( NULL == pWnd ) {

               return NULL;

           }

           if ( cbWndExtra ) {

                pWnd->WndExtra.resize( cbWndExtra, 0 );

           }

           return pWnd;

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<UserWindow *>( pThis );

        }

        std::vector<BYTE>   ClsExtra;

    private:

        int                 cbWndExtra;

};


#endif	/* YW_USER_WNDCLASS_H */
