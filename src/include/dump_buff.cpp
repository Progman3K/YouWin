



static unsigned AppendSegment( TCHAR * lpucDestination, unsigned char const * lpucSource, unsigned long ulSizeOfSegment ) {

    unsigned long ul;
    TCHAR         szByte[16];

    for ( ul = 0; ul < ulSizeOfSegment; ul++ ) {

        _stprintf( szByte,
#ifdef UNICODE
                   Dim( szByte ),
#endif
                   TEXT( "%02lX" ), (unsigned long)(*lpucSource) );

        lpucSource++;

        _tcscat( lpucDestination, szByte );

        if ( ul < ( ulSizeOfSegment - 1 ) ) {

            _tcscat( lpucDestination, TEXT( " " ) );

        }

    }

    return (unsigned)_tcslen( lpucDestination );

}


static bool bIsPrintable( unsigned char c ) {

    if ( ' ' > c ) {

        /* Non printable */
        return false;

    }

#ifdef UNICODE
    if ( 0x80 <= c ) {

        /* Non printable */
        return false;

    }
#endif

    /* Printable */
    return true;

}


static unsigned long LiteralAppend( TCHAR * lpcDestination, unsigned char const * lpucSource, unsigned long ulLen ) {

    unsigned long	ul;

    for( ul = 0; ul < ulLen; ul++ ) {

        if ( bIsPrintable( lpucSource[ ul ] ) ) {

            /* Printable */
            lpcDestination[ ul ] = /* (TCHAR) */lpucSource[ ul ];

        } else {

            /* Non printable */
            lpcDestination[ ul ] = '.';

        }

    }

    return ulLen;

}


static bool InternalDumpBuffer( TSTRING /* dumpbuffer */ & sDumpBuffer, unsigned char const * lpucBuffer, unsigned long ulBufferLen, unsigned long ulSegmentLength, unsigned long ulNumberOfSegmentsPerLine, unsigned long * lpdwLen ) {

    unsigned long         ulSizeOfOneLine;
    unsigned long         ulNumlines;
    unsigned long         ulRemainingDumpLength;
    unsigned long         ulLenDumped;
    unsigned long         ulSegmentPrinted;

    TCHAR *               lpucDumpBuffer;
    TCHAR *               lpucDestinationCursor;
    unsigned char const * lpucSourceCursor;

    /* R/O statics. */
    static TCHAR          szSegOff[] = TEXT( "%04lX:%04lX  " );
    static TCHAR          szDash[]   = TEXT( "-" );
    static TCHAR          szSpacer[] = TEXT( "  " );
    static TCHAR          szEOL[]    = TEXT( "\n" );
    static TCHAR          szNul[]    = TEXT( "" );

    TCHAR                 szHeader[ Dim( szSegOff ) ];

    /*
        Calculate the size of a line.

        A line has the following format (assuming 2 segment per line and a segment lenght of 8):

        BF2A5:0000  05 08 09 23 F1 27 32 FF-05 08 09 23 F1 27 32 FF   ....�..|@....�..|@

        Segment:Offset, Hex Paragraph Dump, Dash, Hex Paragraph Dump, ASCII Dump, newline, nul character (last line only).

    */

    ulSizeOfOneLine =   sizeof( szSegOff )                                                                                                                // "BF2A:0000"
                        //                                  Each Hexchar            Blank spaces between hexchars
                        + ( ulNumberOfSegmentsPerLine * ( ( sizeof( TCHAR ) * ( ulSegmentLength * 2 ) ) + ( sizeof( TCHAR ) * ( ulSegmentLength - 1 ) ) ) ) // "05 08 09 23 F1 27 32 FF"
                        + ( ( ulNumberOfSegmentsPerLine - 1 ) * sizeof( szDash ) )                                                                        // "-"
                        + sizeof( szSpacer )                                                                                                              // "   "
                        + ( ulNumberOfSegmentsPerLine * ( sizeof( TCHAR ) * ulSegmentLength ) )                                                            // "....�..|@....�..|@"
                        + sizeof( szEOL ) + sizeof( szNul );                                                                                              // "\n"

    /* Calculate how many lines. */
    ulNumlines = 1 + ( ulBufferLen / ulSegmentLength );

    /* Allocate the buffer for all the text plus a newline at the beginning and end. */
    // lpucDumpBuffer = (char *)GlobalAllocPtr( GHND, ( ulNumlines * ulSizeOfOneLine ) + ( sizeof( szEOL ) * 2 ) );

    sDumpBuffer.resize( ( ulNumlines * ulSizeOfOneLine ) + ( sizeof( szEOL ) * 2 ) );

    lpucDumpBuffer = &( *( sDumpBuffer.begin() ) );

    if ( NULL == lpucDumpBuffer ) {

        /* Allocation failure. */
        return false;

    }

    /* Set up return values. */
    *lpdwLen = ( ulNumlines * ulSizeOfOneLine );

    lpucDestinationCursor = (TCHAR *)lpucDumpBuffer;

    /* Put newline at the beginning */
    _tcscat( lpucDestinationCursor, szEOL );
    lpucDestinationCursor += _tcslen( szEOL );

    lpucSourceCursor = lpucBuffer;
    ulLenDumped      = 0;

    do {

        /* Append preamble */
        unsigned long ulLen = (unsigned)_stprintf( szHeader,
#ifdef UNICODE
                                     Dim( szHeader ),
#endif
                                     szSegOff, (unsigned long)HIWORD( ulLenDumped ), (unsigned long)LOWORD( ulLenDumped ) );

        _tcscat( lpucDestinationCursor, szHeader );

        /* Point past preamble. */
        lpucDestinationCursor += ulLen;

        /* Reset the counter for the literal dump at the end of the line. */
        unsigned long ulLiteralLen = 0;

        /* Print the segments for the line. */
        for ( ulSegmentPrinted = 0; ulSegmentPrinted < ulNumberOfSegmentsPerLine; ulSegmentPrinted++ ) {

            ulRemainingDumpLength = ( ulBufferLen - ulLenDumped );

            if ( ulRemainingDumpLength >= ulSegmentLength ) {

                /* A FULL segment is to be printed. */

                /* Output segment. */
                ulLen = AppendSegment( lpucDestinationCursor, lpucBuffer + ulLenDumped, ulSegmentLength );
                ulLiteralLen += ulSegmentLength;

                lpucDestinationCursor += ulLen;
                ulLenDumped           += ulSegmentLength;

                if ( ( ( 1 + ulSegmentPrinted ) < ulNumberOfSegmentsPerLine ) && ( ( ulBufferLen - ulLenDumped ) > 0 ) ) {

                    /* Put a dash between them. */
                    _tcscat( lpucDestinationCursor, szDash );
                    lpucDestinationCursor += _tcslen( szDash );

                }

            } else {

                /* An INCOMPLETE segment is to be printed. */

                ulLen = AppendSegment( lpucDestinationCursor, lpucBuffer + ulLenDumped, ulRemainingDumpLength );
                ulLiteralLen          += ulRemainingDumpLength;
                lpucDestinationCursor += ulLen;
                ulLenDumped           += ulRemainingDumpLength;

                /* Pad remainder of line with spaces. */
                ulLen = ( ulSegmentLength - ulRemainingDumpLength ) + ( ( ulSegmentLength - ulRemainingDumpLength ) * 2 );

                for ( unsigned uPadOffset = 0; uPadOffset < ulLen; uPadOffset++ ) {

                    *lpucDestinationCursor = ' ';
                    lpucDestinationCursor++;

                }

            }

        }

        /* Add a few blanks. */
        _tcscat( lpucDestinationCursor, szSpacer );
        lpucDestinationCursor += _tcslen( szSpacer );

        /* Put the actual characters (literals) at the end of the line. */
        LiteralAppend( lpucDestinationCursor, lpucSourceCursor, ulLiteralLen );
        lpucDestinationCursor += ( ulSegmentLength * ulNumberOfSegmentsPerLine );

        /* Put EOL. */
        _tcscat( lpucDestinationCursor, szEOL );
        lpucDestinationCursor += _tcslen( szEOL );

        lpucSourceCursor      += ( ulSegmentLength * ulNumberOfSegmentsPerLine );

    } while( ulLenDumped < ulBufferLen );

    /* Add final newline. */
    //strcat( lpucDumpBuffer, szEOL );

    // sDumpBuffer.append( lpucDumpBuffer );

    return true;

}


void DBGTRACE_API DumpBufferFree( const char * lpcBuffer ) {

    if ( NULL != lpcBuffer ) {

        free( (void *)lpcBuffer );

    }

}


const char * DBGTRACE_API DumpBuffer( unsigned char const * lpucBuffer, unsigned long ulBufferLen, unsigned long ulSegmentLength, unsigned long ulNumberOfSegmentsPerLine, unsigned long * lpdwLen ) {

    TSTRING /* dumpbuffer */ sDumpbuffer;

    if ( ! InternalDumpBuffer( sDumpbuffer, lpucBuffer, ulBufferLen, ulSegmentLength, ulNumberOfSegmentsPerLine, lpdwLen ) ) {

        return NULL;

    }

    char * psz = (char *)calloc( sDumpbuffer.size() + 1, sizeof( sDumpbuffer[0] ) );

    if ( NULL == psz ) {

        return NULL;

    }

    /* Copy over the data */
//    sDumpbuffer.copy( psz, sDumpbuffer.size() );
    for( unsigned u = 0; u < sDumpbuffer.size(); u++ ) {

        *( psz + u ) = sDumpbuffer[u];

    }

    return psz;

}


extern "C" void DBGTRACE_API DBG_TRACE_DUMP_BUFFER( unsigned uLineNo, const char * pszFile, unsigned long dwDebugChannelsBitmap, void const * lpucBuffer, unsigned long ulBufferLen ) {

    if ( 0 == ulBufferLen ) {

        return;

    }

//    if ( ! ( dwDebugChannelsBitmap & g_dwDebugBitmap ) ) {

        /* Not interested in this channel. */
//        return;

//    }

    TSTRING /* dumpbuffer */ sDumpbuffer;

    unsigned long dwLen;
    bool bDumped = InternalDumpBuffer( sDumpbuffer, (const unsigned char *)lpucBuffer, ulBufferLen, 8, 2, &dwLen );

    if ( ! bDumped ) {

        return;

    }

    dwLen = (unsigned)sDumpbuffer.size();

    // DBG_TRACE( dwDebugChannelsBitmap, sDumpbuffer.c_str() );

    dbgtrace( uLineNo, pszFile, dwDebugChannelsBitmap, sDumpbuffer.c_str() );

}
