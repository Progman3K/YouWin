#ifndef __IOS_H__
#define __IOS_H__
#if defined( YOU_WIN_GRAPHICAL_OSX )


#define PostRefresh()
#define RasterUpdate()
#define StartPoints()
#define EndPoints()


extern "C" int OSXGetMessage( class EventQ * pQ, struct timeval * ptimeout );
extern "C" int OSXAddAsyncSelectSocket( SOCKET s, long lEvent );
extern "C" int OSXRemoveAsyncSelectSocket( SOCKET s );


#endif /* YOU_WIN_GRAPHICAL_OSX */
#endif /* __IOS_H__ */
