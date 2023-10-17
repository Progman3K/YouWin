

#include <DbgTrace.h>


#if defined( YOU_WIN_GRAPHICAL_LXFB )



#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <linux/kd.h>

#include <ASCII.h>

#include "ywin.h"
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



#if 0
void fbcon_cursor (int blank)
{
int fd = open("/dev/tty1", O_RDWR);
if(0 < fd)
{
write(fd, "\033[?25", 5);
write(fd, blank ? "h" : "l", 1);
}
close(fd);
}


void fbcon_blank (int blank)
{
ioctl(fb.fd, FBIOBLANK, blank ? VESA_POWERDOWN: VESA_NO_BLANKING);
return;
}

where fb.fd is the fd for /dev/fb0. 
#endif

static struct FBDEV : public Handler {

    int    fbfd;
    char * fbp;
    int    iOldmode;

    long int screensize;

    struct fb_var_screeninfo vinfo = {0};
    struct fb_fix_screeninfo finfo = {0};

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
//        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        screensize = finfo.smem_len;

        // Map the device to memory
        fbp = (char *)mmap( 0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0 );

        if ( fbp == (char *)-1 ) {

            DBG_MSG( DBG_ERROR, TEXT( "ERROR: FAILED TO MAP FRAMEBUFFER DEVICE TO MEMORY %d" ), GetLastError() );
            exit( 4 );

        }

        DBG_MSG( DBG_GRAPHICAL, TEXT( "Display %dx%d, %dbpp, %ld bytes storage\n" ), vinfo.xres, vinfo.yres, vinfo.bits_per_pixel, screensize );

        DBG_MSG( DBG_GRAPHICAL, TEXT( "ID '%s', VRAM start: %lX, type: %u, type aux: %u, visual: %u, line length: %u, MMIO start: %lX, MMIO length %u\n" ), finfo.id, finfo.smem_start, finfo.type, finfo.type_aux, finfo.visual, finfo.line_length, finfo.mmio_start, finfo.mmio_len );

        DBG_MSG( DBG_GRAPHICAL, TEXT( "\nRed bitfield: offset %u, length %u, msb_right %u\nGreen bitfield: offset %u, length %u, msb_right %u\nBlue bitfield: offset %u, length %u, msb_right %u\nTransparent bitfield: offset %u, length %u, msb_right %u" ),
                 vinfo.red.offset,    vinfo.red.length,    vinfo.red.msb_right,
                 vinfo.green.offset,  vinfo.green.length,  vinfo.green.msb_right,
                 vinfo.blue.offset,   vinfo.blue.length,   vinfo.blue.msb_right,
                 vinfo.transp.offset, vinfo.transp.length, vinfo.transp.msb_right

                 );

        g.iCX = vinfo.xres;
        g.iCY = vinfo.yres;

        return 0;

    }

    void Close() {

        if ( (char *)-1 != fbp ) {

            munmap( fbp, screensize );
            fbp = (char *)-1;

        }

        if ( -1 != fbfd ) {

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


void DC::Out( const POINT & pt, COLORREF c ) {

    if ( ( ! ( pt.x < fbdev.vinfo.xres ) ) || ( ! ( pt.y < fbdev.vinfo.yres ) ) ) {

        return;

    }

    unsigned long int location = ( pt.x + fbdev.vinfo.xoffset ) * ( fbdev.vinfo.bits_per_pixel / 8 ) + ( pt.y + fbdev.vinfo.yoffset ) * fbdev.finfo.line_length;

    auto makepixel = []( uint8_t red, uint8_t green, uint8_t blue ) {

        return ( blue >> ( __CHAR_BIT__ - fbdev.vinfo.blue.length ) ) | ( ( green >> ( __CHAR_BIT__ - fbdev.vinfo.green.length ) ) << fbdev.vinfo.green.offset ) | ( ( red >> ( __CHAR_BIT__ - fbdev.vinfo.red.length ) ) << fbdev.vinfo.red.offset );

    };

    uint32_t * pRGBQ = (uint32_t *)( fbdev.fbp + location );

    *pRGBQ = makepixel( GetRValue( c ), GetGValue( c ), GetBValue( c ) );

}


#endif /* YOU_WIN_GRAPHICAL_LXFB */
