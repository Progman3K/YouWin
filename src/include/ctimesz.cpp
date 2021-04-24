

#include <cstring>


#if defined( _WIN32 ) || defined( _WIN32_WCE )
#include <windows.h>
#include <tchar.h>
#include <time.h>
#endif


#ifdef UNDER_CE


time_t time( time_t *inTT ) {

    SYSTEMTIME sysTimeStruct;
    FILETIME fTime;
    ULARGE_INTEGER int64time;

    time_t locTT = 0;

    if ( inTT == NULL ) {



        inTT = &locTT;



    }

    GetSystemTime( &sysTimeStruct );

    if ( SystemTimeToFileTime( &sysTimeStruct, &fTime ) ) {

        memcpy( &int64time, &fTime, sizeof( FILETIME ) );

        /* Subtract the value for 1970-01-01 00:00 (UTC) */
        int64time.QuadPart -= 0x19db1ded53e8000;

        /* Convert to seconds. */
        int64time.QuadPart /= 10000000;
        *inTT = (time_t)int64time.QuadPart;

    }

    return *inTT;

}


void UnixTimeToFileTime( time_t t, LPFILETIME pft ) {

    // Note that LONGLONG is a 64-bit value

    LONGLONG ll;

    ll = Int32x32To64( t, 10000000 ) + 116444736000000000;

    pft->dwLowDateTime = (DWORD)ll;

    pft->dwHighDateTime = ll >> 32;

}


void UnixTimeToSystemTime( time_t t, LPSYSTEMTIME pst ) {

    FILETIME ft;

    UnixTimeToFileTime( t, &ft );
    FileTimeToSystemTime( &ft, pst );

}


#endif


extern "C" inline const TCHAR * DBGTRACE_API CTimesz( time_t UserTime, TCHAR * pszBuffer, unsigned

#ifndef	_WIN32_WCE

    uszBufferSize

#endif

    ) {

#if defined( _WIN32 ) || defined( _WIN32_WCE )

    unsigned long           dwRet;
    TCHAR                   szTime[128];
    TCHAR                   szDate[128];
    TIME_ZONE_INFORMATION   TimeZoneInformation;
    SYSTEMTIME              st;

    if ( 0 == UserTime ) {

        UserTime = time( NULL );

    }

    ZeroMemory( szTime, sizeof( szTime ) );
    ZeroMemory( szDate, sizeof( szDate ) );
    ZeroMemory( &TimeZoneInformation, sizeof( TimeZoneInformation ) );

    dwRet = GetTimeZoneInformation( &TimeZoneInformation );

    switch( dwRet ) {

        case TIME_ZONE_ID_UNKNOWN:

            break;

        case TIME_ZONE_ID_STANDARD:

            UserTime += ( TimeZoneInformation.StandardBias * 60 );
            UserTime -= ( TimeZoneInformation.Bias * 60 );
            break;

        case TIME_ZONE_ID_DAYLIGHT:

            UserTime -=	( ( TimeZoneInformation.Bias + TimeZoneInformation.DaylightBias ) * 60 );
            break;

    }

#ifdef	_WIN32_WCE

    UnixTimeToSystemTime( UserTime, &st );

#else

    {

        struct tm * pGMT;


#ifdef _WIN32

        struct tm GMT;
        ZeroMemory( &GMT, sizeof( GMT ) );
        pGMT = &GMT;
        gmtime_s( &GMT, &UserTime );

#else
        pGMT = gmtime( &UserTime );
#endif

        if ( NULL == pGMT ) {

            return TEXT( "" );

        }

        st.wYear         = (WORD)( 1900 + pGMT->tm_year );
        st.wMonth        = (WORD)( 1 + pGMT->tm_mon );
        st.wDayOfWeek    = (WORD)pGMT->tm_wday;
        st.wDay          = (WORD)pGMT->tm_mday;
        st.wHour         = (WORD)pGMT->tm_hour;
        st.wMinute       = (WORD)pGMT->tm_min;
        st.wSecond       = (WORD)pGMT->tm_sec;
        st.wMilliseconds = 0;

    }

#endif

    GetDateFormat( LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, szDate, ( sizeof( szDate ) / sizeof( szDate[0] ) ) - 1 );
    GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, szTime, ( sizeof( szTime ) / sizeof( szTime[0] ) ) - 1 );

    wsprintf( pszBuffer, TEXT( "%s %s" ), szDate, szTime );

    return pszBuffer;

#else

static time_t Time;

    TCHAR * psz;
    size_t  i;

    Time = UserTime;

    /* Set string NULL in case routine fails. */

    memset( pszBuffer, '\0', uszBufferSize );

    if ( 0 == Time ) {

        Time = time( NULL );

    }

#ifdef UNICODE

    TSTRING s;

    s.absorb( ctime( &Time ) );

    psz = (TCHAR *)s.c_str();

#else

    psz = ctime( &Time );

#endif

    if ( ! psz ) {

        return TEXT( "" );

    }

    i = _tcslen( psz );

    if ( ! i ) {

        return TEXT( "" );

    }

    psz[i - 1] = '\0';

    /* Remove annoying character 0xA from end of line. */

    _tcsncpy( pszBuffer, psz, std::min( (unsigned)i, uszBufferSize ) );

    return pszBuffer;

#endif

}
