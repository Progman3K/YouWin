

#include <DbgTrace.h>


#if defined( YOU_WIN_GRAPHICAL ) && defined( YOU_WIN_GRAPHICAL_XWIN )
#ifndef ANDROID


#include "xwin.h"
#include "graphical.h"
#include "dc.h"


namespace GL {
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
}
using namespace GL;


static /*const*/ std::map<unsigned int /* x keycode */, UINT /* VKey */> vk_list;


static void setkeymap( void ) {

    vk_list[XK_BackSpace]   = VK_BACK;
    vk_list[XK_Tab]         = VK_TAB;
    vk_list[XK_Clear]       = VK_CLEAR;
    vk_list[XK_Return]      = VK_RETURN;
    vk_list[XK_Pause]       = VK_PAUSE;
    vk_list[XK_Scroll_Lock] = VK_SCROLL;
    vk_list[XK_Sys_Req]     = VK_PROCESSKEY;
    vk_list[XK_Escape]      = VK_ESCAPE;
    vk_list[XK_Delete]      = VK_DELETE;


    vk_list[XK_Home]        = VK_HOME;
    vk_list[XK_Left]        = VK_LEFT;
    vk_list[XK_Up]          = VK_UP;
    vk_list[XK_Right]       = VK_RIGHT;
    vk_list[XK_Down]        = VK_DOWN;
    vk_list[XK_Prior]       = VK_PRIOR;
//    vk_list[XK_Page_Up]     = ;
    vk_list[XK_Next]        = VK_NEXT;
//    vk_list[XK_Page_Down]   = ;
    vk_list[XK_End]         = VK_END;
    vk_list[XK_Begin]       = VK_HOME;

    vk_list[XK_Select]      = VK_SELECT;
    vk_list[XK_Print]       = VK_PRINT;
    vk_list[XK_Execute]     = VK_EXECUTE;
    vk_list[XK_Insert]      = VK_INSERT;
//    vk_list[XK_Undo]       = ;
//    vk_list[XK_Redo]       = ;
    vk_list[XK_Menu]        = VK_MENU;
//    vk_list[XK_Find]       = ;
    vk_list[XK_Cancel]      = VK_CANCEL;
    vk_list[XK_Help]        = VK_HELP;
//    vk_list[XK_Break]       = ;
    vk_list[XK_Mode_switch] = VK_MODECHANGE;
//    vk_list[XK_script_switch]       = ;
    vk_list[XK_Num_Lock]    = VK_NUMLOCK;


    vk_list[XK_KP_Space]    = VK_SPACE;


    vk_list[XK_KP_0]        = VK_NUMPAD0;
    vk_list[XK_KP_1]        = VK_NUMPAD1;
    vk_list[XK_KP_2]        = VK_NUMPAD2;
    vk_list[XK_KP_3]        = VK_NUMPAD3;
    vk_list[XK_KP_4]        = VK_NUMPAD4;
    vk_list[XK_KP_5]        = VK_NUMPAD5;
    vk_list[XK_KP_6]        = VK_NUMPAD6;
    vk_list[XK_KP_7]        = VK_NUMPAD7;
    vk_list[XK_KP_8]        = VK_NUMPAD8;
    vk_list[XK_KP_9]        = VK_NUMPAD9;

    vk_list[XK_F1]          = VK_F1;
    vk_list[XK_F2]          = VK_F2;
    vk_list[XK_F3]          = VK_F3;
    vk_list[XK_F4]          = VK_F4;
    vk_list[XK_F5]          = VK_F5;
    vk_list[XK_F6]          = VK_F6;
    vk_list[XK_F7]          = VK_F7;
    vk_list[XK_F8]          = VK_F8;
    vk_list[XK_F9]          = VK_F9;
    vk_list[XK_F10]         = VK_F10;
    vk_list[XK_F11]         = VK_F11;
    vk_list[XK_F12]         = VK_F12;
    vk_list[XK_F13]         = VK_F13;
    vk_list[XK_F14]         = VK_F14;
    vk_list[XK_F15]         = VK_F15;
    vk_list[XK_F16]         = VK_F16;
    vk_list[XK_F17]         = VK_F17;
    vk_list[XK_F18]         = VK_F18;
    vk_list[XK_F19]         = VK_F19;
    vk_list[XK_F20]         = VK_F20;
    vk_list[XK_F21]         = VK_F21;
    vk_list[XK_F22]         = VK_F22;
    vk_list[XK_F23]         = VK_F23;
    vk_list[XK_F24]         = VK_F24;

    vk_list[XK_Shift_L]     = VK_LSHIFT;
    vk_list[XK_Shift_R]     = VK_RSHIFT;

    vk_list[XK_Control_L]   = VK_LCONTROL;
    vk_list[XK_Control_R]   = VK_RCONTROL;

    vk_list[XK_Shift_Lock]  = VK_CAPITAL;

//    vk_list[]       = ;

}


static struct {

    Display * display;
    Window    window;
    long      eventmask;
    int       screen;
    GC        dc;
    Colormap  cmap;

} x;


static struct the_X : public Handler {

       the_X() : Handler( INVALID_SOCKET, NULL ) { setkeymap(); x.display = 0; }

        the_X( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) { x.display = 0; }

        bool EventHandler() override {

            std::map<unsigned int, UINT>::const_iterator pKP;

            KeySym symbol = NoSymbol;
            unsigned uMKButton  = 0;
            unsigned uVKButton  = 0;
            XEvent event;
            TCHAR c[20];
//            int i;
//            XComposeStatus cs;

            while( XCheckWindowEvent( x.display, x.window, x.eventmask, &event ) ) {

                switch( event.type ) {

                    case ButtonPress:
                    case ButtonRelease:

                        if ( Button1 == event.xbutton.button ) {
                            uMKButton = MK_LBUTTON;
                            uVKButton = VK_LBUTTON;
                        } else if ( Button2 == event.xbutton.button ) {
                            uMKButton = MK_MBUTTON;
                            uVKButton = VK_MBUTTON;
                        } else if ( Button3 == event.xbutton.button ) {
                            uMKButton = MK_RBUTTON;
                            uVKButton = VK_RBUTTON;
                        } else if ( Button4 == event.xbutton.button ) {
                            uMKButton = MK_XBUTTON1;
                            uVKButton = VK_XBUTTON1;
                        } else if ( Button5 == event.xbutton.button ) {
                            uMKButton = MK_XBUTTON2;
                            uVKButton = VK_XBUTTON2;
                        } else break;

                        if ( ButtonPress == event.type ) {
                            pQ->PostMouseMsg( false, event.xbutton.x, event.xbutton.y, uVKButton, uMKButton );
                        } else {
                            pQ->PostMouseMsg(  true, event.xbutton.x, event.xbutton.y, uVKButton, uMKButton );
                        }
                        break;

                    case Expose:

                        /* draw or redraw the window */
                        DBG_MSG( DBG_GRAPHICAL, TEXT( "Expose at (%d,%d) width %d, height %d, count %d" ), 
                        event.xexpose.x, event.xexpose.y, event.xexpose.width, event.xexpose.height, event.xexpose.count );
                        break;

                    case KeyPress:
                    case KeyRelease:

                        // i =
                        XLookupString( &event.xkey, c, sizeof( c ), &symbol, 0 /* &cs */ );

    //                    symbol = XLookupKeysym( &event.xkey, 0 );

                        if ( NoSymbol == symbol ) {

                            break;

                        }

                        pKP = vk_list.find( symbol );

                        if ( vk_list.end() != pKP ) {

                            if ( KeyPress == event.type ) {

                                FORWARD_WM_KEYDOWN( NULL, pKP->second, 0, 0, pQ->PostMessage );

                            } else {

                                FORWARD_WM_KEYUP(   NULL, pKP->second, 0, 0, pQ->PostMessage );

                            }

                            break;

                        }

                        switch( symbol ) {

                            case XK_space ... XK_asciitilde:

                                if ( KeyPress == event.type ) {

                                    FORWARD_WM_CHAR( NULL, symbol, 0, pQ->PostMessage );

                                }
                                break;

                            case XK_Alt_L:
                            case XK_Alt_R:
                                // VK_MENU
                                break;

                            case XK_Control_L:
                            case XK_Control_R:
                                // VK_CONTROL
                                break;

                            case XK_Shift_L:
                            case XK_Shift_R:
                                // VK_SHIFT
                                break;

                        }
                        break;

                    case MotionNotify:

                        pQ->PostMouseMove( event.xmotion.x, event.xmotion.y, 0 );
                        break;

                    case ResizeRequest:

                        DBG_MSG( DBG_GRAPHICAL, TEXT( "HOST RESIZING width %d, height %d" ), event.xresizerequest.width, event.xresizerequest.height );
                        break;

                    default:

                        DBG_MSG( DBG_GRAPHICAL, TEXT( "X event type %d unhandled" ), event.type );
                        break;

                }

            }

            XFlush( x.display );
            XFlushGC( x.display, x.dc );

            return true;

        }

} X;


int GL::glInit( int cx, int cy, EventQ & Q, int argc, char * Argv[] ) {

    /* open connection with the server */
    x.display = XOpenDisplay( NULL );

    if ( x.display == NULL ) {

        // fprintf(stderr, "Cannot open display\n");
        return -1;

    }

    x.screen = DefaultScreen( x.display );

    x.dc = DefaultGC( x.display, x.screen );

    x.cmap = DefaultColormap( x.display, x.screen );

    COLORREF c = GetSysColor( COLOR_DESKTOP );

    XColor xcolour;

#define RGB2XCOLOR( c ) (unsigned short int)( 65535.0 * ( c / 255.0 ) )
    xcolour.red   = RGB2XCOLOR( GetRValue( c ) );
    xcolour.green = RGB2XCOLOR( GetGValue( c ) );
    xcolour.blue  = RGB2XCOLOR( GetBValue( c ) );

    xcolour.flags = DoRed | DoGreen | DoBlue;

    XAllocColor( x.display, x.cmap, &xcolour );

    /* create window */
    x.window = XCreateSimpleWindow(
                                    x.display,
                                    RootWindow( x.display, x.screen ),
                                    0, 0, cx, cy,
                                    1,
                                    BlackPixel( x.display, x.screen ),
                                    xcolour.pixel /* WhitePixel( x.display, x.screen ) */
                                  );

    /* select kind of events we are interested in */
    x.eventmask = ButtonPressMask | ButtonReleaseMask | ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ResizeRedirectMask;
    XSelectInput( x.display, x.window, x.eventmask );

    /* map (show) the window */
    XMapWindow( x.display, x.window );

    X.s  = ConnectionNumber( x.display );
    X.pQ = &Q;

    Q.addToQ( Q.ReadQ, &X );

    return 0;

}


void Close() {

    if ( INVALID_SOCKET != X.s ) {

        X.pQ->RemoveSocket( X.s );
        X.s = INVALID_SOCKET;
    }

    if ( 0 != x.display ) {

        XDestroyWindow( x.display, x.window );

        /* close connection to server */
        XCloseDisplay( x.display );
        x.display = 0;

    }

}


void GL::glDestroy( void ) {

    Close();

}


extern "C" void glutPostRedisplay() {

//    XFlush( x.display );

}


extern "C" void glutMainLoopEvent() {

//    XFlush( x.display );

}


void StartPoints( void ) {}


void EndPoints( void ) {

      XFlush( x.display );
      XFlushGC( x.display, x.dc );

}


void DC::Out( const POINT & pt, COLORREF c ) {

    static COLORREF oldC = 0;

    if ( oldC != c ) {

        oldC = c;

        XColor xcolour;

        xcolour.red   = (unsigned short int)( 65535.0 * ( GetRValue( c ) / 255.0 ) );
        xcolour.green = (unsigned short int)( 65535.0 * ( GetGValue( c ) / 255.0 ) );
        xcolour.blue  = (unsigned short int)( 65535.0 * ( GetBValue( c ) / 255.0 ) );

        xcolour.flags = DoRed | DoGreen | DoBlue;

        XAllocColor( x.display, x.cmap, &xcolour );

        XSetForeground( x.display, x.dc, xcolour.pixel );
        //XFillRectangle(d, w, gc, 0, 0, winatt.width, 30);
        //XFlush(d);

        // XSetForeground( x.display, x.dc, c );

    }

    XDrawPoint( x.display, x.window, x.dc, pt.x, pt.y );

}


#endif /* ! ANDROID */
#endif /* YOU_WIN_GRAPHICAL && YOU_WIN_GRAPHICAL_XWIN */
