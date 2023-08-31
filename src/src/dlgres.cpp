

#include "ywin.h"


int PopulateDialogFromTemplate( HINSTANCE hInst, ywWindow * pDlg, const DLGTEMPLATE * pDlgHeader, const UTF_16 * p ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "extra word: %X" ), *p );

    utf16string ctlclassname;
    utf16string text;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "template has %d children:" ), (int)I386PE_INT16_TO_HOST( &pDlgHeader->cdit ) );

    for ( unsigned u = 0; u < (unsigned)I386PE_INT16_TO_HOST( &pDlgHeader->cdit ); u++ ) {

        ctlclassname.clear();
        ctlclassname.tcharz.clear();
        text.clear();
        text.tcharz.clear();

        const UTF_16 * pParams = NULL;

/*
        switch( (unsigned long)p % sizeof( uint32_t ) ) {

            case 0: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ON boundary" ) ); break;
            case 1: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 1"    ) ); break;
            case 2: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 2"    ) ); break;
            case 3: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 3"    ) ); break;

        }
*/
        /* Data for controls starts on a DWORD-aligned boundary, so adjust p if necessary */
        if ( 0 != ( (unsigned long)p % sizeof( unsigned ) ) ) {

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "p is already aligned on a WORD boundary, so to make it DWORD aligned, we only need to increment it to the next WORD" ) );
            p++;

        }

        const DLGITEMTEMPLATE * pControlData = (const DLGITEMTEMPLATE *)p;

        DBG_DMP( DBG_GENERAL_INFORMATION, pControlData->ClassId, 32 );

        RECT r;

        r.left   = I386PE_INT16_TO_HOST( &pControlData->x  );
        r.top    = I386PE_INT16_TO_HOST( &pControlData->y  );
        r.right  = I386PE_INT16_TO_HOST( &pControlData->cx );
        r.bottom = I386PE_INT16_TO_HOST( &pControlData->cy );

        /* Is there an identifier there? */
        if ( 0xFFFF == pControlData->ClassId[0] ) {

            // Class name identifier
            UTF_16 aClassName[32];

            ZeroMemory( aClassName, sizeof( aClassName ) );

            WORD wCtlClass = I386PE_INT16_TO_HOST( &pControlData->ClassId[1] );

            switch( wCtlClass ) {

                case ATOM_BUTTON:

                    aClassName[0] = 'B';
                    aClassName[1] = 'U';
                    aClassName[2] = 'T';
                    aClassName[3] = 'T';
                    aClassName[4] = 'O';
                    aClassName[5] = 'N';
                    ctlclassname.append_from_native( aClassName );
                    break;

                case ATOM_EDITTEXT:

                    aClassName[0] = 'E';
                    aClassName[1] = 'D';
                    aClassName[2] = 'I';
                    aClassName[3] = 'T';
                    ctlclassname.append_from_native( aClassName );
                    break;

                case ATOM_STATIC:

                    aClassName[0] = 'S';
                    aClassName[1] = 'T';
                    aClassName[2] = 'A';
                    aClassName[3] = 'T';
                    aClassName[4] = 'I';
                    aClassName[5] = 'C';
                    ctlclassname.append_from_native( aClassName );
                    break;

                case ATOM_LISTBOX:

                    aClassName[0] = 'L';
                    aClassName[1] = 'I';
                    aClassName[2] = 'S';
                    aClassName[3] = 'T';
                    aClassName[4] = 'B';
                    aClassName[5] = 'O';
                    aClassName[6] = 'X';
                    ctlclassname.append_from_native( aClassName );
                    break;

                case ATOM_SCROLLBAR:

                    aClassName[0] = 'S';
                    aClassName[1] = 'C';
                    aClassName[2] = 'R';
                    aClassName[3] = 'O';
                    aClassName[4] = 'L';
                    aClassName[5] = 'L';
                    aClassName[6] = 'B';
                    aClassName[7] = 'A';
                    aClassName[8] = 'R';
                    ctlclassname.append_from_native( aClassName );
                    break;

                case ATOM_COMBOBOX:

                    aClassName[0] = 'C';
                    aClassName[1] = 'O';
                    aClassName[2] = 'M';
                    aClassName[3] = 'B';
                    aClassName[4] = 'O';
                    aClassName[5] = 'B';
                    aClassName[6] = 'O';
                    aClassName[7] = 'X';
                    ctlclassname.append_from_native( aClassName );
                    break;

                default:

                    return -1;

            }

            /* Update pointer so it points after the control-type */
            p = &pControlData->ClassId[2];

        } else {

            /* Not an identifier, class name follows */
//            DBG_DMP( DBG_GENERAL_INFORMATION, pControlData->ClassId, 16 );

            p = ctlclassname.append_from_resource( pControlData->ClassId );

        }

        if ( 0xFFFF == *p ) {

            p++;
            pParams = p;

            p++;

        } else {

            p = text.append_from_resource( p );

        }

        MapDialogRect( (HWND)pDlg, &r );

        HWND hWnd = CreateWindowEx( I386PE_INT32_TO_HOST( &pControlData->dwExtendedStyle ), ctlclassname.tcharz_str(), text.tcharz_str(), I386PE_INT32_TO_HOST( &pControlData->style ), r.left, r.top, r.right, r.bottom, (HWND)pDlg, (HMENU)(unsigned long)I386PE_INT16_TO_HOST( &pControlData->id ), hInst, (LPVOID)( pParams ? pParams : p ) );

        if ( NULL == hWnd ) {

            DBG_MSG( DBG_ERROR, TEXT( "Unable to create '%s' control %d, (%d,%d)(%d,%d) '%s', extra word: %X" ), ctlclassname.tcharz_str(), I386PE_INT16_TO_HOST( &pControlData->id ), r.left, r.top, r.right, r.bottom, text.tcharz_str(), *p );
            return -1;

        }

        /* Increment past the undocumented extra stuff */
        p++;

    }

    return 0;

}


ywWindow * CreateDialogObject( HINSTANCE hInst, LPCTSTR resname, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam ) {

    HRSRC hRes = FindResource( hInst, resname, RT_DIALOG );

    if ( 0 == hRes ) {

        DBG_MSG( DBG_ERROR, TEXT( "Could not load dialog resource %lX from %lX" ), resname, hInst );
        return NULL;

    }

    HGLOBAL h = LoadResource( hInst, hRes );

    const DLGTEMPLATE * pDlgHeader = (const DLGTEMPLATE *)LockResource( h );

    RECT r;

    r.left   = I386PE_INT16_TO_HOST( &pDlgHeader->x );
    r.top    = I386PE_INT16_TO_HOST( &pDlgHeader->y );
    r.right  = I386PE_INT16_TO_HOST( &pDlgHeader->cx );
    r.bottom = I386PE_INT16_TO_HOST( &pDlgHeader->cy );

    MapDialogRect( hParentWnd, &r );

    DWORD dwStyle = I386PE_INT32_TO_HOST( &pDlgHeader->style );

    if ( ( DS_CONTROL & dwStyle ) == DS_CONTROL ) {

        /* Dialog is a control, remove caption. */
        dwStyle = ( ( ~WS_CAPTION ) & dwStyle );

    }

    if ( ( WS_CAPTION & dwStyle ) == WS_CAPTION ) {

        r.bottom += GetSystemMetrics( SM_CYCAPTION );

    }

    if ( ( DS_CENTER & dwStyle ) == DS_CENTER ) {

        if ( r.right < GetSystemMetrics( SM_CXSCREEN ) ) {

            r.left = ( GetSystemMetrics( SM_CXSCREEN ) - r.right ) / 2;

        }

        if ( r.bottom < GetSystemMetrics( SM_CYSCREEN ) ) {

            r.top = ( GetSystemMetrics( SM_CYSCREEN ) - r.bottom ) / 2;

        }

    }

    const UTF_16 * p = &( pDlgHeader->MenuName[0] );

    HMENU hMenu = 0;

    /* Is there an identifier there? */
    if ( 0 == *p ) {

        /* No menu, class name follows */
        p++;

    } else {

        // ID or string?

        if ( 0xFFFF == *p ) {

            /* ID */

            /* Increment past marker */
            p++;

            hMenu = LoadMenu( hInst, MAKEINTRESOURCE( *p ) );

            if ( NULL == hMenu ) {

                return NULL;

            }

            /* Increment past ID */
            p++;

        } else {

            /* String */
            utf16string menuname;

            p = menuname.append_from_resource( p );

            hMenu = LoadMenu( hInst, menuname.tcharz_str() );

            if ( NULL == hMenu ) {

                return NULL;

            }

        }

        r.bottom += GetSystemMetrics( SM_CYMENU );

    }

    utf16string classname;

    if ( 0 == *p ) {

        /* No class name, title follows */
        p++;

    } else {

        p = classname.append_from_resource( p );

    }

    utf16string caption;

    if ( 0 == *p ) {

        /* No window title */
        p++;

    } else {

        p = caption.append_from_resource( p );

    }

    WORD wPoint = (WORD)-1;

    if ( DS_SETFONT & dwStyle ) {

        /*
        * DS_SETFONT style is present,
        * font point-size is next
        * and the fontname follows.
        */
        wPoint = I386PE_INT16_TO_HOST( p );
        p++;

        utf16string font;
        p = font.append_from_resource( p );

    }

    /* An array of dialog controls follows, it must begin on a DWORD boundary */
    switch( (uintptr_t)p % 4 ) {

        case 0: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ON boundary" ) ); break;
        case 1: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 1"    ) ); break;
        case 2: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 2"    ) ); break;
        case 3: DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "offset 3"    ) ); break;

    }

    Dialog * pWnd = reinterpret_cast<Dialog *>( CreateWindowEx( I386PE_INT32_TO_HOST( &pDlgHeader->dwExtendedStyle ), classname.size() > 0 ? classname.tcharz_str() : TEXT( "DIALOG" ), caption.tcharz_str(), dwStyle, r.left, r.top, r.right, r.bottom, hParentWnd, hMenu, hInst, (void *)lParam ) );

    if ( NULL == pWnd ) {

        return NULL;

    }

    pWnd->wPoint = wPoint;

    pWnd->bDlgProc = bDlgProc;

    /* Instantiate child controls */
    if ( 0 != PopulateDialogFromTemplate( hInst, pWnd, pDlgHeader, p ) ) {

        DestroyWindow( (HWND)pWnd );
        return NULL;

    }

    return pWnd;

}


int NativePopulateDialogFromTemplate( HINSTANCE hInst, ywWindow * pDlg, const DLGTEMPLATE * pDlgHeader, const UTF_16 * p ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "extra word: %X" ), *p );

    utf16string ctlclassname;
    utf16string text;

    for ( unsigned u = 0; u < pDlgHeader->cdit; u++ ) {

        ctlclassname.clear();
        text.clear();

        const DLGITEMTEMPLATE * pControlData = (const DLGITEMTEMPLATE *)p;

        p = ctlclassname.append_from_native( pControlData->ClassId );

        p = text.append_from_native( p );

        RECT r;

        r.left   = pControlData->x;
        r.top    = pControlData->y;
        r.right  = pControlData->cx;
        r.bottom = pControlData->cy;

        MapDialogRect( (HWND)pDlg, &r );

        HWND hWnd = CreateWindowEx( pControlData->dwExtendedStyle, ctlclassname.tcharz_str(), text.tcharz_str(), pControlData->style, r.left, r.top, r.right, r.bottom, (HWND)pDlg, (HMENU)(unsigned long)pControlData->id, hInst, (void *)p );

        if ( NULL == hWnd ) {

            DBG_MSG( DBG_ERROR, TEXT( "Unable to create '%s' control %d, (%d,%d)(%d,%d) '%s', extra word: %X" ), ctlclassname.tcharz_str(), pControlData->id, r.left, r.top, r.right, r.bottom, text.tcharz_str(), *p );
            return -1;

        }

        /* Increment past the undocumented extra stuff */
        p++;

    }

    return 0;

}


static bool InitDialog( ywWindow * pWnd, LPARAM lParam, bool bForceVisible ) {

    IWindow * pTabStopWnd = IWindow::GetTabstop( pWnd, true );

#if 0
    DBG_MSG( DBG_GENERAL_INFORMATION, "TURNING OFF VISIBILITY FOR THIS WINDOW %lX", pWnd );
    /* Turn off WS_VISIBLE in case any drawing code is called. */
    DWORD dwOldStyle = pWnd->dwStyle;
    pWnd->dwStyle = ( ( ~WS_VISIBLE ) & pWnd->dwStyle );
#endif

    BOOLEAN bRet = FORWARD_WM_INITDIALOG( (HWND)pWnd, (HWND)pTabStopWnd, lParam, SendMessage );

    if ( ( NULL != pWnd->pbClosed ) && *pWnd->pbClosed ) {

        /* Error during initialization */
        return false;

    }

    /* Resolve focus */
    if ( bRet ) {

        /* Find and set focus to the first control in the dialog box that is VISIBLE, NOT disabled, and that has the WS_TABSTOP style. */

//        pTabStopWnd = IWindow::GetTabstop( pWnd, true );

        if ( NULL != pTabStopWnd ) {

            SetFocus( (HWND)pTabStopWnd );

        }

    } /* else the user set the focus */

#if 0
    /* Restore original style bits. */
    pWnd->dwStyle = dwOldStyle;

    if ( bForceVisible || ( WS_VISIBLE & pWnd->dwStyle ) ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, "TURNING ON VISIBILITY FOR THIS WINDOW %lX", pWnd );

        /* Make sure style reflects the fact the window is going to be visible */
        pWnd->dwStyle |= WS_VISIBLE;
        RedrawWindow( (HWND)pWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    }
#endif

    return true;

}


HWND CreateDialogParam( HINSTANCE hInstance, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam ) {

    DBG_MSG( DBG_WIN32API, "Entering CreateDialogParam" );

    ywWindow * pWnd = CreateDialogObject( hInstance, pDlgID, hParentWnd, bDlgProc, lParam );

    if ( NULL == pWnd ) {

        DBG_MSG( DBG_WIN32API, "Exiting CreateDialogParam" );
        return NULL;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, "TURNING OFF VISIBILITY FOR THIS WINDOW %lX", pWnd );
    /* Turn off WS_VISIBLE in case any drawing code is called. */
    DWORD dwOldStyle = pWnd->dwStyle;
    pWnd->dwStyle = ( ( ~WS_VISIBLE ) & pWnd->dwStyle );

    BOOLEAN bClosed;

    bClosed = false;

    pWnd->pbClosed = &bClosed;

    if ( ! InitDialog( pWnd, lParam, false ) ) {

        DestroyWindow( (HWND)pWnd );
        DBG_MSG( DBG_WIN32API, "Exiting CreateDialogParam" );
        return NULL;

    }

    pWnd->pbClosed = NULL;

    if ( WS_VISIBLE & dwOldStyle ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, "TURNING ON VISIBILITY FOR THIS WINDOW %lX", pWnd );

        /* Make sure style reflects the fact the window is going to be visible */
        pWnd->dwStyle |= WS_VISIBLE;
        RedrawWindow( (HWND)pWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    }

    DBG_MSG( DBG_WIN32API, "Exiting CreateDialogParam" );
    return (HWND)pWnd;

}


HWND CreateDialog( HINSTANCE hInstance, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc ) {

    return CreateDialogParam( hInstance, pDlgID, hParentWnd, bDlgProc, 0 );

}


HWND CreateDialogIndirectParam( HINSTANCE hInst, const DLGTEMPLATE * pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam ) {

    HMENU hMenu = 0;

    RECT r;

    r.left   = pDlgHeader->x;
    r.top    = pDlgHeader->y;
    r.right  = pDlgHeader->cx;
    r.bottom = pDlgHeader->cy;

    MapDialogRect( hParentWnd, &r );

    if ( ( WS_CAPTION & pDlgHeader->style ) == WS_CAPTION ) {

        r.bottom += GetSystemMetrics( SM_CYCAPTION );

    }

    const UTF_16 * p = &( pDlgHeader->MenuName[0] );

    /* Is there an identifier there? */
    if ( 0 == *p ) {

        /* No menu, class name follows */
        p++;

    } else {

        // ID or string?

        if ( 0xFFFF == *p ) {

            /* ID */

            /* Increment past marker */
            p++;

            hMenu = LoadMenu( hInst, MAKEINTRESOURCE( *p ) );

            if ( NULL == hMenu ) {

                return NULL;

            }

            /* Increment past ID */
            p++;

        } else {

            /* String */
            utf16string menuname;

            p = menuname.append_from_resource( p );

            hMenu = LoadMenu( hInst, menuname.tcharz_str() );

            if ( NULL == hMenu ) {

                return NULL;

            }

        }

        r.bottom += GetSystemMetrics( SM_CYMENU );

    }

    utf16string classname;

    if ( 0 == *p ) {

        /* No class name, title follows */
        p++;

    } else {

        p = classname.append_from_native( p );

    }

    utf16string caption;

    if ( 0 == *p ) {

        /* No window caption */
        p++;

    } else {

        p = caption.append_from_native( p );

    }

    WORD wPoint = (WORD)-1;

    if ( DS_SETFONT & pDlgHeader->style ) {

        /*
        * DS_SETFONT style is present,
        * font point-size is next
        * and the fontname follows.
        */
        wPoint = *p;
        p++;

        utf16string font;
        p = font.append_from_resource( p );

    }

    Dialog * pWnd = reinterpret_cast<Dialog *>( CreateWindowEx( pDlgHeader->dwExtendedStyle, classname.size() > 0 ? classname.tcharz_str() : TEXT( "DIALOG" ), caption.tcharz_str(), pDlgHeader->style, r.left, r.top, r.right, r.bottom, hParentWnd, hMenu, hInst, (void *)lParam ) );

    if ( NULL == pWnd ) {

        return NULL;

    }

    pWnd->wPoint = wPoint;

    pWnd->bDlgProc = bDlgProc;

    /* Instantiate child controls */
    if ( 0 != NativePopulateDialogFromTemplate( hInst, pWnd, pDlgHeader, p ) ) {

        DestroyWindow( (HWND)pWnd );
        return NULL;

    }

    if ( ! InitDialog( pWnd, lParam, false ) ) {

        DestroyWindow( (HWND)pWnd );
        return NULL;

    }

    return pWnd;

}


HWND CreateDialogIndirect( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc ) {

    return CreateDialogIndirectParam( hInst, pDlgHeader, hParentWnd, bDlgProc, 0 );

}


static INT_PTR DoModal( ywWindow * pWnd, LPARAM lParam ) {

    IWindow * pParentPopupWnd = NULL;

    if ( ( NULL != pWnd->pParentWnd ) && ( HWND_DESKTOP != pWnd->pParentWnd ) ) {

      pParentPopupWnd = IWindow::GetPopup( pWnd->pParentWnd );

      if ( NULL != pParentPopupWnd ) {

        pParentPopupWnd->bPopupDisabled = true;

      }

    }

    MSG Msg;

    int iRet = 0;

    /* Make certain the dialog will be visible */
    pWnd->dwStyle |= WS_VISIBLE;
    RedrawWindow( (HWND)pWnd, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    for ( ; ! *pWnd->pbClosed; ) {

        iRet = GetMessage( &Msg, (HWND)pWnd, 0, 0 );

        if ( 1 != iRet ) {

            DBG_MSG( DBG_ERROR, TEXT( "DoModal abends; GetMessage code %d" ), iRet );
            break;

        }

        if ( *pWnd->pbClosed ) {

            break;

        }

        if ( IsDialogMessage( (HWND)pWnd, &Msg ) ) {

            continue;

        }

        TranslateMessage( &Msg );
        DispatchMessage( &Msg );

    }

    if ( ( NULL != pParentPopupWnd ) && ( 0 == pParentPopupWnd->SigGood() ) ) {

        pParentPopupWnd->bPopupDisabled = false;

    }

    return iRet;

}


INT_PTR DialogBoxIndirectParam( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam ) {

    int     iDlgRet = -1;

    BOOLEAN bClosed = false;

    HWND hOldFocusWnd = GetFocus();

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( CreateDialogIndirectParam( hInst, pDlgHeader, hParentWnd, bDlgProc, lParam ) );

    if ( NULL == pWnd ) {

        return -1;

    }

    pWnd->pbClosed     = &bClosed;
    pWnd->piDlgRetCode = &iDlgRet;

    DoModal( pWnd, lParam );

    if ( ( NULL != hOldFocusWnd ) && IsWindow( hOldFocusWnd ) ) {

        SetFocus( hOldFocusWnd );

    }

    DestroyWindow( (HWND)pWnd );

    return iDlgRet;

}


INT_PTR DialogBoxIndirect( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc ) {

    return DialogBoxIndirectParam( hInst, pDlgHeader, hParentWnd, bDlgProc, 0 );

}


INT_PTR DialogBoxParam( HINSTANCE hInst, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam ) {

    int     iDlgRet = -1;

    BOOLEAN bClosed = false;

    HWND hOldFocusWnd = GetFocus();

    ywWindow * pWnd = CreateDialogObject( hInst, pDlgID, hParentWnd, bDlgProc, lParam );

    if ( NULL == pWnd ) {

        return -1;

    }

    pWnd->pbClosed     = &bClosed;
    pWnd->piDlgRetCode = &iDlgRet;

    if ( ! InitDialog( pWnd, lParam, true ) ) {

        DestroyWindow( (HWND)pWnd );
        return -1;

    }

    DoModal( pWnd, lParam );

    if ( ( NULL != hOldFocusWnd ) && IsWindow( hOldFocusWnd ) ) {

        SetFocus( hOldFocusWnd );

    }

    DestroyWindow( (HWND)pWnd );

    if ( IsWindow( hParentWnd ) ) {

        RedrawWindow( hParentWnd, 0, 0, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_INTERNALPAINT | RDW_ALLCHILDREN );

    }

    return iDlgRet;

}


INT_PTR DialogBox( HINSTANCE hInst, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc ) {

    return DialogBoxParam( hInst, pDlgID, hParentWnd, bDlgProc, 0 );

}
