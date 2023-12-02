#ifndef YW_EDIT_H
#define YW_EDIT_H


#include "genericwindow.h"
#include "caret.h"


#define HANDLE_EM_GETHANDLE( hwnd, wParam, lParam, fn )  ((fn)((hwnd)) )
#define HANDLE_EM_REPLACESEL( hwnd, wParam, lParam, fn ) ((fn)((hwnd), (int)(wParam), (LPCTSTR)(lParam)) )
#define HANDLE_EM_SETREADONLY(hwnd,wParam,lParam,fn)     ((fn)((hwnd), (BOOL)(wParam)), 0 )
#define HANDLE_EM_SETSEL( hwnd, wParam, lParam, fn )     ((fn)((hwnd), (int)(wParam), (int)(lParam)) )


class Edit : public ywWindow {

    Caret caret;  // All data concerning the cursor, insertion point.

    using Constants = enum {

        IDT_CARET = 1

    };

    void   OnChar( HWND, TCHAR c, int cRepeat );
    void   OnClear( HWND );
    HANDLE OnGetHandle( HWND );
    void   OnKeydown( HWND, UINT vk, BOOL fDown, int cRepeat, UINT flags );
    void   OnKillfocus( HWND, HWND hOldfocuswnd );
    void   OnPaint( HWND );
    void   OnReplaceSel( HWND, BOOL bCanUndo, LPCTSTR lpszText );
    void   OnSetfocus( HWND, HWND hOldfocuswnd );
    void   OnSetReadonly( HWND, BOOL );
    void   OnSetSel( HWND, int iSelStart, int iSelEnd );
    void   OnSetText( HWND hWnd, LPCTSTR lpszText );
    void   OnTimer( HWND, UINT );

    void   DrawFromBeginningOfWindowToCursor( HDC );
    void   DrawCursorToEOB( unsigned uFormat );

    void   scrolllineup( int line, int height, int width );
    void   scrolllinedown( int line, int height, int width );

    /** Add character as it is typed */
    bool   AddChar( HWND hWnd, TCHAR c ); // Returns the new caret x position.

    void   CalculateScrollPositions( HWND hWnd );

    unsigned uInsertPos;

    public:

        Edit( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : ywWindow( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            uInsertPos = 0;

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

};


template <class WC> class n : public WindowClass {


};


class EditClass : public WindowClass {

    public:

        EditClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Edit( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class ywWindow * pThis ) override {

            delete reinterpret_cast<Edit *>( pThis );

        }

};


#endif /* YW_EDIT_H */
