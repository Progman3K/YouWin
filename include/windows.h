#ifndef YOUWIN_INTERFACE_H
#define YOUWIN_INTERFACE_H


#define YOU_WIN


#include "tchar.h"
#include "basetsd.h"

#include "windef.h"
#include "gdi.h"
#include "winuser.h"


#ifndef _SYSTEMTIME_
#define _SYSTEMTIME_
typedef struct _SYSTEMTIME{

    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;

} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif /* _SYSTEMTIME_ */


typedef struct _TIME_ZONE_INFORMATION {

    LONG       Bias;
    WCHAR      StandardName[32];
    SYSTEMTIME StandardDate;
    LONG       StandardBias;
    WCHAR      DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG       DaylightBias;

} TIME_ZONE_INFORMATION, *PTIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;


typedef struct tagTEXTMETRIC {

    LONG  tmHeight;
    LONG  tmAscent;
    LONG  tmDescent;
    LONG  tmInternalLeading;
    LONG  tmExternalLeading;
    LONG  tmAveCharWidth;
    LONG  tmMaxCharWidth;
    LONG  tmWeight;
    LONG  tmOverhang;
    LONG  tmDigitizedAspectX;
    LONG  tmDigitizedAspectY;
    TCHAR tmFirstChar;
    TCHAR tmLastChar;
    TCHAR tmDefaultChar;
    TCHAR tmBreakChar;
    BYTE  tmItalic;
    BYTE  tmUnderlined;
    BYTE  tmStruckOut;
    BYTE  tmPitchAndFamily;
    BYTE  tmCharSet;

} TEXTMETRIC, * PTEXTMETRIC;


typedef struct tagLOGFONT {

    LONG  lfHeight;
    LONG  lfWidth;
    LONG  lfEscapement;
    LONG  lfOrientation;
    LONG  lfWeight;
    BYTE  lfItalic;
    BYTE  lfUnderline;
    BYTE  lfStrikeOut;
    BYTE  lfCharSet;
    BYTE  lfOutPrecision;
    BYTE  lfClipPrecision;
    BYTE  lfQuality;
    BYTE  lfPitchAndFamily;
    TCHAR lfFaceName[LF_FACESIZE];

} LOGFONT, * PLOGFONT;

typedef int (* FONTENUMPROC)( const LOGFONT * plf, const TEXTMETRIC * ptm, DWORD dwType, LPARAM lParam );

typedef struct tagCREATESTRUCT {

    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    HWND        hwndParent;
    int         cy;
    int         cx;
    int         y;
    int         x;
    LONG        style;
    LPCTSTR     lpszName;
    LPCTSTR     lpszClass;
    DWORD       dwExStyle;

} CREATESTRUCT, * LPCREATESTRUCT;

typedef struct tagSIZE {

    LONG cx;
    LONG cy;

} SIZE, SIZEL, * PSIZE, * LPSIZE, * PSIZEL, * LPSIZEL;


typedef struct tagRECT {

    LONG left;
    LONG top;
    LONG right;
    LONG bottom;

#ifdef __cplusplus
    tagRECT operator () ( long lleft, long ltop, long lright, long lbottom ) {

        left   = lleft;
        top    = ltop;
        right  = lright;
        bottom = lbottom;

        return *this;

    }
#endif

} RECT, * PRECT, * LPRECT;
typedef const RECT * LPCRECT;


typedef struct tagDRAWITEMSTRUCT {

    UINT      CtlType;
    UINT      CtlID;
    UINT      itemID;
    UINT      itemAction;
    UINT      itemState;
    HWND      hwndItem;
    HDC       hDC;
    RECT      rcItem;
    ULONG_PTR itemData;

} DRAWITEMSTRUCT, * PDRAWITEMSTRUCT, * LPDRAWITEMSTRUCT;


typedef struct _RGNDATAHEADER {

    DWORD   dwSize;
    DWORD   iType;
    DWORD   nCount;
    DWORD   nRgnSize;
    RECT    rcBound;

} RGNDATAHEADER, * PRGNDATAHEADER;


typedef struct _RGNDATA {

  RGNDATAHEADER rdh;
  char          Buffer[];

} RGNDATA;


typedef struct tagPAINTSTRUCT {

    HDC  hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];

} PAINTSTRUCT, *PPAINTSTRUCT;


typedef struct {

    unsigned int    style;
    unsigned int    dwExtendedStyle;
    unsigned short  cdit;
    unsigned short  x;
    unsigned short  y;
    unsigned short  cx;
    unsigned short  cy;
    unsigned short  MenuName[];
    // Followed by class name
    // Followed by caption
    // *Might* be followed by a DIALOG_FONT_INFO structure

} DLGTEMPLATE;
typedef const DLGTEMPLATE * LPCDLGTEMPLATE;

typedef struct {

    unsigned int    style;
    unsigned int    dwExtendedStyle;
    unsigned short  x;
    unsigned short  y;
    unsigned short  cx;
    unsigned short  cy;
    unsigned short  id;
    unsigned short  ClassId[];
#if 0
    [Name or Ordinal] Text;
#endif
//  WORD   nExtraStuff;

} DLGITEMTEMPLATE;


typedef struct tagPoint {

    LONG x;  // X (or collumn position) coord on screen.
    LONG y;  // Y (or line number) coord on screen.

#ifdef __cplusplus
    bool operator != ( const tagPoint & pt2 ) const {

        return ( ( x != pt2.x ) || ( y != pt2.y ) );

    }

    tagPoint operator + ( const tagPoint & pt2 ) {

        x += pt2.x;
        y += pt2.y;

        return *this;

    }

    tagPoint operator - ( const tagPoint & pt2 ) {

        x -= pt2.x;
        y -= pt2.y;

        return *this;

    }

    tagPoint operator () ( long lx, long ly ) {

        x = lx;
        y = ly;

        return *this;

    }

#if 0
    tagPoint operator () ( int ix, int iy ) {

        x   = ix;
        y   = iy;

        return *this;

    }
#endif

#endif /* c++ */

} POINT, * PPOINT, * LPPOINT;


typedef struct tagLOGPEN {

    UINT     lopnStyle;
    POINT    lopnWidth;
    COLORREF lopnColor;

} LOGPEN, * PLOGPEN;


typedef struct tagDELETEITEMSTRUCT {

  UINT      CtlType;
  UINT      CtlID;
  UINT      itemID;
  HWND      hwndItem;
  ULONG_PTR itemData;

} DELETEITEMSTRUCT, * PDELETEITEMSTRUCT;


typedef struct {

    HWND    hwnd;
    LPARAM  lParam;
    WPARAM  wParam;
    UINT    message;

} MSG;


typedef struct tagWNDCLASS {

    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCTSTR     lpszMenuName;
    LPCTSTR     lpszClassName;

} WNDCLASS, * PWNDCLASS;


typedef struct tagSCROLLBARINFO {

    DWORD   cbSize;
    RECT    rcScrollBar;
    int     dxyLineButton;
    int     xyThumbTop;
    int     xyThumbBottom;
    int     reserved;
    DWORD   rgstate[CCHILDREN_SCROLLBAR + 1];

} SCROLLBARINFO, *PSCROLLBARINFO, *LPSCROLLBARINFO;


typedef struct tagSCROLLINFO {

    UINT    cbSize;
    UINT    fMask;
    int     nMin;
    int     nMax;
    UINT    nPage;
    int     nPos;
    int     nTrackPos;

} SCROLLINFO, *LPCSCROLLINFO;


typedef struct _NMHDR {

    HWND hwndFrom;
    UINT idFrom;
    UINT code;

} NMHDR, * LPNMHDR;


typedef struct _NMITEMACTIVATE {

    NMHDR  hdr;
    int    iItem;
    int    iSubItem;
    UINT   uNewState;
    UINT   uOldState;
    UINT   uChanged;
    POINT  ptAction;
    LPARAM lParam;
    UINT   uKeyFlags;

} NMITEMACTIVATE, * LPNMITEMACTIVATE;


typedef struct _GRADIENT_RECT {

  ULONG UpperLeft;
  ULONG LowerRight;

} GRADIENT_RECT, *PGRADIENT_RECT;

typedef USHORT COLOR16;

typedef struct _TRIVERTEX {

    LONG    x;
    LONG    y;
    COLOR16 Red;
    COLOR16 Green;
    COLOR16 Blue;
    COLOR16 Alpha;

} TRIVERTEX, *PTRIVERTEX;


typedef struct _GUID {

    DWORD Data1;
    WORD  Data2;
    WORD  Data3;
    BYTE  Data4[8];

#if defined(__cplusplus) || defined(__OBJC__)
    bool equals( const _GUID & guid ) const {

        if ( Data1 == guid.Data1 ) {

            return false;

        }

        if ( Data2 == guid.Data2 ) {

            return false;

        }

        if ( Data3 == guid.Data3 ) {

            return false;

        }

        for ( unsigned u = 0; u < ( sizeof( Data4 ) / sizeof( Data4[0] ) ); u++ ) {

            if ( Data4[u] != guid.Data4[u] ) {

                return false;

            }

        }

        return true;

#if 0
        return (
            ( Data1 == guid.Data1 )
            &&
            ( Data2 == guid.Data2 )
            &&
            ( Data3 == guid.Data3 )
            &&
            ( Data4 == guid.Data4 )
        );
#endif

    }
#if 0
    bool equals( const _GUID * guid ) const {

        return (
            ( Data1 == guid->Data1 )
            &&
            ( Data2 == guid->Data2 )
            &&
            ( Data3 == guid->Data3 )
            &&
            ( Data4 == guid->Data4 )
        );

    }
#endif /* Disabled, remove */
#endif /* __cplusplus || __OBJC__ */

} GUID;
typedef GUID KNOWNFOLDERID;

#define         DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) extern const GUID name DECLSPEC_HIDDEN
#define DEFINE_KNOWN_FOLDER(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)

DEFINE_KNOWN_FOLDER( FOLDERID_Documents, 0xfdd39ad0, 0x238f, 0x46af, 0xad, 0xb4, 0x6c, 0x85, 0x48, 0x03, 0x69, 0xc7 );


typedef enum tagCLSCTX {
    CLSCTX_INPROC_SERVER = 0x1,
    CLSCTX_INPROC_HANDLER = 0x2,
    CLSCTX_LOCAL_SERVER = 0x4,
    CLSCTX_INPROC_SERVER16 = 0x8,
    CLSCTX_REMOTE_SERVER = 0x10,
    CLSCTX_INPROC_HANDLER16 = 0x20,
    CLSCTX_INPROC_SERVERX86 = 0x40,
    CLSCTX_INPROC_HANDLERX86 = 0x80,
    CLSCTX_ESERVER_HANDLER = 0x100,
    CLSCTX_NO_CODE_DOWNLOAD = 0x400,
    CLSCTX_NO_CUSTOM_MARSHAL = 0x1000,
    CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000,
    CLSCTX_NO_FAILURE_LOG = 0x4000,
    CLSCTX_DISABLE_AAA = 0x8000,
    CLSCTX_ENABLE_AAA = 0x10000,
    CLSCTX_FROM_DEFAULT_CONTEXT = 0x20000
} CLSCTX;
#define CLSCTX_INPROC (CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER)


typedef struct {

    GUID  PowerSetting;
    DWORD DataLength;
    UCHAR Data[1];

} POWERBROADCAST_SETTING, * PPOWERBROADCAST_SETTING;


typedef struct tagWINDOWINFO {

  DWORD cbSize;
  RECT  rcWindow;
  RECT  rcClient;
  DWORD dwStyle;
  DWORD dwExStyle;
  DWORD dwWindowStatus;
  UINT  cxWindowBorders;
  UINT  cyWindowBorders;
  ATOM  atomWindowType;
  WORD  wCreatorVersion;

} WINDOWINFO, * PWINDOWINFO, * LPWINDOWINFO;


typedef struct _FILETIME {

    DWORD dwLowDateTime;
    DWORD dwHighDateTime;

} FILETIME, * PFILETIME;


typedef struct _WIN32_FIND_DATA {

    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    TCHAR    cFileName[MAX_PATH];
    TCHAR    cAlternateFileName[14];

} WIN32_FIND_DATA, * PWIN32_FIND_DATA, * LPWIN32_FIND_DATA;


typedef LRESULT (* LPOFNHOOKPROC)( HWND, UINT, WPARAM, LPARAM );


typedef struct tagOFN {

    DWORD         lStructSize;
    HWND          hwndOwner;
    HINSTANCE     hInstance;
    LPCTSTR       lpstrFilter;
    LPTSTR        lpstrCustomFilter;
    DWORD         nMaxCustFilter;
    DWORD         nFilterIndex;
    LPTSTR        lpstrFile;
    DWORD         nMaxFile;
    LPTSTR        lpstrFileTitle;
    DWORD         nMaxFileTitle;
    LPCTSTR       lpstrInitialDir;
    LPCTSTR       lpstrTitle;
    DWORD         Flags;
    WORD          nFileOffset;
    WORD          nFileExtension;
    LPCTSTR       lpstrDefExt;
    LPARAM        lCustData;
    LPOFNHOOKPROC lpfnHook;
    LPCTSTR       lpTemplateName;

} OPENFILENAME, * LPOPENFILENAME;


typedef struct tagCOMPAREITEMSTRUCT {

    UINT      CtlType;
    UINT      CtlID;
    HWND      hwndItem;
    UINT      itemID1;
    ULONG_PTR itemData1;
    UINT      itemID2;
    ULONG_PTR itemData2;
    DWORD     dwLocaleId;

} COMPAREITEMSTRUCT;


typedef INT_PTR (* LPFRHOOKPROC)( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

typedef struct {

    DWORD        lStructSize;
    HWND         hwndOwner;
    HINSTANCE    hInstance;
    DWORD        Flags;
    LPTSTR       lpstrFindWhat;
    LPTSTR       lpstrReplaceWith;
    WORD         wFindWhatLen;
    WORD         wReplaceWithLen;
    LPARAM       lCustData;
    LPFRHOOKPROC lpfnHook;
    LPCTSTR      lpTemplateName;

} FINDREPLACE, *LPFINDREPLACE;


typedef struct tagTPMPARAMS {

    UINT cbSize;
    RECT rcExclude;

} TPMPARAMS, * LPTPMPARAMS;


#ifdef __cplusplus
extern "C" {
#undef REFERENCE
#define REFERENCE &
#endif


typedef const KNOWNFOLDERID REFERENCE REFKNOWNFOLDERID;

typedef const GUID REFERENCE REFCLSID;

HANDLE AddFontMemResourceEx( PVOID pbFont, DWORD cbFont, PVOID pdv, DWORD * pcFonts );

HDC BeginPaint( HWND hWnd, PAINTSTRUCT * pPS );

BOOL BitBlt( HDC hDestDC, int x, int y, int cx, int cy, HDC hSrcDC, int nXSrc, int nYSrc, DWORD dwRop );

DWORD CheckMenuItem( HMENU hMenu, UINT uItem, UINT uCheck );

BOOL ClientToScreen( HWND hWnd, LPPOINT lpPt );

BOOL CloseHandle( HANDLE hObject );

HRESULT CoInitialize( LPVOID pvReserved );

void CoUninitialize( void );

HBITMAP CreateBitmap( int nWidth, int nHeight, UINT cPlanes, UINT cBitsPerPel, const void * lpvBits );

HBITMAP CreateCompatibleBitmap( HDC hDC, int cx, int cy );

HDC CreateCompatibleDC( HDC hDC );

HWND CreateDialogIndirect( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc );

HWND CreateDialogIndirectParam( HINSTANCE hInst, const DLGTEMPLATE * pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam );

HWND CreateDialog( HINSTANCE hInst, LPCTSTR pDlgID, HWND hWnd, DLGPROC bDlgProc );

HWND CreateDialogParam( HINSTANCE hInst, LPCTSTR pDlgID, HWND hWnd, DLGPROC bDlgProc, LPARAM lParam );

HANDLE CreateEvent( struct SECURITY_ATTRIBUTES * pEventAttributes, BOOL bManualReset, BOOL bInitialState, const TCHAR * pszpName );

HFONT CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace );

HFONT CreateFontIndirect( const LOGFONT * plf );

HPEN CreatePen( int fnPenStyle, int nWidth, COLORREF crColor );

HPEN CreatePenIndirect( const LOGPEN * plgpn );

HRGN CreateRectRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );

HBRUSH CreateSolidBrush( COLORREF c );

HWND CreateWindow( LPCTSTR pClassName, LPCTSTR pWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, LPVOID pParam );

HWND CreateWindowEx( DWORD dwExStyle, LPCTSTR pClassName, LPCTSTR pWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParentWnd, HMENU hMenu, HINSTANCE hInst, LPVOID pParam );

LRESULT DefDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

LRESULT DefWindowProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

BOOL DeleteDC( HDC hDC );

BOOL DeleteObject( HGDIOBJ hObj );

BOOL DestroyIcon( HICON hIcon );

BOOL DestroyMenu( HMENU hMenu );

BOOL DestroyWindow( HWND hWnd );

INT_PTR DialogBox( HINSTANCE hInst, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc );

INT_PTR DialogBoxIndirect( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc );

INT_PTR DialogBoxIndirectParam( HINSTANCE hInst, LPCDLGTEMPLATE pDlgHeader, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam );

INT_PTR DialogBoxParam( HINSTANCE hInst, LPCTSTR pDlgID, HWND hParentWnd, DLGPROC bDlgProc, LPARAM lParam );

LRESULT DispatchMessage( const MSG * pMsg );

BOOL DrawEdge( HDC hDC, LPRECT pr, UINT uiEdge, UINT uFlags );

BOOL DrawFocusRect( HDC hDC, const RECT * pr );

BOOL DrawIcon( HDC hDC, int x, int y, HICON hIcon );

BOOL DrawIconEx( HDC hDC, int x, int y, HICON hIcon, int cx, int cy, UINT uAniFrame, HBRUSH hBr, UINT uFlags );

BOOL DrawMenuBar( HWND hWnd );

int DrawText( HDC hDC, LPCTSTR pString, int nCount, LPRECT pr, UINT uFormat );

BOOL EnableMenuItem( HMENU hMenu, UINT uItem, UINT uEnable );

BOOL EnableScrollBar( HWND hWnd, UINT uiSBflags, UINT uiArrows );

BOOL EnumChildWindows( HWND hParentWnd, WNDENUMPROC lpEnumFunc, LPARAM lParam );

int EnumFonts( HDC hDC, LPCTSTR pszFaceName, FONTENUMPROC pFontFunc, LPARAM lParam );

BOOL EnumResourceNames( HMODULE hModule, LPCSTR lpType, ENUMRESNAMEPROC lpEnumFunc, LONG_PTR lParam );

BOOL EnumResourceTypes( HMODULE hModule, ENUMRESTYPEPROC lpEnumFunc, LONG_PTR lParam );

BOOL EnumWindows( WNDENUMPROC lpEnumFunc, LPARAM lParam );

BOOL EnableWindow( HWND hWnd, BOOL bEnable );

int EndDialog( HWND hDlg, int iCode );

BOOL EndPaint( HWND hWnd, const PAINTSTRUCT * pPaint );

int ExcludeClipRect( HDC hDC, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );

BOOL ExtTextOut( HDC hDC, int x, int y, UINT uFlags, const RECT * pr, LPCTSTR pszString, UINT nCount, const int * lpDx );

int FillRect( HDC hDC, const RECT * pr, HBRUSH hbr );

HRSRC FindResource( HMODULE hModule, LPCTSTR pName, LPCTSTR pType );

HANDLE FindFirstFile( const TCHAR * pszFileName, WIN32_FIND_DATA * pFindFileData );
BOOL FindNextFile( HANDLE hFindFile, WIN32_FIND_DATA * pFindFileData );
BOOL FindClose( HANDLE hFindFile );

HWND FindText( LPFINDREPLACE lpfr );

BOOL FreeResource( HGLOBAL h );

BOOL GdiGradientFill( HDC hDC, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nMesh, ULONG ulMode );

HWND GetActiveWindow( void );

COLORREF GetBkColor( HDC hDC );

int GetBkMode( HDC hDC );

BOOL GetClassInfo( HINSTANCE hInst, LPCTSTR lpClassName, WNDCLASS * pWndClass );

ULONG_PTR GetClassLongPtr( HWND hWnd, int iIndex );

int GetClassName( HWND hWnd, LPTSTR pClassName, int nMaxCount );

BOOL GetClientRect( HWND hWnd, LPRECT pr );

HGDIOBJ GetCurrentObject( HDC hDC, UINT uObjectType );

BOOL GetCurrentPositionEx( HDC hDC, LPPOINT lpPt );

HDC GetDC( HWND hWnd );

HDC GetDCEx( HWND hWnd, HRGN hRgn, DWORD flags );

HWND GetDesktopWindow( void );

LONG GetDialogBaseUnits( void );

int GetDlgCtrlID( HWND hWnd );

HWND GetDlgItem( HWND hWnd, int iCtrlID );

UINT GetDlgItemInt( HWND hWnd, int iCtrlID, BOOL * lpTranslated, BOOL bSigned );

UINT GetDlgItemText( HWND hWnd, int iCtrlID, LPTSTR lpString, int nMaxCount );

UINT GetDoubleClickTime( void );

HWND GetFocus( void );

DWORD GetLastError( void );

int GetMessage( MSG * pMsg, HWND hWnd, UINT ufirst, UINT ulast );

// Warning, only valid use is with NULL parameter
HMODULE GetModuleHandle( LPCTSTR pModuleName );

HWND GetNextDlgTabItem( HWND hDlg, HWND hCtlWnd, BOOL bPrevious );

int GetObject( HANDLE h, int c, LPVOID pv );

BOOL GetOpenFileName( LPOPENFILENAME lpofn );

HWND GetParent( HWND hWnd );

DWORD GetRegionData( HRGN hRgn, DWORD dwCount, RGNDATA * pRgnData );

BOOL GetScrollBarInfo( HWND hWnd, LONG lObjectID, PSCROLLBARINFO pSBI );

HGDIOBJ GetStockObject( int nIndex );

HMENU GetSubMenu( HMENU hMenu, int nIndex );

DWORD GetSysColor( int nIndex );

HBRUSH GetSysColorBrush( int nIndex );

int GetSystemMetrics( int nIndex );

COLORREF GetTextColor( HDC hDC );

BOOL GetTextExtentPoint32( HDC hDC, LPCTSTR pszString, int iLen, LPSIZE pSize );

BOOL GetTextMetrics( HDC hDC, TEXTMETRIC * pTM );

DWORD GetTickCount( void );

COLORREF GetPixel( HDC hDC, int x, int y );

BOOL GetWindowInfo( HWND hWnd, PWINDOWINFO pWI );

BOOL GetWindowRect( HWND hWnd, LPRECT pr );

int GetWindowText( HWND hWnd, TCHAR * pszDest, int iMaxLen );

int GetWindowTextLength( HWND hWnd );

LONG_PTR GetWindowLongPtr( HWND hWnd, int iIndex );

ATOM GlobalAddAtom( const TCHAR * pszString );

ATOM GlobalDeleteAtom( ATOM nAtom );

ATOM GlobalFindAtom( const TCHAR * pszString );

UINT GlobalGetAtomName( ATOM nAtom, TCHAR * pszDest, int iMaxLen );

BOOL IsDialogMessage( HWND hDlg, const MSG * pMsg );

// BOOL InSendMessage( void );

BOOL IsIconic( HWND hWnd );

BOOL IsWindow( HWND hWnd );

BOOL IsWindowEnabled( HWND hWnd );

BOOL IsWindowVisible( HWND hWnd );

BOOL InvalidateRect( HWND hWnd, const RECT * pr, BOOL bErase );

BOOL InvalidateRgn( HWND hWnd, HRGN hRgn, BOOL bErase );

BOOL InvertRect( HDC hDC, const RECT * pr );

BOOL KillTimer( HWND hWnd, UINT_PTR uIDEvent );

BOOL LineTo( HDC hDC, int x, int y );

HBITMAP LoadBitmap( HINSTANCE hInst, LPCTSTR ID );

HCURSOR LoadCursor( HINSTANCE hInst, LPCTSTR ID );

HICON LoadIcon( HINSTANCE hInst, LPCTSTR ID );

HMENU LoadMenu( HINSTANCE hInst, LPCTSTR ID );

//#if defined( __DARWIN__ )
//HGLOBAL YWLoadResource( HMODULE hInst, HRSRC hRsrc );
//#else
HGLOBAL LoadResource( HMODULE hInst, HRSRC hRsrc );
#define YWLoadResource LoadResource
//#endif

int LoadString( HINSTANCE hInst, UINT uID, LPTSTR pBuffer, int cchBufferMax );

LPVOID LockResource( HGLOBAL h );

BOOL MapDialogRect( HWND hDlg, LPRECT pr );

BOOL MaskBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop );

BOOL MessageBeep( UINT uType );

int MessageBox( HWND hWnd, LPCTSTR pszText, LPCTSTR pszTitle, UINT uType );

BOOL MoveToEx( HDC hDC, int x, int y, LPPOINT lpPt );

BOOL MoveWindow( HWND hWnd, int x, int y, int cx, int cy, BOOL bRepaint );

int MulDiv( int nNumber, int nNumerator, int nDenominator );

void OutputDebugString( LPCTSTR lpszString );

BOOL PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

void PostQuitMessage( int nExitCode );

BOOL PtInRect( const RECT * pr, POINT pt );

/**
RDW_ALLCHILDREN
RDW_ERASE
RDW_ERASENOW
RDW_FRAME
RDW_INTERNALPAINT
RDW_INVALIDATE
RDW_NOCHILDREN
RDW_NOERASE
RDW_NOFRAME
RDW_NOINTERNALPAINT
RDW_UPDATENOW
RDW_VALIDATE
 */
BOOL RedrawWindow( HWND hWnd, const RECT * pr, HRGN hRgn, UINT flags );

ATOM RegisterClass( const WNDCLASS * pWndClass );

int ReleaseDC( HWND hWnd, HDC hDC );

BOOL RemoveFontMemResourceEx( HANDLE fh );

BOOL ScreenToClient( HWND hWnd, LPPOINT lpPt );

HGDIOBJ SelectObject( HDC hDC, HGDIOBJ hObj );

LRESULT SendDlgItemMessage( HWND hDlg, int nIDDlgItem, UINT uiMsg, WPARAM wParam, LPARAM lParam );

LRESULT SendMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

COLORREF SetBkColor( HDC hDC, COLORREF c );

int SetBkMode( HDC hDC, int iMode );

ULONG_PTR SetClassLongPtr( HWND hWnd, int iIndex, LONG_PTR lVal );

BOOL SetDoubleClickTime( UINT uInterval );

BOOL SetDlgItemInt( HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned );

BOOL SetDlgItemText( HWND hDlg, int nIDDlgItem, LPCTSTR lpszString );

HWND SetFocus( HWND hWnd );

int SelectClipRegion( HDC hDC, HRGN hRgn );

BOOL SetMenu( HWND hWnd, HMENU hMenu );

COLORREF SetPixel( HDC hDC, int x, int y, COLORREF c );

BOOL SetSysColors( int cElements, const INT * lpaElements, const COLORREF * lpaRgbValues );

UINT SetTextAlign( HDC hDC, UINT fMode );

COLORREF SetTextColor( HDC hDC, COLORREF c );

UINT_PTR SetTimer( HWND hWnd, UINT_PTR uID, UINT uiTimerRefresh, TIMERPROC timerfunc );

LONG_PTR SetWindowLongPtr( HWND hWnd, int iIndex, LONG_PTR pData );

BOOL SetWindowText( HWND hWnd, LPCTSTR lpszString );

HRESULT SHGetKnownFolderPath( REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR * ppszPath );

BOOL ShowScrollBar( HWND hWnd, int wBar, BOOL bShow );

BOOL ShowWindow( HWND hWnd, int iShow );

DWORD SizeofResource( HMODULE hModule, HRSRC hResInfo );

BOOL StretchBlt( HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop );

BOOL TextOut( HDC hDC, int x, int y, LPCTSTR pString, int cchString );

BOOL TrackPopupMenuEx( HMENU hMenu, UINT uFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm );

BOOL TranslateMessage( const MSG * pMsg );

BOOL UpdateWindow( HWND hWnd );

BOOL UnregisterClass( LPCTSTR pClassName, HINSTANCE hInstance );

BOOL ValidateRect( HWND hWnd, const RECT * pr );

BOOL ValidateRgn( HWND hWnd, HRGN hRgn );

HWND WindowFromPoint( POINT pt );

void ZeroMemory( void * p,  unsigned long size );

extern int _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR pszCmdLine, int nCmdShow );
typedef int (* WINMAINPROC)( HINSTANCE, HINSTANCE, LPTSTR, int );


#ifdef __cplusplus
}   /* ! extern "C" */
#endif


#endif /* YOUWIN_INTERFACE_H */
