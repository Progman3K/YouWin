

#include <DbgTrace.h>


#if defined( YOU_WIN_GRAPHICAL_LXFB )



#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <linux/kd.h>

#include <ASCII.h>

#include "lxfb.h"
#include "console_input.h"
#include "graphical.h"
#include "dc.h"


static void showCursor(bool show) {
#define CSI "\e["
  if (show) {
    fputs(CSI "?25h", stdout);
  }
  else {
//    fputs(CSI "?25l", stdout);
    fputs(CSI "?12l", stdout);
//    '\033[?12l'
  }
#undef CSI
}


static struct FBDEV : public Handler {

    int    fbfd;
    char * fbp;
    int    iOldmode;

    long int screensize;

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    FBDEV() : Handler( INVALID_SOCKET, NULL ) {

        fbfd       = -1;
        fbp        = (char *)-1;
        iOldmode   = -1;
        screensize = 0;

    }

    FBDEV( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) {}

    int Open( void ) {

        showCursor( false );
        set_console_input_mode();

        fbfd = open( "/dev/fb0", O_RDWR );

        if ( -1 == fbfd ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO OPEN FRAMEBUFFER %d" ), GetLastError() );
            return -1;

        }

#if 0
        int iOldmode = 0;
        if ( -1 == ioctl( fbfd, KDGETMODE, &iOldmode ) ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO GET FRAMEBUFFER MODE %d" ), GetLastError() );
            return -1;

        }

        unsigned int imode = KD_GRAPHICS;
        if ( -1 == ioctl( fbfd, KDSETMODE, &imode ) ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO SET FRAMEBUFFER TO GRAPHICAL MODE %d" ), GetLastError() );
            return -1;

        }
#endif
        if ( -1 == ioctl( fbfd, FBIOGET_FSCREENINFO, &finfo ) ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO OBTAIN FIXED SCREEN INFORMATION %d" ), GetLastError() );
            return -1;

        }

        // Get variable screen information
        if ( -1 == ioctl( fbfd, FBIOGET_VSCREENINFO, &vinfo ) ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: UNABLE TO OBTAIN VARIABLE SCREEN INFORMATION %d" ), GetLastError() );
            return -1;

        }

        // Size of the screen in bytes
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

        // Map the device to memory
        fbp = (char *)mmap( 0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0 );

        if ( fbp == (char *)-1 ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: FAILED TO MAP FRAMEBUFFER DEVICE TO MEMORY %d" ), GetLastError() );
            exit( 4 );

        }

        DBG_MSG( DBG_ERROR, TEXT( "Display %dx%d, %dbpp\n" ), vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

        return 0;

    }

    void Close() {

        if ( (char *)-1 != fbp ) {

            munmap( fbp, screensize );
            fbp = (char *)-1;

        }

        if ( -1 != fbfd ) {
#if 0
            if ( -1 != iOldmode ) {

                ioctl( fbfd, KDSETMODE, &iOldmode );
                iOldmode = -1;

            }
#endif
            close( fbfd );
            fbfd = -1;

        }

        reset_console_input_mode();

        showCursor( true );

    }

    bool EventHandler() override {

        bool bRet = readconsoleinput( getsocket(), pQ );

        if ( ! bRet ) {

            DBG_MSG( DBG_ERROR, TEXT( "Error reading console" ) );
            return false;

        }

        return true;

    }

} fbdev;


int ywDisplay::Init( int cx, int cy, EventQ & Q, int argc, char * Argv[], LPARAM ) {

    int i = fbdev.Open();

    if ( -1 == i ) {

        return -1;

    }

    fbdev.s = fileno( stdin ); // stdin socket is socket zero
    fbdev.pQ = &Q;

    Q.addToQ( Q.ReadQ, &fbdev );

    return 0;

}


void ywDisplay::Destroy( void ) {

    fbdev.Close();

}


//extern "C" void glutPostRedisplay() {}
//extern "C" void glutMainLoopEvent() {}


void DC::Out( const POINT & pt, COLORREF c ) {

    if ( ( ! ( pt.x < fbdev.vinfo.xres ) ) || ( ! ( pt.y < fbdev.vinfo.yres ) ) ) {

        return;

    }

    long int location = ( pt.x + fbdev.vinfo.xoffset ) * ( fbdev.vinfo.bits_per_pixel / 8 ) + ( pt.y + fbdev.vinfo.yoffset ) * fbdev.finfo.line_length;

    RGBQUAD * pRGBQ = (RGBQUAD *)( fbdev.fbp + location );

    pRGBQ->rgbRed      = GetRValue( c );
    pRGBQ->rgbGreen    = GetGValue( c );
    pRGBQ->rgbBlue     = GetBValue( c );
    pRGBQ->rgbReserved = 0; // No transparency

}


#endif /* YOU_WIN_GRAPHICAL_LXFB */
