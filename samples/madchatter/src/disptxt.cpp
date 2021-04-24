

#include "chatter.h"


void CWho::DisplayUserText( IOutput & Output, const TCHAR * pszText ) {

    size_t iLen;

    if ( 0 == ( iLen = _tcslen( pszText ) ) ) {

        return;

    }

    time_t t = now();

    TCHAR * pszTime = _tctime( &t );

    Output.AppendText( pszTime, _tcslen( pszTime ), true );
    Output.AppendText( MAKEINTRESOURCE( IDS_SPACE_COLON_SPACE ), 0, false );
    Output.AppendText( GetName(), 0, false );
    Output.AppendText( MAKEINTRESOURCE( IDS_REMOTE_HOST_SPEAK ), 0, false );
    Output.AppendText( pszText, iLen, true );

}
