

#ifndef __H_APPLE_H__
#define __H_APPLE_H__


#include <TargetConditionals.h>



#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#include <rawinput.h>
#include <iOSApp.h>
#include "iOSKeyMouse.h"

//#define StartPoints()
//#define EndPoints()
//#define PostRefresh()
#define RasterUpdate()
int iOSInit( iOSApp * );
int iOSCleanup( iOSApp * );
void displayKeyboard( iOSApp *, bool );
#endif

// TARGET_OS_EMBEDDED TARGET_OS_MAC TARGET_OS_UNIX TARGET_OS_WIN32

#ifdef __DARWIN__
extern "C" int OSXGetMessage( class EventQ * pQ, struct timeval * ptimeout );
extern "C" int OSXAddAsyncSelectSocket( SOCKET s, long lEvent );
extern "C" int OSXRemoveAsyncSelectSocket( SOCKET s );
#endif


#endif /* __H_APPLE_H__ */
