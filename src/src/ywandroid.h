

#ifndef __H_YOU_WIN_ANDROID_H__
#define __H_YOU_WIN_ANDROID_H__


#include <jni.h>


#include <android/configuration.h>
#include <android/input.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/native_window.h>
#include <android/native_activity.h>


extern int droidInit( struct android_app *, const char ** );
extern void droidDestroy( struct android_app * );
extern void displayKeyboard( struct android_app *, bool );
int droidSelect( struct timeval * ptimeout );


#define StartPoints()
#define EndPoints()
#define PostRefresh()
#define RasterUpdate()


#endif /* __H_YOU_WIN_ANDROID_H__ */
