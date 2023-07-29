

#include <algorithm>
#include <stdio.h>
#include <stdarg.h>


#include "dbwinapi.h"
#include "tstring.h"
#include "ctimesz.cpp"


#ifndef WIN32
#ifndef GetCurrentThreadId
#ifdef __DARWIN__

#define GetCurrentThreadId()  pthread_self()->__sig

#else

#include <pthread.h>
#define GetCurrentThreadId()  pthread_self()

#endif
#endif
#endif



#if defined( DEBUG ) || defined( _DEBUG )

extern "C" inline void DBGTRACE_API DBG_TRACE( unsigned uLineNo, const char * pszFile, unsigned long dwDebugChannelsBitmap, const TCHAR * pszFormat, ... ) {

    size_t  Len;
    va_list args;

    TCHAR   szTemp[16384];
    char    szMsg[32768];

//    if ( ! ( dwDebugChannelsBitmap & g_dwDebugBitmap ) && ( ALL_DEBUG_CHANNELS != dwDebugChannelsBitmap ) ) {

//        return;

//    }

    memset( szTemp, 0, sizeof( szTemp ) );

    va_start( args, pszFormat );

#ifdef _WIN32
    _vsntprintf_s( szTemp, ( sizeof( szTemp ) / sizeof( szTemp[0] ) ), ( sizeof( szTemp ) / sizeof( szTemp[0] ) ) - 1, pszFormat, args );

#else
    _vsntprintf( szTemp, ( sizeof( szTemp ) / sizeof( szTemp[0] ) ), pszFormat, args );
#endif

    va_end( args );

    TSTRING s;

    s.assign( szTemp );

    TCHAR szDateTime[128];
    memset( szDateTime, 0, sizeof( szDateTime ) );

    CTimesz( 0, szDateTime, ( sizeof( szDateTime ) / sizeof( szDateTime[0] ) ) - 1 );

    TSTRING sdate;

    sdate.assign( szDateTime );

    char szLine[32];

    memset( szLine, 0, sizeof( szLine ) );

    if ( 0 != uLineNo ) {

#ifdef _WIN32
        _snprintf_s( szLine, ( sizeof( szLine ) / sizeof( szLine[0] ) ), ( sizeof( szLine ) / sizeof( szLine[0] ) ) - 1, "line %4u, ", uLineNo );
#else
        snprintf( szLine, ( sizeof( szLine ) / sizeof( szLine[0] ) ) - 1, "line %4u, ", uLineNo );
#endif

    }

    char szFile[1024];
    memset( szFile, 0, sizeof( szFile ) );

    if ( NULL != pszFile ) {

#ifdef _WIN32
        _snprintf_s(szFile, (sizeof(szFile) / sizeof(szFile[0])), (sizeof(szFile) / sizeof(szFile[0])) - 1, "file %s: ", pszFile);
#else
        snprintf( szFile, ( sizeof( szFile ) / sizeof( szFile[0] ) ) - 1, "file %s: ", pszFile );
#endif

    }

    memset( szMsg, 0, sizeof( szMsg ) );

#ifdef _WIN32
    Len = _snprintf_s( szMsg, ( sizeof( szMsg ) / sizeof( szMsg[0] ) ), ( sizeof( szMsg ) / sizeof( szMsg[0] ) ) - 1, "%012lX: %s: %s%s%s\r\n", (long unsigned int)GetCurrentThreadId(), sdate.charz_str(), szLine, szFile, s.charz_str() );
#else
    Len = snprintf( szMsg, ( sizeof( szMsg ) / sizeof( szMsg[0] ) ) - 1, "%012lX: %s: %s%s%s\r\n", (long unsigned int)GetCurrentThreadId(), sdate.charz_str(), szLine, szFile, s.charz_str() );
#endif

    if ( ( 0 == Len ) || ( (size_t)-1 == Len ) ) {

        return;

    }

    // Channel filtering
//    if ( NULL != g_TrcFunc ) {

//        g_TrcFunc( dwDebugChannelsBitmap, szMsg );

//    }

#if defined( _WIN32 ) || defined( WIN32 )
    OutputDebugStringA( szMsg );
#else
    fprintf( stderr, "%s", szMsg );
#endif

}


#endif /* DEBUG */
