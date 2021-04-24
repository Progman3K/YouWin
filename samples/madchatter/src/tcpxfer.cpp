

#include "chatter.h"


TCPXfers xfers;


#if 0
static LPCTSTR FD_EVENT( WORD wEventCode ) {

    switch( wEventCode ) {

        case FD_ACCEPT:

            return TEXT( "FD_ACCEPT" );

        case FD_CLOSE:

            return TEXT( "FD_CLOSE" );

        case FD_CONNECT:

            return TEXT( "FD_CONNECT" );

        case FD_READ:

            return TEXT( "FD_READ" );

        case FD_WRITE:

            return TEXT( "FD_WRITE" );

    }

    return TEXT( "UNKNOWN" );

}
#endif


CChatterMainWnd::xfer_session_status CChatterMainWnd::ProcessRecvFile( HWND hWnd, TCPXferInfo & tcpxfr, HNATIVEFILE hFile, SOCKET s ) {

    char cBuffer[1024 * 128];

    for ( ;; ) {

        size_t i = recv( s, cBuffer, sizeof( cBuffer ), 0 );

        if ( 0 == i ) {

            /* EOF */
//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File reception suspended because of recv sized 0 on socket %d" ), s );
            break;

        }

        if ( (size_t)-1 == i ) {

            /* E_WOULDBLOCK is the only acceptable error */
//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File reception suspended because recv returned %d (err: %d) on socket %d" ), i, errno, s );
            break;

        }

//      DWORD dw =
        NativeFile::Write( hFile, cBuffer, i );

        SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, NativeFile::Tell( hFile ), 0 );

        break;

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Fileoffset is %lu" ), NativeFile::Tell( hFile ) );

    if ( NativeFile::Tell( hFile ) >= tcpxfr.fi.ullFilelength ) {

        return xfer_finished_ok;

    }

    return xfer_continue;

}


void CChatterMainWnd::OnWSAAsyncTCPXfer( HWND hWnd, SOCKET s, WORD wEventCode, WORD wErrorCode ) {

    size_t i;
    uintptr_t dw;
    char cBuffer[1024 * 64];

    TCPXfers::iterator x = xfers.find( s );

    /* Which filestream does this refer to? */
    if ( xfers.end() == x ) {

        /* NONE?!? */
//        DBG_MSG( DBG_ERROR, TEXT( "ASYNC TCP EVENT %s, code %d on socket %d, SOCKET ORPHANED, TERMINATING" ), FD_EVENT( wEventCode ), (int)wErrorCode, s );

        closesocket( s );
        return;

    }

    TCPXferInfo & tcpxfr = (*x).second;

    xfer_session_status status = xfer_finished_error;

    HNATIVEFILE hFile = HNATIVEFILE_ERROR;

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ASYNC TCP EVENT %s, code %d on socket %d" ), FD_EVENT( wEventCode ), (int)wErrorCode, s );

    switch( wEventCode ) {

        case FD_ACCEPT:

            {

                SOCKET s2 = accept( s, NULL, NULL );

                if ( (SOCKET)-1 == s2 ) {

//                    DBG_MSG( DBG_ERROR, TEXT( "ACCEPT FAILED ON SOCKET %d" ), s );
                    break;

                }

                outgoingfiles.Remove( tcpxfr.fi.entityfileID );

                KillTimer( hWnd, tcpxfr.fi.uiTimerID );

                WSAAsyncSelect( s2, hWnd, WM_WSAASYNCTCPXFER, FD_WRITE | FD_CLOSE );

                TCPXferInfo tcpxfr2;

                tcpxfr2.fi = tcpxfr.fi;

                TCPXfer xferPair;

                xferPair.first  = s2;
                xferPair.second = tcpxfr2;

                xfers.insert( xferPair );

                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, 0, 0 );
                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETSTEP, 1, 0 );
                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETRANGE32, 0, (LPARAM)tcpxfr.fi.ullFilelength );

            }

            goto TerminateListener;

        case FD_CLOSE:

            status = xfer_finished_ok;
            break;

        case FD_CONNECT:

            WSAAsyncSelect( s, hWnd, WM_WSAASYNCTCPXFER, FD_READ | FD_CLOSE );

            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, 0, 0 );
            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETSTEP, 1, 0 );
            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETRANGE32, 0, (LPARAM)tcpxfr.fi.ullFilelength );

            status = xfer_continue;
            break;

        case FD_READ:

            if ( HNATIVEFILE_ERROR == ( hFile = NativeFile::Open( tcpxfr.fi.localfilename.c_str(), NativeFile::FOR_APPEND ) ) ) {

//                DBG_MSG( DBG_ERROR, TEXT( "ERROR OPENING FILE '%s' FOR APPENDING" ), tcpxfr.fi.localfilename.c_str() );
                goto ProcessSession;

            }

            status = ProcessRecvFile( hWnd, tcpxfr, hFile, s );
            break;

        case FD_WRITE:

            if ( HNATIVEFILE_ERROR == ( hFile = NativeFile::Open( tcpxfr.fi.localfilename.c_str(), NativeFile::FOR_READING ) ) ) {

//                DBG_MSG( DBG_ERROR, TEXT( "ERROR OPENING FILE '%s' FOR READING" ), tcpxfr.fi.localfilename.c_str() );
                goto ProcessSession;

            }

            for ( ;; ) {

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resume sending file %lX from offset %u on socket %d" ), hFile, (unsigned)tcpxfr.ullFilePosition, s );

                NativeFile::Seek( hFile, (DWORD)tcpxfr.ullFilePosition, NativeFile::FROM_BEGINNING );

                dw = NativeFile::Read( hFile, cBuffer, sizeof( cBuffer ) );

                if ( 0 == dw ) {

                    /* EOF, dump stats */
                    status = xfer_continue;

                    /* No writing to be done anymore, wait for remote to close */
                    WSAAsyncSelect( s, hWnd, WM_WSAASYNCTCPXFER, FD_CLOSE );
                    break;

                }

                i = send( s, cBuffer, (int)dw, 0 );

                if ( (size_t)-1 == i ) {

                    /* E_WOULDBLOCK is the only acceptable error */
                    status = xfer_continue;
//                    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File sending suspended because sending block sized %lu returned %d (errno=%d '%s') on socket %d" ), dw, i, errno, strerror( errno ), s );
                    WSAAsyncSelect( s, hWnd, WM_WSAASYNCTCPXFER, FD_WRITE | FD_CLOSE );
                    break;

                }

                tcpxfr.ullFilePosition += i;

                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, (WPARAM)tcpxfr.ullFilePosition, 0 );

            }

            break;

    }

ProcessSession:

    if ( HNATIVEFILE_ERROR != hFile ) {

        NativeFile::Close( hFile );

    }

    switch( status ) {

        case xfer_continue:

            return;

        case xfer_finished_error:

//            DisplayUserText( Output, szMsg );
//            DBG_MSG( DBG_ERROR, TEXT( "TRANSFER ERROR, SOCKET %d TERMINATING" ), s );
            break;

        case xfer_finished_ok:

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Transfer on socket %d completed OK" ), s );
            break;

    }

TerminateListener:

    closesocket( s );
    xfers.erase( x );

}
