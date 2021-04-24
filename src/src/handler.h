

#ifndef YW_H_HANDLER
#define YW_H_HANDLER


#include <winsock2.h>
#include <vector>
#include <sys/select.h>


class Handler {

    public:


        Handler( SOCKET session, class EventQ * pThreadEventQ ) {

            s  = session;
            pQ = pThreadEventQ;

        }

        virtual ~Handler( void ) {}


        int PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );


        virtual bool EventHandler() = 0;


        SOCKET getsocket() {

            return s;

        }


        SOCKET s;
        class EventQ * pQ;

};


//typedef std::vector<Handler *> Q;
class HandlerList : public std::vector<Handler *> {

    public:


        int Find( SOCKET s ) {

            for( unsigned u = 0; u < size(); u++ ) {

                if ( at( u )->getsocket() == s ) {

                    return u;

                }

            }

            return -1;

        }


        void HandleEvents( fd_set & fdlist ) {

            for( iterator i = begin() ; i != end(); ++i ) {

                SOCKET s = (*i)->getsocket();

                if ( FD_ISSET( s, &fdlist ) ) {

                    bool bRet = (*i)->EventHandler();

                    if ( ( ! bRet ) /* || ( -1 == Find( s ) ) */ ) {

                        /* Error or does not wish to continue receiving events */
//                        DBG_MSG( DBG_ERROR, TEXT( "DISCONNECTING EVENT HANDLER FOR SOCKET %d" ), s );
//                        erase( i );

                    }

                    return;

                }

            }

        }

        int SetFDs( fd_set & fdlist ) {

            SOCKET Highest = -1;

//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Evaluating socket set: %u descriptors" ), size() );

            for( iterator i = begin() ; i != end(); ++i ) {

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Found socket %d..." ), (*i)->getsocket() );

                FD_SET( (*i)->getsocket(), &fdlist );

                if ( (*i)->getsocket() > Highest ) {

                    Highest = (*i)->getsocket();

                }

            }

            return Highest;

        }

};


#endif  /* YW_H_HANDLER */
