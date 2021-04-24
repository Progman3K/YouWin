

#include "dbwin.h"


void CMainDlg::OnWSAAsyncSelect( HWND hDlg, SOCKET s, unsigned uEvent, unsigned /* uError */ ) {

    LPDBWIN_DATA lpDBWin;
    int          iRet;

    socklen_t    iLen;

    union {

        sockaddr sa;
        // SOCKADDR_IN sin;

    };

    union {

        DEBUGMSGDATASTRUCT UNCD;
        char               cBuffer[MAXIMUM_MTU_SIZE];

    } Read;

    lpDBWin = (LPDBWIN_DATA)GetWindowLong( hDlg, DWL_USER );

    switch( uEvent ) {

        case FD_READ:

            ZeroMemory( &Read, sizeof( Read ) );

            iLen = sizeof( sa );
            iRet = recvfrom( s, Read.cBuffer, sizeof( Read.cBuffer ), 0, &sa, &iLen );

            if ( 0 < iRet ) {

                COPYDATASTRUCT CD;

                CD.cbData = Read.UNCD.cbData;
                CD.dwData = Read.UNCD.dwData;
                CD.lpData = Read.UNCD.cData;

                ProcessUserData( lpDBWin, &CD );

            }
            break;

    }

}
