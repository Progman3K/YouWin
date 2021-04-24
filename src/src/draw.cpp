

#include "ywin.h"


#ifndef YOU_WIN_TXT


// YOU_WIN_GRAPHICAL


int DC::TypeByteAt( HFONT hUserFont, POINT pt, UINT uFlags, UINT uFormat, TCHAR c, const RECT * pr ) {

    Font * pFont = reinterpret_cast<Font *>( hUserFont );

    long Width = pFont->pHdr->uAvgCharWidth;
    long Height = pFont->pHdr->uAvgCharHeight;

    if ( ' ' == c ) {

        return Width;

    }

    /* Retrieve the glyph for c */
    const glyph * pGlyph = pFont->GetFace( c );

    if ( 0 != pGlyph ) {

        Width = pGlyph->Width();
        Height = pGlyph->Height();

    }

    if ( ! ( DT_CALCRECT & uFormat ) ) {

        /* Check clipping */
        POINT ptBit;

        POINT ptBitmap;

        /* Put each scanline down */

        for ( ptBitmap.y = 0 /* unsigned line = 0 */; ptBitmap.y < Height; ptBitmap.y++ ) {

            for ( ptBitmap.x = 0; ptBitmap.x < Width; ptBitmap.x++ ) {

                COLORREF cPixel = 0;

                if ( ! pGlyph->GetPixel( ptBitmap, cPixel ) ) {

                    /* Should not happen */
                    continue;

                }

                ptBit.y = pt.y + ptBitmap.y;
                ptBit.x = pt.x + ptBitmap.x;

                if ( 0 != cPixel ) {

                    /* Pixel is ON */

                    /*
                    * Each glyph's bitmap pixels represent each pixel's relative
                    * intensity. */
                    float rIntensity = GetRValue( cPixel ) / 255.0;
                    float gIntensity = GetGValue( cPixel ) / 255.0;
                    float bIntensity = GetBValue( cPixel ) / 255.0;

                    /* We must apply these ratios to the DC's text colour. */
                    BYTE red   = GetRValue( text.fg );
                    BYTE green = GetGValue( text.fg );
                    BYTE blue  = GetBValue( text.fg );

                    cPixel = RGB( (BYTE)( red * rIntensity ), (BYTE)( green * gIntensity ), (BYTE)( blue * bIntensity ) );

                    if ( ( NULL == pr ) || PtInRect( pr, ptBit ) ) {

                        SetPixel( ptBit, cPixel, text.fg );

                    }

                } else {

                    /* Pixel is OFF */

                    if ( OPAQUE == iBkMode ) {

                        if ( ( NULL == pr ) || PtInRect( pr, ptBit ) ) {

                            SetPixel( ptBit, text.bg, text.bg );

                        }

                    }

                }

            }

        }

    }

    return Width;

}


#endif /* YOU_WIN_GRAPHICAL */
