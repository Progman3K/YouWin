#ifndef __H_IOS_APP_H__
#define __H_IOS_APP_H__


#include <windows.h>


typedef void (*RENDERPROC)( const POINT &, COLORREF );
typedef void (*STARTPOINTSPROC)( void );
typedef void (*ENDPOINTSPROC)( void );


typedef struct {

    int             argc;
    char * *        argv;
    RENDERPROC      Out;
    STARTPOINTSPROC StartPoints;
    ENDPOINTSPROC   EndPoints;
    WINMAINPROC     _tWinMain;
    int             s;
    int             cx;
    int             cy;

} iOSApp;


extern "C" int iOSMain( iOSApp * );
typedef int (*IOSMAINPROC)( iOSApp * );


#endif // __H_IOS_APP_H__
