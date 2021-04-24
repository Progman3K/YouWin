

#include "ywin.h"


BOOL GetTextExtentPoint32( HDC hDC, LPCTSTR psz, int iLen, LPSIZE pSize ) {

    pSize->cx = 0;
    pSize->cy = 0;

    DC *   pDC   = reinterpret_cast<DC *>( hDC );
    Font * pFont = reinterpret_cast<Font *>( pDC->hFont );

    if ( NULL == pFont ) {

        pFont = reinterpret_cast<Font *>( hSystemFont );

    }

    unsigned uAmpersandCount = 0;

    for ( int i = 0; i < iLen; i++ ) {

        TCHAR c = *( psz + i );

        if ( NUL == c ) {

            break;

        }

        long Width = pFont->pHdr->uAvgCharWidth;
        long Height = pFont->pHdr->uAvgCharHeight;

        const glyph * pGlyph;

        if ( ' ' != c ) {

            pGlyph = pFont->GetFace( c );

            if ( 0 != pGlyph ) {

                Width = pGlyph->Width();
                Height = pGlyph->Height();

            }

        }

        if ( ( '&' == c ) && pDC->bInDrawText && ! ( DT_NOPREFIX & pDC->uiDTMode ) ) {

            /* Take into account the prefixing or double-ampersanding */
            uAmpersandCount++;

        }

        pSize->cx += Width;

        if ( pSize->cy < (LONG)Height ) {

            pSize->cy = Height;

        }

    }

    if ( 0 < uAmpersandCount ) {

        const glyph * pGlyph = pFont->GetFace( '&' );

        pSize->cx -= pGlyph->Width();

    }

    return true;

}
