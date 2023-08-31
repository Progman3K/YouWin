

#include "ywin.h"


static bool BitXOn( const BYTE * puc, unsigned x, unsigned y, unsigned cx, unsigned cy ) {

    unsigned ubit = ( y * cx ) + x;

    BYTE uc = *( puc + ( ubit / 8 ) );

    switch( ubit % 8 ) {

        case 0:  return 128 == ( 128 & uc );
        case 1:  return  64 == (  64 & uc );
        case 2:  return  32 == (  32 & uc );
        case 3:  return  16 == (  16 & uc );
        case 4:  return   8 == (   8 & uc );
        case 5:  return   4 == (   4 & uc );
        case 6:  return   2 == (   2 & uc );
        default: return   1 == (   1 & uc );

    }

}


ResIcon::ResIcon( const BITMAPINFO * p ) {

    pBI = p;
    pDIB = 0;
    pAND = 0;

    switch( getbpp() ) {

        case 1:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - Monochrome" ) );

            pDIB = (BYTE *)&pBI->bmiColors[2];
            pAND = pDIB + ( ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 2 ) / 4 );

#ifdef DEBUG
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "DIB bits:" ) );

            unsigned bitsperline;

            switch( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) ) {

                case 32:

                    bitsperline = 4;
                    break;

                case 64:

                    bitsperline = 8;
                    break;

                case 128:

                    bitsperline = 16;
                    break;

                default:

                    bitsperline = 16;
                    break;

            }

            DBG_DMPBIN( DBG_DATA_DUMPS, bitsperline, pDIB, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 2 ) / 4 );
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "AND bits:" ) );
            DBG_DMPBIN( DBG_DATA_DUMPS, bitsperline, pAND, ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 8 );
#endif /* DEBUG */
            break;

        case 4:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - 16 colour" ) );

            pDIB = (BYTE *)&pBI->bmiColors[16];
            pAND = pDIB + ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 2 );

            DBG_DMP( DBG_DATA_DUMPS, pDIB, ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 2 );
            DBG_DMP( DBG_DATA_DUMPS, pAND, ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 8 );
            break;

        case 8:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - 256 colour" ) );

            /* Bitmap follows palette */
            pDIB = (BYTE *)&pBI->bmiColors[256];
            pAND = pDIB + ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) );

            DBG_DMP( DBG_DATA_DUMPS, pAND, ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 8 );
            break;

        case 24:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - 16,777,215 colours" ) );

            pDIB = (BYTE *)&pBI->bmiColors[0];
            pAND = pDIB + ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) );
            break;

        case 32:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - 32 bit truecolor" ) );

            pDIB = (BYTE *)&pBI->bmiColors[0];
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "AND bits:" ) );
            pAND = pDIB + ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) );
            DBG_DMPBIN( DBG_DATA_DUMPS, 8, pAND, ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) / 8 );
            break;

        default:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - Unsupported bpp: %u" ), getbpp() );
            break;

    }

}


bool ResIcon::GetPixel1bpp( const POINT & pt, COLORREF & c ) const {

    if ( BitXOn( pAND, pt.x, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y, I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ), I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) {

        /* Monochrome bitmaps AND mask is inverted: If the bit is ON, the pixel is transparent */
        return false;

    }

    if ( BitXOn( pDIB, pt.x, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y, I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ), I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) {

        /* Monochrome bitmaps DIB mask: If the bit is ON, the pixel is white */
        c = RGBA( 255, 255, 255, 0 );

    } else {

        /* Pixel is black */
        c = RGBA( 0, 0, 0, 0 );

    }

    return true;

}


bool ResIcon::GetPixel4bpp( const POINT & pt, COLORREF & c ) const {

    if ( BitXOn( pAND, pt.x, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y, I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ), I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) {

        c = RGBA( 0, 0, 0, 255 );

    } else {

        unsigned wordno = ( ( ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y ) * I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) ) + pt.x;

        unsigned offset = wordno / 2;
        unsigned nibble = wordno % 2;

        BYTE uc = *( pDIB + offset );
        unsigned uIndex;

        if ( 0 != nibble ) {

            uIndex = uc & 0x0F;

        } else {

            uIndex = uc & 0xF0;
            uIndex = uIndex >> 4;

        }

        RGBQUAD pixel = pBI->bmiColors[ uIndex ];

        c = RGBA( pixel.rgbRed, pixel.rgbGreen, pixel.rgbBlue, 0 );

    }

    return true;

}


bool ResIcon::GetPixel8bpp( const POINT & pt, COLORREF & c ) const {

    if ( BitXOn( pAND, pt.x, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y, I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ), I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) {

        c = RGBA( 0, 0, 0, 255 );

    } else {

        // set pixel
        RGBQUAD pixel = pBI->bmiColors[ *( pDIB + ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y ) ) + pt.x ) ) ];

        c = RGBA( pixel.rgbRed, pixel.rgbGreen, pixel.rgbBlue, 0 );

    }

    return true;

}


bool ResIcon::GetPixel24bpp( const POINT & pt, COLORREF & c ) const {

    if ( BitXOn( pAND, pt.x, ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y, I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ), I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) ) {

        c = RGBA( 0, 0, 0, 255 );

    } else {

        // set pixel
        RGBQUAD pixel = pBI->bmiColors[ ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y ) ) + pt.x ) ];

        c = RGBA( pixel.rgbRed, pixel.rgbGreen, pixel.rgbBlue, 0 );

    }

    return true;

}


bool ResIcon::GetPixel32bpp( const POINT & pt, COLORREF & c ) const {


    // set pixel
    RGBQUAD pixel = pBI->bmiColors[ ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ) * ( ( ( I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2 ) - 1 ) - pt.y ) ) + pt.x ) ];

    c = RGBA( pixel.rgbRed, pixel.rgbGreen, pixel.rgbBlue, 255 - pixel.rgbReserved );

    return true;

}


bool ResIcon::GetPixel( const POINT & pt, COLORREF & c ) const {

    switch( getbpp() ) {

        case 1:  return GetPixel1bpp( pt, c );
        case 4:  return GetPixel4bpp( pt, c );
        case 8:  return GetPixel8bpp( pt, c );
        case 24: return GetPixel24bpp( pt, c );
        case 32: return GetPixel32bpp( pt, c );

    }

    return false;

}


void Icon::_create( const ResourceList * pResList, const Resource * pRes ) {

    pResource = pRes;

    pDir = (ResourceDirectory *)pResource->Id.pData;

    DBG_MSG( DBG_GENERAL_INFORMATION,
        TEXT( "bWidth: %u, bHeight: %u, bColorCount: %u, bReserved: %u, wPlanes: %u, wBitCount: %u, lBytesInRes: %u, wNameOrdinal: %u" ),
    (unsigned)pDir->bWidth,
    (unsigned)pDir->bHeight,
    (unsigned)pDir->bColorCount,
    (unsigned)pDir->bReserved,
    (unsigned)pDir->wPlanes,
    (unsigned)pDir->wBitCount,
    (unsigned)pDir->lBytesInRes,
    (unsigned)pDir->wNameOrdinal
    );

    pIconDir = (const IconDirectory *)pResource->Id.pData;

    DBG_MSG( DBG_GENERAL_INFORMATION,
        TEXT( "IconGoupHeader size: %u. hdr - Reserved: %u, ResType: %u, ResCount: %u. entry - bWidth: %u, bHeight: %u, bColorCount: %u, bReserved: %u, wPlanes: %u,  wBitCount: %u, lBytesInRes: %u, wNameOrdinal: %u" ),
    (unsigned)I386PE_INT32_TO_HOST( &pResource->Id.pHeader->uiSize ),
    (unsigned)pIconDir->hdr.Reserved,
    (unsigned)pIconDir->hdr.ResType,
    (unsigned)pIconDir->hdr.ResCount,
    (unsigned)pIconDir->entry[0].bWidth,
    (unsigned)pIconDir->entry[0].bHeight,
    (unsigned)pIconDir->entry[0].bColorCount,
    (unsigned)pIconDir->entry[0].bReserved,
    (unsigned)pIconDir->entry[0].wPlanes,
    (unsigned)pIconDir->entry[0].wBitCount,
    (unsigned)pIconDir->entry[0].lBytesInRes,
    (unsigned)pIconDir->entry[0].wNameOrdinal
    );

    for ( unsigned u = 0; u < (unsigned)I386PE_INT16_TO_HOST( &pIconDir->hdr.ResCount ); u++ ) {

        DBG_MSG( DBG_GENERAL_INFORMATION,
            TEXT( "ICONRESDIR - bWidth: %u, bHeight: %u, bColorCount: %u, bReserved: %u, wPlanes: %u, wBitCount: %u, lBytesInRes: %u, wNameOrdinal: %u" ),
        (unsigned)pIconDir->entry[u].bWidth,
        (unsigned)pIconDir->entry[u].bHeight,
        (unsigned)pIconDir->entry[u].bColorCount,
        (unsigned)pIconDir->entry[u].bReserved,
        (unsigned)I386PE_INT16_TO_HOST( &pIconDir->entry[u].wPlanes ),
        (unsigned)I386PE_INT16_TO_HOST( &pIconDir->entry[u].wBitCount ),
        (unsigned)I386PE_INT32_TO_HOST( &pIconDir->entry[u].lBytesInRes ),
        (unsigned)I386PE_INT16_TO_HOST( &pIconDir->entry[u].wNameOrdinal )
        );

        const Resource * pIcon = pResList->find( MAKEINTRESOURCE( I386PE_INT16_TO_HOST( &pIconDir->entry[u].wNameOrdinal ) ), MAKEINTRESOURCE( RT_ICON ) );

        if ( 0 != pIcon ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon %u loaded, size: %u" ), (unsigned)I386PE_INT16_TO_HOST( &pIconDir->entry[u].wNameOrdinal ), I386PE_INT32_TO_HOST( &pIcon->Id.pHeader->uiSize ) );

            const BITMAPINFO * pBI = (const BITMAPINFO *)pIcon->Id.pData;

            DBG_MSG( DBG_GENERAL_INFORMATION,
            TEXT( "Bitmap data - biSize: %u, biWidth: %u, biHeight: %u, biPlanes: %u, biBitCount: %u, biCompression: %u, biSizeImage: %u, biXPelsPerMeter: %u, biYPelsPerMeter: %u, biClrUsed: %u, biClrImportant: %u" ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biSize ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ),
            (unsigned)I386PE_INT16_TO_HOST( &pBI->bmiHeader.biPlanes ),
            (unsigned)I386PE_INT16_TO_HOST( &pBI->bmiHeader.biBitCount ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biCompression ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biSizeImage ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biXPelsPerMeter ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biYPelsPerMeter ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biClrUsed ),
            (unsigned)I386PE_INT32_TO_HOST( &pBI->bmiHeader.biClrImportant )
            );

            switch( I386PE_INT16_TO_HOST( &pBI->bmiHeader.biBitCount ) ) {

                case 0: /* 24 bit true colour */

                    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon - 0 bit colour ???" ) );
                    break;

                case 1:
                case 4:
                case 8:
                case 24:
                case 32:

                    BMP.push_back( ResIcon( pBI ) );
                    break;

                default:

                    break;

            }

        }

    }

}


const IBitmap * Icon::GetBmp( void ) const {

#if 0
    for ( const auto & icon : BMP ) {

        /* TODO: Evaluate each image for its correspondance to the output */
        return &icon;

    }

//    return 0;
#endif

    /* TODO: For now, grab last image (therefore highest-resolution) found */

    if ( BMP.size() < 1 ) {

        return 0;

    }

    return & BMP.back();

}


const Icon * IconList::open( HMODULE hInst, LPCTSTR resname ) {

    /* Look in the resources, and look for this */
    const ResourceList * pResources = reinterpret_cast<const ResourceList *>( hInst );

    const Resource * pResource = pResources->find( resname, RT_GROUP_ICON );

    /* If found in the resources, look in the list to see if an existing icon is already using this. */
    if ( 0 == pResource ) {

        return 0;

    }

    const auto i = find( pResource );

    if ( end() != i ) {

        return &i->second;

    }

    /* If not found, create it. */
    Icon icon( pResources, pResource );

    auto f = emplace( pResource, icon );

    DBG_MSG( DBG_ERROR, TEXT( "Make icon: %s" ), f.second ? "Success" : "Failed" );

    if ( false == f.second ) {

        return 0;

    }

    return &f.first->second;

}


BOOL DrawIcon( HDC hDC, int x, int y, HICON hIcon ) {

    if ( ( NULL == hDC ) || ( NULL == hIcon ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "DC (%lX) OR HICON (%lX) NULL" ), hDC, hIcon );
        return false;

    }

    DC * pDC = reinterpret_cast<DC *>( hDC );

    const Icon * pIcon = reinterpret_cast<const Icon *>( hIcon );

    const IBitmap * pBMP = pIcon->GetBmp();

    if ( 0 == pBMP ) {

        DBG_MSG( DBG_ERROR, TEXT( "NO BITMAP" ) );
        return false;

    }

    StartPoints();

    POINT pt;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "DrawIcon at %d,%d (cx=%lu,cy=%lu)" ), x, y, pBMP->Width(), pBMP->Height() );

    for ( pt.y = 0; pt.y < (LONG)pBMP->Height(); pt.y++ ) {

        for ( pt.x = 0; pt.x < (LONG)pBMP->Width(); pt.x++ ) {

            COLORREF c;

            if ( pBMP->GetPixel( pt, c ) ) {

                if ( 0 != GetAValue( c ) ) {

                    continue;

                }

                POINT ptDC;

                ptDC.x = x + pt.x;
                ptDC.y = y + pt.y;

                pDC->SetPixel( ptDC, c, c );

            }

        }

    }

    EndPoints();

    PostRefresh();
    RasterUpdate();

    return true;

}


BOOL DrawIconEx( HDC hDC, int x, int y, HICON hIcon, int cx, int cy, UINT uAniFrame, HBRUSH hBr, UINT uFlags ) {

    return DrawIcon( hDC, x, y, hIcon );

}
