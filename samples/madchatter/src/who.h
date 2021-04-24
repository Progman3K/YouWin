#ifndef __WHO_H__
#define __WHO_H__


//#include <strings.h>
#include <string.h>


#if defined( linux ) || defined( __DARWIN__ )
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "mercury.h"
#include "output.h"


LPCTSTR INet_NToT( in_addr addr );


/* Used to define a host, should be unique across all hosts. */
typedef struct {

    Entity  me;

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

} Essence;


class CWho {

    public:

        static sockaddr_in broadcast;

        static void init() {

            broadcast.sin_family      = AF_INET;
            broadcast.sin_port        = htons( MERCURY_DGRAM_PORT );
            broadcast.sin_addr.s_addr = htonl( INADDR_BROADCAST );

        }

        CWho( Entity I, sockaddr_in original ) : TimeLastSeen(0) {

            who.me  = I;
            who.sin = original;
            s       = INVALID_SOCKET;
            bInsane = false;

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "I am %lX - %s:%u AF: %u" ), (long)who.me, INet_NToT( who.sin.sin_addr ), (unsigned)ntohs( who.sin.sin_port ), (unsigned)who.sin.sin_family );

        }

        ~CWho() {

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Deletion of %lX - %s:%u AF: %u" ), (long)who.me, INet_NToT( who.sin.sin_addr ), (unsigned)ntohs( who.sin.sin_port ), (unsigned)who.sin.sin_family );

            if ( bInsane ) {

                return;

            }

            bInsane = true;

            if ( INVALID_SOCKET != s ) {

//                closesocket( s );

            }

            s = INVALID_SOCKET;

        }

        const TCHAR * GetName() {

            return Name.c_str();

        }

        Entity GetEntity() {

            return who.me;

        }

        SOCKET GetSocket() {

            return s;

        }

        sockaddr GetSa() {

            return who.sa;

        }

        sockaddr_in GetSin() {

            return who.sin;

        }

        bool SetSocket( SOCKET NewSocket ) {

            if ( bInsane ) {

                /* Operation refused by reason of isanity. */
                return false;

            }

            if ( ( INVALID_SOCKET == NewSocket ) || ( INVALID_SOCKET != s ) ) {

                /* Operation refused, can only be done once. */
                return false;

            }

            s = NewSocket;

            return true;

        }


        long sendmsg( sockaddr_in YourSin, MsgType type, const char * pBuffer, size_t Len ) {

            union {

                sockaddr    sa;
                sockaddr_in sin;

            };

            ZeroMemory( &sa, sizeof( sa ) );

            sin = YourSin;

            union {

                Exchange_t  et;
                char        cBuffer[ sizeof( Exchange_t ) + MAX_DATA_LENGTH];

            };

            ZeroMemory( cBuffer, sizeof( cBuffer ) );

            et.Header.Type      = htons( type );
            et.Header.Length    = htons( (unsigned short)( sizeof( et.Header ) + Len ) );
            et.Header.entity    = who.me;

            memcpy( et.Header.UserData, pBuffer, Len );

            long lRet = sendto( s, cBuffer, (int)( sizeof( et.Header ) + Len ), 0, &sa, sizeof( sa ) );

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Sent datagram on socket %u to %s:%u AF: %u - Code %ld" ), s, INet_NToT( YourSin.sin_addr ), (unsigned)ntohs( YourSin.sin_port ), (unsigned)YourSin.sin_family, lRet );
//            DBG_DMP( DBG_DA TA_DUMPS, cBuffer, sizeof( et.Header ) + iLen );

            return lRet;

        }


        long Chat( sockaddr_in YourSin, const char * pBuffer, int iLen ) {

            return sendmsg( YourSin, MsgType_Chat, pBuffer, iLen );

        }

        long SendFile( HWND hWnd, class Peer &, sockaddr_in YourSin, class File & file );

        long Broadcast( const char * pBuffer, int iLen ) {

            return sendmsg( broadcast, MsgType_Status, pBuffer, iLen );

        }

        bool Sane() {

            return ! bInsane;

        }

        void SetTimeLastSeen( time_t now ) {

            TimeLastSeen = now;

        }

        time_t GetTimeLastSeen( void ) {

            return TimeLastSeen;

        }

//        int recvfrom( IOutput & Output,  );

        int RecvData( HWND hWnd, CWho * pMe, IOutput & Output, Exchange_t * pET, size_t Size );

    private:

        int  ProcessFileXferOffer( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_info * pEF, size_t Size );
        int  ProcessFileXferChunk( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_chunk * pEF, size_t Size );
        int  ProcessFileXferAck( HWND hWnd, CWho * pMe, IOutput & Output, const file_xfer_ack * pEF, size_t Size );

        void DisplayUserText( IOutput & Output, const TCHAR * pszText );

        bool    bInsane;
        SOCKET  s;
        time_t  TimeLastSeen;

        Essence    who;
        textstring Name;

};


#endif /* __WHO_H__ */
