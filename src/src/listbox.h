#ifndef YW_LISTBOX_H
#define YW_LISTBOX_H


#include <vector>
#include "genericwindow.h"


#define HANDLE_LB_ADDSTRING( hwnd, wParam, lParam, fn )     ( (fn)((hwnd), (LPCTSTR)(lParam)) )
#define HANDLE_LB_DELETESTRING( hwnd, wParam, lParam, fn )  ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_LB_GETCOUNT( hwnd, wParam, lParam, fn )      ( (fn)((hwnd)) )
#define HANDLE_LB_GETCURSEL( hwnd, wParam, lParam, fn )     ( (fn)((hwnd)) )
#define HANDLE_LB_GETITEMDATA( hwnd, wParam, lParam, fn )   ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_LB_GETITEMHEIGHT( hwnd, wParam, lParam, fn ) ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_LB_GETTEXT( hwnd, wParam, lParam, fn )       ( (fn)((hwnd), (int)(wParam), (LPTSTR)(lParam)) )
#define HANDLE_LB_GETTEXTLEN( hwnd, wParam, lParam, fn )    ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_LB_INSERTSTRING( hwnd, wParam, lParam, fn )  ( (fn)((hwnd), (int)(wParam), (LPCTSTR)(lParam)) )
#define HANDLE_LB_RESETCONTENT( hwnd, wParam, lParam, fn )  ( (fn)((hwnd)) )
#define HANDLE_LB_SETCURSEL( hwnd, wParam, lParam, fn )     ( (fn)((hwnd), (int)(wParam)) )
#define HANDLE_LB_SETITEMDATA( hwnd, wParam, lParam, fn )   ( (fn)((hwnd), (int)(wParam), (ULONG_PTR)(lParam)) )


class Listbox : public Window {

    public:

        Listbox( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int userx, int usery, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hUserInst, LPVOID pParam ) : Window( pWindowClass, pWindowName, hParent, userx, usery, count_x, count_y, MenuOrID, Style, ExtStyle, wndproc, hUserInst, pParam ) {

            iCaretIndex  = LB_ERR;
            iOffsetIndex = 0;

        }

        static LRESULT WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    private:

        class ListboxItem {

            public:

                ListboxItem() {

                    dwItemData  = 0;
                    IsSelected  = false;

                    LONG lBaseUnits = GetDialogBaseUnits();

                    int iYBaseunit = HIWORD( lBaseUnits );

                    uItemHeight = (unsigned)iYBaseunit;

                }

                TSTRING   text;
                ULONG_PTR dwItemData;
                bool      IsSelected; 
                unsigned  uItemHeight;

        };

        typedef std::vector<ListboxItem *> ItemList;

        ItemList    items;

        int         iOffsetIndex;

        int         iCaretIndex;    /* Who has the focus rectangle */

        int         InsertIntoSortedList( int iBase, int iSize, ListboxItem * pItem );

        int         OnAddStringOrItemData( HWND hWnd, LPCTSTR psz_or_data );
        int         OnDeletestringOrItemData( HWND hWnd, int iIndex );
        void        OnDestroy( HWND hWnd );
        void        OnChar( HWND hWnd, TCHAR c, int cRepeat );
        int         OnCompareItem( HWND hWnd, const COMPAREITEMSTRUCT * pCI );
        bool        OnEraseBackground( HWND hWnd, HDC hDC );
        int         OnGetCount( HWND hWnd );
        int         OnGetCurSel( HWND hWnd );
        ULONG_PTR   OnGetItemData( HWND hWnd, int iIndex );
        unsigned    OnGetItemHeight( HWND hWnd, int iIndex );
        int         OnGetText( HWND hWnd, int iIndex, LPTSTR psz );
        int         OnGetTextLen( HWND hWnd, int iIndex );
        int         OnInsertStringOrItemData( HWND hWnd, int iIndex, LPCTSTR psz_or_data );
        void        OnKeydown( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags );
        void        OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags );
        bool        OnPaint( HWND hWnd );
        int         OnResetContent( HWND hWnd );
        int         OnSetCurSel( HWND hWnd, int iIndex );
        ULONG_PTR   OnSetItemData( HWND hWnd, int iIndex, ULONG_PTR dwData );

        int         SetSelectionAndNotify( HWND hWnd, int iIndex );

};


class ListboxClass : public WindowClass {

    public:

        ListboxClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) : WindowClass( pszName, Wndproc, /* default_colors, */ hBackBrush, styles, hIco ) {}

        class Window * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC userwndproc, HINSTANCE hInst, LPVOID pParam ) override {

           return new Listbox( this, pWindowName, hParent, x, y, count_x, count_y, MenuOrID, Style, ExtStyle, userwndproc, hInst, pParam );

        }

        void Discard( class Window * pThis ) override {

            delete reinterpret_cast<Listbox *>( pThis );

        }

};


#endif /* YW_LISTBOX_H */
