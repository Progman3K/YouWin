

#include "ywin.h"


void Edit::scrolllinedown( int line, int height, int width ) {

    if ( ! ( line < (int)ClientDC.shape.cy  ) ) {

        return;

    }

    // scroll the line above this one first.
    scrolllinedown( line + height, height, width );

    // blit this line to the one above it.
    BitBlt( &ClientDC, 0, line + height, width, height, &ClientDC, 0, line, SRCCOPY );

}


void Edit::scrolllineup( int line, int height, int width ) {

    if ( ! ( line > 0  ) ) {

        return;

    }

    // scroll the line above this one first.
    scrolllineup( line - height, height, width );

    // blit this line to the one above it.
    BitBlt( &ClientDC, 0, line - height, width, height, &ClientDC, 0, line, SRCCOPY );

}


bool Edit::AddChar( HWND hWnd, TCHAR c ) {

    RECT       r;
    TEXTMETRIC tm;

    GetTextMetrics( &ClientDC, &tm );

    switch ( c ) {

        // Special control characters;

        case CARRIAGERETURN:

            break;

        case NEWLINE:

            if ( ( caret.pt.y + ( tm.tmHeight * 2 ) ) > (int)ClientDC.shape.cy ) {

                /* No more room vertically */

                if ( ES_AUTOVSCROLL & dwStyle ) {

                    // blank off the rest of the line
                    r( caret.pt.x, caret.pt.y, ClientDC.shape.cx, caret.pt.y + tm.tmHeight );
                    ClientDC.fill( r, ClientDC.text.bg );

                    // take the current line and copy 
                    scrolllineup( caret.pt.y, tm.tmHeight, ClientDC.shape.cx );

                    r( 0, caret.pt.y, ClientDC.shape.cx, caret.pt.y + tm.tmHeight );
                    ClientDC.fill( r, ClientDC.text.bg );

                    caret.pt.x = 0;

                    uiVScrollPos += tm.tmHeight;

                    /* Update the scrollbars */
                    RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INTERNALPAINT | RDW_INVALIDATE );

                } else {

                    /* Character dropped */
                    return false;

                }

            } else {

                // blank off the rest of the line
                r( caret.pt.x, caret.pt.y, ClientDC.shape.cx, caret.pt.y + tm.tmHeight );
                ClientDC.fill( r, ClientDC.text.bg );

                caret.pt.x = 0;
                caret.pt.y += tm.tmHeight;

            }
            break;

        case TAB:

            break;

        default :

            if ( c < ' ' ) {

                // Unsupported control character; ignore it.
                return false;

            }

    }

    Text.insert( uInsertPos, 1, c );
    uInsertPos++;

    if ( ' ' <= c ) {

        // NOT a control character
        SIZE s;
        GetTextExtentPoint( &ClientDC, &c, 1, &s );

        /* Check linewrap */
        if ( caret.pt.x + s.cx > (int)ClientDC.shape.cx ) {

            if ( ES_AUTOHSCROLL & dwStyle ) {

                /* Perform horizontal scrolling */


            } else {

                /* No horizontal scrolling; this will add a line */

                if ( ( caret.pt.y + ( tm.tmHeight * 2 ) ) > (int)ClientDC.shape.cy ) {

                    /* No more room vertically */

                    if ( ES_AUTOVSCROLL & dwStyle ) {

                        /* Perform vertical scroll */


                    } else {

                        /* Character dropped */
                        return false;

                    }

                } else {

                    /* There is still room vertically */
                    caret.pt.x = 0;
                    caret.pt.y += tm.tmHeight;

                }

            }

        }

        TextOut( &ClientDC, caret.pt.x, caret.pt.y, &c, 1 );

        caret.pt.x += s.cx;

    }

    if ( Text.size() > uInsertPos ) {

        /* Repaint rest of text. */
        DrawCursorToEOB( 0 );

    }

    return true;

}
