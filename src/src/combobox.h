#ifndef YW_COMBOBOX_H
#define YW_COMBOBOX_H


#include <vector>
#include "genericwindow.h"


#define HANDLE_CB_ADDSTRING( hwnd, wParam, lParam, fn )     ( (fn)((hwnd), (LPCTSTR)(lParam)) )
#define HANDLE_CB_DELETESTRING( hwnd, wParam, lParam, fn )  ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_CB_GETCOUNT( hwnd, wParam, lParam, fn )      ( (fn)((hwnd)) )
#define HANDLE_CB_GETCURSEL( hwnd, wParam, lParam, fn )     ( (fn)((hwnd)) )
#define HANDLE_CB_GETITEMDATA( hwnd, wParam, lParam, fn )   ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_CB_GETITEMHEIGHT( hwnd, wParam, lParam, fn ) ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_CB_INSERTSTRING( hwnd, wParam, lParam, fn )  ( (fn)((hwnd), (LPCTSTR)(lParam)) )
#define HANDLE_CB_RESETCONTENT( hwnd, wParam, lParam, fn )  ( (fn)((hwnd)) )
#define HANDLE_CB_SETCURSEL( hwnd, wParam, lParam, fn )     ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_CB_SETITEMDATA( hwnd, wParam, lParam, fn )   ( (fn)((hwnd), (int)(wParam), (ULONG_PTR)(lParam)) )


class Combobox : public Window {

    public:

        Combobox( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            iCaretIndex = CB_ERR;

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        class ComboboxItem {

            public:

                ComboboxItem() {

                    dwItemData  = 0;
                    IsSelected  = false;

                    LONG lBaseUnits = GetDialogBaseUnits();

                    int iYBaseunit = HIWORD( lBaseUnits );

                    uItemHeight = iYBaseunit;

                }

                TSTRING   text;
                ULONG_PTR dwItemData;
                bool      IsSelected; 
                unsigned  uItemHeight;

        };

        typedef std::vector<ComboboxItem *> ItemList;

        ItemList    items; /* This can be either a list of const string pointers, or a list of writeable combobox items depending on the CBS_HASSTRINGS bit */

        int         iCaretIndex;    /* Who has the focus rectangle */

        int         OnAddStringOrItemData( HWND hWnd, LPCTSTR psz_or_data );
        int         OnDeletestringOrItemData( HWND hWnd, int iIndex );
        void        OnDestroy( HWND hWnd );
        bool        OnEraseBackground( HWND hWnd, HDC hDC );
        int         OnGetCount( HWND hWnd );
        int         OnGetCurSel( HWND hWnd );
        LRESULT     OnGetItemData( HWND hWnd, int iIndex );
        unsigned    OnGetItemHeight( HWND hWnd, int iIndex );
        int         OnInsertStringOrItemData( HWND hWnd, int iIndex, LPCTSTR psz_or_data );
        void        OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags );
        bool        OnPaint( HWND hWnd );
        int         OnSetCurSel( HWND hWnd, int iIndex );
        LRESULT     OnSetItemData( HWND hWnd, int iIndex, ULONG_PTR dwData );

        int         OnResetContent( HWND hWnd );

};


class ComboboxClass : public WindowClass {

    public:

        ComboboxClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Combobox( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Combobox *>( pThis );

        }

};


#endif /* YW_COMBOBOX_H */
