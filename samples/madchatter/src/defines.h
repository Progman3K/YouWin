#ifndef MADCHATTER_DEFINES_H
#define MADCHATTER_DEFINES_H


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */

#define EOL "\n"

#include "strings.h"
#include "resource.h"

#define Dim( array ) ( sizeof( array ) / sizeof( array[0] ) )


#define IDSZ_APPNAME                         "Mad Chatter"

#define ERROR_APP_TITLE		                 TEXT( "Mad Chatter - ERROR" )


#ifdef _WIN32
#define SetClassBackgroundBrush( hWnd, hBr ) SetClassLong( hWnd, GCL_HBRBACKGROUND, (LONG)hBr )
#define SetClassIcon( hWnd, hIcon )          SetClassLongPtr( hWnd, GCLP_HICON, (LONG_PTR)hIcon )
#define GetClassIcon( hWnd )                 ((HICON)GetClassLongPtr( hWnd, GCLP_HICON ))
#define REACTIVATE_INSTANCE( hWnd )          SetForegroundWindow( hWnd )
#else
#ifdef _WIN32_WCE
#define SetClassBackgroundBrush( hWnd, hBr ) SetClassWord( hWnd, GCW_HBRBACKGROUND, (WORD)hBr )
#define SetClassIcon( hWnd, hIcon )          SetClassWord( hWnd, GCW_HICON, (WORD)hIcon )
#define GetClassIcon( hWnd )                 ((HICON)GetClassWord( hWnd, GCW_HICON ))
#define REACTIVATE_INSTANCE( hWnd )          BringWindowToTop( hWnd )
#else
#define SetClassIcon( hWnd, hIcon )          SetClassLongPtr( hWnd, GCLP_HICON, (LONG_PTR)hIcon )
#endif
#endif


#define ID_CHATTER_SERVICE_PORT              ( (u_short)(unsigned)4873 )

#define ID_NOTIFICATION_MASK                 ( FD_CONNECT | FD_READ | FD_CLOSE )

#define IDSZ_CHATTER_WINDOW_CLASS            "CHATTER|Main"


#ifdef WIN32
#ifdef _WIN32_WCE
#define IDSZ_CHATTER_INIFILE                 TEXT( "HKEY_LOCAL_MACHINE\\SoftWare\\MadChatter" )
#define IDD_MAIN_DIALOG                      IDD_CHATTER_MAIN_FOR_HANDHELD
#else /* ! _WIN32_WCE */
#define IDSZ_CHATTER_INIFILE                 TEXT( "CHatter.ini" )
#define IDD_MAIN_DIALOG                      IDD_CHATTER_MAIN
#endif /* ! _WIN32_WCE */
#endif /* WIN32 */

#ifndef HANDLE_WM_DISPLAYCHANGE
#define HANDLE_WM_DISPLAYCHANGE(hwnd, wParam, lParam, fn) ((fn)((hwnd), (UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#endif

#ifdef ANDROID
#define IDD_MAIN_DIALOG                      IDD_CHATTER_MAIN_FOR_ANDROID_PORTRAIT
#endif

#if defined( linux ) || defined( __DARWIN__ )
#define IDSZ_CHATTER_INIFILE                 TEXT( "CHatter.ini" )
#endif


#define MAX_HOST_NAME_SIZE                   128
#define MAX_USER_NAME_SIZE                   128

#define IDSZ_SEPARATORS                      "\t, /"
#define IsComment( szToken )                 ( '#' == *szToken )

// #define ID_TIMER_DEFAULT_INTERVAL            300            /* Initial timer timeout in milliseconds*/

#define WM_WSAASYNCSELECT                    (WM_USER + 0x80)

#define WM_WSAASYNCGETHOSTBYNAME             (WM_USER + 0x81)

#define WM_WSAASYNCTCPXFER                   (WM_USER + 0x82)

#define MAX_TEMPSTRING_SIZE                  1024

#define ID_CHATTER_BROADCAST_TIMER           1
//#define ID_SENDFILE_TIMER                    2
#define ID_INDIVIDUAL_XFER_TIMER_ID_BASE     3

#define BROADCAST_TIMER_INTERVAL_SECONDS     ( 2 * 60 )  // Default: Two minutes

#define HEARD_PEER_MAX_LIMIT_SECONDS         ( 4 * 60 )  // Must hear from all peers at least this often. Default: Four minutes

#define DEFAULT_WINDOW_SIZE                  6

#define OFFER_FILE_TIMER_INTERVAL_SECONDS    ( 5 )


#endif /* MADCHATTER_DEFINES_H */
