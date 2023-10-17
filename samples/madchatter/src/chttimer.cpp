

#include "chatter.h"


#ifdef WIN32
void CChatterMainWnd::Sound( HWND hWnd ) {

    static BOOL  bBeeped    = false;
//    static DWORD dwNextBeep = 0;

    if ( ! ( IsMinimized( hWnd ) && bNewCommunications ) ) {

        bBeeped = false;
        return;

    }

    if ( ! bBeeped ) {

#ifndef _WIN32_WCE

        DWORD dwStyle;

        SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW );
        dwStyle = GetWindowExStyle( hWnd );
        SetWindowLong( hWnd, GWL_EXSTYLE, dwStyle | WS_EX_TOPMOST );
//      ShowWindow( g_hMainDlg, SW_SHOWNA );

#endif /* ! _WIN32_WCE */

        bBeeped = true;

    }

//    if ( GetTickCount() < dwNextBeep ) {

//        return;

//    }

//  if ( ! g_bMute ) {

//      if ( ! PlaySoundEvent( g_hInst, ID( IDS_INITIALIZATION_SECTION ), ID( IDS_INCOMING_MESSAGE ), g_szChatterIni ) ) {

//          MessageBeep( 0 );

//      }

//  }

//  dwNextBeep = ( GetTickCount() + g_uiTimerTimeout );

}
#endif  /* WIN32 */


void CChatterMainWnd::Vision( HWND hWnd ) {

    HDC hDC;

    if ( ! ( IsMinimized( hWnd ) && bNewCommunications ) ) {

        return;

    }

    if ( ID_NUM_ANIM_FRAMES <= dwFrame ) {

        dwFrame = 0;

    }

    if ( NULL == ( hDC = GetDC( hWnd ) ) ) {

        return;

    }

#ifndef _WIN32_WCE
#ifdef WIN32
    FlashWindow( hWnd, true );
#endif
#endif /* ! _WIN32_WCE */
    DrawIcon( hDC, 0, 0, hHatAnimIcon[dwFrame] );
    SetClassIcon( hWnd, hHatAnimIcon[dwFrame] );
    UpdateWindow( hWnd );
#ifndef _WIN32_WCE
#ifdef WIN32
    FlashWindow( hWnd, false );
#endif
#endif /* ! _WIN32_WCE */
    UpdateWindow( hWnd );

    ReleaseDC( hWnd, hDC );

    dwFrame++;

}


void CChatterMainWnd::CheckAbsents( HWND hWnd ) {

    unsigned uPeersGoneAwayCount = 0;

    /* Look for partners who've been absent too long */
    for( int i = ListBox_GetCount( hUserListWnd ); 0 < i; i-- ) {

        CWho * pYou = (CWho *)ListBox_GetItemData( hUserListWnd, i - 1 );

        if ( ( pYou->GetTimeLastSeen() + HEARD_PEER_MAX_LIMIT_SECONDS ) < now() ) {

            /* Peer has gone away */
            (void)ListBox_DeleteString( hUserListWnd, i - 1 );
            uPeersGoneAwayCount++;

        }

    }

    if ( 0 < uPeersGoneAwayCount ) {

        HandleSendButtons( hWnd );

    }

}


void CChatterMainWnd::OnTimer( HWND hWnd, UINT uiTimerID ) {

    switch( uiTimerID ) {

        case ID_CHATTER_BROADCAST_TIMER:

            /* Tell everyone I'm still around */
            pMe->Broadcast( NULL, 0 );

            /* Check to see who's left */

            /* Look through the list of peers */
            CheckAbsents( hWnd );
            break;

        default:

            /* All other unaccounted-for timers represent file-transfers */
            for ( size_t u = outgoingfiles.size(); 0 < u; u-- ) {

                File & file = outgoingfiles.at( u - 1 );

                if ( ( 0 == file.peers.size() ) && ( 0 == xfers.size() ) ) {

                    /* No more peers for this file */
                    outgoingfiles.erase( outgoingfiles.begin() + ( u - 1 ) );
                    continue;

                }

                for ( Peers::iterator i = file.peers.begin(); i != file.peers.end(); ++i ) {

                    if ( i->second.uiTimerID != uiTimerID ) {

                        continue;

                    }

                    CWho * pYou = GetYou( i->second.who, i->first, NULL );

                    if ( NULL == pYou ) {

                        /* Peer has gone away since starting the transfer, cancel */

                        TCHAR szLog[1024];

                        ZeroMemory( szLog, sizeof( szLog ) );
                        int iLen = _stprintf( szLog, TEXT( "Peer %s:%d has gone away since starting the transfer, cancelling" ), INet_NToT( i->first.sin_addr ), i->first.sin_port );
                        AppendText( szLog, iLen, true );
//                        DBG_MSG( DBG_GENERAL_INFORMATION, szLog );
                        KillTimer( hWnd, uiTimerID );
                        file.peers.erase( i );
                        return;

                    }

                    pMe->SendFile( hWnd, i->second, pYou->GetSin(), file );

//                    file.Xfer( hWnd, &i->second, pYou );

                }

            }

            /* Check if there is a fragment to send or if a file is long overdue and should be cancelled */
            break;

    }

#ifdef WIN32
    Sound( hWnd );
#endif  /* WIN32 */
    Vision( hWnd );

}
