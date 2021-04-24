

#include <ws2x.h>


class CUDPTrace {

    private:

        SOCKET  TraceSocket;

        BOOL bPrepSocket( HWND hNotifyWnd );

    public:

        CUDPTrace( void ) {

            TraceSocket = -1;

        }

        ~CUDPTrace( void ) {

            Close();

        }

        BOOL bInit( HWND hWnd ) {

            if ( ! bPrepSocket( hWnd ) ) {

                return false;

            }

            return true;

        }

        void Close( void ) {

            if ( (SOCKET)-1 != TraceSocket ) {

                closesocket( TraceSocket );

            }

            TraceSocket = -1;

        }

};
