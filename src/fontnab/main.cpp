

#include "project.h"
#include <dbgtrace.cpp>


const char * pszApp = "";


void PrintHelp( void ) {

    fprintf( stderr, "\n%s [-e] | -h | [-f fontname] ..."
        "\n    If no options specified,"
        "\n    will write out all font definitions."
        "\n    -e Will enum font info to the console"
        "\n    -h Will print this help.\n", pszApp
    );

}


int fputsz( const TCHAR * psz, FILE * pFile ) {

    _fputts( psz, pFile );
    _fputts( EOL, pFile );

    return 0;

}


const TCHAR * ltoa( LONG l, TCHAR * pBuf, size_t size ) {

    _sntprintf( pBuf, size, TEXT( "%ld" ), l );
    return pBuf;

}


static void PrintFontHeader( const LOGFONT * plf, const TEXTMETRIC * ptm, FILE * pFile ) {

    TCHAR szNum[64];

    memset( szNum, 0, sizeof( szNum ) );

    _fputts( ltoa( plf->lfWeight, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( "  Point" ), pFile );

    _fputts( ltoa( Font_Header::grayscale, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( "  flags" ), pFile );

    _fputts( ltoa( ptm->tmHeight, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( " Average character height" ), pFile );

    _fputts( ltoa( ptm->tmAveCharWidth, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( " Average character width" ), pFile );

    _fputts( ltoa( ptm->tmHeight, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( " Maximum character height" ), pFile );

    _fputts( ltoa( ptm->tmMaxCharWidth, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( " Maximum character width" ), pFile );

    _fputts( ltoa( ptm->tmExternalLeading, szNum, Dim( szNum ) - 1 ), pFile );
    fputsz( TEXT( " Leading" ), pFile );

    fputsz( plf->lfFaceName, pFile );

    fputsz( TEXT( "" ), pFile );

}


int CALLBACK FontInfoProc( const LOGFONT * plf, const TEXTMETRIC * ptm, DWORD dwType, LPARAM lpData ) {

    if ( 90 < ptm->tmHeight ) {

        return true;

    }

    PrintFontHeader( plf, ptm, stdout );

    return true;

}


int CALLBACK FontCaptureProc( const LOGFONT * plf, const TEXTMETRIC * ptm, DWORD dwType, LPARAM lParam ) {

//    Font font;
    TSTRING outputfilename;

    outputfilename.assign( plf->lfFaceName );
    outputfilename.replacewith( ' ', '_' );
    outputfilename.append( TEXT( ".tfnt" ) );

    FILE * pFile = fopen( outputfilename.charz_str(), "wt" );

    PrintFontHeader( plf, ptm, pFile );

    // Get DC to display
    HDC hDC = CreateCompatibleDC( NULL );

    HFONT hFont = CreateFontIndirect( plf );

    HFONT hOldFont = SelectFont( hDC, hFont );

    // for each font, create a dc with a width and height set to the max of the font
    HBITMAP hBMP = CreateCompatibleBitmap( GetDC( NULL ), ptm->tmMaxCharWidth, plf->lfHeight );

    HBITMAP hOldBMP = SelectBitmap( hDC, hBMP );

    COLORREF OldFG = SetTextColor( hDC, RGB( 255, 255, 255 ) );
    COLORREF OldBk = SetBkColor( hDC, 0 );

    RECT r;

    r.left   = 0;
    r.top    = 0;
    r.right  = ptm->tmMaxCharWidth;
    r.bottom = plf->lfHeight;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "hDC %lX, font %s hFont %lX, hOldFont %lX, hBMP %lX, hOldBMP %lX, OldFG %lX, OldBk %lX, ptm->tmMaxCharWidth %d, plf->lfHeight %ld, sizeof TCHAR %u" ), hDC, plf->lfFaceName, hFont, hOldFont, hBMP, hOldBMP, OldFG, OldBk, (long)ptm->tmMaxCharWidth, (long)plf->lfHeight, sizeof( TCHAR ) );

    TCHAR szChar[sizeof( TCHAR ) + 1];

    for ( TCHAR u = ( ' ' + 1 ); u < 256; u++ ) {

        // Wipe the DC contents
        FillRect( hDC, &r, GetStockBrush( BLACK_BRUSH ) );

        memset( szChar, 0, sizeof( szChar ) );

        // Print the character
        szChar[0] = u;
        TextOut( hDC, 0, 0, szChar, 1 );

        // Read back the bitmap
        int iMaxWidth = 0;

        std::vector<TSTRING> scanlines;

        for ( int y = r.top; y < r.bottom; y++ ) {

            TSTRING Line;

            for ( int x = r.left; x < r.right; x++ ) {

                COLORREF c = GetPixel( hDC, x, y );

                Line.append( 0 < x ? TEXT( " " ) : TEXT( "" ) );

                TCHAR szHex[16];

                memset( szHex, 0, sizeof( szHex ) );

                _sntprintf( szHex, Dim( szHex ) - 1, TEXT( "%08lX" ), c );

                Line.append( szHex );

                if ( ( 0 != c ) && ( ( x + 1 ) > iMaxWidth ) ) {

                    iMaxWidth = x + 1;

                }

            }

            // for each scanline, emit a string representing the dots in the glyph
            scanlines.push_back( Line );

            Line.clear();

        }

        // Filter out any non-printing glyphs
        if ( 0 < iMaxWidth ) {

            TCHAR szDec[32];

            memset( szDec, 0, sizeof( szDec ) );

            // Print the character code to the file
            _sntprintf( szDec, Dim( szDec ) - 1, TEXT( "%u" ), u );

            fputsz( szDec, pFile );

            // Truncate the bitmap
            for ( size_t u = 0; u < scanlines.size(); u++ ) {

                scanlines.at( u ).resize( ( iMaxWidth * 8 ) + ( iMaxWidth - 1 ) );
                fputsz( scanlines.at( u ).c_str(), pFile );

            }

            fputsz( TEXT( "" ), pFile );

        }

        scanlines.clear();

    }

    SetBkColor( hDC, OldBk );

    SetTextColor( hDC, OldFG );

    SelectBitmap( hDC, hOldBMP );

    DeleteBitmap( hBMP );

    SelectFont( hDC, hOldFont );

    DeleteFont( hFont );

    DeleteDC( hDC );

    fclose( pFile );

    return true;

}


#ifdef __MINGW32__
int main( int iArgC, char * Argv[] ) {
    pszApp = Argv[0];
#else
int _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow ) {
    int iArgC = 0;
    std:vector<TSTRING> Argv;
#endif

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "FONTNAB" ) );

    bool bEnumAllFonts = true;
    int iRet = 0;

    int i;
    while ( -1 != ( i = getopt( iArgC, Argv, "f:e::h" ) ) ) {

        switch( i ) {

            /* Enum fonts info */
            case 'e':

                return EnumFonts( GetDC( NULL ), NULL, FontInfoProc, 0 );

            case 'f': {

                    TSTRING font;

                    font.absorb( optarg );

                    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Font requested: %s" ), font.c_str() );
                    iRet += EnumFonts( GetDC( NULL ), font.c_str(), FontCaptureProc, 0 );

                }
                bEnumAllFonts = false;
                break;

            /* Print error */
            default:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "UNKNOWN OPTION (%d): %c" ), i, i );
                fprintf( stderr, "\nUNKNOWN OPTION (%d): %c\n", i, i );

            /* Print help */
            case 'h':

                PrintHelp();
                return -1;

        }

    }

    if ( bEnumAllFonts ) {

        // Enumerate the fonts
        return EnumFonts( GetDC( NULL ), NULL, FontCaptureProc, 0 );

    }

    return iRet;

}
