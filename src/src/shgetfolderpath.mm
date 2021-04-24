
#import <Foundation/Foundation.h>
#include "txtwin.h"

#include "../include/iosimport.h"


HRESULT SHGetKnownFolderPath( const KNOWNFOLDERID & rfid, DWORD dwFlags, HANDLE hToken, PWSTR * ppszPath ) {

    TSTRING App;
    TSTRING WorkingFolder;
    TSTRING::size_type found;

    if ( FOLDERID_Documents.equals( rfid ) ) {

        NSArray * paths = NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES );
        NSString * documentsDirectory = [paths objectAtIndex:0];

//        App.assign( g.app->argv[0] );
//        found = App.find_last_of( '/' );
//        WorkingFolder = App.substr( 0, found );
//        strncpy( *ppszPath, WorkingFolder.c_str(), PATH_MAX );
        strncpy( *ppszPath, [documentsDirectory UTF8String], PATH_MAX );
        return S_OK;

    }

    return E_FAIL;

}


HRESULT SHGetKnownFolderPath( const KNOWNFOLDERID * rfid, DWORD dwFlags, HANDLE hToken, PWSTR * ppszPath ) {

    if ( NULL == rfid ) {

        DBG_MSG( DBG_ERROR, TEXT( "NULL PATH STORAGE" ) );
        return E_POINTER;

    }

    return SHGetKnownFolderPath( *rfid, dwFlags, hToken, ppszPath );

}


HRESULT SHGetFolderPath( HWND /* hwndOwner */, int nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath ) {

    if ( NULL == pszPath ) {

        DBG_MSG( DBG_ERROR, TEXT( "NULL PATH STORAGE" ) );
        return E_POINTER;

    }

    *pszPath = '\0';

    switch( nFolder ) {

        case CSIDL_PERSONAL:

            return SHGetKnownFolderPath( FOLDERID_Documents, dwFlags, hToken, &pszPath );

        default:

            return E_NOTIMPL;

    }


    return S_OK;

}
