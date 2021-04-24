#ifndef YW_DIALOG_H
#define YW_DIALOG_H


#include "genericwindow.h"


class Dialog : public Window {

    public:

        Dialog( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            dwUser      = 0;
            dwMsgResult = 0;
            wPoint      = (WORD)-1;

        }

        LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

        DWORD dwUser;
        DWORD dwMsgResult;

        WORD wPoint;

    private:

        void OnChar( HWND hWnd, UINT ch, int cRepeat );
        void OnKeydown( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags );

};


class DialogClass : public WindowClass {

    public:

        DialogClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Dialog( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Dialog *>( pThis );

        }

};


#endif /* YW_DIALOG_H */
