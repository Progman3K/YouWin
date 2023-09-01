

//#include "ywin.h"


#if defined( YOU_WIN_GRAPHICAL ) && defined( YOU_WIN_GRAPHICAL_OSX )


#include <map>
#include <string>


#include <winuser.h>
#include <ASCII.h>


// THESE DEFINITIONS ARE COPIED FROM WINDOWS.H TEMPORARILY UNTIL I FIGURE OUT HOW TO PREVENT SYMBOL COLLISIONS

#ifdef UNICODE
#ifndef TEXT
#define TEXT(string)                      L##string
#endif
#else
#ifndef TEXT
#define TEXT(string)                      string
#endif
#endif
#define _T(x)                             TEXT(x)

typedef int SOCKET;
typedef unsigned short WORD;

///////////////////////////////////////////////////////////////////////

#import <Cocoa/Cocoa.h>
#import <CoreServices/CoreServices.h>

#include <DbgTrace.h>
#include <osxywapp.h>
#include <wsanotif.h>

static osx_ywapp *  pApp = NULL;

typedef std::pair <SOCKET, CFSocketRef> SocketRefSelectPair;
typedef std::map <SOCKET, CFSocketRef> SocketRefSelectList;


SocketRefSelectList SocketRefs;


typedef std::pair <SOCKET, CFRunLoopSourceRef> RunLoopSourceRefSelectPair;
typedef std::map <SOCKET, CFRunLoopSourceRef> RunLoopSourceRefSelectList;

RunLoopSourceRefSelectList RunLoopSourceRefs;


static const TCHAR * FD_EVENTS( WORD wEventCode, char * lpszEvents ) {

    strcpy( lpszEvents, "" );

    if ( FD_ACCEPT & wEventCode ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "FD_ACCEPT" );

    }

    if ( FD_CLOSE & wEventCode ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "FD_CLOSE" );

    }

    if ( FD_CONNECT & wEventCode ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "FD_CONNECT" );

    }

    if ( FD_READ & wEventCode ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "FD_READ" );

    }

    if ( FD_WRITE & wEventCode ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "FD_WRITE" );

    }

    if ( 0 == strlen( lpszEvents ) ) strcat( lpszEvents, "UNKNOWN" );

    return lpszEvents;

}


static const TCHAR * NSKeyMak( NSUInteger flags ) {

    static TCHAR szKeyMask[256];

    bzero( szKeyMask, sizeof( szKeyMask ) );

    if ( flags & NSAlphaShiftKeyMask ) {

        strncat( szKeyMask, " NSAlphaShiftKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSShiftKeyMask ) {

        strncat( szKeyMask, " NSShiftKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSControlKeyMask ) {

        strncat( szKeyMask, " NSControlKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSAlternateKeyMask ) {

        strncat( szKeyMask, " NSAlternateKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSCommandKeyMask ) {

        strncat( szKeyMask, " NSCommandKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSNumericPadKeyMask ) {

        strncat( szKeyMask, " NSNumericPadKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSHelpKeyMask ) {

        strncat( szKeyMask, " NSHelpKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

    if ( flags & NSFunctionKeyMask ) {

        strncat( szKeyMask, " NSFunctionKeyMask", ARRAY_SIZE( szKeyMask ) - 1 );

    }

//    if ( flags & NSDeviceIndependentModifierFlagsMask ) {

//        strncat( szKeyMask, " NSDeviceIndependentModifierFlagsMask", Dim( szKeyMask ) - 1 );

//    }

    return szKeyMask;

}


static const TCHAR * kCFSocketEvents( CFOptionFlags flags, TCHAR * lpszEvents ) {

    strcpy( lpszEvents, "" );

    if ( kCFSocketAcceptCallBack & flags ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "kCFSocketAcceptCallBack" );

    }

    if ( kCFSocketConnectCallBack & flags ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "kCFSocketConnectCallBack" );

    }

    if ( kCFSocketReadCallBack & flags ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "kCFSocketReadCallBack" );

    }

    if ( kCFSocketWriteCallBack & flags ) {

        if ( 0 != strlen( lpszEvents ) ) strcat( lpszEvents, " | " );
        strcat( lpszEvents, "kCFSocketWriteCallBack" );

    }

    if ( 0 == strlen( lpszEvents ) ) strcat( lpszEvents, "UNKNOWN" );

    return lpszEvents;

}


static void OSXSocketCallBack( CFSocketRef sref, CFSocketCallBackType flags, CFDataRef address, const void * data, void * info ){

    long lEvent = 0;

    SOCKET s = CFSocketGetNative( sref );

    if ( kCFSocketReadCallBack & flags ) {

        lEvent |= FD_READ;

    }

    if ( kCFSocketConnectCallBack & flags ) {

        lEvent |= FD_CONNECT;

    }

    if ( kCFSocketWriteCallBack & flags ) {

        lEvent |= FD_WRITE;

    }

#ifdef DEBUG
    TCHAR szNativeEvents[128];
    TCHAR szEvents[128];
    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Native event %s on socket %d: %lX (%s)" ), kCFSocketEvents( flags, szNativeEvents ), s, lEvent, FD_EVENTS( lEvent, szEvents ) );
#endif

    AsyncSelectList::iterator i = SocketInputs.find( s );

    if( SocketInputs.end() == i ) {

        DBG_MSG( DBG_ERROR, TEXT( "EVENT HANDLER FOR SOCKET %d NOT FOUND" ), s );
        return;

    }

    AsyncSocket * pInput = (*i).second;

    pInput->EventHandler();

    /* Post a pseudo-event to the OSX application message queue so it retrieves any posted messages this handler may have generated. */
    NSEvent * event = [NSEvent
        otherEventWithType:NSApplicationDefined
        location: (NSPoint){ 0, 0 }
        modifierFlags:NSApplicationDefined
        timestamp:(NSTimeInterval)0
        windowNumber:0
        context:[NSGraphicsContext currentContext]
        subtype:0
        data1:0
        data2:0
        ];

    [pApp->app postEvent:event atStart:YES];

}


extern "C" int OSXAddAsyncSelectSocket( SOCKET s, long lEvents ) {

    CFOptionFlags flags = 0;

#ifdef DEBUG
    TCHAR szEvents[128];
    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Setting event notifications on socket %d: %lX (%s)" ), s, (long)lEvents, FD_EVENTS( lEvents, szEvents ) );
#endif

    CFRunLoopSourceRef rls = NULL;

    // Find RunLoopSource reference
    RunLoopSourceRefSelectList::iterator j = RunLoopSourceRefs.find( s );

    if ( 0 == lEvents ) {

        // remove notifications for this socket.
        if( RunLoopSourceRefs.end() != j ) {

            DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFRunLoopSourceRef exists, removing it." ) );
            rls = (*j).second;

            CFRunLoopRemoveSource( CFRunLoopGetCurrent(), rls, kCFRunLoopCommonModes );

        } else {

            DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFRunLoopSourceRef doesn't exist, done." ) );

        }

        return 0;

    }

    if ( FD_CLOSE & lEvents ) {

        flags |= kCFSocketReadCallBack;

    }

    if ( FD_READ & lEvents ) {

        flags |= kCFSocketReadCallBack;

    }

    if ( FD_ACCEPT & lEvents ) {

        // kCFSocketAcceptCallBack performs accept() for you, so it is not acceptable.
        // Instead, we must add the socket to the readable descriptor set and perform an 
        // FD_ACCEPT notification manually on receipt of the read event.
        flags |= kCFSocketReadCallBack;

    }

    if ( FD_CONNECT & lEvents ) {

        flags |= kCFSocketConnectCallBack;

    }

    if ( FD_WRITE & lEvents ) {

        flags |= kCFSocketWriteCallBack;

    }

    // Find socket reference
    SocketRefSelectList::iterator i = SocketRefs.find( s );

    CFSocketRef sref = NULL;

    if( SocketRefs.end() == i ) {

        DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFSocketRef doesn't exist, creating it." ) );
        sref = CFSocketCreateWithNative( NULL, s, flags, OSXSocketCallBack, NULL );

        SocketRefs.insert( SocketRefSelectPair( s, sref ) );

    } else {

        DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFSocketRef exists, updating it." ) );

        // Exists, update it
        sref = (*i).second;

        CFOptionFlags newflags = 0;

        CFOptionFlags oldflags = CFSocketGetSocketFlags( sref );

#ifdef DEBUG
        DBG_MSG( DBG_NETWORK_INFO, TEXT( "Socket %d's old OSX socket-notification flags: %lX (%s)" ), s, (long)oldflags, kCFSocketEvents( oldflags, szEvents ) );
#endif

        // Clear the old flags.

        oldflags &= ~( kCFSocketReadCallBack | kCFSocketAcceptCallBack | kCFSocketConnectCallBack | kCFSocketWriteCallBack );

        // Set the new flags.
        newflags = ( flags | oldflags );

#ifdef DEBUG
        DBG_MSG( DBG_NETWORK_INFO, TEXT( "Socket %d's NEW OSX socket-notification flags: %lX (%s)" ), s, (long)newflags, kCFSocketEvents( newflags, szEvents ) );
#endif

        CFSocketSetSocketFlags( sref, newflags );

        CFSocketEnableCallBacks( sref, flags );

        return 0;

    }

    DBG_MSG( DBG_NETWORK_INFO, TEXT( "Setting os/x event notifications on socket %d: %lX" ), s, (long)flags );

    if( RunLoopSourceRefs.end() == j ) {

        DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFRunLoopSourceRef doesn't exist, creating it." ) );
        rls = CFSocketCreateRunLoopSource( NULL, sref, 0 );

        RunLoopSourceRefs.insert( RunLoopSourceRefSelectPair( s, rls ) );

    } else {

        DBG_MSG( DBG_NETWORK_INFO, TEXT( "CFRunLoopSourceRef exists, updating it???" ) );
        rls = (*j).second;

    }

    CFRunLoopAddSource( CFRunLoopGetCurrent(), rls, kCFRunLoopDefaultMode );

    return 0;

}


static void PostKeyMsg( bool bUp, NSEvent * event, EventQ * pQ ) {

    int iCharsLen1 = [[event characters] length];

    NSString * str = [event characters];

    unichar c = [str characterAtIndex:0];

//  NSString * st2 = [event charactersIgnoringModifiers];

    int iCharsLen2 = [[event charactersIgnoringModifiers] length];

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Key %s scancode %X, length %d, length without modifiers %d, char %d" ), bUp ? "up" : "down", [event keyCode], iCharsLen1, iCharsLen2, c );

    unsigned vKey;

    switch( c ) {

        case NSUpArrowFunctionKey:    vKey = VK_UP;     break;
        case NSDownArrowFunctionKey:  vKey = VK_DOWN;   break;
        case NSLeftArrowFunctionKey:  vKey = VK_LEFT;   break;
        case NSRightArrowFunctionKey: vKey = VK_RIGHT;  break;
        case NSF1FunctionKey:         vKey = VK_F1;     break;
        case NSF2FunctionKey:         vKey = VK_F2;     break;
        case NSF3FunctionKey:         vKey = VK_F3;     break;
        case NSF4FunctionKey:         vKey = VK_F4;     break;
        case NSF5FunctionKey:         vKey = VK_F5;     break;
        case NSF6FunctionKey:         vKey = VK_F6;     break;
        case NSF7FunctionKey:         vKey = VK_F7;     break;
        case NSF8FunctionKey:         vKey = VK_F8;     break;
        case NSF9FunctionKey:         vKey = VK_F9;     break;
        case NSF10FunctionKey:        vKey = VK_F10;    break;
        case NSF11FunctionKey:        vKey = VK_F11;    break;
        case NSF12FunctionKey:        vKey = VK_F12;    break;
        case NSF13FunctionKey:        vKey = VK_F13;    break;
        case NSF14FunctionKey:        vKey = VK_F14;    break;
        case NSF15FunctionKey:        vKey = VK_F15;    break;
        case NSF16FunctionKey:        vKey = VK_F16;    break;
        case NSF17FunctionKey:        vKey = VK_F17;    break;
        case NSF18FunctionKey:        vKey = VK_F18;    break;
        case NSF19FunctionKey:        vKey = VK_F19;    break;
        case NSF20FunctionKey:        vKey = VK_F20;    break;
        case NSF21FunctionKey:        vKey = VK_F21;    break;
        case NSF22FunctionKey:        vKey = VK_F22;    break;
        case NSF23FunctionKey:        vKey = VK_F23;    break;
        case NSF24FunctionKey:        vKey = VK_F24;    break;
        case NSInsertFunctionKey:     vKey = VK_INSERT; break;
        case NSDeleteFunctionKey:     vKey = VK_DELETE; break;
        case NSHomeFunctionKey:       vKey = VK_HOME;   break;
        case NSEndFunctionKey:        vKey = VK_END;    break;
        case NSPageUpFunctionKey:     vKey = VK_PRIOR;  break;
        case NSPageDownFunctionKey:   vKey = VK_NEXT;   break;

        case CARRIAGERETURN:          vKey = VK_RETURN; break;
        case DEL:                     vKey = VK_BACK;   break;
        case ESC:                     vKey = VK_ESCAPE; break;
        case ' ':                     vKey = VK_SPACE;  break;
        case TAB:                     vKey = VK_TAB;    break;

        default:

            if ( ! bUp ) {

                FORWARD_WM_CHAR( NULL, c, 0, pQ->PostMessage );
                return;
            }

    }

    bUp ? FORWARD_WM_KEYUP(   NULL, vKey, 0, 0, pQ->PostMessage )
        : FORWARD_WM_KEYDOWN( NULL, vKey, 0, 0, pQ->PostMessage );

}


extern "C" int OSXGetMessage( EventQ * pQ, struct timeval * ptimeout ) {

    /* Returning 0 means to quit */

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "osx getmessage" ) );

    NSEvent * event;

    if ( NULL == ptimeout ) {

        event = [pApp->app nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantFuture] inMode:NSDefaultRunLoopMode dequeue:YES];

    } else {

        NSDate * endDate;

        endDate = [NSDate dateWithTimeIntervalSinceNow: ( ptimeout->tv_sec + ( ( ptimeout->tv_sec * 1000.0 ) / 1000.0 ) )];

        event = [pApp->app nextEventMatchingMask:NSAnyEventMask untilDate: endDate inMode:NSDefaultRunLoopMode dequeue:YES];

    }

    if ( nil == event ) {

        /* Timer expired */
        return 0;

    }

    switch( [event type] ) {

        case NSAppKitDefined:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "AppKit defined" ) );
            break;

        case NSApplicationDefined:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Application defined" ) );
            break;

        case NSFlagsChanged: {

            NSUInteger flags = [event modifierFlags];
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Flags changed %X:%s" ), flags, NSKeyMak( flags ) );

            }
            break;

        case NSKeyDown:

            PostKeyMsg( false, event, pQ );
            break;

        case NSKeyUp:

            PostKeyMsg( true, event, pQ );
            break;

        case NSLeftMouseDown: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Left mouse down at (%d,%d), view maxY: %d" ), (int)pt.x, (int)( cy - pt.y ), cy );
            pQ->PostMouseMsg( false, pt.x, cy - pt.y, VK_LBUTTON, MK_LBUTTON );

            }
            break;

        case NSLeftMouseDragged: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Left mouse drag at (%d,%d)" ), (int)pt.x, (int)( cy - pt.y ) );

            pQ->PostMouseMove( pt.x, cy - pt.y, MK_LBUTTON );

            }
            break;

        case NSLeftMouseUp: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Left mouse up" ) );
            pQ->PostMouseMsg( true, pt.x, cy - pt.y, VK_LBUTTON, MK_LBUTTON );

            }
            break;

        case NSMouseEntered:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Mouse entered" ) );
            break;

        case NSMouseExited:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Mouse exited" ) );
            break;

        case NSMouseMoved:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Mouse moved" ) );
            break;

        case NSOtherMouseDown: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Middle mouse down" ) );
            pQ->PostMouseMsg( false, pt.x, cy - pt.y, VK_MBUTTON, MK_MBUTTON );

            }
            break;

        case NSOtherMouseDragged: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Left mouse drag at (%d,%d)" ), (int)pt.x, (int)( cy - pt.y ) );

            pQ->PostMouseMove( pt.x, cy - pt.y, MK_MBUTTON );

            }
            break;

        case NSOtherMouseUp: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Middle mouse up" ) );
            pQ->PostMouseMsg( true, pt.x, cy - pt.y, VK_MBUTTON, MK_MBUTTON );

            }
            break;

        case NSRightMouseDown: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Right mouse down" ) );
            pQ->PostMouseMsg( false, pt.x, cy - pt.y, VK_RBUTTON, MK_RBUTTON );

            }
            break;

        case NSRightMouseDragged: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Right mouse drag" ) );

            pQ->PostMouseMove( pt.x, cy - pt.y, MK_RBUTTON );

            }
            break;

        case NSRightMouseUp: {

            NSPoint pt = [event locationInWindow];

            int cy = GetSystemMetrics( SM_CYSCREEN );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Right mouse up" ) );
            pQ->PostMouseMsg( true, pt.x, cy - pt.y, VK_RBUTTON, MK_RBUTTON );

            }
            break;

        case NSScrollWheel:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Scroll mouse, phase: %lX, modifierFlags: %lX, deltaX: %F, deltaY: %F" ), (long)[event phase], (long)[event modifierFlags], [event deltaX], [event deltaY] );

            if ( 0 > [event deltaY] ) {

                FORWARD_WM_KEYDOWN( NULL, VK_UP, 0, 0, pQ->PostMessage );

            } else {

                FORWARD_WM_KEYDOWN( NULL, VK_DOWN, 0, 0, pQ->PostMessage );

            }
            break;

        case NSSystemDefined:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "System defined" ) );
            break;

        default:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Unknown event type %u" ), [event type] );
            break;

    }

    [pApp->app sendEvent:event];

    [pApp->app updateWindows];

    return 1;

}


extern "C" int osxmain( osx_ywapp * app ) {

    pApp = app;

    const TCHAR * pszApp = pApp->argv[0];

    int iRet = -1;

    int nCmdShow = SW_SHOW;

    size_t size = 0;

    HINSTANCE hInstance = NULL;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "os/x '%s' - Startup" ), pszApp );

    iRet = GL::glInit( pApp->cx, pApp->cy, pApp->argc, pApp->argv );

    if ( 0 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing: GL init failed" ) );
        goto Outtahere;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Display layer started" ) );

    if ( ( g.pTopWnd = Desktop::Create( 0, "DESKTOP", "", WS_VISIBLE, 0, 0, pApp->cx, pApp->cy, NULL, NULL, hYouWinModule, 0 ) ) == NULL ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing: unable to create desktop window" ) );
        goto Outtahere;

    }

    RedrawWindow( (HWND)g.pTopWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    hInstance = LoadResources( "resource", NULL, &size );

    if ( NULL != hInstance ) {

        iRet = _tWinMain( hInstance, NULL, (LPTSTR)pszApp, nCmdShow );

        fclose( (FILE *)hInstance );
        hInstance = NULL;

    } else {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - resources '%s' not found" ), pszApp );

        iRet = -1;

    }

Outtahere:

    CloseWindowLib();

    if ( NULL != hYouWinModule ) {

        fclose( (FILE *)hYouWinModule );
        hYouWinModule = NULL;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "'%s' - Shutdown (%d)" ), pszApp, iRet );

    return iRet;

}



#endif /* YOU_WIN_GRAPHICAL && YOU_WIN_GRAPHICAL_OSX */
