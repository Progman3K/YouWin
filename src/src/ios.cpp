


#include "ywin.h"


#if defined(__APPLE__)


static iOSKeyMouse * pInput = NULL;


bool iOSKeyMouse::SendUpdates( void ) {

    if ( -1 == s ) {

        // Input lost, should messagebeep or something
        return false;

    }

    if ( updates.IsEmpty() ) {

        /* Nothing to do */
        return true;

    }

    if ( 0 == updates.size() ) {

        /* Single-level nesting */
        RECT r;

        r.left   = updates.x;
        r.top    = updates.y;
        r.right  = r.left + updates.cx;
        r.bottom = r.top  + updates.cy;

        updates.add( r );

    }

    PaintMsg Msg;

    Msg.Header.Length = sizeof( Msg ) + ( updates.size() * sizeof( RECT ) );
    Msg.Header.Type   = MsgHeader::Type_Paint;

    if ( -1 == send( s, (char *)&Msg, sizeof( Msg ), 0 ) ) {

        // Serious error
        // YouWin has shutdown or error, main thread should exit
        return false;

    }

    if ( -1 == send( s, (char *)&( updates.at( 0 ) ), updates.size() * sizeof( RECT ), 0 ) ) {

        // Serious error
        // YouWin has shutdown or error, main thread should exit
        return false;

    }

    updates.reset();

    return true;

}


void PostRefresh() {

    pInput->SendUpdates();

}


void displayKeyboard( iOSApp * app, bool bShow ) {

    KeyboardMsg Msg;

    Msg.Header.Length = sizeof( Msg );
    Msg.Header.Type   = MsgHeader::Type_Keyboard;
    Msg.flags         = bShow ? KeyboardMsg::Show : KeyboardMsg::Hide;

    if ( -1 == send( app->s, (char *)&Msg, sizeof( Msg ), 0 ) ) {

        // Serious error
        // YouWin has shutdown or error, main thread should exit
        return;

    }

}


void StartPoints( void ) {

    g.app->StartPoints();

}


void EndPoints( void ) {

    g.app->EndPoints();

}


void DC::Out( const POINT & pt, COLORREF c ) {

    if ( pInput->updates.IsEmpty() ) {

        pInput->updates.x  = pt.x;
        pInput->updates.y  = pt.y;
        pInput->updates.cx = pt.x + 1;
        pInput->updates.cy = pt.y + 1;

    } else {

        if ( pt.x < pInput->updates.x ) {

            pInput->updates.x = pt.x;

        } else if ( ( pt.x + 1 ) > pInput->updates.cx ) {

            pInput->updates.cx = pt.x + 1;

        }

        if ( pt.y < pInput->updates.y ) {

            pInput->updates.y = pt.y;

        } else if ( ( pt.y + 1 ) > pInput->updates.cy ) {

            pInput->updates.cy = pt.y + 1;

        }

    }

    g.app->Out( pt, c );

}


static void ProcessInput( const RawPacket * raw, LPARAM lParam ) {

    iOSKeyMouse * pThis = (iOSKeyMouse *)lParam;

    switch( raw->Header.Type ) {

        case MsgHeader::Type_VKey:

            switch( raw->vKey.flags ) {

                case VKMsg::ActionDown:

                    // VK_LBUTTON == MK_LBUTTON
                    pThis->pQ->PostMouseMsg( false, raw->vKey.x, raw->vKey.y, raw->vKey.vKey, MK_LBUTTON );

                case VKMsg::ActionUp:

                    pThis->pQ->PostMouseMsg( true, raw->vKey.x, raw->vKey.y, raw->vKey.vKey, MK_LBUTTON );
                    break;

                case VKMsg::ActionMove:

                    pThis->pQ->PostMouseMove( raw->vKey.x, raw->vKey.y, raw->vKey.vKey );
                    break;

            }

            break;

        case MsgHeader::Type_Keyboard:

            // It is implied that the flags-type of the message is Char.
            switch( raw->keyboard.c ) {

                case BS:

                    FORWARD_WM_KEYDOWN( NULL, VK_BACK, 0, 0, pThis->pQ->PostMessage );
                    break;

                case CR:

                    FORWARD_WM_KEYDOWN( NULL, VK_RETURN, 0, 0, pThis->pQ->PostMessage );
                    break;

                case DEL:

                    FORWARD_WM_KEYDOWN( NULL, VK_BACK, 0, 0, pThis->pQ->PostMessage );
                    break;

                case ESC:

                    FORWARD_WM_KEYDOWN( NULL, VK_ESCAPE, 0, 0, pThis->pQ->PostMessage );
                    break;

                case ' ':

                    FORWARD_WM_KEYDOWN( NULL, VK_SPACE, 0, 0, pThis->pQ->PostMessage );
                    break;

                case TAB:

                    FORWARD_WM_KEYDOWN( NULL, VK_TAB, 0, 0, pThis->pQ->PostMessage );
                    break;

                default:

                    FORWARD_WM_CHAR( NULL, raw->keyboard.c, 0, pThis->pQ->PostMessage );
                    break;

            }
            break;

        case MsgHeader::Type_Orientation: {

            HWND hWnd = GetDesktopWindow();

            if ( NULL != hWnd ) {

                FORWARD_WM_DISPLAYCHANGE( hWnd, 24, raw->orientation.cx, raw->orientation.cy, SendMessage );

            }

        }
        break;

        default:

            break;

    }

}


bool iOSKeyMouse::EventHandler() {

    int i = RawInput::ProcessRecv( s, &input, ProcessInput, (LPARAM)this );

    if ( -1 == i ) {

        // YouWin has shutdown or error, main thread should exit
        return false;

    }

    return true;

}


int iOSInit( iOSApp * app ) {

    g.iCX = app->cx;
    g.iCY = app->cy;

    pInput = new iOSKeyMouse( &g.Q, app->s );

    if ( NULL == pInput ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error creating input object" ) );
        return -1;

    }

    int iRet = g.Q.addToQ( g.Q.ReadQ, pInput );

    if ( 0 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error adding input object to queue" ) );
        return -1;

    }

    return 0;

}


int iOSCleanup( iOSApp * app ) {

    if ( NULL != pInput ) {

        delete pInput;
        pInput = NULL;

    }

    return 0;

}


#endif /* __APPLE__ */
