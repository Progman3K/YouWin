

#include "ywin.h"


HRESULT SHGetKnownFolderPath( const KNOWNFOLDERID & rfid, DWORD dwFlags, HANDLE hToken, PWSTR * ppszPath ) {

    TSTRING App;
    TSTRING WorkingFolder;

    if ( FOLDERID_Documents.equals( rfid ) ) {

        struct passwd * ppw = getpwuid( geteuid() );

        if ( NULL == ppw ) {

            DBG_MSG( DBG_ERROR, TEXT( "USER PROFILE RETRIEVAL FAILED" ) );
            return E_FAIL;

        }

        const WCHAR * pszPath = 0;

#ifdef UNICODE
        TSTRING t;
        t.absorb( ppw->pw_dir );
        pszPath = t.c_str();
#else
// TODO: RESOLVE CHARSIZE DIFFERENCES
//        pszPath = ppw->pw_dir;
#endif

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "User folder path is '%lX'" ), pszPath );

//        _tcsncpy( *ppszPath, pszPath, PATH_MAX );

#if 0
        App.assign( g.app->argv[0] );
        found = App.find_last_of( '/' );
        WorkingFolder = App.substr( 0, found );
        strncpy( *ppszPath, WorkingFolder.c_str(), PATH_MAX );
#endif

        return S_OK;

    }

    return E_FAIL;

}


HRESULT SHGetKnownFolderPath( const KNOWNFOLDERID * rfid, DWORD dwFlags, HANDLE hToken, PWSTR * ppszPath ) {

    return SHGetKnownFolderPath( *rfid, dwFlags, hToken, ppszPath );

}


HRESULT SHGetFolderPath( HWND /* hwndOwner */, int nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath ) {

    if ( NULL == pszPath ) {

        DBG_MSG( DBG_ERROR, TEXT( "NULL PATH STORAGE" ) );
        return E_POINTER;

    }

    *pszPath = '\0';

    switch( nFolder ) {

        default:
            return E_NOTIMPL;

        case CSIDL_PERSONAL:

            return SHGetKnownFolderPath( FOLDERID_Documents, dwFlags, hToken, (PWSTR *)&pszPath );

    }

    return S_OK;

}
