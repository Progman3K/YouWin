    #import <UIKit/UIKit.h>
    #import <Foundation/Foundation.h>
    #import <Foundation/NSArray.h>


    #import <dlfcn.h>
#define IDSZ_LIBAPP "madchatter.dylib"

    #import <sys/socket.h>
    #import <netinet/in.h>
    #import <pthread.h>
    #import "../src/bitmap.h"
    #import "ASCII.h"
    #import "rawinput.h"
    #import "iOSApp.h"
    #import "DbgTrace.h"
    #import <algorithm>


typedef struct {

    int      argc;
    char * * argv;
    int      cx;
    int      cy;

    union {

        sockaddr    sa;
        sockaddr_in sin;

    };

} T_PARAMS;


extern protoBitmap<COLORREF> ViewFB;
extern protoBitmap<COLORREF> OldFB;

extern pthread_mutex_t gViewFBx;
extern T_PARAMS params;

extern int gsOutput;
extern void * RunYouWin( void * );
extern void ProcessCommand( const RawPacket *, LPARAM );
extern void resizeFramebuffer( int cx, int cy );
extern bool SendInputMsg( int s, MsgHeader * pMsg );
extern void iosStaticInit( int cx, int cy );
extern void ExitApp( int i );

#define IDE_KEYBOARD 1

extern UIView * Viewself;
