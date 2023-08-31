

#include "ywin.h"


int Combobox::OnAddStringOrItemData( HWND hWnd, LPCTSTR psz_or_data ) {

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        ComboboxItem * pItem = new ComboboxItem();

        if ( NULL == pItem ) {

            return CB_ERRSPACE;

        }

        pItem->text.assign( psz_or_data );

        items.push_back( pItem );

        // Temporary kludge so we can see the effect
        SetWindowText( hWnd, psz_or_data );

    } else {

        items.push_back( (ComboboxItem *)psz_or_data );

    }

    RedrawWindow( hWnd, NULL, NULL,  RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return items.size() - 1;

}


int Combobox::OnGetCount( HWND hWnd ) {

    return items.size();

}


int Combobox::OnSetCurSel( HWND hWnd, int iIndex ) {

    if ( ! ( ( -1 == iIndex ) || ( ( 0 <= iIndex ) && ( (size_t)iIndex < items.size() ) ) ) ) {

        return CB_ERR;

    }

    iCaretIndex = iIndex;

    for ( unsigned uItem = 0; uItem < items.size(); uItem++ ) {

        // Unselect all but iIndex
        items.at( uItem )->IsSelected = ( (unsigned)iCaretIndex == uItem );

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return iIndex;

}


int Combobox::OnGetCurSel( HWND hWnd ) {

    return iCaretIndex;

}


unsigned Combobox::OnGetItemHeight( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return (unsigned)CB_ERR;

    }

    return items.at( iIndex )->uItemHeight;

}


LRESULT Combobox::OnGetItemData( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return CB_ERR;

    }

    ComboboxItem * pItem = items.at( iIndex );

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        return (LRESULT)pItem->dwItemData;

    } else {

        return (LRESULT)pItem;

    }

}


int Combobox::OnInsertStringOrItemData( HWND hWnd, int iIndex, LPCTSTR psz_or_data ) {

    if ( -1 == iIndex ) {

        return OnAddStringOrItemData( hWnd, psz_or_data );

    }

    if ( 0 > iIndex ) {

        return CB_ERR;

    }

    if ( ! ( items.size() > (size_t)iIndex ) ) {

        return CB_ERR;

    }

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        ComboboxItem * pItem = new ComboboxItem();

        if ( NULL == pItem ) {

            return CB_ERRSPACE;

        }

        pItem->text.assign( psz_or_data );

        items.insert( items.begin() + iIndex, pItem );

        // Temporary kludge so we can see the effect
        SetWindowText( hWnd, psz_or_data );

    } else {

        items.insert( items.begin() + iIndex, (ComboboxItem *)psz_or_data );

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return iIndex;

}


LRESULT Combobox::OnSetItemData( HWND hWnd, int iIndex, ULONG_PTR dwData ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return CB_ERR;

    }

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        ComboboxItem * pItem = items.at( iIndex );

        return (LRESULT)( pItem->dwItemData = dwData );

    } else {

        items[iIndex] = reinterpret_cast<ComboboxItem *>( dwData );
        return 0;

    }

}


void Combobox::OnDestroy( HWND hWnd ) {

    if ( ! ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) ) {

        return;

    }

    for ( ; items.size(); ) {

        ComboboxItem * pItem = items.at( 0 );

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Delete combobox item %lX" ), pItem );

        delete pItem;

        items.erase( items.begin() );

    }

}


int Combobox::OnDeletestringOrItemData( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return CB_ERR;

    }

    ComboboxItem * pItem = items.at( iIndex );

    DELETEITEMSTRUCT di;

    di.CtlID    = (unsigned long)hMenu;
    di.CtlType  = ODT_COMBOBOX;
    di.hwndItem = hWnd;
    di.itemID   = iIndex;

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        if ( 0 != pItem->dwItemData ) {

            di.itemData = pItem->dwItemData;

        }

        delete pItem;

    } else {

        di.itemData = (ULONG_PTR)pItem;

    }

    FORWARD_WM_DELETEITEM( pParentWnd, &di, SendMessage );

    items.erase( items.begin() + iIndex );

    return items.size();

}


int Combobox::OnResetContent( HWND hWnd ) {

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        for ( ; items.size(); ) {

            ComboboxItem * pItem = items.at( 0 );

            if ( 0 != pItem->dwItemData ) {

                DELETEITEMSTRUCT    di;

                di.CtlID    = (unsigned long)hMenu;
                di.CtlType  = ODT_COMBOBOX;
                di.hwndItem = hWnd;
                di.itemData = pItem->dwItemData;
                di.itemID   = 0;

                FORWARD_WM_DELETEITEM( pParentWnd, &di, SendMessage );

            }

            delete pItem;

            items.erase( items.begin() );

        }

    } else {

        for ( ; items.size(); ) {

            ComboboxItem * pItem = items.at( 0 );

            if ( 0 != pItem ) {

                DELETEITEMSTRUCT    di;

                di.CtlID    = (unsigned long)hMenu;
                di.CtlType  = ODT_COMBOBOX;
                di.hwndItem = hWnd;
                di.itemData = (ULONG_PTR)pItem;
                di.itemID   = 0;

                FORWARD_WM_DELETEITEM( pParentWnd, &di, SendMessage );

            }

            items.erase( items.begin() );

        }

    }

    return 0;

}


bool Combobox::OnPaint( HWND hWnd ) {

    PAINTSTRUCT ps;

    ZeroMemory( &ps, sizeof( ps ) );

    BeginPaint( hWnd, &ps );

    RECT r;
    GetClientRect( hWnd, &r );

    if ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) {

        COLORREF oldbkcr = GetBkColor( ps.hdc );
        COLORREF oldfgcr = GetTextColor( ps.hdc );

        for ( unsigned uItem = 0, uY = 0; ( uItem < items.size() ) && ( uY < (unsigned)r.bottom ); uItem++ ) {

            if ( items.at( uItem )->IsSelected ) {

                SetBkColor( ps.hdc, SysColorHighLight.GetColor() );
                SetTextColor( ps.hdc, SysColorHighLightText.GetColor() );

            } else {

                SetBkColor( ps.hdc, SysColorWindow.GetColor() );
                SetTextColor( ps.hdc, SysColorWindowText.GetColor() );

            }

            TextOut( ps.hdc, 0, uY, items.at( uItem )->text.c_str(), items.at( uItem )->text.size() );

            uY += items.at( uItem )->uItemHeight;

        }

        SetBkColor( ps.hdc, oldbkcr );
        SetTextColor( ps.hdc, oldfgcr );

    } else {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Owner-drawn combobox items not painted" ) );

    }

    EndPaint( hWnd, &ps );

    return true;

}


bool Combobox::OnEraseBackground( HWND hWnd, HDC hDC ) {

    if ( ! ( ( CBS_SIMPLE & dwStyle ) || ( CBS_HASSTRINGS & dwStyle ) ) ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Owner-drawn combobox background not erased" ) );
        return true;

    }

    RECT r;
    GetClientRect( hWnd, &r );

    RECT rItem;

    SolidBrush brBackground( SysColorWindow.GetColor(), true );
    SolidBrush brSelection( SysColorHighLight.GetColor(), true );

    LONG Y = 0;

    ItemList::size_type Item = 0;

    for ( ; Y < r.bottom; Item++ ) {

        if ( Item < items.size() ) {

            ComboboxItem * pItem = items.at( Item );

            rItem.left   = 0;
            rItem.top    = Y;

            rItem.right  = r.right;

            Y += pItem->uItemHeight;

            rItem.bottom = Y;

            FillRect( hDC, &rItem, (HBRUSH)( pItem->IsSelected ? &brSelection : &brBackground ) );

        } else {

            rItem.left   = 0;
            rItem.top    = Y;

            rItem.right  = r.right;

            rItem.bottom = ( r.bottom - Y );

            Y = r.bottom;

            FillRect( hDC, &rItem, (HBRUSH)&brBackground );

        }

    }

    return true;

}


void Combobox::OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int userx, int usery, UINT uiKeyFlags ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Combobox left-click (%d,%d)" ), userx, usery );

    RECT  rItem;
    POINT pt;

    pt.x = userx;
    pt.y = usery;

    RECT r;
    GetClientRect( hWnd, &r );

    for ( unsigned uItem = 0, uY = 0; ( uItem < items.size() ) && ( uY < (unsigned)r.bottom ); uItem++ ) {

        rItem.left  = 0;
        rItem.right = r.right;
        rItem.top   = uY;

        uY += items.at( uItem )->uItemHeight;

        rItem.bottom = uY;

        if ( PtInRect( &rItem, pt ) ) {

            int iRet = ComboBox_SetCurSel( hWnd, (int)uItem );

            if ( ( CB_ERR == iRet ) || ( -1 == iRet ) ) {

                DBG_MSG( DBG_ERROR, TEXT( "ERROR SETTING SELECTION IN COMBOBOX TO ITEM %u" ), uItem );

            }

        }

    }

}


LRESULT Combobox::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Combobox * pWnd = reinterpret_cast<Combobox *>( hWnd );

    switch( uiMsg ) {

        case CB_ADDSTRING:

            return HANDLE_CB_ADDSTRING( hWnd, wParam, lParam, pWnd->OnAddStringOrItemData );

        case CB_DELETESTRING:

            return HANDLE_CB_DELETESTRING( hWnd, wParam, lParam, pWnd->OnDeletestringOrItemData );

        case CB_GETCOUNT:

            return HANDLE_CB_GETCOUNT( hWnd, wParam, lParam, pWnd->OnGetCount );

        case CB_GETCURSEL:

            return HANDLE_CB_GETCURSEL( hWnd, wParam, lParam, pWnd->OnGetCurSel );

        case CB_GETITEMDATA:

            return HANDLE_CB_GETITEMDATA( hWnd, wParam, lParam, pWnd->OnGetItemData );

        case CB_GETITEMHEIGHT:

            return HANDLE_CB_GETITEMHEIGHT( hWnd, wParam, lParam, pWnd->OnGetItemHeight );

        case CB_RESETCONTENT:

            return HANDLE_CB_RESETCONTENT( hWnd, wParam, lParam, pWnd->OnResetContent );

        case CB_SETCURSEL:

            return HANDLE_CB_SETCURSEL( hWnd, wParam, lParam, pWnd->OnSetCurSel );

        case CB_SETITEMDATA:

            return HANDLE_CB_SETITEMDATA( hWnd, wParam, lParam, pWnd->OnSetItemData );

        case WM_DESTROY:

            HANDLE_WM_DESTROY( hWnd, wParam, lParam, pWnd->OnDestroy );
            break;

        case WM_ERASEBKGND:

            return HANDLE_WM_ERASEBKGND( hWnd, wParam, lParam, pWnd->OnEraseBackground );

        case WM_LBUTTONDOWN:

            HANDLE_WM_LBUTTONDOWN( hWnd, wParam, lParam, pWnd->OnLButtonDown );
            break;

        case WM_PAINT:

            return pWnd->OnPaint( hWnd );

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}
