

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


#endif /* __H_APPLE_H__ */
