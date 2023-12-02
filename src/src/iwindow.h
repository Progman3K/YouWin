#ifndef YW_I_WINDOW_H
#define YW_I_WINDOW_H


#include <vector>


#include "bitmap.h"


#include "regions.h"


#define SIGNATURE "JCG"


typedef BOOLEAN ( * FPBENUMTEXTWINDOWSPROC)( class IWindow * pWnd, LPARAM lParam );
int iEnumWindows( FPBENUMTEXTWINDOWSPROC fpbEnumTextWindowsProc, BOOLEAN bAscending, class IWindow * pWndStart, LPARAM lParam );


class WindowArea : public protoBitmap<COLORREF> {

    public:

#if 0
        BITMAP_FMT getfmt( void ) const override {

            return BITMAP_FMT_NONE;

        }


        unsigned getbpp( void ) const override { return 24; }

        bool GetPixel( const POINT & /* pt */, COLORREF & /* c */ ) const override { return false; }

        bool SetPixel( const POINT & /* pt */, COLORREF /* c */ ) override { return true; }

        long Width( void ) const override { return 0; }

        long Height( void ) const override { return 0; }

        const void * data( void ) const override { return 0; }

        size_t size( void ) const override { return false; }
#endif
};


void WindowInfo( class IWindow * );


class IWindow {


    BYTE ucSig[sizeof(SIGNATURE)];       // Makes it possible to identify structure.


    public:

        IWindow *   pParentWnd;

        HMENU       hMenu;             // Control ID for child-windows

        std::vector<IWindow *> children;

        unsigned    x;                // position on parent.
        unsigned    y;                // position on parent.
        unsigned    cx;               // Number of character collumns (width) including frame.
        unsigned    cy;               // Number of character lines (height) including frame.

        ywRegion    ClientArea;
        ywRegion    NonClientArea;

        WindowArea  ClientPixels;
        WindowArea  NonClientPixels;

        DWORD       dwStyle;
        DWORD       dwExStyle;

        bool        bPopupDisabled;

        IWindow( IWindow * hParent, DWORD Style, int rel_to_parent_x, int rel_to_parent_y, unsigned int count_x, unsigned int count_y ) {

            // Stamp it with signature.
            ucSig[0] = 'J';
            ucSig[1] = 'C';
            ucSig[2] = 'G';
            ucSig[3] = '\0';

            pParentWnd      = hParent;
            dwStyle         = Style;
            x               = rel_to_parent_x;
            y               = rel_to_parent_y;
            cx              = count_x;
            cy              = count_y;
            bPopupDisabled  = false;

        }


        ~IWindow() {

            // Erase signature.
            ucSig[0] = 0;
            ucSig[1] = 0;
            ucSig[2] = 0;
            ucSig[3] = '\0';

        }


        int SigGood() {

            if ( ( 'J' == ucSig[0] ) && ( 'C' == ucSig[1] ) && ( 'G' == ucSig[2] ) ) {

                return 0;

            }

            return -1;

        }


        bool CanAcceptFocus() {

            if ( ! ( WS_VISIBLE & dwStyle ) ) {

                return false;

            }

            if ( WS_DISABLED & dwStyle ) {

                return false;

            }

            if ( ! ( WS_TABSTOP & dwStyle ) ) {

                return false;

            }

            return true;

        }

        /* For any given window, return its ancestor who is the popup.
        * Example: A combobox child control passed in will return the
        * handle not of its immediate parent (listbox), but of the ancestor
        * who is the popup window hosting any number of child windows, among them the combobox.
        *
        * If the handle passed in is already a popup, then it will return itself.
        */
        static IWindow * GetPopup( IWindow * pWnd ) {

            if ( ( NULL == pWnd ) || ( HWND_DESKTOP == (HWND)pWnd ) ) {

//                DBG_MSG( DBG_ERROR, TEXT( "NO POPUP FOUND" ) );
                return NULL;

            }

            if ( WS_CHILD & pWnd->dwStyle ) {

                return GetPopup( pWnd->pParentWnd );

            }

            WindowInfo( pWnd );

            return pWnd;

        }


        // Absolute X and Y coord of window
        POINT GetParentOffset( void ) {

            POINT   pt;

            pt.x = 0;
            pt.y = 0;

//            if ( NULL == this ) {

//                pt.x = 0;
//                pt.y = 0;

//                return pt;

//            } else {

                pt.x = x;
                pt.y = y;

                if ( WS_CHILD & dwStyle ) {

                    pt.x += pParentWnd->ClientArea.x;
                    pt.y += pParentWnd->ClientArea.y;

                }

//            }

            if ( ( NULL == pParentWnd ) || ( HWND_DESKTOP == pParentWnd ) || ( ! ( WS_CHILD & dwStyle ) ) ) {

                return pt;

            }

            return pt + pParentWnd->GetParentOffset();

        }


        BOOLEAN bPointInWindow( POINT pt2 ) {

            POINT pt = GetParentOffset();

            if (
                ( pt2.x >=  pt.x              ) && // Within
                ( pt2.x < ( pt.x + (LONG)cx ) ) && // all
                ( pt2.y >=  pt.y            )   && // figure's
                ( pt2.y < ( pt.y + (LONG)cy ) )    // sides?
            ) {

                return true;

            }

            return false;

        }

#if 0
        // Returns the window covering this point.
        IWindow * pWndPointObscured( POINT pt ) {

//            if ( NULL == this ) {

//                return NULL;

//            }

            IWindow * pWnd;

            for( pWnd = pPrevSiblingWnd; pWnd; pWnd = pWnd->pPrevSiblingWnd ) {

                if ( ! ( WS_VISIBLE & pWnd->dwStyle ) ) {

                    continue;

                }

                if ( ! pWnd->bPointInWindow( pt ) ) {

                    // The point doesn't fall within its extents.
                    continue;

                }

                // The point does fall within its extents.
                if ( WS_CHILD & pWnd->dwStyle ) {

                    /* Make sure output is clipped to parent's client-area */
                    RECT r;

                    POINT ptParent;

                    ptParent.x = 0;
                    ptParent.y = 0;

                    ClientToScreen( pWnd->pParentWnd, &ptParent );

                    GetClientRect( pWnd->pParentWnd, &r );

                    r.left   = ptParent.x;
                    r.top    = ptParent.y;
                    r.right  = r.left + r.right;
                    r.bottom = r.top  + r.bottom;

                    if ( ! PtInRect( &r, pt ) ) {

                        continue;

                    }

                }

                return pWnd;

            }

            // No visible windows above me obscuring the point.
            return NULL;

        }
#endif

        static IWindow * GetTabstop( IWindow * pWnd, bool bForwards ) {

            IWindow * pTabstopWnd = NULL;

            if ( bForwards ) {

                for ( auto i = pWnd->children.begin(); i != pWnd->children.end(); i++ ) {

                    if ( ! (*i)->CanAcceptFocus() ) {

                        continue;

                    }

                    pTabstopWnd = *i;
                    break;

                }

            } else {

                for ( auto i = pWnd->children.rbegin(); i != pWnd->children.rend(); i++ ) {

                    if ( ! (*i)->CanAcceptFocus() ) {

                        continue;

                    }

                    pTabstopWnd = *i;
                    break;

                }

            }

            return pTabstopWnd;

        }


        static IWindow * GetNextTabstop( IWindow * pWnd, IWindow * pCtlWnd, bool bForward ) {

            /* Walk the list and for all children of hDlg, return the one ( iCtrlID == hMenu ) */
            bool bTabstopFound = false;

            if ( bForward ) {

                for ( auto i = pWnd->children.begin(); i != pWnd->children.end(); i++ ) {

                    if ( pCtlWnd == *i ) {

                        bTabstopFound = true;
                        continue;

                    }

                    if ( bTabstopFound ) {

                        if ( (*i)->CanAcceptFocus() ) {

                            return *i;

                        }

                    }

                }

                /* Couldn't find a tabstop AFTER the control in question, so return the very first tabstop */
                return GetTabstop( pWnd, true );

            } else {

                for ( auto i = pWnd->children.rbegin(); i != pWnd->children.rend(); i++ ) {

                    if ( pCtlWnd == *i ) {

                        bTabstopFound = true;
                        continue;

                    }

                    if ( bTabstopFound ) {

                        if ( (*i)->CanAcceptFocus() ) {

                            return *i;

                        }

                    }

                }

                /* Couldn't find a tabstop BEFORE the control in question, so return the very last tabstop */
                return GetTabstop( pWnd, false );

            }

        }


//        static IWindow * TopmostWindow( void );

};


#endif /* YW_I_WINDOW_H */
