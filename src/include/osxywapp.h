#ifndef __OSX_YW_APP__
#define __OSX_YW_APP__


#include <Cocoa/Cocoa.h>


#include "ywnativeapi.h"


#define LoadResource YWLoadResource
#include <windows.h>


typedef struct {

    int      cx;
    int      cy;
    int      argc;
    char * * argv;
    id       app;

} osx_ywapp;


extern "C" int osxmain( osx_ywapp * pApp );


#endif /* __OSX_YW_APP__ */
