

#include "project.h"


int changesuffix( std::string & filename, const char * pSuffix ) {

    size_t dotpos = filename.rfind( '.' );

    if ( filename.npos != dotpos ) {

        filename.replace( dotpos + 1, filename.npos, pSuffix );

    } else {

        filename.append( "." );
        filename.append( pSuffix );

    }

    return 0;

}


#ifdef _WIN32
int _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow ) {
#else
int main( int iArgC, char * argv[] ) {
#endif

    if ( 1 >= iArgC ) {

        fprintf( stderr, "%s - NOT ENOUGH ARGUMENTS", argv[0] );
        fprintf( stderr, "EX: %s fontfile.tfnt [fontfile2.tfnt ...]", argv[0] );
        return -1;

    }

    for (int i = 1; i < iArgC; i++ ) {

        FILE * pFile;

        std::string inputfilename;

        inputfilename.assign( argv[i] );

        // Open .TFNT file passed as argument
        pFile = fopen( inputfilename.c_str(), "rt" );

        if ( NULL == pFile ) {

            fprintf( stderr, "UNABLE TO OPEN SOURCE [%s]", inputfilename.c_str() );
            return -1;

        }

        // Dump font data
        Font_Header * pHdr = (Font_Header *)malloc( sizeof( Font_Header ) );
        unsigned totalsize = sizeof( Font_Header );

        int iRet = ReadFontData( pFile, pHdr, totalsize );

        Font font( pHdr );
        if ( 0 != ReadCharset( pFile, &font ) ) {

            return -1;

        }

        fclose( pFile );

        if ( iRet < 0 ) {

            fprintf( stderr, "ERROR PARSING FONT DEFINITION [%s]", inputfilename.c_str() );
            return iRet;

        }

        std::string outputfilename;

        outputfilename = inputfilename;
        changesuffix( outputfilename, "fnt" );

        pFile = fopen( outputfilename.c_str(), "wb" );

        if ( NULL == pFile ) {

            fprintf( stderr, "UNABLE TO OPEN DESTINATION [%s]", outputfilename.c_str() );
            return -1;

        }

        // Now write compiled font back out as a binary file.
        iRet = WriteFontData( pFile, &font, totalsize );
        fclose( pFile );

        if ( iRet < 0 ) {

            fprintf( stderr, "ERROR WRITING DESTINATION [%s]", outputfilename.c_str() );
            return -1;

        }

    }

    return 0;

}
