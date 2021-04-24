

#ifndef DEBUG_TRACE_LIB_H
#define DEBUG_TRACE_LIB_H


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


#include <stdint.h>
#include <ctime>
#include <limits.h>
#include <tchar.h>


#ifndef ARRAY_SIZE
#define ARRAY_SIZE( array_x ) ( sizeof( array_x ) / sizeof( array_x[0] ) )
#endif


#if defined( linux ) || defined( ANDROID ) || defined( __DARWIN__ ) || defined( __APPLE_CC__ )

#define DBGTRACE_API

#else

#ifdef DBGTRACE_EXPORTS

#define DBGTRACE_API /* __declspec(dllexport) */

#else

#define DBGTRACE_API /* __declspec(dllimport) */

#endif

#endif


#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#ifdef _WIN32
#define DBG_TRACE               dbgtrace
#else
#ifndef DEBUG
inline void dbgtrace(...){}
#endif
#define DBG_TRACE               dbgtrace
#endif


#define DBG_TRACE_DUMP_BUFFER   dbgtracebuffer
#define DBG_TRACE_ASSERT        dbgtraceassert


/* ---------------------------------------------------- Debug Channels ---------------------------------------- */
#define ALL_DEBUG_CHANNELS      ((unsigned long)-1)
#define DBG_ERROR               0x0001L
#define DBG_WARNING             0x0002L
#define DBG_GENERAL_INFORMATION 0x0004L
#define DBG_CONSOLE             0x0008L
#define DBG_WINDOW_MESSAGES     0x0010L
#define DBG_GRAPHICAL           0x0020L
#define DBG_FONT_SYSTEM         0x0040L
#define DBG_DATA_DUMPS          0x0080L
#define DBG_NETWORK_INFO        0x0100L
#define DBG_WIN32API            0x0200L


#if ( defined( _DEBUG ) || defined( DEBUG ) )


typedef void (* printfunc)( unsigned long ulTraceLevel, const char * pszString );


/* Programmers must NOT call the following API functions but rather the corresponding macros.  */
void DBGTRACE_API traceMSG( unsigned long dwDebugChannelsBitmap, unsigned uLineNo, const char * lpszFile, long lNest, const TCHAR * pszPrefix, void * hWnd, unsigned int uiMsg, unsigned wParam, intptr_t lParam );
void DBGTRACE_API SetTraceLevel( unsigned long dwDebugBitmap );
void DBGTRACE_API SetTraceOutput( printfunc TraceFunc );
void DBGTRACE_API DBG_TRACE( unsigned uLineNo, const char * pszFile, unsigned long dwDebugChannelsBitmap, const TCHAR * lpszFormat, ... );
void DBGTRACE_API DBG_TRACE_DUMP_BUFFER( unsigned uLineNo, const char * pszFile, unsigned long dwDebugChannelsBitmap, void const * lpBuffer, unsigned long uBufferLen );
void DBGTRACE_API DBG_TRACE_ASSERT( unsigned uLineNo, const char * pszFile, const TCHAR * lpszExpr );


/* Programmers must call the following API (macros) and not the functions defined above.  */
//#define DBG_MSG                dbgtraceheader( __LINE__, __FILE__ ); DBG_TRACE
#define DBG_MSG( level, format, ... ) DBG_TRACE( __LINE__, __FILE__, level, format, ## __VA_ARGS__ )
#define DBG_DMP( level, buffer, size ) DBG_TRACE_DUMP_BUFFER( __LINE__, __FILE__, level, buffer, size )
#define DBG_ASSERT( expr ) \
{ \
    if ( !(expr) ) { \
\
        DBG_TRACE_ASSERT( __LINE__, __FILE__, TEXT( #expr ) ); \
    } \
}
#define TRACE_MESSAGE( dwDebugChannelsBitmap, hWnd, uiMsg, wParam, lParam )                 traceMSG( dwDebugChannelsBitmap, __LINE__, __FILE__, 0, NULL, hWnd, uiMsg, wParam, lParam )
#define TRACE_MESSAGE_NESTED( dwDebugChannels, Nest, Prefix, hWnd, uiMsg, wParam, lParam )  traceMSG( dwDebugChannels, __LINE__, __FILE__, Nest, Prefix, hWnd, uiMsg, wParam, lParam )
#define SET_TRACE_LEVEL( dwDebugBitmap )                                                    SetTraceLevel( dwDebugBitmap )
#define SET_TRACE_OUTPUT( printfunc )                                                       SetTraceOutput( printfunc );


#else


extern void NulFunction( unsigned long dwDebugChannelsBitmap, const char * lpszFormat, ... );


#ifdef __cplusplus


inline void DBG_MSG( unsigned long, const TCHAR *, ... ) {}
inline void DBG_DMP( unsigned long, const char *, int ) {}


#else


#define DBG_MSG                                         1 ? (void)0 : NulFunction
#define DBG_DMP                                         1 ? (void)0 : NulFunction


#endif


#define TRACE_MESSAGE( dwDebugChannelsBitmap, hWnd, uiMsg, wParam, lParam )
#define TRACE_MESSAGE_NESTED( dwDebugChannels, Nest, Prefix, hWnd, uiMsg, wParam, lParam )
#define SET_TRACE_LEVEL( dwDebugBitmap )
#define DBG_DMP( dwDebugBitmap, lpucBuffer, uBufferLen )
#define DBG_ASSERT( expr )
#define SET_TRACE_OUTPUT( printfunc )


#endif


/* -------------------------------------------------------- Regular API -------------------------------------------------------- */


/**

    Parameters:

    lpucBuffer

        Pointer to beginning of memory to dump.

    ulBufferLen

        Size in bytes of memory (pointed by lpucBuffer) to dump.

    ulSegmentLength

        How many hexadecimal digits should be dumped per-segment.

    ulNumberOfSegmentsPerLine

        A line can contain one or more segments.

    lpdwLen

        The length of the string returned by the function, including CR/LFs but excluding the ending NUL.

    Return Value:

        If the function fails, NULL.

        If the function succeeds, a pointer to the hex-dumped memory.

        This value must be freed by DumpBufferFree.

*/
const char * DBGTRACE_API DumpBuffer( const unsigned char * lpucBuffer, unsigned long ulBufferLen, unsigned long ulSegmentLength, unsigned long ulNumberOfSegmentsPerLine, unsigned long * lpdwLen );


void DBGTRACE_API DumpBufferFree( const char * );


const TCHAR * DBGTRACE_API CTimesz( time_t UserTime, TCHAR * lpszBuffer, unsigned uszBufferSize );


#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif  /* __cplusplus */


#endif  /* DEBUG_TRACE_LIB_H */
