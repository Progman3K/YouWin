#ifndef YW_H_GENERIC_WINDOW_H
#define YW_H_GENERIC_WINDOW_H


#include <vector>


#include "iwindow.h"
#include "dc.h"
#include "wndclass.h"
#include "UTF16.h"


class ywWindow : public IWindow {

    public:

        DC ClientDC;
        DC NonClientDC;

        ywWindow( class WindowClass * pWindowClass, LPCTSTR pWindowName, HWND hParent, int rel_to_parent_x, int rel_to_parent_y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hInstance, LPVOID pParam ) : IWindow( reinterpret_cast<IWindow *>( hParent ), Style, rel_to_parent_x, rel_to_parent_y, count_x, count_y ), ClientDC( this, &ClientArea, &ClientPixels, DC::StaticToWindow ), NonClientDC( this, &NonClientArea, &NonClientPixels, DC::StaticToWindow ) {

            // ---------------------------- Initialize it.

            hMenu               = MenuOrID;
            dwExStyle           = ExtStyle;
            bDlgProc            = 0;
            pbClosed            = NULL;
            piDlgRetCode        = NULL;
            bDirty              = false;

            fErase              = false;

            bDrawFramePending   = false;
            lUserData           = 0;
            WndProc             = wndproc;
            hInst               = hInstance;

            uiHScrollPos        = 0;
            uiHScrollMax        = 0;
            uiHScrollMin        = 0;
            uiVScrollPos        = 0;
            uiVScrollMax        = 0;
            uiVScrollMin        = 0;

            pClass              = pWindowClass;

            bScrollLock         = false;
            bNoRedraw           = false;

            if ( NULL != pWindowName ) {

                this->Text.assign( pWindowName );

            }

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "%lX '%s' control %d, instance %lX, style %lX, extstyle %lX, x,y(%d,%d) cx,cy(%d,%d) '%s', pParam: %0lX" ), this, pClass->GetClassName(), hMenu, hInst, dwStyle, dwExStyle, x, y, cx, cy, NULL != pWindowName ? pWindowName : TEXT( "" ), pParam );

            CalculateRegions();

        }

        ~ywWindow() {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "%s %lX, ID %lu deleted" ), pClass->GetClassName(), this, (unsigned long)hMenu );

        }

        // Internal.
        static ywWindow * Create( DWORD ExtStyle, LPCTSTR pClassName, LPCTSTR pWindowName, DWORD style, int ix, int iy, unsigned int cx, unsigned int cy, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, LPVOID pParam );

        unsigned            uiHScrollPos;     // Horizontal scroll offset.
        unsigned            uiHScrollMax;     //
        unsigned            uiHScrollMin;     //

        unsigned            uiVScrollPos;     // Vertical scroll offset.
        unsigned            uiVScrollMax;     //
        unsigned            uiVScrollMin;     //

        BOOLEAN *           pbClosed;         // Window is closed and pending deletion.
        bool                bDirty;
        bool                fErase;            /* WM_ERASEBKGND is pending */
        bool                bDrawFramePending;
        int *               piDlgRetCode;      // The value of EndDialog( hWnd, x )
//        HMENU               hMenu;             // Control ID for child-windows
        BOOLEAN             bScrollLock;       // TRUE if this window will NOT scroll when text reaches it's last line.
        BOOLEAN             bNoRedraw;         // Output to this window is NOT to be painted. Used to "Halt" the display.
        LONG_PTR            lUserData;         //
        WNDPROC             WndProc;           //
        DLGPROC             bDlgProc;          //
//        DWORD               dwExStyle;
        HINSTANCE           hInst;
        class WindowClass * pClass;
        TSTRING             Text;

        LRESULT DefWndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

        void CalculateRegions();

        static ywWindow * ToWnd( HWND hWnd, const char * pszFile, unsigned uLine );

//        static Window * At( POINT * );

        RECT rCaption;

        RECT vscrollArea;
        RECT vscrollThumbTop;
        RECT vscrollMiddle;
        RECT vscrollThumbBottom;

        RECT hscrollArea;
        RECT hscrollThumbLeft;
        RECT hscrollMiddle;
        RECT hscrollThumbRight;

        RECT rthumb;

    private:

        void OnDestroy( HWND hWnd );
        void OnEnable( HWND hWnd, BOOL bEnable );
        bool OnEraseBackground( HWND hWnd, HDC hDC );
        void OnMouseClicks( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags );
        void OnNCMouseClicks( HWND hWnd, BOOLEAN bDblClick, int x, int y, UINT uiKeyFlags );
        UINT OnNCHitTest( HWND hWnd, int x, int y );
        void OnNCPaint( HWND hWnd, HRGN hRgn );
        void OnParentNotify( HWND hWnd, UINT uiMsg, HWND hChildWnd, int iChildID );

        void OnSetfocus( HWND hWnd, HWND hOldfocuswnd );

        void OnSetRedraw( HWND hWnd, BOOL bRedraw );

        void OnSetText( HWND hWnd, LPCTSTR lpszText );

        void DrawScrollBar( HDC hDC, bool bHorizontal, SCROLLBARINFO * );

};


using WindowList = std::vector<ywWindow *>;


#endif /* YW_H_GENERIC_WINDOW_H */
