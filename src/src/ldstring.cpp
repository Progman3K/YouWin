

#include "ywin.h"


int LoadString( HINSTANCE hInst, UINT uID, LPTSTR lpBuffer, int iBufferMax ) {

    if ( 1 > iBufferMax ) {

        return 0;

    }

    const ResourceList * pResources = reinterpret_cast<const ResourceList *>( hInst );

    resourcestringlocator string;

    string.us = LOWORD( uID );

    const Resource * pRes = pResources->find( ID( string.ID.blocknumber ) + 1, RT_STRING );

    if ( 0 == pRes ) {

        return 0;

    }

    StringEntry * pSE = (StringEntry *)pRes->Id.pData;

    utf16string resstring;

    for ( unsigned u = 0; u <= string.ID.blockposition; u++ ) {

        if ( u == string.ID.blockposition ) {

            /* Found string we are looking for */
            resstring.append_from_resource( pSE->Text, I386PE_INT16_TO_HOST( &pSE->wLen ) );
            return _tcslen( _tcsncpy( lpBuffer, resstring.tcharz_str(), iBufferMax ) );

        } else {

            /* Skip over to next string */
            pSE = (StringEntry *)( &pSE->Text[I386PE_INT16_TO_HOST( &pSE->wLen )] );

        }

    }

    return 0;

}
