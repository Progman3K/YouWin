

#include "strings.h"
#include "build.h"
// #include <version.h>

#ifndef HANDLE_WM_COPYDATA
#define HANDLE_WM_COPYDATA( hWnd, wParam, lParam, fn )              ( ( fn )( ( hWnd ), (HWND)( wParam ), (COPYDATASTRUCT *)( lParam ) ) )
#endif

#ifndef FORWARD_WM_COPYDATA
#define FORWARD_WM_COPYDATA( hWnd, hFromWnd, lpCopyDataStruct, fn ) ( fn )( ( hWnd ), WM_COPYDATA, (UINT)(hFromWnd), (LPARAM)(COPYDATASTRUCT FAR *)( lpCopyDataStruct ) )
#endif

#define Dim( array )                                    ( sizeof( array ) / sizeof( array[0] ) )
//#define ID                                              MAKEINTRESOURCE

#define	MAX_TEMPSTRING_SIZE								1024
#define	EOFMARKER										EOT
#define	DEFAULT_TRACEFILE_SIZE							2048
#define	MINIMUM_TRACEFILE_SIZE							32


#define	IDSZ_DBWIN_WINDOW_CLASS							"SUPER DBWIN"
#define	IDSZ_DEFAULT_DISPLAY_FONT_NAME					"Courrier New"
#define	WM_WSAASYNCSELECT								( WM_USER + 100 )
#define	ID_UPDATE_OUTPUT_TIMER							100


#ifdef	_WIN32_WCE
#define	IDSZ_INIFILE									"HKEY_LOCAL_MACHINE\\SoftWare\\DBWin"
#define	DLG_STYLES										( DS_LOCALEDIT | WS_SYSMENU | WS_OVERLAPPED | DS_MODALFRAME )
#else
#define	IDSZ_INIFILE									"DBWIN.INI"
#define	DLG_STYLES										( DS_LOCALEDIT | WS_SYSMENU | WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX )
#endif	/* ! _WIN32_WCE */


/* Icon resource IDs. */
#define	IDI_MAIN										1


/* Dialog resource IDs. */
#define	IDD_MAIN										1
#define	IDD_SETTINGS									2
#define	IDD_ABOUT										3


/* Menu resource IDs. */
#define	IDM_MAIN										1000


/* Main dialog menu and control IDs. */
#define	IDM_EXIT										IDCANCEL
#define	IDCMDBAR_MENU									1000
#define	IDE_OUTPUT										1100
#define	IDM_CLEAR_OUTPUT								1200
#define	IDM_COPY										1300
#define	IDM_SELECT_ALL									1400
#define	IDM_FIND										1500
#define	IDM_ABOUT										1600
#define	IDM_SETTINGS									1700
#define	IDM_ALLOC_BREAK									1800
#define	IDM_OUTPUT_TO_WINDOW							1900
#define	IDM_OUTPUT_TO_FILE								2000
#define	IDM_OUTPUT_TO_COM1								2100
#define	IDM_OUTPUT_TO_COM2								2200
#define	IDM_OUTPUT_TO_MONOCHROME						2300
#define	IDM_OUTPUT_DISABLE								2400
#define	IDM_ALWAYS_ON_TOP_TOGGLE						2500
#define	IDM_SAVE_DEBUG_SETTINGS							2600
#define	IDM_SAVE_BUFFER_AS								2700


/* Settings dialog control IDs. */
#define	IDB_CHOOSE_FONT									100
#define	IDRB_WORDWRAP									110


/* About dialog control IDs. */
#define	IDST_ABOUT_APP_NAME								100
#define	IDST_ABOUT_APP_COPYRIGHT						110
#define	IDST_ABOUT_APP_VERSION							120


#ifdef _WIN32

#define	IDSZ_APP_CAPTION								"Debug Messages*"
#define	IDSZ_WINSOCK									"WSOCK32.DLL"

#else

#define	IDSZ_APP_CAPTION								"Debug Messages"
#define	IDSZ_WINSOCK									"WINSOCK.DLL"
#define	DS_3DLOOK										0x0004L

#endif
