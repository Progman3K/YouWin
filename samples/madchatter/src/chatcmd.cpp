

#include "chatter.h"


BOOL AreYouSure( HINSTANCE hInst, HWND hFocusWnd, LPCTSTR lpszMessageTitle, LPCTSTR lpszExtra, UINT uDefButton ) {

    TCHAR	szString[1024];
    TCHAR	szMessage[1024];

    ZeroMemory( szMessage, sizeof( szMessage ) );
    ZeroMemory( szString, sizeof( szString ) );

    if ( NULL != lpszMessageTitle ) {

        if ( HIWORD( lpszMessageTitle ) == 0 ) {

            LoadString( hInst, LOWORD( (uintptr_t)lpszMessageTitle ), szMessage, Dim( szMessage ) - 1 );

        } else {

            _tcsncpy( szMessage, lpszMessageTitle, Dim( szMessage ) - 1 );

        }

    }

    if ( lpszExtra && ( HIWORD( lpszExtra ) == 0 ) ) {

        if ( LoadString( hInst, LOWORD( (uintptr_t)lpszExtra ), szString, Dim( szString ) - 1 ) ) {

            /* User wants us to access parameter from string table.	*/
            return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, szString, szMessage, MB_YESNO | uDefButton | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

        } else {

            return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, TEXT( "" ), szMessage, MB_YESNO | uDefButton | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

        }

    }

    return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, lpszExtra, szMessage, MB_YESNO | uDefButton | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

}


void CChatterMainWnd::Error( HWND hFocusWnd, HINSTANCE hInst, LPCTSTR lpszText, LPCTSTR lpszTitle ) {

    TCHAR szMessage[512];

    if ( lpszText && ( HIWORD( lpszText ) == 0 ) ) {

        if ( 0 == LoadString( hInst, LOWORD( (uintptr_t)lpszText ), szMessage, Dim( szMessage ) - 1 ) ) {

            _stprintf( szMessage, TEXT( "Inaccesible string %u" ), (unsigned)( LOWORD( (uintptr_t)lpszText ) ) );

        }

    } else {

        _tcsncpy( szMessage, lpszText ? lpszText : TEXT( "Error" ), Dim( szMessage ) - 1 );

    }

    if ( lpszTitle && ( HIWORD( lpszTitle ) == 0 ) ) {

        TCHAR szString[1024];

        if ( LoadString( hInst, LOWORD( (uintptr_t)lpszTitle ), szString, Dim( szString ) - 1 ) ) {

            /* User wants us to access parameter from string table.	*/
            MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, szMessage, szString, MB_ICONHAND | MB_SYSTEMMODAL );

        } else {

            MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, szMessage, NULL, MB_ICONHAND | MB_SYSTEMMODAL );

        }

    } else {

        MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, szMessage, lpszTitle, MB_ICONHAND | MB_SYSTEMMODAL );

    }

}


void CChatterMainWnd::HandleSendButtons( HWND hDlg ) {

    if ( Button_GetCheck( GetDlgItem( hDlg, IDB_ALL_CALL ) ) ) {

        /* broadcast is ON, enable sendfile. */
        Button_Enable( GetDlgItem( hDlg, IDB_SENDFILE ), true );

        if ( 0 == Edit_GetTextLength( GetDlgItem( hDlg, IDE_USER_INPUT ) ) ) {

            /* There is no text, disable send. Done */
            Button_Enable( GetDlgItem( hDlg, IDOK ), false );

        } else {

            Button_Enable( GetDlgItem( hDlg, IDOK ), true );

        }

    } else {

        /* Broadcast is OFF, disable sendfile unless a specific peer is selected */

        /* There is text, broadcast is OFF */
        if ( LB_ERR == ListBox_GetCurSel( hUserListWnd ) ) {

            /* There is no peer selected, disable sends. Done. */
            Button_Enable( GetDlgItem( hDlg, IDB_SENDFILE ), false );

            Button_Enable( GetDlgItem( hDlg, IDOK ), false );
            return;

        }

        Button_Enable( GetDlgItem( hDlg, IDB_SENDFILE ), true );

        /* There is text */
        if ( 0 == Edit_GetTextLength( hInputWnd ) ) {

            /* There is no text, disable send. Done */
            Button_Enable( GetDlgItem( hDlg, IDOK ), false );

        } else {

            /* There is text, enable send. Done */
            Button_Enable( GetDlgItem( hDlg, IDOK ), true );

        }

    }

}


BOOL CChatterMainWnd::SendChat( HWND hDlg, HINSTANCE hInst, const char * pBuffer, unsigned uLen ) {

    CWho *  pYou;

    if ( Button_GetCheck( GetDlgItem( hDlg, IDB_ALL_CALL ) ) ) {

        pMe->Broadcast( pBuffer, uLen );
        return true;

    }

    int i;
    if ( LB_ERR == ( i = ListBox_GetCurSel( hUserListWnd ) ) ) {

        Error( hDlg, hInst, MAKEINTRESOURCE( IDS_PICK_DESTINATION ), MAKEINTRESOURCE( IDS_PROGRAM_TITLE ) );
        return false;

    }

    pYou = (CWho *)ListBox_GetItemData( hUserListWnd, i );

    pMe->Chat( pYou->GetSin(), pBuffer, uLen );

    return true;

}


void CChatterMainWnd::OnClose( HWND hDlg ) {

    if ( ! AreYouSure( GetWindowInstance( hDlg ), hDlg, MAKEINTRESOURCE( IDS_PROGRAM_TITLE ), MAKEINTRESOURCE( IDS_EXIT ), MB_DEFBUTTON2 ) ) {

        return;

    }

    EndDialog( hDlg, 0 );

}


BOOL GetFileName( HWND hDlg, LPTSTR lpstrFile, DWORD nMaxFile ) {

    TCHAR szHome[PATH_MAX];

    ZeroMemory( szHome, sizeof( szHome ) );

    if ( ! ( S_OK == SHGetFolderPath( hDlg, CSIDL_PERSONAL, NULL, 0, szHome ) ) ) {

//        DBG_MSG( DBG_ERROR, TEXT( "FAILED TO RETRIEVE PATH" ) );

    }

    OPENFILENAME ofn;

    ZeroMemory( &ofn, sizeof( ofn ) );

    ofn.lStructSize     = sizeof( ofn );
    ofn.hwndOwner       = hDlg;
    ofn.lpstrFile       = lpstrFile;
    ofn.lpstrInitialDir = szHome;
    ofn.nMaxFile        = nMaxFile;
//    ofn.hInstance       = GetModuleHandle( NULL );
    ofn.Flags           = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    return ( IDOK == GetOpenFileName( &ofn ) );

}



void CChatterMainWnd::PrepareSendFile( HWND hWnd, LPCTSTR lpszSendFile, CWho * pYou, unsigned short usFlags, unsigned int uiParam ) {

    if ( 0 == pYou ) {

        return;

    }

    HNATIVEFILE hFile = NativeFile::Open( lpszSendFile, NativeFile::FOR_READING );

    if ( HNATIVEFILE_ERROR == hFile ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Unable to open file '%s'" ), lpszSendFile );
        return;

    }

    FILEINFO fi;

    fi.usFlags = usFlags;

    fi.uiTimerID = uNextTimerID;

    fi.uiParam = uiParam;

    fi.localfilename.assign( lpszSendFile );

    if ( ! fi.get_fname( lpszSendFile, fi.filename ) ) {

        fi.filename.assign( lpszSendFile );

    }

    fi.entityfileID = GenerateEntity();

    NativeFile::Seek( hFile, 0, NativeFile::FROM_END );

    fi.ullFilelength = NativeFile::Tell( hFile );

    NativeFile::Close( hFile );

    fi.usChunksize = TYPICAL_CHUNK_SIZE;

    if ( file_xfer_info::TCP_SEND & usFlags ) {

        union {

            sockaddr    sa;
            sockaddr_in sin;

        };

        ZeroMemory( &sa, sizeof( sa ) );

        SOCKET s = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        sin.sin_addr.s_addr = htonl( INADDR_ANY );
        sin.sin_port        = htons( uiParam );
        sin.sin_family      = AF_INET;

//        int i;

//        i =
        bind( s, &sa, sizeof( sa ) );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "bind( %d ) --> %d" ), s, i );

//        i =
        listen( s, 1 );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "listen( %d ) --> %d" ), s, i );

//        i =
        WSAAsyncSelect( s, hWnd, WM_WSAASYNCTCPXFER, FD_ACCEPT );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "WSAAsyncSelect( %d ) --> %d" ), s, i );

        ZeroMemory( &sa, sizeof( sa ) );

        socklen_t iAddrLen = sizeof( sa );
//        i =
        getsockname( s, &sa, &iAddrLen );

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "getsockname --> %d: port %d" ), i, ntohs( sin.sin_port ) );

        fi.uiParam = ntohs( sin.sin_port );

        if ( 0 == fi.uiParam ) {

            // fail
//            DBG_MSG( DBG_ERROR, TEXT( "UNABLE TO SET UP LISTENING PORT" ) );
            return;

        }

        TCPXferInfo tcpxfr;

        tcpxfr.fi = fi;

        TCPXfer xferPair;

        xferPair.first  = s;
        xferPair.second = tcpxfr;

        xfers.insert( xferPair ); //xfers.end()

    }

    /* Put in queue so it gets offered periodically */
    File * pFile = outgoingfiles.Add( lpszSendFile );

    Peer * pPeer = pFile->FindPeer( pYou->GetSin() );

    if ( NULL != pPeer ) {

        /* Existing transfer */
//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Already sending file '%s' to %s:%d" ), pFile->fi.filename.c_str(), INet_NToT( pYou->GetSin().sin_addr ), pYou->GetSin().sin_port );
        return;

    }

    /* New transfer */
    pFile->fi = fi;

    /* Add to files-I'm-sending list */

    pPeer = pFile->AddPeer( pYou->GetSin() );

    if ( NULL == pPeer ) {

        return;

    }

    pPeer->uWindowSize = DEFAULT_WINDOW_SIZE;

    pPeer->state = XFER_STATE_WAITING_ACCEPT;

    pFile->InitializePeerStorage( pPeer );

    pPeer->who = pYou->GetEntity();
    pPeer->uiTimerID = uNextTimerID;

    SetTimer( hWnd, uNextTimerID, OFFER_FILE_TIMER_INTERVAL_SECONDS * 1000, NULL );

    FORWARD_WM_TIMER( hWnd, uNextTimerID, PostMessage );

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Offering file %s, %lu bytes on timer ID %u" ), lpszSendFile, (long)fi.ullFilelength, uNextTimerID );

    uNextTimerID++;

}


void CChatterMainWnd::OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

    int     i;
	BOOL    bSent;
    TCHAR   szSendFile[PATH_MAX + 1];
    TCHAR   szUserMessage[MAX_DATA_LENGTH + sizeof( TCHAR )];

    switch( iID ) {

        case IDE_USER_INPUT:
        case IDLB_USERLIST:
        case IDB_ALL_CALL:

            HandleSendButtons( hDlg );
            break;

        case IDB_MUTE:

            //g_bMute = ( ! g_bMute );

            // SetAppProfileBool( g_hInst, MAKEINTRESOURCE( IDS_INITIALIZATION_SECTION ), MAKEINTRESOURCE( IDS_MUTE_SOUND ), g_bMute, g_szChatterIni );
            break;

        case IDB_SENDFILE:

            /* Choose file */
            ZeroMemory( szSendFile, sizeof( szSendFile ) );

            if ( ! GetFileName( hDlg, szSendFile, Dim( szSendFile ) - 1 ) ) {

                break;

            }

            if ( Button_GetCheck( GetDlgItem( hDlg, IDB_ALL_CALL ) ) ) {

                /* broadcast is ON, offer file to everyone. */
                PrepareSendFile( hDlg, szSendFile, NULL, 0, 0 );

            } else {

                /* Broadcast is OFF, send file to selected peer */

                if ( LB_ERR == ( i = ListBox_GetCurSel( hUserListWnd ) ) ) {

                    /* There is no peer selected, error. */
                    break;

                }

                /* Send to this peer */
                CWho *  pYou;

                if ( LB_ERR == (LRESULT)( pYou = (CWho *)ListBox_GetItemData( hUserListWnd, i ) ) ) {

                    /* Error retrieving who. */
                    break;

                }

                PrepareSendFile( hDlg, szSendFile, pYou, file_xfer_info::TCP_SEND, 0 );

            }

            break;

        case IDCANCEL:

            FORWARD_WM_CLOSE( hDlg, PostMessage );
            break;

        case IDOK:

//            EnumChildWindows( hDlg, (WNDENUMPROC)MemorizePositions, 0 );

            ZeroMemory( szUserMessage, sizeof( szUserMessage ) );

            if ( 0 == ( i = GetWindowText( hInputWnd, szUserMessage, Dim( szUserMessage ) - 1 ) ) ) {

                break;

            }

#ifdef UNICODE
            {

                char szASCIIMsg[ Dim( szUserMessage ) ];
                ZeroMemory( szASCIIMsg, sizeof( szASCIIMsg ) );
                i = WideCharToMultiByte( CP_UTF8, 0, szUserMessage, i, szASCIIMsg, Dim( szASCIIMsg ) - 1, NULL, NULL );

			    bSent = SendChat( hDlg, GetWindowInstance( hDlg ), szASCIIMsg, i );

            }
#else
			bSent = SendChat( hDlg, GetWindowInstance( hDlg ), szUserMessage, i );
#endif

            if ( bSent ) {

                AppendText( g_szChatterHostName, Dim( g_szChatterHostName ), true );
                AppendText( MAKEINTRESOURCE( IDS_HOST_SPEAK ), 0, false );
                AppendText( szUserMessage, Dim( szUserMessage ), false );

                SetWindowText( hInputWnd, TEXT( "" ) );

                if ( GetFocus() == hCtlWnd ) {

                    /* OK button used to send IDOK, about to be disabled; set to other control */
                    SetFocus( hInputWnd );

                }

                Button_Enable( GetDlgItem( hDlg, IDOK ), false );

            }
            break;

    }

}
