

#include <Cocoa/Cocoa.h>


typedef struct {

    id  app;

} osxywapp;


extern "C" int osxmain( osxywapp * pApp, int cx, int cy, int argc, const char * * argv );
