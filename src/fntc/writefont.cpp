

#include "project.h"


bool bWrite( const void * data, size_t len, FILE * pFile ) {

    if ( len != fwrite( data, 1, len, pFile ) ) {

        fprintf( stderr, "OUTPUT ERROR %lu bytes", (unsigned long)len );
        return false;

    }

    return true;

}


int WriteCharset( FILE * pFile, ywFont * pFont ) {

    unsigned u;

    /* Write how many glyphs are in this character set */
    u = (unsigned)pFont->glyphs.size();

    fprintf( stdout, "writing - '%s': %u glyphs\n", pFont->pHdr->szName, u );

    if ( ! bWrite( &u, sizeof( u ), pFile ) ) {

        fprintf( stderr, "OUTPUT ERROR writing charset length %d", u );
        return -1;

    }

    size_t uDataSize;

    if ( Font_Header::monochrome == pFont->pHdr->flags ) {

        uDataSize = sizeof( char );

    } else {

        uDataSize = sizeof( COLORREF );

    }

    for ( auto pFace = pFont->glyphs.begin(); pFace != pFont->glyphs.end(); pFace++ ) {

        //unsigned short u = (unsigned)pFace->second.pFace->size();
        unsigned short uscanlinecount = (unsigned)( pFace->second->cx * pFace->second->cy ) * uDataSize;

        if ( ! (

            bWrite( &pFace->second->c,            sizeof( pFace->second->c ),                            pFile ) &&
            bWrite( &pFace->second->cx,           sizeof( pFace->second->cx ),                           pFile ) &&
            bWrite( &pFace->second->cy,           sizeof( pFace->second->cy ),                           pFile ) &&
            bWrite( &uscanlinecount,              sizeof( uscanlinecount ),                              pFile ) &&
            bWrite( &pFace->second->uscanlines,   ( pFace->second->cx * pFace->second->cy ) * uDataSize, pFile ) ) ) {

            fprintf( stderr, "OUTPUT ERROR writing char %d", pFace->second->c );
            return -1;

        } else {

//            fprintf( stdout, "Character %u, %ux%u, %u lines of %u bytes\n", (unsigned)pFace->second.c, pFace->second.cx, pFace->second.cy, u, (unsigned)uDataSize );

        }

#if 0
        POINT pt;

        for( pt.y = 0; pt.y < pFace->second.pFace->Height(); pt.y++ ) {

            for ( pt.x = 0; pt.x < pFace->second.pFace->Width(); pt.x++ ) {

                COLORREF c;

                if ( pFace->second.pFace->GetPixel( pt, c ) ) {

                    fprintf( stdout, "%c", ( 0 == c ) ? '0' : '1' );
                    fprintf( stdout, "%c", ( 0 == c ) ? '0' : '1' );

                } else {

                    fprintf( stdout, "x" );

                }

            }

            fprintf( stdout, "%c", NEWLINE );

        }
#endif

    }

    return 0;

}


int WriteFontData( FILE * pFile, ywFont * pFont, unsigned uHeaderSize ) {

    if (

        // Write header
        bWrite( pFont->pHdr, uHeaderSize, pFile ) &&

        /* Add NULL at the end of the name */
//        bWrite( pFont->name.charz_str(), pFont->name.size() + 1, pFile ) &&

        ( 0 == WriteCharset( pFile, pFont ) )

    ) {

        return 0;

    }

    return -1;

}
