#ifndef YW_BUTTON_H
#define YW_BUTTON_H


#include "genericwindow.h"


#define HANDLE_BM_GETCHECK( hwnd, wParam, lParam, fn )      ( (fn)((hwnd)) )


class Button : public Window {

    public:

        Button( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            iButtonstate = BST_INDETERMINATE;

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        int      iButtonstate;

        void     AutoCheck();

        int      OnGetCheck( HWND );
        void     OnKeydown( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags );
        void     OnKeyup( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags );
        void     OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags );
        void     OnPaint( HWND, PAINTSTRUCT * );

        void     DrawGroupBox( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );
        void     DrawCheckBox( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );
        void     DrawBitmap( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );
        void     DrawIcon( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );
        void     DrawOwnerDraw( HWND hWnd, RECT * pr, PAINTSTRUCT * pPS );

};


class ButtonClass : public WindowClass {

    public:

        ButtonClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           // return new CButton( class WindowClass * pWindowClass, HWND hParent, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, WNDPROC wndproc );
           return new Button( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Button *>( pThis );

        }

};


#endif /* YW_BUTTON_H */
