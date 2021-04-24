

#include "ywin.h"


typedef struct {

    LPCTSTR pszName;
    Font_Header * pHdr;

} LocateFont;


static BOOL CALLBACK EnumFontResNamesProc( HMODULE hModule, LPCTSTR restype, LPTSTR resname, LONG_PTR lParam ) {

    LocateFont * plf = (LocateFont *)lParam;

    HRSRC hRes = FindResource( hModule, resname, restype );

    HGLOBAL h = LoadResource( hModule, hRes );

    Font_Header * pHdr = (Font_Header *)LockResource( h );

    if ( 0 != _tcscmp( plf->pszName, pHdr->szName ) ) {

        FreeResource( h );
        return true;

    }

    plf->pHdr = pHdr;

    return false;

}





void Font::_create( void ) {

    DBG_MSG( DBG_FONT_SYSTEM,
        TEXT( "Font %lX - Point size: %u, flags: %u, AvgCharHeight: %u, AvgCharWidth: %u, MaxCharHeight: %u, MaxCharWidth: %u, Leading: %u, typeface name: '%s'" ),
        this,
        pHdr->uWeight,
        pHdr->flags,
        pHdr->uAvgCharHeight,
        pHdr->uAvgCharWidth,
        pHdr->uMaxCharHeight,
        pHdr->uMaxCharWidth,
        pHdr->uLeading,
        pHdr->szName
    );

//    DBG_DMP( DBG_DATA_DUMPS, (char *)pFontHdr, sizeof( Font_Header ) + 128 );

    const unsigned * p = (const unsigned *)( pHdr->szName + strlen( pHdr->szName ) + 1 );

    unsigned u = *p;

    DBG_MSG( DBG_FONT_SYSTEM, TEXT( "Font reports %u character set" ), u );

    /* Increment so it points to the first char */
    p++;

    const chardef * pChardef = (chardef *)p;

    for ( ; u ; u-- ) {

#if 0
        DBG_MSG(
            DBG_FONT_SYSTEM,
            TEXT( "Character (%u), Width: %u, Height: %u, %u scanlines" ),
            (unsigned)pChardef->c, pChardef->cx, pChardef->cy, pChardef->uscanlinecount
        );
#endif

//        glyphs.insert( pChardef->c, pChardef );

        glyphs.insert( glyphs.end(), FacePair( pChardef->c, pChardef ) );

        pChardef = (chardef *)(((unsigned char *)pChardef) + sizeof( chardef ) + ( sizeof( COLORREF ) * ( pChardef->cx * pChardef->cy ) ));

    }

#if 0
    /* Define space */
    spc.c     = (TCHAR)' ';
    spc.cx    = pHdr->uAvgCharWidth;
    spc.cy    = pHdr->uAvgCharHeight;
    spc.pFace = Bitmap::alloc( spc.cx, spc.cy, 1, ( Font_Header::monochrome == hdr.flags ) ? 1 : 32, NULL ) ;

    /* Define dim block */
    POINT pt;

    dimblock.c     = (TCHAR)-1;
    dimblock.cx    = hdr.uAvgCharWidth;
    dimblock.cy    = hdr.uAvgCharHeight;
    dimblock.pFace = Bitmap::alloc( dimblock.cx, dimblock.cy, 1, ( Font_Header::monochrome == hdr.flags ) ? 1 : 32, NULL ) ;

    for ( pt.y = 0; pt.y < dimblock.cy; pt.y++ ) {

        for ( pt.x = 0; pt.x < dimblock.cx; pt.x++ ) {

            dimblock.pFace->SetPixel( pt, ( ( pt.x + pt.y ) % 2 ) ? RGB( 0, 0, 0 ) : RGB( 128, 128, 128 ) );

        }

    }
#endif
}







const Font * FontList::open( const ResourceList & resources, LPCTSTR pszName ) {

    /*
        look in the current list.
        If not found, enumerate reources, looking for font name.
        If found, a new font is created using that resource's physical address,
        and is added to the list.

    */

    const auto i = find( pszName );

    if ( end() != i ) {

        return &i->second;

    }

    DBG_MSG( DBG_FONT_SYSTEM, TEXT( "Warning: Font '%s' not in existing list" ), pszName );

    LocateFont lf;

    lf.pszName = pszName;
    lf.pHdr = 0;

    if ( ! EnumResourceNames( (HMODULE)&resources, MAKEINTRESOURCE( RESTYP_FONT ), EnumFontResNamesProc, (LONG_PTR)&lf ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "Error: No fonts in resources" ), pszName );
        return 0;

    }

    if ( 0 == lf.pHdr ) {

        DBG_MSG( DBG_ERROR, TEXT( "Error: Font '%s' not in resources" ), pszName );
        return 0;

    }

    /* Make the font */
    Font font( lf.pHdr );
    TSTRING name( pszName );
    auto f = emplace( name, font );

    DBG_MSG( DBG_ERROR, TEXT( "Make font '%s': %s" ), pszName, f.second ? "Success" : "Failed" );

    if ( false == f.second ) {

        return 0;

    }

    f.first->second._create();

    return &f.first->second;

}


HFONT CreateFontIndirect( const LOGFONT * plf ) {

    const Font * pFont = fonts.Find( plf->lfFaceName );

    return (HFONT)pFont;

}


HFONT CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace ) {

    LOGFONT lf;

    ZeroMemory( &lf, sizeof( lf ) );

    lf.lfCharSet        = fdwCharSet;
    lf.lfClipPrecision  = fdwClipPrecision;
    lf.lfEscapement     = nEscapement;

    strncpy( lf.lfFaceName, lpszFace, Dim( lf.lfFaceName ) - 1 );

    lf.lfHeight         = nHeight;
    lf.lfItalic         = fdwItalic;
    lf.lfOrientation    = nOrientation;
    lf.lfOutPrecision   = fdwOutputPrecision;
    lf.lfPitchAndFamily = fdwPitchAndFamily;
    lf.lfQuality        = fdwQuality;
    lf.lfStrikeOut      = fdwStrikeOut;
    lf.lfUnderline      = fdwUnderline;
    lf.lfWeight         = fnWeight;
    lf.lfWidth          = nWidth;

    return CreateFontIndirect( &lf );

}


int EnumFonts( HDC hDC, LPCTSTR pszFaceName, FONTENUMPROC pFontFunc, LPARAM lParam ) {

    LOGFONT lf;
    TEXTMETRIC tm;

    int iRet = 0;

    for ( FontList::const_iterator i = fonts.begin(); fonts.end() != i; ++i ) {

        ZeroMemory( &lf, sizeof( lf ) );
        ZeroMemory( &tm, sizeof( tm ) );

        const Font * pFont = &i->second;

        pFont->GetMetrics( &tm );

        _tcsncpy( lf.lfFaceName, pFont->pHdr->szName, Dim( lf.lfFaceName ) - 1 );
        lf.lfWeight = pFont->pHdr->uWeight;
        lf.lfHeight = tm.tmHeight;

        iRet = pFontFunc( &lf, &tm, RASTER_FONTTYPE, lParam );

        if ( 0 == iRet ) {

            break;

        }

    }

    return iRet;

}
