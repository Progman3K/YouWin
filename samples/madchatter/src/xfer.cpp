

#include "chatter.h"


long CWho::SendFile( HWND hWnd, Peer & peer, sockaddr_in sin, File & file ) {

    size_t Len;

    union {

        file_xfer_chunk chunk;
        file_xfer_info info;

        char cBuffer[MAX_DATA_LENGTH];

    };

    unsigned short usBlockSize;

    ZeroMemory( cBuffer, sizeof( cBuffer ) );

    switch( peer.state ) {

        case XFER_STATE_WAITING_ACCEPT:

            /* Send a query to ask if the peer wants the file */
            info.entityfileID       = htonll( file.fi.entityfileID );
            info.usRequest          = htons( MsgType_FileXfer_Offer_Query );
            info.usFlags            = htons( file.fi.usFlags );
            info.uiParam            = htonl( file.fi.uiParam );
            info.uiVerificationHash = 0;
            info.ullFilelength      = htonll( file.fi.ullFilelength );
            info.usChunksize        = htons( file.fi.usChunksize );
            strcpy( info.szFilename, file.fi.filename.charz_str() );
            Len = strlen( info.szFilename );

            return sendmsg( sin, MsgType_FileXfer_Offer, cBuffer, sizeof( info ) + Len + 1 );

        case XFER_STATE_RECEIVINGBLOCKS:

            /* Nothing to do on transmit */

            break;

        case XFER_STATE_WAITING_ACKS:

            HNATIVEFILE hFile = NativeFile::Open( file.fi.localfilename.c_str(), NativeFile::FOR_READING );

            chunk.entityfileID = htonll( file.fi.entityfileID );
            //chunk.
            for( size_t u = 0; ( u < peer.uWindowSize ) && ( u  < peer.unacknowledged_blocks.size() ); u++ ) {

                chunk.uiChunkNo = htonl( peer.unacknowledged_blocks.at( u ).uiChunkNo );

                DWORD dwPos = peer.unacknowledged_blocks.at( u ).uiChunkNo * file.fi.usChunksize;

                NativeFile::Seek( hFile, dwPos, NativeFile::FROM_BEGINNING );

                if ( dwPos < file.fi.ullFilelength ) {

                    if ( ( file.fi.ullFilelength - dwPos ) <= file.fi.usChunksize ) {

                        usBlockSize = (unsigned short)( file.fi.ullFilelength - dwPos );

                    } else {

                        usBlockSize = file.fi.usChunksize;

                    }

                } else {

                    /* */
//                    DBG_MSG( DBG_ERROR, TEXT( "SERIOUS ERROR TRYING TO SEND FILE '%s', position %ld, file-length: %llu." ), file.fi.filename.c_str(), dwPos, file.fi.ullFilelength );
                    usBlockSize = 0;

                }

                chunk.Length = htons( usBlockSize );

                NativeFile::Read( hFile, chunk.cData, usBlockSize );

                size_t i = sendmsg( sin, MsgType_FileXfer_Chunk, cBuffer, sizeof( chunk ) + usBlockSize );

                if ( (size_t)-1 == i ) {

                    break;

                }

                peer.unacknowledged_blocks.at( u ).uiRetyCount++;

                peer.uHighestOutstandingBlockNo = peer.unacknowledged_blocks.at( u ).uiChunkNo;

            }

            NativeFile::Close( hFile );

            return 0;

    }

    return -1;

}
