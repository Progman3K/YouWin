

#include "chatter.h"


TCHAR       g_szChatterHostName[MAX_HOST_NAME_SIZE];
TCHAR       g_szChatterUserName[MAX_USER_NAME_SIZE];

HICON       hHatAnimIcon[4] = { NULL, NULL, NULL, NULL };
HICON       hMainIcon = NULL;

FileList    outgoingfiles;
FileList    incomingfiles;

sockaddr_in CWho::broadcast;


time_t now( void ) {

    return time( NULL );

}


Entity GenerateEntity( void ) {

//    std::random_device rand;

    return ( rand() * GetTickCount() );

}


bool bIsTextMode( void ) {

    LONG lBaseUnits = GetDialogBaseUnits();

    if ( ( 1 == HIWORD( lBaseUnits ) ) && ( 1 == LOWORD( lBaseUnits ) ) ) {

        return true;

    }

    return false;

}


int
#ifdef _MSC_VER
__stdcall
#endif
_tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR pszCmdLine, int nCmdShow) {

#ifndef ANDROID

//    DWORD dwDebugMessagesFilter = (DWORD)-1;

    /* Turn OFF the window message tracing */
//    dwDebugMessagesFilter = dwDebugMessagesFilter & ( ~DBG_WINDOW_MESSAGES );
//    dwDebugMessagesFilter = dwDebugMessagesFilter & ( ~DBG_DATA_DUMPS );

//    SET_TRACE_LEVEL( dwDebugMessagesFilter );

#endif

    OutputDebugString( TEXT( "HELLO MADCHATTER!" ) );

//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Mercury statistics:" ) );
    {
//    unsigned short     Length;
//    unsigned long long entity;
//    char               UserData[];

//	DBG_MSG( DBG_NETWORK_INFO, TEXT( "sizeof( unsigned short )=%u, sizeof( unsigned long long )=%u, sizeof( char[] )=%u" ), sizeof( Length ), sizeof( entity ), sizeof( MsgHeader::UserData ) );
    }

//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Message header size: %u" ), sizeof( MsgHeader ) );
//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Message header size: %u, Exchange_t size: %u" ), sizeof( MsgHeader ), sizeof( Exchange_t ) );
//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Filexfr header size: %u, Exchange_f size: %u" ), sizeof( file_xfer_header ), sizeof( Exchange_f ) );
//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Filexfr ack size:    %u" ), sizeof( file_xfer_ack ) );
//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Filexfr chunk size:  %u" ), sizeof( file_xfer_chunk ) );
//    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Filexfr info size:   %u" ), sizeof( file_xfer_info ) );

    CWho::init();

    hMainIcon = WinInit( hInst, hPrevInst );

    if ( NULL == hMainIcon ) {

        return -1;

    }

    sockaddr_in sin;

    ZeroMemory( &sin, sizeof( sin ) );

    sin.sin_family      = AF_INET;
    sin.sin_port        = htons( MERCURY_DGRAM_PORT );
    sin.sin_addr.s_addr = htonl( INADDR_ANY );

    CWho me( GenerateEntity(), sin );

    int iRet = iInit( me );

    if ( 0 == iRet ) {

        STARTUP_INFO si = { &me, pszCmdLine, nCmdShow };

        int iDlgID;

        if ( GetSystemMetrics( SM_CYSCREEN ) > GetSystemMetrics( SM_CXSCREEN ) ) {

            iDlgID = bIsTextMode() ? IDD_CHATTER_MAIN_TEXT_PORTRAIT : IDD_CHATTER_MAIN_FOR_ANDROID_PORTRAIT;

        } else {

            iDlgID = bIsTextMode() ? IDD_CHATTER_MAIN_TEXT : IDD_CHATTER_MAIN_FOR_ANDROID_LANDSCAPE;

        }

        iRet = (int)DialogBoxParam( hInst, MAKEINTRESOURCE( iDlgID ), HWND_DESKTOP, (DLGPROC)CChatterMainWnd::bDlgProc, (LPARAM)(LPSTARTUP_INFO)&si );

    }

    DestroyIcon( hMainIcon );

    CleanUp( hInst, me );

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Chatter shutdown (%d)" ), iRet );

    OutputDebugString( TEXT( "GOODBYE MADCHATTER!" ) );

    return iRet;

}
