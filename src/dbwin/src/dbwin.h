

//#pragma warning( disable : 4115 4200 4201 4214 4514 4699 )
#include <cstdio>
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#endif


#ifdef  _WIN32_WCE
#include<commctrl.h>
#endif  /* ! _WIN32_WCE */


#if defined( linux ) || defined( ANDROID )
#include <twindows.h>
#include <arpa/inet.h>
#endif

#include <ws2x.h>

#include "defines.h"

#include <ASCII.h>
#include <dbwinapi.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "appendtext.h"
#include "udptrace.h"
#include "capp.h"
#include "main_wnd.h"
#include "aboutwnd.h"
#include "settings.h"


typedef enum {

    MENU_POPUP_FILE = 0,
    MENU_POPUP_EDIT,
    MENU_POPUP_OPTIONS,
    MENU_POPUP_CLEAR,
    MENU_POPUP_HELP,

    MENU_POPUP_COUNT /* NOT a popup-menu placeholder, used to keep track of how many there are. */


} MENU_POPUPS;


extern HINSTANCE    g_hInst;
extern UINT         g_uiFindMsg;
extern HWND         g_hMainDlg;


/* File storage */
extern TCHAR        g_szIniFile[1024];

extern void DeleteText( HWND hEditWnd, unsigned uFactorToDelete );
extern BOOL Sure( HINSTANCE hInst, HWND hFocusWnd, LPCTSTR lpszMessageTitle, LPCTSTR lpszExtra, unsigned uLine, LPCTSTR lpszFile );
extern BOOL bFindFile( HWND hWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, HINSTANCE hInst );
BOOL bFind( HWND hWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, HINSTANCE hInst );

