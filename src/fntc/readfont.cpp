

#include "project.h"


char * fgetsz( char * pData, size_t maxbufsize, FILE * pFile ) {

    char * psz = fgets( pData, maxbufsize, pFile );

    if ( NULL == psz ) {

        return psz;

    }

    int iLen = strlen( psz );

    for ( int i = 0; i < iLen; i++ ) {

        if ( *( psz + i ) < ' ' ) {

            *( psz + i ) = 0;
            break;

        }

    }

    return psz;

}


bool bReadValue( FILE * pFile, unsigned long int * lNum, int iBase ) {

    if ( feof( pFile ) ) {

        return false;

    }

    char szLine[1024];

    memset( szLine, '\0', sizeof( szLine ) );

    char * psz = fgetsz( szLine, Dim( szLine ) - 1, pFile );

    if ( NULL == psz ) {

        return false;

    }

    *lNum = (unsigned long)strtol( szLine, NULL, iBase );

    return true;

}


int ReadCharset( FILE * pFile, ywFont * pFont ) {

    char * psz;
    char szLine[4096];

    // Loop to read each character.
    for ( ;; ) {

        if ( feof( pFile ) ) {

            break;

        }

        memset( szLine, '\0', sizeof( szLine ) );

        psz = fgetsz( szLine, Dim( szLine ) - 1, pFile );

        if ( NULL == psz ) {

            break;

        }

        if ( 0 == strlen( psz ) ) {

            /* Skip over blank lines */
            continue;

        }

        chardef * pFace = (chardef *)malloc( sizeof( chardef ) );
        unsigned pixels = 0;

        pFace->c  = (unsigned)atoi( psz );
        pFace->cx = 0;
        pFace->cy = 0;

//        face.pFace = Bitmap::alloc( face.cx, face.cy, 1, ( Font_Header::monochrome == pFont->hdr.flags ) ? 1 : 32, NULL );

        // Loop to read each scanline of character.
        for ( pFace->cy = 0;; pFace->cy++ ) {

            if ( feof( pFile ) ) {

                break;

            }

            memset( szLine, '\0', sizeof( szLine ) );

            psz = fgetsz( szLine, Dim( szLine ) - 1, pFile );

            if ( NULL == psz ) {

                break;

            }

            if ( sizeof( char ) > strlen( psz ) ) {

                break;

            }

            // Loop to read each pixel of the scanline.

            if ( Font_Header::monochrome == pFont->pHdr->flags ) {

                for ( pFace->cx = 0; *psz && ( ( '0' == *psz ) || ( '1' == *psz ) ); pFace->cx++, psz++ ) {

                    COLORREF c = ( '1' == *psz ) ? RGB( 255, 255, 255 ) : 0;

                    pFace = (chardef *)realloc( pFace, sizeof( chardef ) + pixels + 1 );

                    unsigned char * pPixels = (unsigned char *)pFace->uscanlines;

                    pPixels[pixels] = c;

                    pixels++;

                }

            } else {

                char * pszDigit = strtok( psz, " " );

                /* 24 bit grayscale with unused alpha channel or 32-bit grayscale */
                for ( pFace->cx = 0; NULL != pszDigit; pFace->cx++ ) {

                    COLORREF c = 0;

                    for ( unsigned u = 0; u < sizeof( COLORREF ) * 2; u++ ) {

                        unsigned char uc = *pszDigit;

                        c = c << 4;

                        switch ( uc ) {

                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9':

                                uc = uc - '0';
                                break;

                            case 'A':
                            case 'B':
                            case 'C':
                            case 'D':
                            case 'E':
                            case 'F':

                                uc = ( uc - 'A' ) + 10;
                                break;

                        }

                        c |= uc;

                        pszDigit++;

                    }

                    pFace = (chardef *)realloc( pFace, sizeof( chardef ) + ( ( pixels + 1 ) * sizeof( COLORREF ) ) );
                    COLORREF * pPixels = (COLORREF *)pFace->uscanlines;

                    pPixels[pixels] = c;

                    pixels++;

                    pszDigit = strtok( NULL, " " );

                }

            }

        }

        ywFont::FacePair pair;

        pFace->uscanlinecount = pFace->cy;

        pair.first  = pFace->c;
        pair.second = pFace;

//        fprintf( stdout, "Read character %u, %dx%d, %u scanlines\n", (unsigned)face.c, face.cx, face.cy, face.uscanlinecount[0] );

        pFont->glyphs.insert( pair );

    }

    return 0;

}


int ReadFontData( FILE * pFile, Font_Header * & pHdr, unsigned & uSize ) {

    // Read header

    unsigned long int lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uWeight        = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->flags          = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uAvgCharHeight = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uAvgCharWidth  = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uMaxCharHeight = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uMaxCharWidth  = (unsigned)lNum;

    if ( ! bReadValue( pFile, &lNum, 0 ) ) {

        return -1;

    }

    pHdr->uLeading  = (unsigned)lNum;

    /* Read the name of the font */
    char szLine[1024];

    if ( feof( pFile ) ) {

        return -1;

    }

    memset( szLine, '\0', sizeof( szLine ) );

    char * psz = fgetsz( szLine, Dim( szLine ) - 1, pFile );

    if ( NULL == psz ) {

        return -1;

    }

    unsigned aligned = strlen( psz );

    uSize += aligned + 1;

    pHdr = (Font_Header *)realloc( pHdr, uSize );

    strcpy( pHdr->szName, psz );

    return 0;

}
