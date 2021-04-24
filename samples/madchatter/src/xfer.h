#ifndef __XFER_H__
#define __XFER_H__


#include <map>
#include <string>
#include <vector>


#include "sa.h"


class textstring : public std::basic_string <TCHAR> {

    std::basic_string<char> s;

	public:


		void absorb( const char * psz ) {

			clear();

			for ( ; *psz; psz++ ) {

				char  c = *psz;
				TCHAR wc = c;
				append( &wc, 1 );

			}

		}


        const char * charz_str() {

            s.clear();

            for( size_t u = 0; u < size(); u++ ) {

                s.push_back( (char)at( u ) );

            }

            return s.c_str();

        }


};


typedef enum {

    BLOCK_STATE_UNACKNOWLEDGED
    ,BLOCK_STATE_ACKNOWLEDGED

} BLOCK_STATE;


typedef struct {

    unsigned int uiChunkNo;
    unsigned int uiRetyCount;
//    BLOCK_STATE  state;

} BLOCK;


typedef enum {

    XFER_STATE_WAITING_ACCEPT
    ,XFER_STATE_WAITING_ACKS
    ,XFER_STATE_RECEIVINGBLOCKS

} XFER_STATE;


typedef std::vector<BLOCK> BLOCKS;


class Peer {

    public:

        Peer() {

            uHighestOutstandingBlockNo = 0;
            uBlocksAcknowledged        = 0;
            uTransmitCount             = 0;
            uDupCount                  = 0;
            uWindowSize                = 0;
            who                        = 0;
            uiTimerID                  = 0;
            state                      = XFER_STATE_RECEIVINGBLOCKS;

        }

        Entity who;

        UINT_PTR uiTimerID;

        XFER_STATE state;

        unsigned uWindowSize;
        unsigned uHighestOutstandingBlockNo;

        unsigned uBlocksAcknowledged;
        unsigned uTransmitCount;

        unsigned uDupCount;

        BLOCKS unacknowledged_blocks;
//        std::vector<BLOCK> acknowledged_blocks;

};


typedef struct tagFILEINFO {

    bool get_fname( LPCTSTR lpszSendFile, textstring & userfilename ) {

#ifdef _WIN32
        const TCHAR * slash = _tcsrchr( lpszSendFile, '\\' );
#else
        const char * slash = strrchr( lpszSendFile, '/' );
#endif

        if ( NULL == slash ) {

            return false;

        }

        slash++;

        userfilename.assign( slash );

        return true;

    }

    Entity                  entityfileID;

    unsigned short          usFlags;
    unsigned int            uiParam;

    UINT_PTR                uiTimerID;

    unsigned int            uiVerificationHash;
    unsigned long long      ullFilelength;
    unsigned short          usChunksize;

    textstring              localfilename;

    textstring              filename;

    tagFILEINFO() {

        entityfileID = 0;
		usFlags = 0;
		uiParam = 0;
		uiTimerID = 0;
		uiVerificationHash = 0;
		ullFilelength = 0;
		usChunksize = 0;

    }

} FILEINFO;


class TCPXferInfo {

    public:

        unsigned long long ullFilePosition;

        TCPXferInfo() {

            ullFilePosition = 0;

        }

        FILEINFO fi;

};


typedef std::map<tSA, Peer> Peers;
typedef std::pair <tSA, Peer> PeerPair;
typedef std::pair<SOCKET, TCPXferInfo> TCPXfer;

class TCPXfers : public std::map<SOCKET, TCPXferInfo>  {

    public:

        bool findbyID( FileID entityfileID ) const {

            for ( TCPXfers::const_iterator i = begin(); i != end(); ++i ) {

                if ( (*i).second.fi.entityfileID == entityfileID ) {

                    return true;

                }

            }

            return false;

        }

};


class File {

    public:

        FILEINFO fi;
        Peers    peers;

        void InitializePeerStorage( Peer * pPeer ) {

            /* Determine how many blocks this will transmit */

            BLOCK block;

            block.uiRetyCount = 0;

            unsigned uChunkNos = 0;

            if ( fi.ullFilelength <= fi.usChunksize ) {

                uChunkNos = 1;

            } else {

                uChunkNos = (unsigned)( fi.ullFilelength / fi.usChunksize );

                if ( 0 != ( fi.ullFilelength - ( fi.usChunksize * uChunkNos ) ) ) {

                    uChunkNos++;

                }

            }

            pPeer->unacknowledged_blocks.resize( uChunkNos, block );

            for ( unsigned int u = 0; u < uChunkNos; u++ ) {

                pPeer->unacknowledged_blocks.at( u ).uiChunkNo = u;

            }

        }


        Peer * FindPeer( const tSA & sin ) {

            Peers::iterator i;

            i = peers.find( sin );

            if ( peers.end() != i ) {

                return & i->second;

            }

            return NULL;

        }


        Peer * AddPeer( const tSA & sin ) {

            Peer     peer;
            PeerPair newpeer( sin, peer );

            std::pair<Peers::iterator,bool> p = peers.insert( newpeer );

            return &p.first->second;

        }

//        int Xfer( HWND hWnd, Peer * pPeer, CWho * pYou );

};


/*

 Files added to this list have these different states:

 - If the file was already in the list,
   the peer is simply added to the list and
   the state is set to awaiting confirmation for that peer.

 - Awaiting confirmation of acceptance.
   This can result in the file being cancelled and removed from the list

 - After acceptance, the file is sent a few blocks at a time.
   A window-size number of packets will be sent and await acknowledgement.

 - If a cancellation is received,
   the file xfer to that peer is stopped,
   when no hosts await the file,
   the file is removed from the list.

 - If a peer replies that it has received all of the file,
   the peer is removed from the file's recipient-list.

*/
class FileList: public std::vector<File> {

    public:

#if 0
        bool get_fname( LPCTSTR lpszSendFile, TSTRING & filename ) {

#ifdef _WIN32
            const char * slash = strrchr( lpszSendFile, '\\' );
#else
            const char * slash = strrchr( lpszSendFile, '/' );
#endif

            if ( NULL == slash ) {

                return false;

            }

            slash++;

            filename.assign( slash );

            return true;

        }
#endif

        File * Find( Entity entityfileID ) {

            for ( unsigned u = 0; u < size(); u++ ) {

                if ( at( u ).fi.entityfileID == entityfileID ) {

                    return & at( u );

                }

            }

            return NULL;

        }


        bool Remove( Entity entityfileID ) {

            for ( unsigned u = 0; u < size(); u++ ) {

                if ( at( u ).fi.entityfileID == entityfileID ) {

                    erase( begin() + u );
                    return true;

                }

            }

            return false;

        }


        File * Add( LPCTSTR pszFileName ) {

            File file;

            push_back( file );

            File * pFile = & ( at( size() - 1 ) );

            pFile->fi.localfilename.assign( pszFileName );

            pFile->fi.get_fname( pszFileName, pFile->fi.filename );

            if ( 0 == pFile->fi.filename.size() ) {

                pFile->fi.filename.assign( pszFileName );

            }

            return pFile;

        }


};


#endif /* __XFER_H__ */
