

#include "ywin.h"


void Edit::OnChar( HWND hWnd, TCHAR c, int cRepeat ) {

    if ( ES_READONLY & dwStyle ) {

        MessageBeep( MB_BEEP );
        return;

    }

    /* Check for special keys, like arrows, home-end, del, ins  */
    switch( c ) {
    }

//    if ( ' ' > c ) {

//        return;

//    }

    bool bHide = caret.hide( hWnd );

    AddChar( hWnd, c );

    if ( bHide ) {

        caret.Invert( hWnd );

    }

    FORWARD_WM_COMMAND( pParentWnd, (unsigned long)hMenu, hWnd, EN_CHANGE, PostMessage );

}


void Edit::OnTimer( HWND hWnd, UINT uTimerID ) {

    /* Check if caret owner */
    if ( GetFocus() != hWnd ) {

        /* If not, kill timer, done. */
        KillTimer( hWnd, uTimerID );
        return;

    }

    caret.Invert( hWnd );

}


void Edit::DrawCursorToEOB( unsigned uFormat ) {

    TEXTMETRIC tm;
    GetTextMetrics( &ClientDC, &tm );

    POINT   pt;

    pt( caret.pt.x, caret.pt.y );

    unsigned u = 0;

    /* Back up to beginnning of line */
    for ( ; 0 < pt.x; ) {

        u++;

        SIZE s;
        GetTextExtentPoint( &ClientDC, Text.c_str() + ( uInsertPos - u ), 1, &s );

        pt.x -= s.cx;

    }

    RECT r;
    r( pt.x, pt.y, ClientDC.shape.cx, ClientDC.shape.cy );

    if ( ! ( DT_ONE_LINE & uFormat ) ) {

        ClientDC.fill( r, ClientDC.text.bg );

    }

    // Draw at the cursor and the rest of the line.
    DrawText( &ClientDC, Text.c_str() + ( uInsertPos - u ), Text.size() - uInsertPos + u, &r, DT_EDITCONTROL | DT_NOPREFIX | uFormat );

}


void Edit::OnKeydown( HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags ) {

    TCHAR      c;
    SIZE       s;
    unsigned   uLen;
    POINT      NewCaretPos;
    unsigned   uNewInsertPos;
    TEXTMETRIC tm;

    /* Check for special keys */
    switch( vk ) {

        case VK_BACK:

            if ( ES_READONLY & dwStyle ) {

                return;

            }

            if ( ! ( 0 < uInsertPos ) ) {

                return;

            }

            FORWARD_WM_KEYDOWN( hWnd, VK_LEFT,   cRepeat, flags, PostMessage );
            FORWARD_WM_KEYDOWN( hWnd, VK_DELETE, cRepeat, flags, PostMessage );
            break;

        case VK_DELETE:

            if ( ES_READONLY & dwStyle ) {

                return;

            }

            if ( ! ( Text.size() > uInsertPos ) ) {

                return;

            }

            Text.erase( uInsertPos, 1 );

            DrawCursorToEOB( 0 );

            FORWARD_WM_COMMAND( pParentWnd, (unsigned long)hMenu, hWnd, EN_CHANGE, PostMessage );
            break;

        case VK_LEFT:

            if ( ! ( uInsertPos > 0 ) ) {

                break;

            }

            uInsertPos--;

            c = Text.at( uInsertPos );

            if ( NEWLINE != c ) {

                GetTextExtentPoint( &ClientDC, &c, 1, &s );
                caret.pt.x -= s.cx;
                return;

            }

            NewCaretPos   = caret.pt;
            uNewInsertPos = uInsertPos;

            /* Go up one line */

            /* Measure new line */
            uLen = 0;
            for ( ; uNewInsertPos > 0; uLen++ ) {

                uNewInsertPos--;

                c = Text.at( uNewInsertPos );

                if ( NEWLINE == c ) {

                    /* Went one too far */
                    uNewInsertPos++;
                    break;

                }

            }

            /* Forward until near original column */
            NewCaretPos.x = 0;

            for ( ; uLen > 0; uLen-- ) {

                c = Text.at( uNewInsertPos );

                GetTextExtentPoint( &ClientDC, &c, 1, &s );

                uNewInsertPos++;

                NewCaretPos.x += s.cx;

            }

            uInsertPos = uNewInsertPos;

            GetTextMetrics( &ClientDC, &tm );

            if ( 0 > ( NewCaretPos.y - tm.tmHeight ) ) {

                RECT r;

                r( NewCaretPos.x, NewCaretPos.y, ClientDC.shape.cx, NewCaretPos.y + tm.tmHeight );

                scrolllinedown( NewCaretPos.y, tm.tmHeight, ClientDC.shape.cx );

                ClientDC.fill( r, ClientDC.text.bg );

                /* Display new top line */

            } else {

                NewCaretPos.y -= tm.tmHeight;

            }

            caret.pt   = NewCaretPos;

            DrawCursorToEOB( DT_ONE_LINE );
            break;

        case VK_RIGHT:

            if ( ! ( uInsertPos < Text.size() ) ) {

                break;

            }

            c = Text.at( uInsertPos );

            uInsertPos++;

            if ( NEWLINE != c ) {

                GetTextExtentPoint( &ClientDC, &c, 1, &s );
                caret.pt.x += s.cx;
                break;

            }

            caret.pt.x = 0;

            GetTextMetrics( &ClientDC, &tm );

            if ( ClientDC.shape.cy < (unsigned long)( caret.pt.y + ( tm.tmHeight * 2 ) ) ) {

                RECT r;

                r( caret.pt.x, caret.pt.y, ClientDC.shape.cx, caret.pt.y + ( tm.tmHeight * 2 ) );

                scrolllineup( caret.pt.y, tm.tmHeight, ClientDC.shape.cx );

                ClientDC.fill( r, ClientDC.text.bg );

                /* Display new bottom line */
                DrawCursorToEOB( DT_ONE_LINE );

            } else {

                caret.pt.y += tm.tmHeight;

            }

            break;

        case VK_UP:

            /* Note column */
            NewCaretPos   = caret.pt;
            uNewInsertPos = uInsertPos;

            /* Back up to BOL */
            for ( ;; ) {

                if ( ! ( uNewInsertPos > 0 ) ) {

                    return;

                }

                uNewInsertPos--;

                c = Text.at( uNewInsertPos );

                if ( NEWLINE == c ) {

                    break;

                }

            }

            /* Go up one line */

            /* Measure new line */
            uLen = 0;
            for ( ; uNewInsertPos > 0; uLen++ ) {

                uNewInsertPos--;

                c = Text.at( uNewInsertPos );

                if ( NEWLINE == c ) {

                    /* Went one too far */
                    uNewInsertPos++;
                    break;

                }

            }

            /* Forward until near original column */
            NewCaretPos.x = 0;

            for ( ; uLen > 0; uLen-- ) {

                if ( ! ( NewCaretPos.x < caret.pt.x ) ) {

                    break;

                }

                c = Text.at( uNewInsertPos );

                GetTextExtentPoint( &ClientDC, &c, 1, &s );

                uNewInsertPos++;

                NewCaretPos.x += s.cx;

            }

            uInsertPos = uNewInsertPos;

            GetTextMetrics( &ClientDC, &tm );

            if ( 0 > ( NewCaretPos.y - tm.tmHeight ) ) {

                RECT r;

                r( NewCaretPos.x, NewCaretPos.y, ClientDC.shape.cx, NewCaretPos.y + tm.tmHeight );

                scrolllinedown( NewCaretPos.y, tm.tmHeight, ClientDC.shape.cx );

                ClientDC.fill( r, ClientDC.text.bg );

                /* Display new top line */
                DrawCursorToEOB( DT_ONE_LINE );

            } else {

                NewCaretPos.y -= tm.tmHeight;

            }

            caret.pt = NewCaretPos;

            break;

        case VK_DOWN:

            /* Note column */
            NewCaretPos   = caret.pt;
            uNewInsertPos = uInsertPos;

            /* Forward to EOL */
            for ( ;; ) {

                if ( ! ( uNewInsertPos < Text.size() ) ) {

                    return;

                }

                c = Text.at( uNewInsertPos );

                uNewInsertPos++;

                if ( NEWLINE == c ) {

                    /* Go one further */
                    break;

                }

            }

            /* Go down one line */

            /* Forward until near original column */
            NewCaretPos.x = 0;

            for ( ; uNewInsertPos < Text.size(); uNewInsertPos++ ) {

                if ( ! ( NewCaretPos.x < caret.pt.x ) ) {

                    break;

                }

                c = Text.at( uNewInsertPos );

                if ( NEWLINE == c ) {

                    break;

                }

                GetTextExtentPoint( &ClientDC, &c, 1, &s );

                NewCaretPos.x += s.cx;

            }

            uInsertPos = uNewInsertPos;

            GetTextMetrics( &ClientDC, &tm );

            if ( ClientDC.shape.cy < (unsigned long)( NewCaretPos.y + ( tm.tmHeight * 2 ) ) ) {

                RECT r;

                r( NewCaretPos.x, NewCaretPos.y, ClientDC.shape.cx, NewCaretPos.y + ( tm.tmHeight * 2 ) );

                scrolllineup( NewCaretPos.y, tm.tmHeight, ClientDC.shape.cx );

                ClientDC.fill( r, ClientDC.text.bg );

                caret.pt   = NewCaretPos;

                /* Display new bottom line */
                DrawCursorToEOB( DT_ONE_LINE );

            } else {

                NewCaretPos.y += tm.tmHeight;
                caret.pt   = NewCaretPos;

            }

            break;

        case VK_RETURN:

            if ( ( ES_WANTRETURN & dwStyle ) && ( ES_MULTILINE & dwStyle ) ) {

                FORWARD_WM_CHAR( hWnd, NEWLINE, cRepeat, SendMessage );

            }
            break;

        case VK_SPACE:

            FORWARD_WM_CHAR( hWnd, ' ', cRepeat, SendMessage );
            break;

        default:

            /* Not a special key */
            FORWARD_WM_KEYDOWN( hWnd, vk, cRepeat, flags, DefWindowProc );
            break;

    }

}


void Edit::OnReplaceSel( HWND hWnd, BOOL bCanUndo, LPCTSTR lpszText ) {

    // Freeze the display until we add the text completely.
    BOOLEAN bOldNoRedraw = bNoRedraw;
    bNoRedraw = true;

    for ( ; *lpszText ; lpszText++ ) {

        AddChar( hWnd, *lpszText );

    }

    bNoRedraw = bOldNoRedraw;

    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

}


void Edit::OnSetSel( HWND hWnd, int iSelStart, int iSelEnd ) {
}


void Edit::CalculateScrollPositions( HWND hWnd ) {

    HDC hDC = GetDC( hWnd );

    TEXTMETRIC tm;
    GetTextMetrics( hDC, &tm );

    const TCHAR * pBOS = Text.c_str();

    /* Calculate the true size (max cx, max cy) of the line */
    SIZE scrolls;
    scrolls.cx = 0;
    scrolls.cy = 0;

    unsigned u = 0;

    for ( ; '\0' != *( pBOS + u ); ) {

        size_t len = _tcscspn( pBOS, TEXT( "\n" ) );

        SIZE s;
        GetTextExtentPoint( hDC, pBOS, len, &s );

        u += len;

        scrolls.cy += s.cy;

        if ( s.cx > scrolls.cx ) {

            scrolls.cx = s.cx;

        }

    }

}


void Edit::DrawFromBeginningOfWindowToCursor( HDC hDC ) {

    // Draw from cursor to BOL.
    POINT pt;
    pt.x = caret.pt.x;
    pt.y = caret.pt.y;

    unsigned u                 = uInsertPos;
    unsigned uDrawLen          = 0;
//    unsigned uCurrentLineWidth = pt.x;
    RECT r;
    r.left   = 0;
    r.top    = 0;
    r.right  = ClientDC.shape.cx;
    r.bottom = ClientDC.shape.cy;
    // = { 0, 0, ClientDC.shape.cx, ClientDC.shape.cy };

    TEXTMETRIC tm;
    GetTextMetrics( hDC, &tm );

    for ( bool bFinished = false; ( ! bFinished ) && ( u > 0 ); u-- ) {

        TCHAR c = Text.at( u - 1 );

        SIZE s;
        GetTextExtentPoint( &ClientDC, &c, 1, &s );

        switch( c ) {

            case NEWLINE:

                if ( ( pt.y - tm.tmHeight ) < 0 ) {

                    bFinished = true;
                    break;

                }

                uDrawLen++;

                pt.y -= tm.tmHeight;

                /* Have to find width of this new line
                 * back up until either BOL or another NEWLINE is found
                 */

                pt.x = ClientDC.shape.cx;
                continue;

            default:

                if ( 0 <= ( pt.x - s.cx ) ) {

                    uDrawLen++;

                    pt.x -= s.cx;

                } else {

                    if ( ( pt.y - tm.tmHeight ) < 0 ) {

                        bFinished = true;
                        break;

                    }

                    uDrawLen++;

                    pt.y -= tm.tmHeight;
                    pt.x = ClientDC.shape.cx;

                }
                break;

        }

    }

    if ( 0 < uDrawLen ) {

        DrawText( hDC, Text.c_str() + uInsertPos - uDrawLen, uDrawLen, &r, DT_EDITCONTROL | DT_NOPREFIX );

    }

}


void Edit::OnPaint( HWND hWnd ) {

    caret.hide( hWnd );

    PAINTSTRUCT ps;

    ZeroMemory( &ps, sizeof( ps ) );

    BeginPaint( hWnd, &ps );

    if ( 0 != Text.size() ) {

        COLORREF oldbkcr = SetBkColor( ps.hdc, GetSysColor( COLOR_WINDOW ) );
        COLORREF oldfgcr = SetTextColor( ps.hdc, GetSysColor( COLOR_WINDOWTEXT ) );

        DrawFromBeginningOfWindowToCursor( ps.hdc );

        DrawCursorToEOB( 0 );

        SetBkColor( ps.hdc, oldbkcr );
        SetTextColor( ps.hdc, oldfgcr );

    }

    EndPaint( hWnd, &ps );

    if ( GetFocus() == hWnd ) {

        caret.Invert( hWnd );

    }

    return;

}


void Edit::OnKillfocus( HWND hWnd, HWND /* hOldfocuswnd */ ) {

    KillTimer( hWnd, IDT_CARET );

    caret.hide( hWnd );

#if defined( ANDROID ) || ( defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE )
    displayKeyboard( g.app, false );
#endif

}


void Edit::OnSetfocus( HWND hWnd, HWND hOldfocuswnd ) {

    caret.Invert( hWnd );

#ifndef DEBUG
    SetTimer( hWnd, IDT_CARET, 500, NULL );
#endif

#if defined( ANDROID ) || ( defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE )
    displayKeyboard( g.app, true );
#endif

}


void Edit::OnSetText( HWND hWnd, LPCTSTR lpszText ) {

    bool bHide = caret.hide( hWnd );

    caret.pt( 0, 0 );

    uInsertPos = 0;

    FORWARD_WM_SETTEXT( hWnd, lpszText, DefWindowProc );

    if ( bHide ) {

        caret.Invert( hWnd );

    }

}


void Edit::OnClear( HWND ) {
}


HANDLE Edit::OnGetHandle( HWND ) {

    return (HANDLE)Text.c_str();

}

void Edit::OnSetReadonly( HWND hWnd, BOOL bReadonly ) {

    if ( bReadonly ) {

        dwStyle |= ES_READONLY;

    } else {

        dwStyle = ( ( ~ES_READONLY ) & dwStyle );

    }

}


LRESULT Edit::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Edit * pWnd = reinterpret_cast<Edit *>( hWnd );

    switch( uiMsg ) {

        case EM_GETHANDLE:

            return (LRESULT)HANDLE_EM_GETHANDLE( hWnd, wParam, lParam, pWnd->OnGetHandle );

        case EM_REPLACESEL:

            HANDLE_EM_REPLACESEL( hWnd, wParam, lParam, pWnd->OnReplaceSel );
            return 0;

        case EM_SETREADONLY:

            HANDLE_EM_SETREADONLY( hWnd, wParam, lParam, pWnd->OnSetReadonly );
            return 0;

        case EM_SETSEL:

            HANDLE_EM_SETSEL( hWnd, wParam, lParam, pWnd->OnSetSel );
            return 0;

        case WM_CHAR:

            HANDLE_WM_CHAR( hWnd, wParam, lParam, pWnd->OnChar );
            return 0;

        case WM_CLEAR:

            HANDLE_WM_CLEAR( hWnd, wParam, lParam, pWnd->OnClear );
            break;

        case WM_KEYDOWN:

            pWnd->caret.hide( hWnd );

            HANDLE_WM_KEYDOWN( hWnd, wParam, lParam, pWnd->OnKeydown );

            if ( GetFocus() == hWnd ) {

                pWnd->caret.Invert( hWnd );

            }
            return 0;

        case WM_KILLFOCUS:

            HANDLE_WM_KILLFOCUS( hWnd, wParam, lParam, pWnd->OnKillfocus );
            break;

        case WM_PAINT:

            HANDLE_WM_PAINT( hWnd, wParam, lParam, pWnd->OnPaint );
            return 0;

        case WM_SETFOCUS:

            HANDLE_WM_SETFOCUS( hWnd, wParam, lParam, pWnd->OnSetfocus );
            break;

        case WM_SETTEXT:

            HANDLE_WM_SETTEXT( hWnd, wParam, lParam, pWnd->OnSetText );
            return true;

        case WM_TIMER:

            HANDLE_WM_TIMER( hWnd, wParam, lParam, pWnd->OnTimer );
            return 0;

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}
