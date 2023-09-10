 
#ifndef YOUWIN_WTYPES_H
#define YOUWIN_WTYPES_H


#include "tchar.h"


typedef unsigned char BYTE;
typedef BYTE * PBYTE;
typedef BYTE * LPBYTE;

typedef BYTE BOOLEAN;

typedef float FLOAT;

typedef unsigned short USHORT;

typedef void * HANDLE;
typedef HANDLE HGDIOBJ;
typedef HANDLE HBRUSH;
typedef HANDLE HBITMAP;
typedef HANDLE HPEN;
typedef HANDLE HCURSOR;
typedef HANDLE HFONT;
typedef HANDLE HMENU;
typedef HANDLE HICON;
typedef HANDLE HINSTANCE;
typedef HANDLE HWND;
typedef HANDLE HIMAGELIST;
typedef int INT;
typedef long INT_PTR;
typedef long LONG;
typedef unsigned long ULONG;
typedef LONG * LONG_PTR;
typedef ULONG * ULONG_PTR;
typedef long long LONGLONG;
typedef int SOCKET;
typedef unsigned long WPARAM;
typedef unsigned int UINT;
typedef long LPARAM;
typedef char CHAR;
typedef char * PSTR, * LPSTR;
typedef const char * PCSTR, * LPCSTR;
typedef TCHAR * LPTSTR;
typedef const TCHAR * LPCTSTR;
typedef unsigned long DWORD;
typedef DWORD * LPDWORD;
typedef int WINBOOL;

#ifndef _OBJC_OBJC_H_
typedef signed char BOOL;
#endif

typedef unsigned long DWORD_PTR;
typedef long LRESULT;
typedef unsigned long UINT_PTR;
typedef unsigned short WORD;
typedef WORD ATOM;
typedef void * LPVOID;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE HRSRC;
typedef HANDLE HRGN;
typedef HANDLE HDC;
typedef HINSTANCE HMODULE;
typedef unsigned char UCHAR;
typedef void * PVOID;
typedef LONG HRESULT;
typedef unsigned short WCHAR;
typedef WCHAR * PWCHAR;
typedef WCHAR * PWSTR;
typedef PWSTR LPWSTR;


typedef LRESULT (* WNDPROC)( HWND, UINT, WPARAM, LPARAM );
typedef INT_PTR (* DLGPROC)( HWND, UINT, WPARAM, LPARAM );
typedef BOOL (* WNDENUMPROC)( HWND, LPARAM );
typedef void (* TIMERPROC)( HWND, UINT, UINT_PTR, DWORD );
typedef BOOL (* ENUMRESNAMEPROC)( HMODULE, LPCTSTR, LPTSTR, LONG_PTR );
typedef BOOL (* ENUMRESTYPEPROC)( HMODULE, LPTSTR, LONG_PTR );


typedef struct {

    HWND    hwnd;
    LPARAM  lParam;
    WPARAM  wParam;
    UINT    message;

} MSG;


#endif /* YOUWIN_WTYPES_H */
