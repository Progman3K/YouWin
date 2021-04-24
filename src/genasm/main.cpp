

#include "project.h"


static FILE * Input = stdin;
static FILE * Output = stdout;

static const char * pszRequestedAssembler = "gas";

static const char * pszInputfile = 0;

static AsmFormat asmformat = AsmFormatGAS;

static const char * pszSymbol = "_binary_resource_res";

static int nLiteralsPerLine = 32;

static const char * pszApp = "";


static void PrintHelp( void ) {

    fprintf( stderr, "\n%s [-a fbe|gas|osx] [-i input_file] [-o output_file] [-l number_of_chars_per_literal_line] [-s symbol_to_create] | -h"
        "\n    If not specified,"
        "\n    assembler will default to gas"
        "\n        in the case of gas and osx, the input_file must be specified"
        "\n    input_file will default to stdio"
        "\n    output_file will default to stdout"
        "\n    number_of_chars_per_literal_line will default to 32"
        "\n    symbol_to_create will default to _binary_resource_res"
        "\n        It is important to note that whatever name is supplied,"
        "\n        an additional symbol with the suffix _size will also be created;"
        "\n        an int that contains the binary object's size."
        "\n    -h will print this help.\n", pszApp
    );

}


static int outputline( int nLPL, FILE * inputfile, FILE * outputfile ) {

    /* print out bytes */
    for ( int i = 0; i < nLPL; i++ ) {

        int c = fgetc( inputfile );

        if ( EOF == c ) {

            return -1;

        }

        if ( 0 == i ) {

            /* Output line prefix */
            fprintf( outputfile, "    .byte " );

        }

        fprintf( outputfile, "%s0x%02X", i > 0 ? "," : "", (unsigned)c );

    }

    return 0;

}


static int emitasmfbe( const char * pszsym, int nLPL, FILE * inputfile, FILE * outputfile ) {

    /* Print header */
    fprintf( outputfile, ".global %s\n", pszsym );
    fprintf( outputfile, ".global %s_size\n", pszsym );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".section .rodata,\"a\"\n" );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".balign 4\n" );
    fprintf( outputfile, "%s:\n", pszsym );

    for( ; ! feof( inputfile ); ) {

        int i = outputline( nLPL, inputfile, outputfile );

        if ( 0 == i ) {

            fprintf( outputfile, "\n" );

        }

    }

    fprintf( outputfile, "\n" );

    /* Print footer */
    fprintf( outputfile, "1:\n" );
    fprintf( outputfile, "%s_size:\n", pszsym );
    fprintf( outputfile, ".int 1b - %s\n", pszsym );

    return 0;

}


static int emitasmgas( const char * pszsym, int nLPL, const char * inputfile, FILE * outputfile ) {

    /* Print header */
    fprintf( outputfile, ".global %s\n", pszsym );
    fprintf( outputfile, ".global %s_size\n", pszsym );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".section .rodata\n" );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".balign 4\n" );
    fprintf( outputfile, "%s:\n", pszsym );

    fprintf( outputfile, "    .incbin \"%s\"\n", inputfile );

    /* Print footer */
    fprintf( outputfile, "1:\n" );
    fprintf( outputfile, "%s_size:\n", pszsym );
    fprintf( outputfile, ".int 1b - %s\n", pszsym );

    return 0;

}


static int emitasmosx( const char * pszsym, int nLPL, const char * inputfile, FILE * outputfile ) {

    /* Print header */
    fprintf( outputfile, ".global %s\n", pszsym );
    fprintf( outputfile, ".global %s_size\n", pszsym );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".section __DATA, __const\n" );
    fprintf( outputfile, "#\n" );
    fprintf( outputfile, ".balign 4\n" );
    fprintf( outputfile, "%s:\n", pszsym );

    fprintf( outputfile, "    .incbin \"%s\"\n", inputfile );

    /* Print footer */
    fprintf( outputfile, "1:\n" );
    fprintf( outputfile, "%s_size:\n", pszsym );
    fprintf( outputfile, ".int 1b - %s\n", pszsym );

    return 0;

}


static bool ProcessArgs( int iArgc, char * pArgv[] ) {

    const char * pszOutputfile = 0;

    int i;
    while ( -1 != ( i = getopt( iArgc, pArgv, "a:i:o:l:s:h" ) ) ) {

        switch( i ) {

            /* Assembler format */
            case 'a':

                pszRequestedAssembler = optarg;

                if ( 0 == strcmp( "fbe", pszRequestedAssembler ) ) {

                    asmformat = AsmFormatFBE;
                    break;

                } else if ( 0 == strcmp( "gas", pszRequestedAssembler ) ) {

                    asmformat = AsmFormatGAS;
                    break;

                } else if ( 0 == strcmp( "osx", pszRequestedAssembler ) ) {

                    asmformat = AsmFormatOSX;
                    break;

                }

                fprintf( stderr, "\nUNKNOWN ASSEMBLER (%s): valid options are fbe gas osx\n", pszRequestedAssembler );
                PrintHelp();
                return false;

            /* Input file */
            case 'i':

                pszInputfile = optarg;
                break;

            /* Output file */
            case 'o':

                pszOutputfile = optarg;
                break;

            /* Numbers of chars per literal line */
            case 'l': {

                    const char * pszNum = optarg;

                    int n = atoi( pszNum );

                    if ( n > 0 ) {

                        nLiteralsPerLine = n;

                    }

                }
                break;

            /* The variable name that will be created */
            case 's':

                pszSymbol = optarg;
                break;


            /* Print error */
            default:

                fprintf( stderr, "\nUNKNOWN OPTION (%d): %c\n", i, i );

            /* Print help */
            case 'h':

                PrintHelp();
                return false;

        }

    }

    FILE * fIn = 0;
    if ( 0 != pszInputfile ) {

        fIn = fopen( pszInputfile, "r" );

        if ( 0 == fIn ) {

            fprintf( stderr, "\nUNABLE TO OPEN INPUT FILE '%s'\n", pszInputfile );
            return false;

        }

    }

    FILE * fOut = 0;
    if ( 0 != pszOutputfile ) {

        fOut = fopen( pszOutputfile, "w" );

        if ( 0 == fOut ) {

            fprintf( stderr, "\nUNABLE TO OPEN OUTPUT FILE '%s'\n", pszOutputfile );

            if ( 0 != fIn ) {

                /* Clean up first */
                fclose( fIn );

            }

            return false;

        }

        Output = fOut;

    }

    if ( 0 != fIn ) {

        Input = fIn;

    }

    return true;

}


static void noinputfile( const char * pszAsm ) {

    fprintf( stderr, "\nFOR ASSEMBLER (%s) INPUT_FILE MUST BE SPECIFIED\n", pszAsm );
    PrintHelp();

}


int main( int iArgC, char * argv[] ) {

    pszApp = argv[0];

    if ( 0 < iArgC ) {

        /* Parse arguments eventually
         * -i input_file
         * -o output_file
         *  */
        if ( ! ProcessArgs( iArgC, argv ) ) {

            return -1;

        }

    }

    int iRet = 0;

    switch( asmformat ) {

        case AsmFormatFBE:

            emitasmfbe( pszSymbol, nLiteralsPerLine, Input, Output );
            break;

        case AsmFormatGAS:

            if ( 0 == pszInputfile ) {

                noinputfile( pszRequestedAssembler );
                iRet = -1;
                break;

            }

            emitasmgas( pszSymbol, nLiteralsPerLine, pszInputfile, Output );
            break;

        case AsmFormatOSX:

            if ( 0 == pszInputfile ) {

                noinputfile( pszRequestedAssembler );
                iRet = -1;
                break;

            }

            emitasmosx( pszSymbol, nLiteralsPerLine, pszInputfile, Output );
            break;

    }

    fclose( Input );
    fclose( Output );

    return iRet;

}
