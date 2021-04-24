

#include "chatter.h"


int iUIBusy = 0;


int CWho::ProcessFileXferOffer( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_info * pEF, size_t Size ) {

    // For now automatically accept the file transfer

    int iRet = 0;

    Exchange_f answer;
    File * pFile;
    Peer * pPeer = NULL;
    FILEINFO fi;

    textstring filename;

    TCHAR szMsg[1024];

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File offer response type '%u'" ), ntohs( pEF->info.usRequest ) );
    switch ( ntohs( pEF->usRequest ) ) {

        case MsgType_FileXfer_Offer_Query:

            if ( 0 != iUIBusy ) {

                break;

            }

            pFile = incomingfiles.Find( ntohll( pEF->entityfileID ) );

            if ( NULL != pFile ) {

                /* Already receiving this file */
                break;

            }

            if ( xfers.findbyID( ntohll( pEF->entityfileID ) ) ) {

                /* Already receiving this file */
                break;

            }

            TCHAR szHome[PATH_MAX];

            ZeroMemory( szHome, sizeof( szHome ) );

            if ( S_OK != SHGetFolderPath( hWnd, CSIDL_PERSONAL, NULL, 0, szHome ) ) {

                break;

            }

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Folder path '%s'" ), szHome );

            fi.localfilename.assign( szHome );

            /* Copy to object in computable form */
            fi.usFlags            = ntohs( pEF->usFlags );
            fi.entityfileID       = ntohll( pEF->entityfileID );
            fi.uiVerificationHash = ntohl( pEF->uiVerificationHash );
            fi.ullFilelength      = ntohll( pEF->ullFilelength );
            fi.usChunksize        = ntohs( pEF->usChunksize );
            fi.uiParam            = ntohl( pEF->uiParam );

            TCHAR szTitle[4096];
            LPCTSTR lpszFilename;

            filename.absorb( pEF->szFilename );

            lpszFilename = filename.c_str();

            _stprintf( szTitle, TEXT( "File '%s' is being offered" ), lpszFilename );

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File '%s' (%lX) is being offered to us" ), pEF->szFilename, (long)ntohll( pEF->entityfileID ) );

//            DialogBoxParam( hInst, MAKEINTRESOURCE( iDlgID ), hWnd, (DLGPROC)CChatterMainWnd::bDlgProc, (LPARAM)(LPSTARTUP_INFO)&si );
            TCHAR szSaveToPath[2048];

            ZeroMemory( szSaveToPath, sizeof( szSaveToPath ) );

            _tcsncpy( szSaveToPath, filename.c_str(), Dim( szSaveToPath ) - 1 );

            iUIBusy = true;
            iRet = NativeFile::iSaveTo( hWnd, 0, 0, szTitle, szSaveToPath, Dim( szSaveToPath ) - 1, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, fi.localfilename.c_str(), NULL, NULL, 0, NULL );
            iUIBusy = false;

            if ( IDOK != iRet ) {

                ZeroMemory( &answer, sizeof( answer ) );

                /* Copy over relevant members, no byteswapping necessary as they are already in network order. */
                answer.info.entityfileID       = pEF->entityfileID;
                answer.info.uiVerificationHash = pEF->uiVerificationHash;
                answer.info.ullFilelength      = pEF->ullFilelength;
                answer.info.usChunksize        = pEF->usChunksize;

                /* This member must be byteswapped  */
                answer.info.usRequest          = htons( MsgType_FileXfer_Offer_Reject );

                pMe->sendmsg( GetSin(), MsgType_FileXfer_Offer, answer.cBuffer, sizeof( answer.info ) );

                break;

            }

            // Accepted the file
            fi.localfilename.assign( szSaveToPath );

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File %lX saved to '%s'" ), (long)ntohll( pEF->entityfileID ), fi.localfilename.c_str() );

            /* See if UDP or TCP transfer */
            if ( file_xfer_info::TCP_SEND & fi.usFlags ) {

                int i;

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "TCP RECV '%s' %lu bytes" ), fi.localfilename.c_str(), (unsigned long)fi.ullFilelength );

                SOCKET sxfer = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

                if ( (SOCKET)-1 == sxfer ) {

                    iRet = -1;
                    break;

                }

                i = WSAAsyncSelect( sxfer, hWnd, WM_WSAASYNCTCPXFER, FD_CONNECT | FD_READ );

                if ( 0 != i ) {

                    iRet = -1;
                    break;

                }

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WSAAsyncSelect( %d ) --> %d" ), s, i );

                union {

                    sockaddr    sa;
                    sockaddr_in sin;

                };

                ZeroMemory( &sa, sizeof( sa ) );

                sin.sin_addr   = GetSin().sin_addr;
                sin.sin_port   = htons( (unsigned short)ntohl( pEF->uiParam ) );
                sin.sin_family = AF_INET;

                connect( sxfer, &sa, sizeof( sa ) );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "connect( %d, %s:%d ) --> %d (%d)" ), sxfer, INet_NToT( GetSin().sin_addr ), fi.uiParam, i, WSAGetLastError() );

                TCPXfer xferPair;

                TCPXferInfo tcpxfr;

                tcpxfr.fi = fi;

                xferPair.first  = sxfer;
                xferPair.second = tcpxfr;

                xfers.insert( xferPair );

                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETRANGE32, 0, (LPARAM)tcpxfr.fi.ullFilelength );

            } else {


                pFile = incomingfiles.Add( fi.localfilename.c_str() );

                pFile->fi = fi;

                pPeer = pFile->AddPeer( GetSin() );

                pFile->InitializePeerStorage( pPeer );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "UDP RECV '%s' %lu blocks" ), fi.localfilename.c_str(), (unsigned long)pPeer->unacknowledged_blocks.size() );

                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETRANGE32, 0, pPeer->unacknowledged_blocks.size() );

                // Add the file to the incoming files list.
                ZeroMemory( &answer, sizeof( answer ) );

                /* Copy over relevant members, no byteswapping necessary as they are already in network order. */
                answer.info.entityfileID       = pEF->entityfileID;
                answer.info.uiVerificationHash = pEF->uiVerificationHash;
                answer.info.ullFilelength      = pEF->ullFilelength;
                answer.info.usChunksize        = pEF->usChunksize;

                /* This member must be byteswapped  */
                answer.info.usRequest          = htons( MsgType_FileXfer_Offer_Accept );

                pMe->sendmsg( GetSin(), MsgType_FileXfer_Offer, answer.cBuffer, sizeof( answer.info ) );

            }

            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETSTEP, (WPARAM)1, 0 );
            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, (WPARAM)0, 0 );

            _stprintf( szMsg, TEXT( "Receiving file '%s' (%lu %s)" ), fi.localfilename.c_str(),
                     NULL == pPeer ? (unsigned long)fi.ullFilelength : (unsigned long)pPeer->unacknowledged_blocks.size(),
                     NULL == pPeer ? TEXT( "bytes" ) : TEXT( "blocks" )
                   );

            DisplayUserText( Output, szMsg );

            break;

        case MsgType_FileXfer_Offer_Accept:

            // Offer accepted
            // Look for file in list of outgoing files, change its state
            // for this peer from waiting-for-accept to receiving-blocks
            pFile = outgoingfiles.Find( ntohll( pEF->entityfileID ) );

            if ( NULL == pFile ) {

//                DBG_MSG( DBG_ERROR, TEXT( "Accept response to inexistant file/entity %lX" ), (long)ntohll( pEF->entityfileID ) );
                iRet = -1;
                break;

            }

            pPeer = pFile->FindPeer( GetSin() );

            if ( NULL == pPeer ) {

//                DBG_MSG( DBG_ERROR, TEXT( "Accept response to unsolicitated peer" ) );
                iRet = -1;
                break;

            }

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File %lX offer accepted" ), (long)pEF->entityfileID );

            pPeer->state = XFER_STATE_WAITING_ACKS;

            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETRANGE32, 0, pPeer->unacknowledged_blocks.size() );
            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETSTEP, (WPARAM)1, 0 );
            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_SETPOS, (WPARAM)0, 0 );
            break;

        case MsgType_FileXfer_Offer_Reject:

            // Offer rejected.
            // Remove the peer for this file.
//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File %lX offer rejected" ), (long)pEF->entityfileID );

            pFile = outgoingfiles.Find( ntohll( pEF->entityfileID ) );

            if ( NULL == pFile ) {

//                DBG_MSG( DBG_ERROR, TEXT( "Reject response to inexistant file/entity %lX" ), (long)pEF->entityfileID );
                iRet = -1;
                break;

            }
            {

                Peers::iterator i = pFile->peers.find( GetSin() );

                if ( pFile->peers.end() == i ) {

//                    DBG_MSG( DBG_ERROR, TEXT( "Accept response to unsolicitated peer" ) );
                    iRet = -1;
                    break;

                }

                if ( file_xfer_info::TCP_SEND & pFile->fi.usFlags ) {

                    KillTimer( hWnd, i->second.uiTimerID );

                }

                pFile->peers.erase( i );

            }
            break;

        default:

//            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN file-transfer offer response type %u" ), (unsigned)ntohs( pEF->usRequest ) );
            iRet = -1;

    }

    return iRet;

}


int CWho::ProcessFileXferAck( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_ack * pEF, size_t Size ) {

    union {

        file_xfer_chunk chunk;

        char cBuffer[MAX_DATA_LENGTH];

    };

    unsigned short usBlockSize;

    ZeroMemory( cBuffer, sizeof( cBuffer ) );
    File * pFile = outgoingfiles.Find( ntohll( pEF->entityfileID ) );

    if ( NULL == pFile ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Ack received for inexistant file/entity %lX" ), (long)ntohll( pEF->entityfileID ) );
        return -1;

    }

    Peer * pPeer = pFile->FindPeer( GetSin() );

    if ( NULL == pPeer ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Ack received for file %s from inexistant peer, file/entity %lX" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ) );
        return -1;

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File '%s' (%lX) ack %u received" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ), ntohl( pEF->auiChunkNos[0] ) );

    /*
        * remove block from the unacknowleged list
        * when the list is empty, stop sending file
    */
    unsigned int uiChunkNo = ntohl( pEF->auiChunkNos[0] );

    for( BLOCKS::iterator i = pPeer->unacknowledged_blocks.begin(); i != pPeer->unacknowledged_blocks.end(); ++i ) {

        if ( i->uiChunkNo == uiChunkNo ) {

            pPeer->uBlocksAcknowledged++;
            pPeer->uTransmitCount += i->uiRetyCount;

            pPeer->unacknowledged_blocks.erase( i );

            SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_STEPIT, 0, 0 );

            break;

        }

    }

    /* Check if there are still unacknowledged blocks to send */
    if ( 0 == pPeer->unacknowledged_blocks.size() ) {

        TCHAR szMsg[1024];

        _stprintf( szMsg, TEXT( "File '%s' (%lX)%sSend COMPLETE:%s%u blocks acknowledged%s(%u transmits)" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ), TEXT( EOL ), TEXT( EOL ), pPeer->uBlocksAcknowledged, TEXT( EOL ), pPeer->uTransmitCount );

        DisplayUserText( Output, szMsg );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File '%s' (%llX) send COMPLETE: %u blocks acknowledged (%u transmits)" ), pFile->localfilename.c_str(), ntohll( pEF->entityfileID ), pPeer->uBlocksAcknowledged, pPeer->uTransmitCount );

        KillTimer( hWnd, pPeer->uiTimerID );

        Peers::iterator i = pFile->peers.find( GetSin() );

        if ( pFile->peers.end() == i ) {

//            DBG_MSG( DBG_ERROR, TEXT( "ERROR unable to remove peer" ) );
            return -1;

        }

        pFile->peers.erase( i );

    } else {

        /* If we can shift the window over, do so */
        if ( ( pPeer->unacknowledged_blocks.at( 0 ).uiChunkNo + pPeer->uWindowSize ) > pPeer->uHighestOutstandingBlockNo ) {

            HNATIVEFILE hFile = NativeFile::Open( pFile->fi.localfilename.c_str(), NativeFile::FOR_READING );

            for ( unsigned u = 0; u < pPeer->unacknowledged_blocks.size(); u++ ) {

                if ( ! ( pPeer->unacknowledged_blocks.at( u ).uiChunkNo < ( pPeer->unacknowledged_blocks.at( 0 ).uiChunkNo + pPeer->uWindowSize ) ) ) {

                    break;

                }

                if ( 0 != pPeer->unacknowledged_blocks.at( u ).uiRetyCount ) {

                    continue;

                }

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Shifting send window." ) );

                chunk.entityfileID = htonll( pFile->fi.entityfileID );

                chunk.uiChunkNo = htonl( pPeer->unacknowledged_blocks.at( u ).uiChunkNo );

                DWORD dwPos = pPeer->unacknowledged_blocks.at( u ).uiChunkNo * pFile->fi.usChunksize;

                NativeFile::Seek( hFile, dwPos, NativeFile::FROM_BEGINNING );

                if ( dwPos < pFile->fi.ullFilelength ) {

                    if ( ( pFile->fi.ullFilelength - dwPos ) <= pFile->fi.usChunksize ) {

                        usBlockSize = (unsigned short)( pFile->fi.ullFilelength - dwPos );

                    } else {

                        usBlockSize = pFile->fi.usChunksize;

                    }

                } else {

                    /* */
//                    DBG_MSG( DBG_ERROR, TEXT( "SERIOUS ERROR TRYING TO SEND FILE '%s', position %ld, file-length: %lu." ), pFile->fi.filename.c_str(), dwPos, (long)pFile->fi.ullFilelength );
                    usBlockSize = 0;

                }

                chunk.Length = htons( usBlockSize );

                NativeFile::Read( hFile, chunk.cData, usBlockSize );

                pMe->sendmsg( GetSin(), MsgType_FileXfer_Chunk, cBuffer, sizeof( chunk ) + usBlockSize );

                pPeer->unacknowledged_blocks.at( u ).uiRetyCount++;

                pPeer->uHighestOutstandingBlockNo = pPeer->unacknowledged_blocks.at( u ).uiChunkNo;

            }

            NativeFile::Close( hFile );

        }

    }

    return 0;

}


int CWho::ProcessFileXferChunk( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_chunk * pEF, size_t Size ) {

    File * pFile = incomingfiles.Find( ntohll( pEF->entityfileID ) );

    if ( NULL == pFile ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Chunk received for inexistant file/entity %lX" ), (long)ntohll( pEF->entityfileID ) );
        return -1;

    }

    Peer * pPeer = pFile->FindPeer( GetSin() );

    if ( NULL == pPeer ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Chunk received for file %s from inexistant peer, file/entity %lX" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ) );
        return -1;

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "File '%s' (%lX) chunk %u received, size %d" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ), ntohl( pEF->uiChunkNo ), Size );

    union {

        file_xfer_ack ack;

        char cBuffer[MAX_DATA_LENGTH];

    };

    ack.entityfileID   = pEF->entityfileID;
    ack.Length         = htons( 1 );
    ack.auiChunkNos[0] = pEF->uiChunkNo;

    pMe->sendmsg( GetSin(), MsgType_FileXfer_Ack, cBuffer, sizeof( ack ) + ( sizeof( unsigned int ) * 1 ) );

    pPeer->uBlocksAcknowledged++;

    bool bFound = false;
    unsigned int uiChunkNo = ntohl( pEF->uiChunkNo );

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Look for chunk %u in %u outstanding blocks" ), uiChunkNo, pPeer->unacknowledged_blocks.size() );

    for( BLOCKS::iterator i = pPeer->unacknowledged_blocks.begin(); i != pPeer->unacknowledged_blocks.end(); ++i ) {

        if ( i->uiChunkNo == uiChunkNo ) {

            bFound = true;

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Found... Open '%s'" ), pFile->fi.localfilename.c_str() );

            HNATIVEFILE hFile = NativeFile::Open( pFile->fi.localfilename.c_str(), NativeFile::FOR_UPDATING );

            if ( HNATIVEFILE_ERROR != hFile ) {

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Write chunk %u (size %u) at %lu" ), uiChunkNo, ntohs( pEF->Length ), uiChunkNo * pFile->fi.usChunksize );

                NativeFile::Seek( hFile, uiChunkNo * pFile->fi.usChunksize, NativeFile::FROM_BEGINNING );

                NativeFile::Write( hFile, pEF->cData, ntohs( pEF->Length ) );

                NativeFile::Close( hFile );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Remove chunk %u from outstanding blocks" ), uiChunkNo );
                pPeer->unacknowledged_blocks.erase( i );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Update GUI" ) );
                SendMessage( GetDlgItem( hWnd, IDPB_FILEXFER ), PBM_STEPIT, 0, 0 );

            } else {

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "UNABLE TO OPEN FILE '%s'" ), pFile->fi.localfilename.c_str() );

            }
            break;

        }

    }

    if ( ! bFound ) {

        pPeer->uDupCount++;

    }

    if ( 0 == pPeer->unacknowledged_blocks.size() ) {

        /* File received */
        TCHAR szMsg[1024];

        _stprintf( szMsg, TEXT( "File '%s' (%lX)%sReceive COMPLETE:%s%u duplicate blocks received%s(%u acks transmitted)" ), pFile->fi.localfilename.c_str(), (long)ntohll( pEF->entityfileID ), TEXT( EOL ), TEXT( EOL ), pPeer->uDupCount, TEXT( EOL ), pPeer->uBlocksAcknowledged );

        DisplayUserText( Output, szMsg );

    }

    return 0;

}


int CWho::RecvData( HWND hWnd, CWho * pMe,  IOutput & Output, Exchange_t * pET, size_t Size ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Transaction type %u, size %d." ), (unsigned)ntohs( pET->Header.Type ), Size );

    textstring text;

    switch( ntohs( pET->Header.Type ) ) {

        case MsgType_Status:

            text.absorb( pET->Header.UserData );
            DisplayUserText( Output, text.c_str() );
            break;

        case MsgType_Chat:

            text.absorb( pET->Header.UserData );
            DisplayUserText( Output, text.c_str() );
            break;

        case MsgType_FileXfer_Ack:

            ProcessFileXferAck( hWnd, pMe, Output, (file_xfer_ack *)pET->Header.UserData, Size );
            break;

        case MsgType_FileXfer_Chunk:

            ProcessFileXferChunk( hWnd, pMe, Output, (file_xfer_chunk *)pET->Header.UserData, Size );
            break;

        case MsgType_FileXfer_Offer:

            /* On file fragment reception */
                /* Check if in approved or banned list */
            ProcessFileXferOffer( hWnd, pMe, Output, reinterpret_cast<const file_xfer_info *>(pET->Header.UserData), Size );
            break;

    }

    return 0;

}
