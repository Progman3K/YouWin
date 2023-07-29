

#include "ywin.h"


#if defined( YOU_WIN_GRAPHICAL ) && defined( YOU_WIN_GRAPHICAL_OPENGL )
#ifndef ANDROID


namespace GL {
#ifdef __DARWIN__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/glx.h>
#endif
}


/* These defines missing from glut headers??? */
#define GLUT_MOUSEWHEEL_UP   0x0003
#define GLUT_MOUSEWHEEL_DOWN 0x0004

#define GLUT_KEY_LSHIFT      0x0070
#define GLUT_KEY_RSHIFT      0x0071
#define GLUT_KEY_CONTROL     0x0072
#define GLUT_KEY_ALT         0x0074


using namespace GL;


#include "glevents.h"


static GLEvents GLInput;

static int      window      = 0;

static unsigned uMKControl  = 0;
static unsigned uMKLButton  = 0;
static unsigned uMKMButton  = 0;
static unsigned uMKRButton  = 0;
static unsigned uMKShift    = 0;
static unsigned uMKXButton1 = 0;
static unsigned uMKXButton2 = 0;


void StartPoints( void ) {

//    DBG_MSG( DBG_GRAPHICAL, TEXT( "GL StartPoints" ) );
    glBegin( GL_POINTS );

}


void EndPoints( void ) {

//    DBG_MSG( DBG_GRAPHICAL, TEXT( "GL EndPoints" ) );
    glEnd();

    glFlush();

}


void DC::Out( const POINT & pt, COLORREF c ) {

    glColor4f( GetRValue( c ) / 255.0, GetGValue( c ) / 255.0, GetBValue( c ) / 255.0, GetAValue( c ) / 255.0 );
    glVertex2f( pt.x + 0.5, pt.y + 0.5 );

}


void MouseButton( int button, int state, int x, int y ) {

  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
    DBG_MSG( DBG_GRAPHICAL, TEXT( "GL mouse button %d, state %d at (%d,%d)" ), button, state, x, y );

    switch ( button ) {

        case GLUT_LEFT_BUTTON:

            switch( state ) {

                case GLUT_DOWN: { uMKLButton = MK_LBUTTON; GLInput.pQ->PostMouseMsg( false, x, y, VK_LBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;
                case GLUT_UP:   { uMKLButton = 0;          GLInput.pQ->PostMouseMsg(  true, x, y, VK_LBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;

            }
            return;

        case GLUT_RIGHT_BUTTON:

            switch( state ) {

                case GLUT_DOWN: { uMKRButton = MK_RBUTTON; GLInput.pQ->PostMouseMsg( false, x, y, VK_RBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;
                case GLUT_UP:   { uMKRButton = 0;          GLInput.pQ->PostMouseMsg(  true, x, y, VK_RBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;

            }
            return;

        case GLUT_MIDDLE_BUTTON:

            switch( state ) {

                case GLUT_DOWN: { uMKMButton = MK_MBUTTON; GLInput.pQ->PostMouseMsg( false, x, y, VK_MBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;
                case GLUT_UP:   { uMKMButton = 0;          GLInput.pQ->PostMouseMsg(  true, x, y, VK_MBUTTON, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) ); } break;

            }
            return;

        case GLUT_MOUSEWHEEL_UP:

            FORWARD_WM_KEYDOWN( NULL, VK_UP, 0, 0, GLInput.PostMessage );
            break;

        case GLUT_MOUSEWHEEL_DOWN:

            FORWARD_WM_KEYDOWN( NULL, VK_DOWN, 0, 0, GLInput.PostMessage );
            break;

    }

}


void MouseCapture( int x, int y ) {

    GLInput.pQ->PostMouseMove( x, y, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) );

}


void MouseMove( int x, int y ) {

    GLInput.pQ->PostMouseMove( x, y, ( uMKControl | uMKLButton | uMKMButton | uMKRButton | uMKShift | uMKXButton1 | uMKXButton2 ) );

}


static void PostKeyMsg( bool bUp, unsigned char c, int x, int y ) {

    UINT vKey;

    switch( c ) {

        case CARRIAGERETURN:  vKey = VK_RETURN; break;
        case BS:  vKey = VK_BACK;   break;
        case DEL: vKey = VK_DELETE; break;
        case ESC: vKey = VK_ESCAPE; break;
        case ' ': vKey = VK_SPACE;  break;
        case TAB: vKey = VK_TAB;    break;

        default:

            if ( ' ' <= c ) {

                if ( ! bUp ) {

                    FORWARD_WM_CHAR( NULL, c, 0, GLInput.PostMessage );

                }

            } else {

                DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN key%s control key %d at (%d,%d)" ), bUp ? "up" : "down", c, x, y );

            }

            return;

    }

    /* Check for printable chars */
    bUp ? FORWARD_WM_KEYUP(   NULL, vKey, 0, 0, GLInput.PostMessage )
        : FORWARD_WM_KEYDOWN( NULL, vKey, 0, 0, GLInput.PostMessage );

}


void glkeysup( unsigned char c, int x, int y ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ASCII key %d UP at (%d,%d)" ), c, x, y );
    PostKeyMsg( true, c, x, y );

}
void glkeys( unsigned char c, int x, int y ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ASCII key %d DOWN at (%d,%d)" ), c, x, y );
    PostKeyMsg( false, c, x, y );

}


static void PostFKeyMsg( bool bUp, int c, int x, int y ) {

    UINT vKey;

    switch( c ) {

        case GLUT_KEY_F1:        vKey = VK_F1;                   break;
        case GLUT_KEY_F2:        vKey = VK_F2;                   break;
        case GLUT_KEY_F3:        vKey = VK_F3;                   break;
        case GLUT_KEY_F4:        vKey = VK_F4;                   break;
        case GLUT_KEY_F5:        vKey = VK_F5;                   break;
        case GLUT_KEY_F6:        vKey = VK_F6;                   break;
        case GLUT_KEY_F7:        vKey = VK_F7;                   break;
        case GLUT_KEY_F8:        vKey = VK_F8;                   break;
        case GLUT_KEY_F9:        vKey = VK_F9;                   break;
        case GLUT_KEY_F10:       vKey = VK_F10;                  break;
        case GLUT_KEY_F11:       vKey = VK_F11;                  break;
        case GLUT_KEY_F12:       vKey = VK_F12;                  break;

        case GLUT_KEY_LEFT:      vKey = VK_LEFT;                 break;
        case GLUT_KEY_UP:        vKey = VK_UP;                   break;
        case GLUT_KEY_RIGHT:     vKey = VK_RIGHT;                break;
        case GLUT_KEY_DOWN:      vKey = VK_DOWN;                 break;

        case GLUT_KEY_PAGE_UP:   vKey = VK_PRIOR;                break;
        case GLUT_KEY_PAGE_DOWN: vKey = VK_NEXT;                 break;

        case GLUT_KEY_HOME:      vKey = VK_HOME;                 break;
        case GLUT_KEY_END:       vKey = VK_END;                  break;
        case GLUT_KEY_INSERT:    vKey = VK_INSERT;               break;

        case GLUT_KEY_LSHIFT:    vKey = VK_LSHIFT;
                                  bUp ? uMKShift = 0
                                      : uMKShift = MK_SHIFT;     break;

        case GLUT_KEY_RSHIFT:    vKey = VK_RSHIFT;
                                  bUp ? uMKShift = 0
                                      : uMKShift = MK_SHIFT;     break;

        case GLUT_KEY_CONTROL:   vKey = VK_CONTROL;
                                  bUp ? uMKControl = 0
                                      : uMKControl = MK_CONTROL; break;

        case GLUT_KEY_ALT:       vKey = VK_LMENU;                break;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN function key %d at (%d,%d)" ), c, x, y );
            return;

    }

    bUp ? FORWARD_WM_KEYUP(   NULL, vKey, 0, 0, GLInput.PostMessage )
        : FORWARD_WM_KEYDOWN( NULL, vKey, 0, 0, GLInput.PostMessage );


}


void glfunctionkeysup( int c, int x, int y ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Function key %d UP at (%d,%d)" ), c, x, y );
// uMKXButton1 = MK_XBUTTON1;
// uMKXButton2 = MK_XBUTTON2;

    PostFKeyMsg( true, c, x, y );

}
void glfunctionkeys( int c, int x, int y ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Function key %d DOWN at (%d,%d)" ), c, x, y );
// uMKXButton1 = 0;
// uMKXButton2 = 0;

    PostFKeyMsg( false, c, x, y );

}


void GL::drawscreen( void ) {

    DBG_MSG( DBG_GRAPHICAL, TEXT( "GL drawscreen" ) );
    glutSwapBuffers();

}


void reshape( int cx, int cy ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Setting up a 2D projection, desktop resized to %dx%d" ), cx, cy );

//    glutInitWindowSize( cx, cy );

    glViewport( 0, 0, cx, cy );

//    glutReshapeWindow( cx, cy );

    glMatrixMode( GL_PROJECTION );

    /* Reset world coordinates first ... */
    glLoadIdentity();

    /* Then set them to what we want based on the new aspect ratio */
    glOrtho( 0, cx, cy, 0, 0, 1 );

    glMatrixMode( GL_MODELVIEW );

    /* Displacement trick for exact pixelization */
    glTranslatef( 0.375, 0.375, 0 );

    glLoadIdentity();

    HWND hWnd = GetDesktopWindow();

    if ( NULL == hWnd ) {

        COLORREF c = GetSysColor( COLOR_BACKGROUND );

        glClearColor( GetRValue( c ) / 255.0, GetGValue( c ) / 255.0, GetBValue( c ) / 255.0, GetAValue( c ) / 255.0 );

        glClear( GL_COLOR_BUFFER_BIT );

    } else {

        FORWARD_WM_DISPLAYCHANGE( hWnd, 24, cx, cy, SendMessage );

    }

}


void PrepGL( int cx, int cy ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "OpenGL initialization begins" ) );

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB /* | GLUT_DEPTH */ );

    glDisable( GL_DEPTH_TEST );

    glViewport( 0, 0, cx, cy );

    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

#ifdef __DARWIN__
    gluOrtho2D( 0, cx, cy, 0 );
#else
    glOrtho( 0, cx, cy, 0, 0, 1 );
#endif

    glMatrixMode( GL_MODELVIEW );

    /* Displacement trick for exact pixelization */
    glTranslatef( 0.375, 0.375, 0 );

    glLoadIdentity();

    reshape( cx, cy );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "OpenGL initialization ends" ) );

}


int GL::glInit( int cx, int cy, EventQ & Q, int argc, char * argv[] ) {

#ifndef __DARWIN__

    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB /* | GLUT_DEPTH */ );

    glDisable( GL_DEPTH_TEST );

    glViewport( 0, 0, cx, cy );

    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

#ifdef __DARWIN__
    gluOrtho2D( 0, cx, cy, 0 );
#else
    glOrtho( 0, cx, cy, 0, 0, 1 );
#endif

    glMatrixMode( GL_MODELVIEW );

    glTranslatef( 0.375, 0.375, 0 );

    glLoadIdentity();

    glutInitWindowSize( cx, cy );

    window = glutCreateWindow( argv[0] );

    Display * dpy = glXGetCurrentDisplay();

    SOCKET s = ConnectionNumber( dpy );

    if ( -1 == s ) {

        return -1;

    }

    GLInput.s  = s;
    GLInput.pQ = &Q;

    Q.addToQ( Q.ReadQ, &GLInput );

#endif /* ! __DARWIN__ */

//    PrepGL( cx, cy );

    glutKeyboardFunc( glkeys );
    glutKeyboardUpFunc( glkeysup );

    glutSpecialFunc( glfunctionkeys );
    glutSpecialUpFunc( glfunctionkeysup );

    glutDisplayFunc( drawscreen );

    glutMouseFunc( MouseButton );

    glutMotionFunc( MouseCapture );

    glutPassiveMotionFunc( MouseMove );

    glutReshapeFunc( reshape );

    return 0;

}


void GL::glDestroy( void ) {

    if ( 0 != window ) {

        glutDestroyWindow( window );
        window = 0;

    }

}



#endif /* ! ANDROID */
#endif /* YOU_WIN_GRAPHICAL && YOU_WIN_GRAPHICAL_OPENGL */
