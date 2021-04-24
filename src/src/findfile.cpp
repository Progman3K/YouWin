

#include "ywin.h"


HANDLE FindFirstFile( const TCHAR * pszFileName, WIN32_FIND_DATA * pFindFileData ) {

    CFindFirst * p = new CFindFirst;

    strncpy( p->szDir, pszFileName, Dim( p->szDir ) - 1 );

    TSTRING Dir = dirname( p->szDir );

    p->pDir = opendir( Dir.c_str() );

    if ( 0 == p->pDir ) {

        delete p;
        return 0;

    }

#if 0
    int iRet = readdir_r( p->pDir, &p->entry, &p->pEntry );
#else
    p->pEntry = readdir( p->pDir );
#endif

    if ( /* ( 0 != iRet ) || */ ( NULL == p->pEntry ) ) {

        closedir( p->pDir );
        p->pDir = 0;

        delete p;

        return 0;

    }

    _tcsncpy( pFindFileData->cFileName, p->pEntry->d_name, Dim( pFindFileData->cFileName ) );

    return p;

}


BOOL FindNextFile( HANDLE hFindFile, WIN32_FIND_DATA * pFindFileData ) {

    CFindFirst * p = reinterpret_cast<CFindFirst *>( hFindFile );

#if 0
    int iRet = readdir_r( p->pDir, &p->entry, &p->pEntry );
#else
    p->pEntry = readdir( p->pDir );
#endif

    if ( /* ( 0 != iRet ) || */ ( NULL == p->pEntry ) ) {

        closedir( p->pDir );
        p->pEntry = 0;
        p->pDir   = 0;
        return false;

    }

    _tcsncpy( pFindFileData->cFileName, p->pEntry->d_name, Dim( pFindFileData->cFileName ) );

    return true;

}


BOOL FindClose( HANDLE hFindFile ) {

    CloseHandle( hFindFile );
    return true;

}
