

#ifndef YW_H_YOU_WIN_H
#define YW_H_YOU_WIN_H


#if ! defined( YOU_WIN_TXT ) && ! defined( YOU_WIN_GRAPHICAL )
#error ONE OF THE FOLLOWING MUST BE DEFINED - YOU_WIN_TXT or YOU_WIN_GRAPHICAL
#endif
#if defined( YOU_WIN_TXT ) && defined( YOU_WIN_GRAPHICAL )
#error ONLY ONE OF THE FOLLOWING MUST BE DEFINED - YOU_WIN_TXT or YOU_WIN_GRAPHICAL
#endif
#if defined( YOU_WIN_GRAPHICAL ) && ! ( defined( YOU_WIN_GRAPHICAL_OPENGL ) || defined( YOU_WIN_GRAPHICAL_XWIN ) || defined( ANDROID) || defined( YOU_WIN_GRAPHICAL_OSX ) )
#error WHEN BUILDING YOU_WIN_GRAPHICAL ONLY ONE OF THE FOLLOWING MUST BE DEFINED - YOU_WIN_GRAPHICAL_OPENGL or YOU_WIN_GRAPHICAL_XWIN or ANDROID or YOU_WIN_GRAPHICAL_OSX
#endif


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cstring>
#include <cerrno>

#include <memory>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <pthread.h>

#include <DbgTrace.h>

#include <ywnativeapi.h>

#include <windowsx.h>
#include <commctrl.h>
#include <dshow.h>

#include <netinet/in.h>
#include <fcntl.h>
#include <pwd.h>

#ifdef __MACH__
#include <dispatch/dispatch.h>
#include <mach/mach_time.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <mach-o/ldsyms.h>
#else /* Other unices */
#include <semaphore.h>
#endif

#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>


#if defined(YOU_WIN_GRAPHICAL_OSX)
#include "apple.h"
#endif


#ifdef YOU_WIN_TXT

#include "text.h"

#else /* GRAPHICAL */

#include "graphical.h"

#ifdef ANDROID
#include "ywandroid.h"
#endif

#endif /* GRAPHICAL */


#include <ASCII.h>

#include "AsyncReadSocket.h"
#include "AsyncWriteSocket.h"
#include "atom.h"
#include "bitmap.h"
#include "brush.h"
#include "click.h"
#include "findfile.h"
#include "font.h"
#include "pen.h"
#include "dc.h"
#include "defwindowclass.h"
#include "event.h"
#include "cursor.h"
#include "DlgRes.h"
#include "eventq.h"
#include "icon.h"

#include "syscolors.h"

#include "genericwindow.h"
#include "desktop.h"
#include "dialog.h"
#include "button.h"
#include "edit.h"
#include "combobox.h"
#include "listbox.h"
#include "static.h"
#include "progressbar.h"
#include "animate.h"
#include "trackbar.h"
#include "tabcontrol.h"
#include "treeview.h"
#include "listview.h"
#include "userwndclass.h"
#include "menu.h"
#include "messagebox.h"
#include "getopenfilename.h"

#include "defines.h"

#undef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) extern const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }


#ifndef Dim
#define Dim( array ) ( sizeof( array ) / sizeof( array[0] ) )
#endif

// Global variables and typedefs.
typedef struct {

    BOOLEAN              bInit;                       // Has library passed initialization.
    int                  iCX;                         // Display X size
    int                  iCY;                         // Display Y size
    BYTE                 ucWndSig[sizeof(SIGNATURE)]; // Signature for sanity checks on handles.
    IWindow *            pTopWnd;                     // Bottom-most window. (Desktop)
    Window *             pFocusWnd;                   // Who has focus/caret
    LPARAM               lClientData;                 // Private data passed back to user at terminaloutputfunc I/O
//    unsigned short       usAutoTimerID;               // Next Auto-ID timer ID
    TERMINALOUTPUTFUNC   pTerminal;                   // Raw output goes here
#if defined( ANDROID ) && defined( YOU_WIN_GRAPHICAL )
    struct android_app * app;
#endif
#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iOSApp *             app;
#endif
    EventQ               Q;

} GLOBALS;


extern GLOBALS g;          // Variables global to entire application.
extern HFONT   hSystemFont;
extern HMODULE hYouWinModule;

extern DesktopClass     CDesktop;
extern DialogClass      CDialog;
extern ButtonClass      CButton;
extern EditClass        CEdit;
extern ListboxClass     CListbox;
extern ComboboxClass    CCombobox;
extern StaticClass      CStatic;
extern ProgressbarClass CProgressbar;

// Returns a pointer to the windows data storage or NULL if handle is NOT valid.
#define IsWnd( h ) Window::ToWnd( h, __FILE__, __LINE__ )

// ------------------------------ Native API

extern "C" unsigned long repaint( RECT & r );

// Returns 0 if all went well.
int CloseWindowLib( void );


#ifdef __MACH__
#define SYSTEM_RESOURCE_SEGMENT_START binary_ywresource_res
#define SYSTEM_RESOURCE_SEGMENT_SIZE  binary_ywresource_res_size
#define USER_RESOURCE_SEGMENT_START   binary_resource_res
#define USER_RESOURCE_SEGMENT_SIZE    binary_resource_res_size
#else
#define SYSTEM_RESOURCE_SEGMENT_START _binary_ywresource_res
#define SYSTEM_RESOURCE_SEGMENT_SIZE  _binary_ywresource_res_size
#define USER_RESOURCE_SEGMENT_START   _binary_resource_res
#define USER_RESOURCE_SEGMENT_SIZE    _binary_resource_res_size
#endif

extern const char SYSTEM_RESOURCE_SEGMENT_START[];
extern const int  SYSTEM_RESOURCE_SEGMENT_SIZE;
extern const char USER_RESOURCE_SEGMENT_START[];
extern const int  USER_RESOURCE_SEGMENT_SIZE;


#endif /* YW_H_YOU_WIN_H */
