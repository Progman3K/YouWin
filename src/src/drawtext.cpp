

#include "ywin.h"


/**
    DC * pDC
    int x
    int y
    UINT uFlags
    UINT uFormat
    const RECT * pr     // Optional clipping rectangle
    LPCTSTR lpString
    int nCount
*/
static BOOL txtloop( DC * pDC, POINT & pt, UINT uFlags, UINT uFormat, const RECT * pr, LPCTSTR lpString, int iLen ) {

    POINT ptUnderline;       // DC position of character
    TCHAR cUnderline   = -1; // Glyph to underline

    for ( ; 0 < iLen; ) {

        TCHAR c = *lpString;

        lpString++;

        iLen--;

        /* Check if there was an underline character */
        if ( ( 0 == iLen ) && ( (TCHAR)-1 != cUnderline ) ) {

            /* There was, draw the underline */
#ifdef YOU_WIN_TXT
            underline_on();

            /* Type out the glyph */
            pDC->TypeByteAt( pDC->hFont, ptUnderline, uFlags, uFormat, cUnderline, pr );

            underline_off();
#else
            pDC->TypeByteAt( pDC->hFont, ptUnderline, uFlags, uFormat, '_', pr );
#endif

            /* Reset for next line */
            cUnderline  = -1;

        }

        if ( '\n' == c ) {

            if ( DT_ONE_LINE & uFormat ) {

                return true;

            }

            if ( ! ( DT_SINGLELINE & uFormat ) ) {

                /* Start a new line */
                pt.x = pr->left;
                pt.y += (reinterpret_cast<ywFont *>(pDC->hFont))->pHdr->uMaxCharHeight;
                continue;

            }

        }

        if ( ' ' > c ) {

            // It's a control character

        } else {

            if ( ( '&' == c ) && ! ( DT_NOPREFIX & uFormat ) ) {

                if ( ( 0 < iLen ) && ( '&' == *lpString ) ) {

                    /* Next character is also an ampersand, then print ONE ampersand */
                    iLen--;
                    lpString++;

                } else {

                    /* Mark the next character as being potentially the underlined one */
                    ptUnderline = pt;
                    cUnderline  = *lpString;
                    continue;

                }

            }

            // NOT a control character
            pt.x += pDC->TypeByteAt( pDC->hFont, pt, uFlags, uFormat, c, pr );

        }

    }

    return true;

}


#if 0
int processtxt( DC * pDC, UINT uFormat, RECT * pr, LPCTSTR lpString, int iLen ) {

    RECT r2 = *pr;

    if ( DT_CENTER & uFormat ) {

        if ( DT_SINGLELINE & uFormat ) {

            int TextX = 0, TextY = 0;

            // Get the length in pixels of the string to print
            SIZE s;
            GetTextExtentPoint32( pDC, lpString, iLen, &s );

            // if it is larger than the button, then print it at x offset 0

            if ( s.cx < ( pr->right - pr->left ) ) {

                // Since it is smaller than the width of the button, subtract its length from the width of the button
                // Then divide whatever that is by 2, and make x that.
                TextX = ( ( pr->right - pr->left ) - s.cx ) / 2;

            }

            r2.left += TextX;

            // if it is higher than the button, then print it at y offset 0

            if ( s.cy < ( pr->bottom - pr->top ) ) {

                // Since it is smaller than the height of the button, subtract its height from the height of the button
                // Then divide whatever that is by 2, and make y that.
                TextY = ( ( pr->bottom - pr->top ) - s.cy ) / 2;

            }

            r2.top  += TextY;

            return txtloop( pDC, r2.left, r2.top, 0, uFormat, pr, lpString, iLen );

        } else {

            /* Multiple-lines of centered text */
            size_t eol = 0;

            eol = strcspnn( lpString, '\n', iLen );

            for ( ; iLen > 0; ) {

                int TextX, TextY;

                if ( 0 == eol ) {

                    /* Last line */

                    TextX = 0;
                    TextY = 0;

                    // Get the length in pixels of the string to print
                    SIZE s;
                    GetTextExtentPoint32( pDC, lpString, iLen, &s );

                    // if it is larger than the button, then print it at x offset 0

                    if ( s.cx < ( pr->right - pr->left ) ) {

                        // Since it is smaller than the width of the button, subtract its length from the width of the button
                        // Then divide whatever that is by 2, and make x that.
                        TextX = ( ( pr->right - pr->left ) - s.cx ) / 2;

                    }

                    r2.left += TextX;

                    return txtloop( pDC, r2.left, r2.top, 0, uFormat, pr, lpString, iLen );

                }

                TextX = 0;
                TextY = 0;

                // Get the length in pixels of the string to print
                SIZE s;
                GetTextExtentPoint32( pDC, lpString, eol + 1, &s );

                // if it is larger than the button, then print it at x offset 0

                if ( s.cx < ( pr->right - pr->left ) ) {

                    // Since it is smaller than the width of the button, subtract its length from the width of the button
                    // Then divide whatever that is by 2, and make x that.
                    TextX = ( ( pr->right - pr->left ) - s.cx ) / 2;

                }

                r2.left = pr->left + TextX;

                /* Add DT_SINGLELINE temporarily so it steps through a line at a time */
                txtloop( pDC, r2.left, r2.top, 0, uFormat | DT_SINGLELINE, pr, lpString, eol );

                lpString += eol + 1;

                iLen -= eol + 1;

                r2.top += s.cy;

                eol = strcspnn( lpString, '\n', iLen );

            }

        }

    }

    return txtloop( pDC, r2.left, r2.top, 0, uFormat, pr, lpString, iLen );

}
#endif


/**
 * Return the length of the next word and its size in ps
 */
int nextword( DC * pDC, SIZE * ps, RECT & r, UINT uFormat, LPCTSTR lpString, int iLen ) {

    int i = 0;

    ps->cx = 0;
    ps->cy = 0;

    for ( ; i < iLen; i++ ) {

        SIZE s;

        s.cx = 0;
        s.cy = 0;

        GetTextExtentPoint32( pDC, lpString + i, 1, &s );

        ps->cx += s.cx;

        if ( s.cy > ps->cy ) {

            ps->cy = s.cy;

        }

        if ( ' ' >= *( lpString + i ) ) {

            return i + 1;

        }


    }

    return i;

}


int strcspnn( const TCHAR * pSrc, TCHAR c, size_t len ) {

    size_t ret;

    for ( ret = 0; ret < len; ret++ ) {

        if ( c == *(pSrc + ret) ) {

            return ret + 1;

        }

    }

    return ret;

}

int nextline( DC * pDC, SIZE * ps, RECT & r, UINT uFormat, LPCTSTR lpString, int iLen ) {

    int iRet = strcspnn( lpString, '\n', iLen );

    GetTextExtentPoint32( pDC, lpString, iRet, ps );

    return iRet;

#if 0
    int iBOL = 0;

    int iWordlen = 0;
    int iLineLen = 0;

    SIZE s;

    for ( ; iLen > 0; ) {

        iWordlen = nextword( pDC, &s, r, uFormat, lpString + iBOL, iLen - iLineLen );

        iLineLen += iWordlen;

    }

    return iLineLen;
#endif
}


static int DrawText2( DC * pDC, POINT & pt, LPCTSTR lpString, int iLen, LPRECT pr, UINT uFormat ) {

    RECT r;

    r = *pr;

    SIZE s;

    s.cx = 0;
    s.cy = 0;

    int oneline = iLen;

    if ( DT_SINGLELINE & uFormat ) {

        /* Obtain length of entire line (length) and print it, centered if need be.
         * Carriage-returns and newlines are printable characters and do not affect word-wrap,
         * even if word-wrap is specified.
         */
        GetTextExtentPoint32( pDC, lpString, iLen, &s );

        if ( DT_BOTTOM & uFormat ) {

            if ( ( r.bottom - r.top ) >= s.cy ) {

                pt.y = ( r.bottom - s.cy );

            }

        } else if ( DT_VCENTER & uFormat ) {

            if ( ( r.bottom - r.top ) >= s.cy ) {

                pt.y += ( ( ( r.bottom - r.top ) / 2 ) - ( s.cy / 2 ) );

            }

        }

    } else {

        oneline = nextline( pDC, &s, r, uFormat, lpString, iLen );

    }

    for ( ;; ) {

        int pad = 0;

        if ( DT_CENTER & uFormat ) {

            /* Fit inside the line */
            pad = ( r.right - r.left ) - s.cx;
            pad = pad / 2;

        } else if ( DT_RIGHT & uFormat ) {

            pad = ( r.right - r.left ) - s.cx;

        }

        pt.x += pad;

        if ( DT_CALCRECT & uFormat ) {

            /* Check if line would go past rightmost margin */
            if ( pt.x + s.cx > r.right ) {

                /* Stretch margin */
                r.right = pt.x + s.cx;

            }

            if ( pt.y + s.cy > r.bottom ) {

                /* Elongate rectangle */
                r.bottom = pt.y + s.cy;

            }

        }

        /* Default DT_LEFT */
        // BOOL bRet =
        txtloop( pDC, pt, 0, uFormat, &r, lpString, oneline );

        iLen -= oneline;
        lpString += oneline;

        if ( ( 1 > iLen ) || ( DT_SINGLELINE & uFormat ) || ( DT_ONE_LINE & uFormat ) ) {

            break;

        }

        oneline = nextline( pDC, &s, r, uFormat, lpString, iLen );

    }

    if ( DT_CALCRECT & uFormat ) {

        *pr = r;

    }

    return pt.y;

}


int DrawText( HDC hDC, LPCTSTR lpString, int iLen, LPRECT pr, UINT uFormat ) {

    if ( 1 > iLen ) {

        if ( -1 == iLen ) {

            iLen = strlen( lpString );

        } else {

            /* Any other value is illegal */
            return false;

        }

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

#ifdef YOU_WIN_TXT
    POINT ptOldCaret = getxy();
#endif

    StartPoints();

    int iRet = 0;

    pDC->bInDrawText = true;
    UINT uiOldDTMode = pDC->uiDTMode;

    pDC->uiDTMode = uFormat;

    if ( TA_UPDATECP & pDC->uiTextAlignMode ) {

        iRet = DrawText2( pDC, pDC->ptPen, lpString, iLen, pr, uFormat );

    } else {

        POINT pt;

        pt.x = pr->left;
        pt.y = pr->top;

        iRet = DrawText2( pDC, pt, lpString, iLen, pr, uFormat );

    }

    // bRet = processtxt( pDC, uFormat, pr, lpString, iLen );

    pDC->bInDrawText = false;
    pDC->uiDTMode    = uiOldDTMode;

    /* Iterate character by character, line-by-line */
#ifdef YOU_WIN_TXT
    gotoxy( ptOldCaret.x, ptOldCaret.y );
#endif

    EndPoints();

    return iRet;

}


BOOL ExtTextOut( HDC hDC, int x, int y, UINT uFlags, const RECT * pr, LPCTSTR lpString, UINT nCount, const int * lpDx ) {

    DC * pDC = reinterpret_cast<DC *>( hDC );

    /* If no bounding rectangle is provided, each character will draw its background colour or not if transparent */
    if ( ( ETO_OPAQUE & uFlags ) && ( 0 != pr ) ) {

        SolidBrush  br( pDC->text.bg, true );

        FillRect( hDC, pr, (HBRUSH)&br );

    }

    if ( 1 > nCount ) {

        return false;

    }

#ifdef YOU_WIN_TXT
    POINT ptOldCaret = getxy();
#endif

    StartPoints();

    RECT r;

    r.left   = 0;
    r.top    = 0;
    r.right  = pDC->shape.cx;
    r.bottom = pDC->shape.cy;

    if ( ETO_CLIPPED & uFlags && ( NULL != pr ) ) {

        r = *pr;

    }

    POINT pt;

    pt.x = x;
    pt.y = y;

    BOOL bRet = txtloop( pDC, pt, uFlags, DT_SINGLELINE | DT_NOPREFIX, &r, lpString, nCount );

#ifdef YOU_WIN_TXT
    gotoxy( ptOldCaret.x, ptOldCaret.y );
#endif

    EndPoints();

    return bRet;

}
