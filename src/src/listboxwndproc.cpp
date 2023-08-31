

#include "ywin.h"


int Listbox::OnCompareItem( HWND hWnd, const COMPAREITEMSTRUCT * pCI ) {

    ListboxItem * pItem1 = reinterpret_cast<ListboxItem *>( pCI->itemData1 );
    ListboxItem * pItem2 = reinterpret_cast<ListboxItem *>( pCI->itemData2 );

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Compare '%s' to '%s'" ), pItem1->text.c_str(), pItem2->text.c_str() );

    return _tcscmp( pItem1->text.c_str(), pItem2->text.c_str() );

}


int Listbox::InsertIntoSortedList( int iBase, int iSize, ListboxItem * pItem ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "InsertIntoSortedList( base %d, size %d, item '%s' )" ), iBase, iSize, pItem->text.c_str() );

    if ( 0 == iSize ) {

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Insert item '%s' in empty list at index %d" ), pItem->text.c_str(), iBase );
        items.insert( items.begin() + iBase, pItem );
        return iBase;

    }

    COMPAREITEMSTRUCT ci;
    ZeroMemory( &ci, sizeof( ci ) );

    ci.hwndItem = this;
    ci.CtlID    = (unsigned long)hMenu;

    int iRet;

    if ( 1 == iSize ) {

        ci.itemID1   = -1;
        ci.itemData1 = (ULONG_PTR)pItem;

        ci.itemID2   = iBase;
        ci.itemData2 = (ULONG_PTR)items.at( iBase );

        iRet = FORWARD_WM_COMPAREITEM( this, &ci, SendMessage );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "First item is %s the second item" ), 0 > iRet ? "smaller than" : 0 == iRet ? "equal to" : "bigger than" );

        if ( ( 0 > iRet ) || ( 0 == iRet ) ) {

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Inserting item at index %d" ), iBase );
            items.insert( items.begin() + iBase, pItem );
            return iBase;

        }

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Inserting item at index %d" ), iBase + 1 );
        items.insert( items.begin() + iBase + 1, pItem );
        return iBase + 1;

    }

    /* Split array into halves */

    ci.itemID1   = -1;
    ci.itemData1 = (ULONG_PTR)pItem;

    ci.itemID2   = ( iBase + iSize ) / 2;
    ci.itemData2 = (ULONG_PTR)items.at( iBase + ( iSize / 2 ) );

    iRet = FORWARD_WM_COMPAREITEM( this, &ci, SendMessage );

    if ( 0 < iRet ) {

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Item belongs in upper half" ) );
        return InsertIntoSortedList( iBase + ( iSize / 2 ), iSize - ( iSize / 2 ), pItem );

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Item belongs in lower half" ) );
    return InsertIntoSortedList( iBase, iSize - ( iSize / 2 ), pItem );

}


int Listbox::OnAddStringOrItemData( HWND hWnd, LPCTSTR psz_or_data ) {

    int i;

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        ListboxItem * pItem = new ListboxItem();

        if ( NULL == pItem ) {

            return LB_ERRSPACE;

        }

        pItem->text.assign( psz_or_data );

        if ( LBS_SORT & dwStyle ) {

            i = InsertIntoSortedList( 0, items.size(), pItem );

        } else {

            items.push_back( pItem );
            i = items.size() - 1;

        }

        // Temporary kludge so we can see the effect
        SetWindowText( hWnd, psz_or_data );

    } else {

        items.push_back( (ListboxItem *)psz_or_data );
        i = items.size() - 1;

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return i;

}


int Listbox::OnGetCount( HWND hWnd ) {

    return items.size();

}


int Listbox::OnSetCurSel( HWND hWnd, int iIndex ) {

    if ( ! ( ( -1 == iIndex ) || ( ( 0 <= iIndex ) && ( (size_t)iIndex < items.size() ) ) ) ) {

        return LB_ERR;

    }

    iCaretIndex = iIndex;

    ListboxItem * pSelectedItem = items.at( iIndex );

    if ( ( pSelectedItem->uItemHeight >= cy ) || ( iIndex < iOffsetIndex ) ) {

        iOffsetIndex = iIndex;

    }

    unsigned uCumulativeHeight = 0;

    for ( int iItem = 0; (unsigned)iItem < items.size(); iItem++ ) {

        ListboxItem * pItem = items.at( iItem );

        // Unselect all but iIndex
        pItem->IsSelected = ( iCaretIndex == iItem );

        if ( iItem >= iOffsetIndex ) {

            uCumulativeHeight += pItem->uItemHeight;

            if ( ( iItem <= iIndex ) && ( iIndex >= iOffsetIndex ) ) {

                if ( uCumulativeHeight >= cy ) {

                    iOffsetIndex++;

                }

            }

        }

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return iIndex;

}


int Listbox::OnGetCurSel( HWND hWnd ) {

    return iCaretIndex;

}


unsigned Listbox::OnGetItemHeight( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return (unsigned)LB_ERR;

    }

    return items.at( iIndex )->uItemHeight;

}


int Listbox::OnGetText( HWND hWnd, int iIndex, LPTSTR psz ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return LB_ERR;

    }

    ListboxItem * pItem = items.at( iIndex );

    _tcsncpy( psz, pItem->text.c_str(), pItem->text.length() );

    return pItem->text.length();

}


int Listbox::OnGetTextLen( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return LB_ERR;

    }

    ListboxItem * pItem = items.at( iIndex );

    return pItem->text.length();

}


ULONG_PTR Listbox::OnGetItemData( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return (ULONG_PTR)LB_ERR;

    }

    ListboxItem * pItem = items.at( iIndex );

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        return pItem->dwItemData;

    } else {

        return (ULONG_PTR)pItem;

    }

}


int Listbox::OnInsertStringOrItemData( HWND hWnd, int iIndex, LPCTSTR psz_or_data ) {

    if ( -1 == iIndex ) {

        return OnAddStringOrItemData( hWnd, psz_or_data );

    }

    if ( 0 > iIndex ) {

        return LB_ERR;

    }

    if ( ! ( items.size() > (size_t)iIndex ) ) {

        return LB_ERR;

    }

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        ListboxItem * pItem = new ListboxItem();

        if ( NULL == pItem ) {

            return LB_ERRSPACE;

        }

        pItem->text.assign( psz_or_data );

        items.insert( items.begin() + iIndex, pItem );

        // Temporary kludge so we can see the effect
        SetWindowText( hWnd, psz_or_data );

    } else {

        items.insert( items.begin() + iIndex, (ListboxItem *)psz_or_data );

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return iIndex;

}


ULONG_PTR Listbox::OnSetItemData( HWND hWnd, int iIndex, ULONG_PTR dwData ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return (ULONG_PTR)LB_ERR;

    }

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        ListboxItem * pItem = items.at( iIndex );

        return ( pItem->dwItemData = dwData );

    } else {

        items[iIndex] = reinterpret_cast<ListboxItem *>( dwData );
        return 0;

    }

}


void Listbox::OnDestroy( HWND hWnd ) {

    if ( ! ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) ) {

        return;

    }

    for ( ; items.size(); ) {

        ListboxItem * pItem = items.at( 0 );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Delete listbox item %lX" ), pItem );

        delete pItem;

        items.erase( items.begin() );

    }

}


int Listbox::OnDeletestringOrItemData( HWND hWnd, int iIndex ) {

    if ( ( 0 > iIndex ) || ( items.size() <= (size_t)iIndex ) ) {

        return LB_ERR;

    }

    ListboxItem * pItem = items.at( iIndex );

    DELETEITEMSTRUCT di;

    di.CtlID    = (unsigned long)hMenu;
    di.CtlType  = ODT_LISTBOX;
    di.hwndItem = hWnd;
    di.itemID   = iIndex;

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        if ( 0 != pItem->dwItemData ) {

            di.itemData = pItem->dwItemData;

        }

        delete pItem;

    } else {

        di.itemData = (ULONG_PTR)pItem;

    }

    FORWARD_WM_DELETEITEM( pParentWnd, &di, SendMessage );

    items.erase( items.begin() + iIndex );

    if ( iCaretIndex == iIndex ) {

        iCaretIndex = LB_ERR;

    } else if ( ( iIndex < iCaretIndex ) && ( LB_ERR < iCaretIndex ) ) {

        iCaretIndex--;

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

    return items.size();

}


int Listbox::OnResetContent( HWND hWnd ) {

    iOffsetIndex = 0;
    iCaretIndex  = LB_ERR;

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        for ( ; items.size(); ) {

            ListboxItem * pItem = items.at( 0 );

            if ( 0 != pItem->dwItemData ) {

                DELETEITEMSTRUCT    di;

                di.CtlID    = (unsigned long)hMenu;
                di.CtlType  = ODT_LISTBOX;
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

            ListboxItem * pItem = items.at( 0 );

            if ( 0 != pItem ) {

                DELETEITEMSTRUCT    di;

                di.CtlID    = (unsigned long)hMenu;
                di.CtlType  = ODT_LISTBOX;
                di.hwndItem = hWnd;
                di.itemData = (ULONG_PTR)pItem;
                di.itemID   = 0;

                FORWARD_WM_DELETEITEM( pParentWnd, &di, SendMessage );

            }

            items.erase( items.begin() );

        }

    }

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );
    return 0;

}


bool Listbox::OnPaint( HWND hWnd ) {

    PAINTSTRUCT ps;

    ZeroMemory( &ps, sizeof( ps ) );

    BeginPaint( hWnd, &ps );

    RECT r;
    GetClientRect( hWnd, &r );

    if ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) {

        COLORREF oldbkcr = GetBkColor( ps.hdc );
        COLORREF oldfgcr = GetTextColor( ps.hdc );

        for ( int iItem = iOffsetIndex, uY = 0; ( (unsigned)iItem < items.size() ) && ( uY < r.bottom ); iItem++ ) {

            if ( items.at( iItem )->IsSelected ) {

                SetBkColor( ps.hdc, SysColorHighLight.GetColor() );
                SetTextColor( ps.hdc, SysColorHighLightText.GetColor() );

            } else {

                SetBkColor( ps.hdc, SysColorWindow.GetColor() );
                SetTextColor( ps.hdc, SysColorWindowText.GetColor() );

            }

            TextOut( ps.hdc, 0, uY, items.at( iItem )->text.c_str(), items.at( iItem )->text.size() );

            uY += items.at( iItem )->uItemHeight;

        }

        SetBkColor( ps.hdc, oldbkcr );
        SetTextColor( ps.hdc, oldfgcr );

    } else {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Owner-drawn listbox items not painted" ) );

    }

    EndPaint( hWnd, &ps );

    return true;

}


bool Listbox::OnEraseBackground( HWND hWnd, HDC hDC ) {

    if ( ! ( ( LBS_STANDARD & dwStyle ) || ( LBS_HASSTRINGS & dwStyle ) ) ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Owner-drawn listbox background not drawn" ) );
        return true;

    }

    RECT r;
    GetClientRect( hWnd, &r );

    RECT rItem;

    SolidBrush brBackground( SysColorWindow.GetColor(), true );
    SolidBrush brSelection( SysColorHighLight.GetColor(), true );

    for ( long iItem = iOffsetIndex, uY = 0; uY < r.bottom; iItem++ ) {

        if ( (unsigned)iItem < items.size() ) {

            ListboxItem * pItem = items.at( iItem );

            rItem.left   = 0;
            rItem.top    = uY;

            rItem.right  = r.right;

            uY += pItem->uItemHeight;

            rItem.bottom = uY;

            FillRect( hDC, &rItem, (HBRUSH)( pItem->IsSelected ? &brSelection : &brBackground ) );

        } else {

            rItem.left   = 0;
            rItem.top    = uY;

            rItem.right  = r.right;

            rItem.bottom = r.bottom;

            uY = r.bottom;

            FillRect( hDC, &rItem, (HBRUSH)&brBackground );

        }

    }

    return true;

}


void Listbox::OnLButtonDown( HWND hWnd, BOOLEAN bDblClick, int userx, int usery, UINT uiKeyFlags ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Listbox left-%sclick (%d,%d)" ), bDblClick ? "DOUBLE" : "single", userx, usery );

    RECT  rItem;
    POINT pt;

    pt.x = userx;
    pt.y = usery;

    RECT r;
    GetClientRect( hWnd, &r );

    for ( int iItem = iOffsetIndex, uY = 0; ( (unsigned)iItem < items.size() ) && ( uY < r.bottom ); iItem++ ) {

        rItem.left  = 0;
        rItem.right = r.right;
        rItem.top   = uY;

        uY += items.at( iItem )->uItemHeight;

        rItem.bottom = uY;

        if ( PtInRect( &rItem, pt ) ) {

            int i = ListBox_GetCurSel( hWnd );

            if ( i != iItem ) {

                /* Selection has changed */

                int iRet = ListBox_SetCurSel( hWnd, iItem );

                if ( LB_ERR == iRet ) {

                    DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO RESET LISTBOX" ) );

                }

                /* Notify parent */

                if ( LBS_NOTIFY & dwStyle ) {

                    FORWARD_WM_COMMAND( (HWND)pParentWnd, (int)(long)hMenu, hWnd, LBN_SELCHANGE, SendMessage );

                }

            }

            if ( bDblClick && ( LBS_NOTIFY & dwStyle ) ) {

                FORWARD_WM_COMMAND( (HWND)pParentWnd, (int)(long)hMenu, hWnd, LBN_DBLCLK, SendMessage );

            }

        }

    }

}


int Listbox::SetSelectionAndNotify( HWND hWnd, int iIndex ) {

    if ( iIndex == iCaretIndex ) {

        return iIndex;

    }

    int i = OnSetCurSel( hWnd, iIndex );

    /* Notify parent */

    if ( ( LB_ERR != i ) && ( LBS_NOTIFY & dwStyle ) ) {

        FORWARD_WM_COMMAND( (HWND)pParentWnd, (long)hMenu, hWnd, LBN_SELCHANGE, SendMessage );

    }

    return i;

}


void Listbox::OnChar( HWND hWnd, TCHAR c, int cRepeat ) {

    if ( ( LBS_WANTKEYBOARDINPUT & dwStyle ) && ( ! ( LBS_HASSTRINGS & dwStyle ) ) ) {

        int iRet = 0;

        if ( ( LBS_OWNERDRAWFIXED & dwStyle ) || ( LBS_OWNERDRAWVARIABLE & dwStyle ) ) {

            iRet = FORWARD_WM_CHARTOITEM( pParentWnd, c, hWnd, iCaretIndex, SendMessage );

        }

        if ( -2 == iRet ) {

            return;

        }

    }

//    FORWARD_WM_COMMAND( pParentWnd, (unsigned long)hMenu, hWnd, EN_CHANGE, PostMessage );

}


void Listbox::OnKeydown( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags ) {

    int iRet;

    if ( LBS_WANTKEYBOARDINPUT & dwStyle && ( ! ( ( LBS_OWNERDRAWFIXED & dwStyle ) || ( LBS_OWNERDRAWVARIABLE & dwStyle ) ) ) ) {

        iRet = FORWARD_WM_VKEYTOITEM( pParentWnd, vk, hWnd, iCaretIndex, SendMessage );

        if ( -2 == iRet ) {

            return;

        }

    }

    /* Check for special keys */
    switch( vk ) {

        case VK_SPACE:

//            if ( BS_AUTOCHECKBOX & dwStyle ) {

//                AutoCheck();

//            }

            /* Notify parent */
//            FORWARD_WM_COMMAND( pParentWnd, (unsigned long)hMenu, hWnd, BN_CLICKED, PostMessage );
            break;

        case VK_DOWN:

            iRet = SetSelectionAndNotify( hWnd, iCaretIndex + 1 );

            if ( LB_ERR == iRet ) {

                MessageBeep( MB_BEEP );

            }
            break;

        case VK_UP:

            if ( 0 < iCaretIndex ) {

                iRet = SetSelectionAndNotify( hWnd, iCaretIndex - 1 );

                if ( LB_ERR != iRet ) {

                    break;

                }

            }

            MessageBeep( MB_BEEP );
            break;

    }

}


LRESULT Listbox::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Listbox * pWnd = reinterpret_cast<Listbox *>( hWnd );

    switch( uiMsg ) {

        case LB_ADDSTRING:

            return HANDLE_LB_ADDSTRING( hWnd, wParam, lParam, pWnd->OnAddStringOrItemData );

        case LB_DELETESTRING:

            return HANDLE_LB_DELETESTRING( hWnd, wParam, lParam, pWnd->OnDeletestringOrItemData );

        case LB_GETCOUNT:

            return HANDLE_LB_GETCOUNT( hWnd, wParam, lParam, pWnd->OnGetCount );

        case LB_GETCURSEL:

            return HANDLE_LB_GETCURSEL( hWnd, wParam, lParam, pWnd->OnGetCurSel );

        case LB_GETITEMDATA:

            return (LRESULT)HANDLE_LB_GETITEMDATA( hWnd, wParam, lParam, pWnd->OnGetItemData );

        case LB_GETITEMHEIGHT:

            return HANDLE_LB_GETITEMHEIGHT( hWnd, wParam, lParam, pWnd->OnGetItemHeight );

        case LB_GETTEXT:

            return HANDLE_LB_GETTEXT( hWnd, wParam, lParam, pWnd->OnGetText );

        case LB_GETTEXTLEN:

            return HANDLE_LB_GETTEXTLEN( hWnd, wParam, lParam, pWnd->OnGetTextLen );

        case LB_INSERTSTRING:

            return HANDLE_LB_INSERTSTRING( hWnd, wParam, lParam, pWnd->OnInsertStringOrItemData );

        case LB_RESETCONTENT:

            return HANDLE_LB_RESETCONTENT( hWnd, wParam, lParam, pWnd->OnResetContent );

        case LB_SETCURSEL:

            return HANDLE_LB_SETCURSEL( hWnd, wParam, lParam, pWnd->OnSetCurSel );

        case LB_SETITEMDATA:

            return (LRESULT)HANDLE_LB_SETITEMDATA( hWnd, wParam, lParam, pWnd->OnSetItemData );

        case WM_CHAR:

            HANDLE_WM_CHAR( hWnd, wParam, lParam, pWnd->OnChar );
            break;

        case WM_COMPAREITEM:

            return HANDLE_WM_COMPAREITEM( hWnd, wParam, lParam, pWnd->OnCompareItem );

        case WM_DESTROY:

            HANDLE_WM_DESTROY( hWnd, wParam, lParam, pWnd->OnDestroy );
            break;

        case WM_ERASEBKGND:

            return HANDLE_WM_ERASEBKGND( hWnd, wParam, lParam, pWnd->OnEraseBackground );

        case WM_KEYDOWN:

            HANDLE_WM_KEYDOWN( hWnd, wParam, lParam, pWnd->OnKeydown );
            break;

        case WM_LBUTTONDBLCLK:

            HANDLE_WM_LBUTTONDBLCLK( hWnd, wParam, lParam, pWnd->OnLButtonDown );
            break;

        case WM_LBUTTONDOWN:

            HANDLE_WM_LBUTTONDOWN( hWnd, wParam, lParam, pWnd->OnLButtonDown );
            break;

        case WM_PAINT:

            return pWnd->OnPaint( hWnd );

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}
