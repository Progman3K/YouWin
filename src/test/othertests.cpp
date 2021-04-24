void SocketTest( void ) {

    SOCKET s = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    WSAAsyncSelect( s, GetDesktopWindow(), WM_WSAASYNCTCPXFER, FD_READ | FD_CLOSE );

    closesocket( s );

}


void OnTimer( HWND hWnd, UINT_PTR uID ) {

//    printf( "\nWM_TIMER %lX:%X.", (LONG)hWnd, uID );

}


WNDPROC g_OldWndProc = NULL;


LRESULT lWndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    TRACE_MESSAGE( (DWORD)-1, hWnd, uiMsg, wParam, lParam );

    return g_OldWndProc( hWnd, uiMsg, wParam, lParam );

}


class array_item {

    public:

        array_item( int iPos, int i ) {

            iPosition = iPos;
            iVal = i;

        }

        int iPosition;
        int iVal;

};

std::vector<array_item> an_array;


int comparefunc( const array_item * pItem1, const array_item * pItem2 ) {

    return 0;

}


void MeasureStrings( HWND hDlg, HDC hDC, LPCTSTR lpszName, LPTSTR lpszOut ) {

    SIZE sizeAlone;
    SIZE sizeWithAmpersand;

    GetTextExtentPoint( hDC, "W",  1, &sizeAlone );
    GetTextExtentPoint( hDC, "&W", 2, &sizeWithAmpersand );

    sprintf( lpszOut, "Control type %s: %ld alone, %ld with ampersand", lpszName, sizeAlone.cx, sizeWithAmpersand.cx );

}


void ListBoxTest( HWND hDlg ) {

    HWND hLBWnd = GetDlgItem( hDlg, IDLB_TEST );

    int i;

    i = ListBox_AddString( hLBWnd, "A" );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "String 'A' index is %d" ), i );

    i = ListBox_AddString( hLBWnd, "C" );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "String 'C' index is %d" ), i );

    i = ListBox_AddString( hLBWnd, "B" );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "String 'B' index is %d" ), i );

}


void TestTextSize( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

    TCHAR      szText[128];
    RECT       r;
    HBRUSH     hbr;
    TEXTMETRIC tm;
    SIZE       s;

    if ( BN_CLICKED != uiNotifyCode ) {

        return;

    }

    switch( iID ) {

        case IDCANCEL:

            MessageBox( hDlg, "Quitting", "Test", MB_OK );
            PostQuitMessage( 0 );
            break;

        case IDOK:

            MoveWindow( hDlg, 0, 0, 200, 300, true );
            break;

            BOOL bTranslated = false;

            UINT u = GetDlgItemInt( hDlg, IDE_TEST, &bTranslated, true );

            sprintf( szText, "GetDlgItemInt returned %d, translate %s", u, bTranslated ? "success" : "FAILED" );

            MessageBox( hDlg, szText, "info", MB_OK );

            hbr = CreateSolidBrush( RGB( 255, 255, 255 ) );

            HWND hOutputWnd = GetDlgItem( hDlg, IDST_OUTPUT );
            HDC hStaticDC   = GetDC( hOutputWnd );
            bool bOneLine = ( BST_CHECKED == Button_GetCheck( GetDlgItem( hDlg, IDB_ONELINE ) ) );

            s.cx = -1;
            s.cy = -1;

            if ( GetTextExtentPoint( hStaticDC, "", 0, &s ) ) {

                sprintf( szText, "GetTextExtentPoint on empty string gives %ldx%ld", s.cx, s.cy );
//                        MessageBox( hDlg, szText, "info", MB_OK );

            } else {

                MessageBox( hDlg, "GetTextExtentPoint on empty string FAILED", "info", MB_OK );

            }

            int iLen = GetDlgItemText( hDlg, IDE_TEST, szText, sizeof( szText ) / sizeof( szText[0] ) );

            GetTextExtentPoint( hStaticDC, szText, iLen, &s );

            GetTextMetrics( hStaticDC, &tm );

//                    r.left  = 0;
//                    r.right = r.left + s.cx;

            typedef struct {

                UINT    uiFlag;
                LPCTSTR lpszName;

            } FLAG_AND_DESC;

            FLAG_AND_DESC   uFlags[] = {
                { 0,             "Normal"        },
                { DT_NOPREFIX,   "DT_NOPREFIX"   },
                { DT_HIDEPREFIX, "DT_HIDEPREFIX" },
                { DT_PREFIXONLY, "DT_PREFIXONLY" }
            };

            r.left   = 0;
            r.top    = 0;
            r.right  = r.left + s.cx;
            r.bottom = r.top + ( s.cy * ( sizeof( uFlags ) / sizeof( uFlags[0] ) ) );

            for ( unsigned u = 0; u < ( sizeof( uFlags ) / sizeof( uFlags[0] ) ); u++ ) {

//                        r.top    = u * s.cy;
//                        r.bottom = r.top + s.cy;

                FillRect( hStaticDC, &r, hbr );
                DrawText( hStaticDC, szText, iLen, &r, ( bOneLine ? DT_SINGLELINE : 0 ) | uFlags[u].uiFlag );
//                        TextOut( hStaticDC, r.left, r.top, szText, iLen );
                SetDlgItemText( hDlg, IDST_DESCRIPTION, uFlags[u].lpszName );
                MessageBox( hDlg, "that's one", "info", MB_OK );

            }

            DeleteBrush( hbr );

            ReleaseDC( hOutputWnd, hStaticDC );
            break;

    }

}


// HINSTANCE   hInst;


//char  szBackGroundFile[] = "backgrnd.asc";

//char  szWindow1Text[] = IDSZ_TEXT1;

//char    szWindow2Text[] = IDSZ_TEXT2;


// Quit the program altogether on a Q, stop whatever looping and continue on ESC.

    if ( atexit( ExitProc ) ) {

        printf( "\nAbnormal termination : Unable to register termination callback." );
        return -1;

    }


int Pause( SOCKET s ) {

    char    c;
    int     iRet;

    fd_set fdlist;
    FD_ZERO( &fdlist );
    FD_SET( s, &fdlist );

    iRet = select(  s + 1, &fdlist, NULL, NULL, NULL );

    if ( 0 >= iRet ) {

        printf( "SERIOUS ERROR ON SELECT" );
        return -1;

    }

    iRet = read( s, &c, sizeof( c ) );

    if ( 0 >= iRet ) {

        printf( "SERIOUS ERROR ON READ" );
        return -1;

    }

// ch = toupper( c );

    if ( ( 'Q' == c ) || ( 'q' == c ) ) {

        exit( 0 );

    }

    return c;

}


void ErrorActivating( void ) {

    printf( "\nAbnormal termination : TextWindows library failed activation of a window." );
    exit( -1 );

}

#if 0
void ToggleActivation( SOCKET s, HWND hWnd, HWND hWnd2 ) {

    bool Toggle = false;

    do {

        if ( Toggle ) {

            if ( 0 != ActivateTextWindow( hWnd ) ) {

                ErrorActivating();

            }

        } else {

            if ( 0 != ActivateTextWindow( hWnd2 ) ) {

                ErrorActivating();

            }

        }

        Toggle =! Toggle;

    } while ( Pause( s ) != ESC );

}


void EraseAndRedrawDesktop( void ) {

    Cls( 0 );
    RedrawDesktop();

}


void AddTextLines( SOCKET s, HWND hWnd, HWND hWnd2 ) {

    for ( int i = 0;; i++ ) {

        iPrintTextWindow( hWnd, "\n%d: Hello %s. %d", i, "World", i );
        iPrintTextWindow( hWnd2, "\n%d: Hello again, %s. %d", i, "World", i );

        UpdateWindow( hWnd );
        UpdateWindow( hWnd2 );

        // Establish file descriptor lists for stdin and server reading.  
        fd_set fdlist;
        FD_ZERO( &fdlist );
        FD_SET( s, &fdlist );

        int iRet = select(  s + 1, &fdlist, NULL, NULL, NULL );

        if ( 0 >= iRet ) {

            perror( "select" );
            exit( -1 );

        }

        if ( FD_ISSET( s, &fdlist ) ) {

            i = Pause( s );

            if ( ESC == i ) {

                break;

            }

        }

    }

}


typedef struct {

    unsigned x; unsigned cx;

    unsigned y; unsigned cy;

} Window;

bool bRectInRect( Window * pWnd, Window * pWnd2 ) {

    bool bIntersectX = false;
    bool bIntersectY = false; /* Intersection detected on the X,Y */

    if ( pWnd2->x < pWnd->x ) {

        if ( pWnd->x < ( pWnd2->x + pWnd2->cx ) ) {

            bIntersectX = true;

            if ( pWnd2->y < pWnd->y ) {

                if ( pWnd->y < ( pWnd2->y + pWnd2->cy ) ) {

                    bIntersectY = true;

                }

            } else {

                // pWnd2->y >= pWnd->y
                if ( pWnd2->y < ( pWnd->y + pWnd->cy ) ) {

                    bIntersectY = true;

                }

            }

        }

    } else {

        // pWnd2->x >= pWnd->x
        if ( pWnd2->x < ( pWnd->x + pWnd->cx ) ) {

            /* Intersection detected on the X */
            bIntersectX = true;

            if ( pWnd2->y < pWnd->y ) {

                if ( pWnd->y < ( pWnd2->y + pWnd2->cy ) ) {

                    bIntersectY = true;

                }

            } else {

                // pWnd2->y >= pWnd->y
                if ( pWnd2->y < ( pWnd->y + pWnd->cy ) ) {

                    bIntersectY = true;

                }

            }

        }

    }

    return bIntersectX && bIntersectY;

}


void testwindowing( SOCKET s ) {

    HWND hLB = CreateWindowEx( 0, "LISTBOX", "", LBS_STANDARD | /* LBS_HASSTRINGS | */ WS_VISIBLE | WS_TABSTOP, 100, 100, 400, 400, NULL, NULL, GetModuleHandle( NULL ), 0 );

    BOOL  bRet;
    RECT r;

    r.left   = 100;
    r.top    = 100;
    r.right  = r.left + 100;
    r.bottom = r.top  + 100;

    HDC hDC = GetDC( hLB );

//    MessageBox( NULL, NULL != hDC ? "dc success" : "fail", "Test", MB_OK );

    bRet = DrawEdge( hDC, &r, EDGE_BUMP, BF_RECT | BF_FLAT );

    MSG Msg;
    GetMessage( &Msg, NULL, 0, 0 );

    Pause( s );
//    MessageBox( NULL, bRet ? "drawedge success" : "drawedge fail", "Test", MB_OK );

    HWND hWnd1;
    HWND hWnd2;

    if ( ! ( hWnd1 = CreateWindow( NULL, NULL, WS_VISIBLE | WS_HSCROLL /* | WS_BORDER */, 2, 3, 40, 26, HWND_DESKTOP, NULL, NULL, 0 ) ) ) {

        printf( "\nExecution error : TextWindows library OPENWINDOW 1 failure." );
        return;

    }

    SetWindowText( hWnd1, szWindow1Text );

    if ( ! ( hWnd2 = CreateWindow( NULL, NULL, WS_VISIBLE | WS_VSCROLL /* | WS_BORDER */, 0, 8, 40, 20, HWND_DESKTOP, NULL, NULL, 0 ) ) ) {

        printf( "\nExecution error : TextWindows library OPENWINDOW 2 failure." );
        return;

    }

    SetWindowText( hWnd2, szWindow2Text );

    if ( 0 != SetTextWindowColors( hWnd1, GetSysColor( COLOR_HIGHLIGHTTEXT ), GetSysColor( COLOR_HIGHLIGHT ) ) ) {

        printf( "\nExecution error : TextWindows library SetTextWindowColors 1 failure." );
        return;

    }

    if ( 0 != SetTextWindowColors( hWnd2, GetSysColor( COLOR_MENU ), GetSysColor( COLOR_MENUTEXT ) ) ) {

        printf( "\nExecution error : TextWindows library SetTextWindowColors 2 failure." );
        return;

    }

    UpdateWindow( hWnd1 );
    UpdateWindow( hWnd2 );

    Window W1, W2;

    GetWindowRect( hWnd1, &r );

#define Rect2Wnd( W, r )     \
    W.x  = r.left; \
    W.cx = r.right - r.left; \
    W.y  = r.top; \
    W.cy = r.bottom - r.top

    Rect2Wnd( W1, r );

    GetWindowRect( hWnd2, &r );

    Rect2Wnd( W2, r );

    if ( bRectInRect( &W1, &W2 ) ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Windows intersect" ) );

    } else {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Windows do NOT intersect" ) );

    }

    HWND hLBWnd;
    if ( ! ( hLBWnd = CreateWindow( "LISTBOX", NULL, WS_VISIBLE | LBS_HASSTRINGS /* | WS_HSCROLL | WS_BORDER */, 50, 0, 30, 20, HWND_DESKTOP, NULL, NULL, 0 ) ) ) {

        printf( "\nExecution error : TextWindows library OPENWINDOW (listbox) failure." );
        return;

    }

    ListBox_AddString( hLBWnd, "Fire" );
    ListBox_AddString( hLBWnd, "Smoke" );
    ListBox_AddString( hLBWnd, "Less" );
    ListBox_AddString( hLBWnd, "More" );
    ListBox_AddString( hLBWnd, "Weed" );
    ListBox_AddString( hLBWnd, "Rake" );

    ListBox_SetCurSel( hLBWnd, 4 );

    UpdateWindow( hLBWnd );

    Pause( s );

    if ( 0 != SetBackGround( szBackGroundFile ) ) {

        printf( "\nError setting desktop background." );
        return;

    }

    ToggleActivation( s, hWnd1, hWnd2 );

    EraseAndRedrawDesktop();

    Pause( s );

    Cls( hWnd1 );

    Pause( s );

    Cls( hWnd2 );

    Pause( s );

    AddTextLines( s, hWnd1, hWnd2 );

    if ( false == DestroyWindow( hWnd1 ) ) {

        printf( "\nAbnormal termination : TextWindows library failed to close window 1." );
        return;

    }

    EraseAndRedrawDesktop();

    Pause( s );

    if ( false == DestroyWindow( hWnd2 ) ) {

        printf( "\nAbnormal termination : TextWindows library failed to close window 2." );
        return;

    }

    EraseAndRedrawDesktop();

    Pause( s );

}
#endif

void teststrings( HINSTANCE hInst ) {

    TCHAR   szString[1024];

    for ( unsigned u = 1; u <= 32; u++ ) {

        bzero( szString, sizeof( szString ) );

        LoadString( hInst, u, szString, ( sizeof( szString ) / sizeof( szString[0] ) ) - 1 );

    }

}


void testicons( HINSTANCE hInst ) {

    HICON h = LoadIcon( hInst, MAKEINTRESOURCE( IDI_TEST ) );

    if ( NULL != h ) {

        DestroyIcon( h );

    }

}


void /* cdecl */ ExitProc( void ) {

//    if ( 0 != CloseTextWindowLib() ) {

//        printf( "\nTermination handler" );

//    }

//    if ( NULL != hInst ) {

//        fclose( hInst );

//        hInst = NULL;

//    }

}

#if 0
    POINT pt;

    pt.x = 1;
    pt.y = 1;

    RECT r;
    r.left   = 0;
    r.top    = 0;
    r.right  = 1;
    r.bottom = 1;

    BOOL  bRet;
    bRet = PtInRect( &r, pt );
    printf( "Point (%ld,%ld) is %sin" EOL, pt.x, pt.y, bRet ? "" : "NOT " );
    printf( "[%ld.%ld.%ld.%ld]" EOL, r.left, r.top, r.right, r.bottom );

    MessageBox( NULL, "test", "hello world", MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND );

    teststrings( hInst );

    testicons( hInst );

    testwindowing( fileno( stdin ) );
#endif


#if 0
    HWND hCBWnd = GetDlgItem( hDlg, IDCB_TEST );

    if ( NULL != hCBWnd ) {

        TCHAR szTemp[128];

        POINT ptClient;
        POINT ptScreen;

        ptClient.x = 0;
        ptClient.y = 0;

        ClientToScreen( hCBWnd, &ptClient );

        ptScreen = ptClient;

        sprintf( szTemp, "(0,0) on the combobox equals (%ld,%ld) on the screen", ptClient.x, ptClient.y );

        MessageBox( hDlg, szTemp, "Test", MB_OK );

        ScreenToClient( hCBWnd, &ptClient );

        sprintf( szTemp, "(%ld,%ld) on the screen equals (%ld,%ld) on the combobox", ptScreen.x, ptScreen.y, ptClient.x, ptClient.y );

        MessageBox( hDlg, szTemp, "Test", MB_OK );

    }
#endif
//    POINT pt;

//    pt.x = 200;
//    pt.y = 220;

//    HWND hWnd = WindowFromPoint( pt );

//    TCHAR szClassName[128];

//    bzero( szClassName, sizeof( szClassName ) );

//    if ( NULL != hWnd ) {

//        GetClassName( hWnd, szClassName, 127 );

//        MessageBox( NULL, szClassName, "Who is there", MB_OK );

//    }


//    CreateDialogParam( hInst, TEXT( "IDD_MAIN_TEXTNAME" ), HWND_DESKTOP, NULL, 0 );

//    TCHAR szText[128];
//    sprintf( szText, "Doubleclick CX = %u, CY = %u", GetSystemMetrics( SM_CXDOUBLECLK ), GetSystemMetrics( SM_CYDOUBLECLK ) );
//    MessageBox( HWND_DESKTOP, szText, "info", MB_OK );

