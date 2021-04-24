

#include "chatter.h"


typedef struct {

	union {

		hostent		Host;
		char		cBuffer[MAXGETHOSTSTRUCT];

	};

} NAME_RESOLUTION, * PNAME_RESOLUTION, * LPNAME_RESOLUTION;

#ifdef WIN32
extern	NAME_RESOLUTION g_Name;
extern	HANDLE			g_hCurrentNameResolution;
NAME_RESOLUTION				g_Name;

void CChatterMainWnd::OnWSAAsyncGetHostByName( HWND hWnd, HANDLE /* hAsync */, unsigned /* uBuffLen */, unsigned uError ) {

	IN_ADDR	Address;

	if ( 0 != uError ) {

//		DBG_MSG( DBG_ERROR, TEXT( "Name resolution failed: %s" ), lpszMapErrorCode( uError ) );
		Error( hWnd, GetWindowInstance( hWnd ), lpszMapErrorCode( uError ), MAKEINTRESOURCE( IDS_PROGRAM_TITLE ) );
		return;

	}

	Address = *((LPIN_ADDR)g_Name.Host.h_addr );

}
#endif /* WIN32 */

