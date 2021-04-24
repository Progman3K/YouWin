#ifndef __CHATWND_H__
#define __CHATWND_H__


#include "dialoginfo.h"
#include "output.h"
#include "who.h"
#include "defines.h"
#include "DlgWnd.h"


/*___________________________________________________________________________

    WinSock Message Crackers
___________________________________________________________________________*/
#ifndef HANDLE_WM_WSAASYNCSELECT
/* OnWsaAsyncSelect( HWND hWnd, SOCKET s, unsigned uFDEvent, unsigned uErrorCode ); */
#define HANDLE_WM_WSAASYNCSELECT( hWnd, wParam, lParam, fn ) ( (fn)( (hWnd), (SOCKET)( wParam ), (WSAGETSELECTEVENT( lParam )), (WSAGETASYNCERROR( lParam )) ), 0L )
#endif /* HANDLE_WM_WSAASYNCSELECT */

#ifndef FORWARD_WM_WSAASYNCSELECT
#define FORWARD_WM_WSAASYNCSELECT( hWnd, uiMsg, s, Event, Error, fn ) ( (fn)( (hWnd), (uiMsg), (WPARAM)( s ), (MAKELPARAM( ( Event ), ( Error ) )) ) )
#endif /* FORWARD_WM_WSAASYNCSELECT */

#ifndef HANDLE_WM_WSAASYNCGETHOSTBYNAME
/* OnWsaAsyncGethost( HWND hWnd, HANDLE hAsyncRequest, unsigned uBufferLen, unsigned uErrorCode ); */
#define HANDLE_WM_WSAASYNCGETHOSTBYNAME( hWnd, wParam, lParam, fn ) ( (fn)( (hWnd), (HANDLE)( wParam ), (WSAGETASYNCBUFLEN( lParam )), (WSAGETASYNCERROR( lParam )) ), 0L )
#endif /* HANDLE_WM_WSAASYNCGETHOSTBYNAME */


#define ID_NUM_ANIM_FRAMES 4


class CChatterMainWnd : public DlgWnd<CChatterMainWnd>, public IOutput {

        static BOOL DoEdit_ScrollCaret( HWND hEditWnd ) {

            int iLen;

            iLen = GetWindowTextLength( hEditWnd );
            Edit_SetSel( hEditWnd, iLen, iLen );

#if defined( _WIN32 ) || defined( WIN32 )
            Edit_ScrollCaret( hEditWnd );
#endif

            return true;

        }


        static void AddText( HWND hEditWnd, LPCTSTR lpszText ) {

            int iLen;

            iLen = GetWindowTextLength( hEditWnd );
            Edit_SetSel( hEditWnd, iLen, iLen );
            Edit_ReplaceSel( hEditWnd, lpszText );

        }


        static BOOL EditAppendTextEx( HINSTANCE hInst, HWND hEditCtl, LPCTSTR lpszText, size_t StringSize, BOOL bOnANewLine, BOOL bScrollCaret ) {

            TCHAR szTemp[1024];

            if ( ! IsWindow( hEditCtl ) ) {

                /* Window does not yet exist or no longer exists. */
                return false;

            }

            if ( 0 == HIWORD( lpszText ) ) {

                ZeroMemory( szTemp, sizeof( szTemp ) );

                if ( 0 == LoadString( hInst, LOWORD( (uintptr_t)lpszText ), szTemp, ( sizeof( szTemp ) / sizeof( szTemp[0] ) ) - 1 ) ) {

                    return false;

                }

                lpszText = szTemp;

            }

            if ( bOnANewLine ) {

                AddText( hEditCtl, TEXT( EOL ) );

            }

            AddText( hEditCtl, lpszText );

            if ( bScrollCaret ) {

                DoEdit_ScrollCaret( hEditCtl );
            }

            return true;

        }


        static int EditAppendText( HINSTANCE hInst, HWND hWnd, const TCHAR * lpszText, size_t StringSize, bool bOnANewLine ) {

            return EditAppendTextEx( hInst, hWnd, lpszText, StringSize, bOnANewLine, true );

        }


    public:

        CChatterMainWnd() {

            bNewCommunications = false;
            hAppIcon           = NULL;
            hInputWnd          = NULL;
            hOutputWnd         = NULL;
            hUserListWnd       = NULL;
            pMe                = NULL;
            hFileXfer          = NULL;
            dwFrame            = 0;
            uNextTimerID       = ID_INDIVIDUAL_XFER_TIMER_ID_BASE;

            for ( unsigned u = 0; u < Dim( hHatAnimIcon ); u++ ) {

                hHatAnimIcon[u] = NULL;

            }

        }

        virtual ~CChatterMainWnd() {}

        int AppendText( const TCHAR * pszText, size_t StringSize, bool bOnANewLine ) override {

            return EditAppendText( GetWindowInstance( m_hDlg ), hOutputWnd, pszText, StringSize, bOnANewLine );

        }

        INT_PTR bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override;

    private:

        typedef enum {

            xfer_finished_error,
            xfer_continue,
            xfer_finished_ok

        } xfer_session_status;

        CWho *   pMe;

        CWho *   GetYou( Entity entity, sockaddr_in sin, int * lpiListBoxIndex );

        bool     bNewCommunications;

        HWND     hInputWnd;
        HWND     hOutputWnd;
        HWND     hUserListWnd;
        HWND     hFileXfer;
        UINT_PTR uNextTimerID;

        DialogInfo portrait;
        DialogInfo landscape;

        HICON    hAppIcon;

        HICON    hHatAnimIcon[ID_NUM_ANIM_FRAMES];

        DWORD    dwFrame;
        void     Vision( HWND hWnd );
#ifdef WIN32
        void     Sound( HWND hWnd );
#endif /* WIN32 */

        xfer_session_status ProcessRecvFile( HWND hWnd, TCPXferInfo & tcpxfr, HNATIVEFILE hFile, SOCKET s );

        void     Error( HWND hFocusWnd, HINSTANCE hInst, LPCTSTR lpszText, LPCTSTR lpszTitle );

        void     CheckAbsents( HWND hDlg );

        void     HandleSendButtons( HWND hDlg );

        BOOL     SendChat( HWND hDlg, HINSTANCE hInst, const char * pBuffer, unsigned uLen );
        void     PrepareSendFile( HWND hWnd, LPCTSTR lpszSendFile, CWho * pYou, unsigned short usFlags, unsigned int uiParams );

        void     OnClose( HWND hDlg );
        void     OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        void     OnDeleteItem( HWND hDlg, const DELETEITEMSTRUCT * pdi );
        void     OnDestroy( HWND hDlg );
        void     OnDisplayChange( HWND hDlg, UINT uiBitsPerPixel, UINT cx, UINT cy );
        BOOL     OnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );
        void     OnSize( HWND hDlg, UINT uiState, int iCX, int iCY );
        void     OnTimer( HWND hDlg, UINT uiTimerID );
        void     OnWSAAsyncNotification( HWND hDlg, SOCKET s, WORD wEventCode, WORD wErrorCode );
        void     OnWSAAsyncGetHostByName( HWND hDlg, HANDLE hAsyncTask, unsigned uBuffLen, unsigned uError );
        void     OnWSAAsyncTCPXfer( HWND hDlg, SOCKET s, WORD wEventCode, WORD wErrorCode );

};


#endif /* __CHATWND_H__ */
