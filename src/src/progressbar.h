#ifndef YW_PROGRESSBAR_H
#define YW_PROGRESSBAR_H


#include "genericwindow.h"


#define HANDLE_PBM_SETPOS( hwnd, wParam, lParam, fn )     ( (fn)((hwnd), (unsigned)(wParam)) )
#define HANDLE_PBM_SETRANGE32( hwnd, wParam, lParam, fn ) ( (fn)((hwnd), (unsigned)(wParam), (DWORD)(lParam)) )
#define HANDLE_PBM_SETSTEP( hwnd, wParam, lParam, fn )    ( (fn)((hwnd), (unsigned)(wParam)) )
#define HANDLE_PBM_STEPIT( hwnd, wParam, lParam, fn )     ( (fn)((hwnd)) )


class Progressbar : public ywWindow {

    public:

        Progressbar( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : ywWindow( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            uLow           = 0;
            dwHigh         = 100;

            uStepIncrement = 10;

            uLastStep      = 0;

            dwPosition     = 0;

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        DWORD    dwPosition;

        unsigned uLow;
        DWORD    dwHigh;

        unsigned uStepIncrement;

        unsigned uLastStep;

        void     OnPaint( HWND hWnd, PAINTSTRUCT * pPS );
        DWORD    OnSetPos( HWND hWnd, unsigned uPos );
        DWORD    OnSetRange32( HWND hWnd, unsigned uLow, DWORD ulHigh );
        unsigned OnSetStep( HWND hWnd, unsigned uStep );
        DWORD    OnStepIt( HWND hWnd );

};


class ProgressbarClass : public WindowClass {

    public:

        ProgressbarClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Progressbar( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class ywWindow * pThis ) override {

            delete reinterpret_cast<Progressbar *>( pThis );

        }

};


#endif /* YW_PROGRESSBAR_H */
