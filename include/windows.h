#ifndef YOUWIN_INTERFACE_H
#define YOUWIN_INTERFACE_H


#define YOU_WIN


#include "tchar.h"
#include "basetsd.h"

#include "gdi.h"
#include "winuser.h"


#define ANTIALIASED_QUALITY               4

#define BF_LEFT                           1
#define BF_TOP                            2
#define BF_RIGHT                          4
#define BF_BOTTOM                         8
#define BF_TOPLEFT                        (BF_TOP|BF_LEFT)
#define BF_TOPRIGHT                       (BF_TOP|BF_RIGHT)
#define BF_BOTTOMLEFT                     (BF_BOTTOM|BF_LEFT)
#define BF_BOTTOMRIGHT                    (BF_BOTTOM|BF_RIGHT)
#define BF_RECT                           (BF_LEFT|BF_TOP|BF_RIGHT|BF_BOTTOM)
#define BF_DIAGONAL                       16
#define BF_DIAGONAL_ENDTOPRIGHT           (BF_DIAGONAL|BF_TOP|BF_RIGHT)
#define BF_DIAGONAL_ENDTOPLEFT            (BF_DIAGONAL|BF_TOP|BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMLEFT         (BF_DIAGONAL|BF_BOTTOM|BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMRIGHT        (BF_DIAGONAL|BF_BOTTOM|BF_RIGHT)
#define BF_MIDDLE                         0x0800
#define BF_SOFT                           0x1000
#define BF_ADJUST                         0x2000
#define BF_FLAT                           0x4000
#define BF_MONO                           0x8000

#define BDR_INNER                         0x000C
#define BDR_OUTER                         0x0003
#define BDR_RAISED                        0x0005
#define BDR_RAISEDINNER                   0x0004
#define BDR_RAISEDOUTER                   0x0001
#define BDR_SUNKEN                        0x000A
#define BDR_SUNKENINNER                   0x0008
#define BDR_SUNKENOUTER                   0x0002

#define BLACK_BRUSH                       0x0004

#define BM_GETCHECK                       0x00F0
#define BM_GETIMAGE                       0x00F6
#define BM_SETCHECK                       0x00F1
#define BM_SETIMAGE                       0x00F7

#define BN_CLICKED                        0

#define BS_3STATE                         0x0005
#define BS_AUTO3STATE                     0x0006
#define BS_AUTOCHECKBOX                   0x0003
#define BS_BITMAP                         0x0080

#define BS_CENTER                         0x0300

#define BS_CHECKBOX                       0x0002
#define BS_DEFPUSHBUTTON                  0x0001
#define BS_FLAT                           0x8000
#define BS_GROUPBOX                       0x0007
#define BS_ICON                           0x0040

#define BS_LEFT                           0x0100
#define BS_MULTILINE                      0x2000
#define BS_OWNERDRAW                      0x000B
#define BS_PUSHBUTTON                     0x0000
#define BS_TEXT                           0x0000
#define BS_USERBUTTON                     0x0008
#define BS_VCENTER                        0x0c00

#define BST_CHECKED                       1
#define BST_INDETERMINATE                 2
#define BST_UNCHECKED                     0

#define CALLBACK

#define CB_ADDSTRING                      0x0143
#define CB_DELETESTRING                   0x0144
#define CB_ERR                            (-1)
#define CB_ERRSPACE                       (-2)
#define CB_GETCOUNT                       0x0146
#define CB_GETCURSEL                      0x0147
#define CB_GETITEMDATA                    0x0150
#define CB_GETITEMHEIGHT                  0x0154
#define CB_INSERTSTRING                   0x014A
#define CB_RESETCONTENT                   0x014B
#define CB_SETCURSEL                      0x014E
#define CB_SETITEMDATA                    0x0151

#define CBS_HASSTRINGS                    0x0200
#define CBS_SIMPLE                        0x0001

#define CCHILDREN_SCROLLBAR               5

#define CLIP_DEFAULT_PRECIS               0

#define CLR_INVALID                       0xFFFFFFFF

#define COLOR_3DDKSHADOW                  21
#define COLOR_3DFACE                      15
#define COLOR_3DHIGHLIGHT                 20
#define COLOR_3DHILIGHT                   20
#define COLOR_3DLIGHT                     22
#define COLOR_3DSHADOW                    16

#define COLOR_BTNHILIGHT                  20
#define COLOR_BTNHIGHLIGHT                20

#define COLOR_INACTIVECAPTIONTEXT         19

#define COLOR_INFOBK                      24
#define COLOR_INFOTEXT                    23
#define COLOR_HOTLIGHT                    26

#define COLOR_GRADIENTACTIVECAPTION       27
#define COLOR_GRADIENTINACTIVECAPTION     28

#define COLOR_ACTIVEBORDER                10
#define COLOR_ACTIVECAPTION               2
#define COLOR_APPWORKSPACE                12
#define COLOR_BACKGROUND                  1
#define COLOR_BTNFACE                     15
#define COLOR_BTNSHADOW                   16
#define COLOR_BTNTEXT                     18
#define COLOR_CAPTIONTEXT                 9
#define COLOR_DESKTOP                     1
#define COLOR_GRAYTEXT                    17
#define COLOR_HIGHLIGHT                   13
#define COLOR_HIGHLIGHTTEXT               14
#define COLOR_INACTIVEBORDER              11
#define COLOR_INACTIVECAPTION             3
#define COLOR_MENU                        4
#define COLOR_MENUTEXT                    7
#define COLOR_SCROLLBAR                   0
#define COLOR_WINDOW                      5
#define COLOR_WINDOWFRAME                 6
#define COLOR_WINDOWTEXT                  8

#define COMPLEXREGION                     3

#define CW_USEDEFAULT                     ((INT)0x80000000)

#define CS_BYTEALIGNCLIENT                0x00001000
#define CS_BYTEALIGNWINDOW                0x00002000
#define CS_CLASSDC                        0x00000040
#define CS_DBLCLKS                        0x00000008
#define CS_DROPSHADOW                     0x00020000
#define CS_GLOBALCLASS                    0x00004000
#define CS_HREDRAW                        0x00000002
#define CS_NOCLOSE                        0x00000200
#define CS_OWNDC                          0x00000020
#define CS_PARENTDC                       0x00000080
#define CS_SAVEBITS                       0x00000800
/* Special class style that indicates a class owned by the system, not the user, can not be passed in by the user */
#define CS_SYSTEM                         0x10000000
#define CS_VREDRAW                        0x00000001

#define CSIDL_PERSONAL                    5

#define CTLCOLOR_BTN                      3
#define CTLCOLOR_DLG                      4
#define CTLCOLOR_EDIT                     1
#define CTLCOLOR_LISTBOX                  2
#define CTLCOLOR_MAX                      7
#define CTLCOLOR_MSGBOX                   0
#define CTLCOLOR_SCROLLBAR                5
#define CTLCOLOR_STATIC                   6

#define DCX_WINDOW                        1
#define DCX_CACHE                         2
#define DCX_PARENTCLIP                    32
#define DCX_CLIPSIBLINGS                  16
#define DCX_CLIPCHILDREN                  8
#define DCX_NORESETATTRS                  4
#define DCX_INTERSECTUPDATE               0x200
#define DCX_LOCKWINDOWUPDATE              0x400
#define DCX_EXCLUDERGN                    64
#define DCX_INTERSECTRGN                  128
#define DCX_VALIDATE                      0x200000

/* This may be removed in future */
#define DECLSPEC_HIDDEN

#define DEFAULT_CHARSET                   1

#define DEFAULT_PITCH                     0

#define DI_NORMAL                         3

#define DLGWINDOWEXTRA                    30

#define DS_3DLOOK                         0x00000004
#define DS_CENTER                         0x00000800
#define DS_CONTROL                        0x00000400
#define DS_FIXEDSYS                       0x00000008
#define DS_LOCALEDIT                      0x00000020
#define DS_MODALFRAME                     0x00000080
#define DS_SETFONT                        0x00000040
#define DS_SETFOREGROUND                  0x00000200

#define DSTINVERT                         0x00550009

#define DT_TOP                            0x00000000
#define DT_LEFT                           0x00000000
#define DT_CENTER                         0x00000001
#define DT_RIGHT                          0x00000002
#define DT_VCENTER                        0x00000004
#define DT_BOTTOM                         0x00000008
#define DT_WORDBREAK                      0x00000010
#define DT_SINGLELINE                     0x00000020
#define DT_EXPANDTABS                     0x00000040
#define DT_TABSTOP                        0x00000080
#define DT_NOCLIP                         0x00000100
#define DT_EXTERNALLEADING                0x00000200
#define DT_CALCRECT                       0x00000400
#define DT_NOPREFIX                       0x00000800
#define DT_INTERNAL                       0x00001000
#define DT_EDITCONTROL                    0x00002000
#define DT_PATH_ELLIPSIS                  0x00004000
#define DT_END_ELLIPSIS                   0x00008000
#define DT_MODIFYSTRING                   0x00010000
#define DT_RTLREADING                     0x00020000
#define DT_WORD_ELLIPSIS                  0x00040000
#define DT_HIDEPREFIX                     0x00100000
#define DT_PREFIXONLY                     0x00200000

#define DT_ONE_LINE                       0x00800000  // Internal flag for edit/multi-line controls

#define DWL_DLGPROC                       4
#define DWL_MSGRESULT                     0
#define DWLP_MSGRESULT                    0
#define DWL_USER                          8

#define E_FAIL                            0x80004005
#define E_NOTIMPL                         0x80004001
#define E_POINTER                         0x80004003

#define EDGE_BUMP                         (BDR_RAISEDOUTER|BDR_SUNKENINNER)
#define EDGE_ETCHED                       (BDR_SUNKENOUTER|BDR_RAISEDINNER)
#define EDGE_RAISED                       (BDR_RAISEDOUTER|BDR_RAISEDINNER)
#define EDGE_SUNKEN                       (BDR_SUNKENOUTER|BDR_SUNKENINNER)

#define EM_GETHANDLE                      0x00BD
#define EM_GETMODIFY                      0x00B8
#define EM_GETSEL                         0x00B0
#define EM_LIMITTEXT                      0x00C5
#define EM_REPLACESEL                     0x00C2
#define EM_SETMODIFY                      0x00B9
#define EM_SETREADONLY                    0x00CF
#define EM_SETSEL                         0x00B1

#define EN_CHANGE                         768
#define EN_ERRSPACE                       1280
#define EN_HSCROLL                        1537
#define EN_KILLFOCUS                      512
#define EN_MAXTEXT                        1281
#define EN_SETFOCUS                       256
#define EN_UPDATE                         1024
#define EN_VSCROLL                        1538

#define ERROR                             0
#define ERROR_SUCCESS                     0

#define ES_AUTOHSCROLL                    128
#define ES_AUTOVSCROLL                    64
#define ES_LEFT                           0
#define ES_MULTILINE                      4
#define ES_NOHIDESEL                      256
#define ES_READONLY                       0x800
#define ES_WANTRETURN                     4096

#define ESB_DISABLE_BOTH                  3
#define ESB_DISABLE_DOWN                  2
#define ESB_DISABLE_LEFT                  1
#define ESB_DISABLE_LTUP                  1
#define ESB_DISABLE_RIGHT                 2
#define ESB_DISABLE_RTDN                  2
#define ESB_DISABLE_UP                    1
#define ESB_ENABLE_BOTH                   0

#define ETO_CLIPPED                       0x0004
#define ETO_GLYPH_INDEX                   0x0010

#define FAILED(Status)                    ((HRESULT)(Status)<0)

#ifndef FALSE
#define FALSE                             0
#endif

#define FINDMSGSTRING                     "commdlg_FindReplace"

#define FR_DOWN                           1
#define FR_FINDNEXT                       8
#define FR_MATCHCASE                      4


#define FW_BOLD                           700
#define FW_EXTRABOLD                      800
#define FW_NORMAL                         400


/**
 * Colour text cell backgrounds
 */
#define ETO_OPAQUE                        0x0002    // Colour text cell backgrounds

#define GCL_CBCLSEXTRA                    (-20)
#define GCL_CBWNDEXTRA                    (-18)
#define GCL_HICON                         (-14)
#define GCL_STYLE                         (-26)
#define GCLP_HBRBACKGROUND                (-10)
#define GCLP_HICON                        GCL_HICON
#define GCLP_WNDPROC                      (-24)

#define GDI_ERROR                         0xFFFFFFFF

#define GetRValue(c)                      ((BYTE)(c))
#define GetGValue(c)                      ((BYTE)(((WORD)(c))>>8))
#define GetBValue(c)                      ((BYTE)((c)>>16))
#define GetAValue(c)                      ((BYTE)((c)>>24))

#define GetTextExtentPoint                GetTextExtentPoint32

#define GRADIENT_FILL_RECT_H              0x00
#define GRADIENT_FILL_RECT_V              0x01

#define GWL_EXSTYLE                       (-20)
#define GWL_STYLE                         (-16)
#define GWL_USERDATA                      (-21)
#define GWL_WNDPROC                       (-4)
#define GWLP_HINSTANCE                    (-6)
#define GWLP_USERDATA                     (-21)

#define HGDI_ERROR                        ((HANDLE)GDI_ERROR)

#define HIBYTE(w)                         ((BYTE)(((WORD)(w)>>8)&0xFF))
#define HIWORD(l)                         ((WORD)((DWORD)(l) >> 16))

#define HOLLOW_BRUSH                      5

#define HTBORDER                          18
#define HTBOTTOM                          15
#define HTBOTTOMLEFT                      16
#define HTBOTTOMRIGHT                     17
#define HTCAPTION                         2
#define HTCLIENT                          1
#define HTCLOSE                           20
#define HTERROR                           -2
#define HTGROWBOX                         4
#define HTHELP                            21
#define HTHSCROLL                         6
#define HTLEFT                            10
#define HTMENU                            5
#define HTMAXBUTTON                       9
#define HTMINBUTTON                       8
#define HTNOWHERE                         0
#define HTREDUCE                          8
#define HTRIGHT                           11
#define HTSIZE                            4
#define HTSYSMENU                         3
#define HTTOP                             12
#define HTTOPLEFT                         13
#define HTTOPRIGHT                        14
#define HTTRANSPARENT                     -1
#define HTVSCROLL                         7
#define HTZOOM                            9

#define HWND_BROADCAST                    ((HWND)0xffff)

#define HWND_DESKTOP                      ((HWND)-1)

#define ID( i )                           ((const TCHAR *)(DWORD_PTR)i)

#define IDC_ARROW                         MAKEINTRESOURCE(32512)

#define IDABORT                           3
#define IDCANCEL                          2
#define IDCLOSE                           8
#define IDCONTINUE                        11
#define IDIGNORE                          5
#define IDNO                              7
#define IDOK                              1
#define IDRETRY                           4
#define IDTRYAGAIN                        10
#define IDYES                             6

#define IMAGE_ICON                        1

#define INFINITE                          0xFFFFFFFF

#define INVALID_ATOM                      ((ATOM)0)
#define INVALID_HANDLE_VALUE              (HANDLE)(-1)

#define LB_ADDSTRING                      0xF180
#define LB_DELETESTRING                   0x0182

#define LB_ERR                            (-1)
#define LB_ERRSPACE                       (-2)

#define LB_GETCOUNT                       0xF18B
#define LB_GETCURSEL                      0x0188
#define LB_GETITEMDATA                    0x0199
#define LB_GETITEMHEIGHT                  0x01A1
#define LB_GETTEXT                        0x0189
#define LB_GETTEXTLEN                     0x018A
#define LB_INSERTSTRING                   0x0181
#define LB_RESETCONTENT                   0x0184
#define LB_SETCURSEL                      0x0186
#define LB_SETITEMDATA                    0x019A

#define LBN_DBLCLK                        2
#define LBN_ERRSPACE                      (-2)
#define LBN_KILLFOCUS                     5
#define LBN_SELCANCEL                     3
#define LBN_SELCHANGE                     1
#define LBN_SETFOCUS                      4

#define LBS_DISABLENOSCROLL               0x001000
#define LBS_EXTENDEDSEL                   0x000800
#define LBS_HASSTRINGS                    0x000040
#define LBS_MULTICOLUMN                   0x000200
#define LBS_MULTIPLESEL                   0x000008
#define LBS_NODATA                        0x002000
#define LBS_NOINTEGRALHEIGHT              0x000100
#define LBS_NOREDRAW                      0x000004
#define LBS_NOSEL                         0x004000
#define LBS_NOTIFY                        0x000001
#define LBS_OWNERDRAWFIXED                0x000010
#define LBS_OWNERDRAWVARIABLE             0x000020
#define LBS_SORT                          0x000002
#define LBS_STANDARD                      0xA00003
#define LBS_USETABSTOPS                   0x000080
#define LBS_WANTKEYBOARDINPUT             0x000400

#define LF_FACESIZE                       32

#define LOBYTE(w)                         ((BYTE)(w))

#define LOWORD(l)                         ((WORD)((DWORD_PTR)(l) & 0xFFFF))

#define MAKEINTRESOURCE(i)                ((const TCHAR *)(DWORD_PTR)i)
#define MAKELONG(l,h)                     ((LONG)(((WORD)(l)) | (((DWORD)((WORD)(h))) << 16)))
#define MAKELPARAM(low,high)              ((LPARAM)(DWORD)MAKELONG(low,high))
#define MAKEWORD(a,b)                     ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
#define MAKEWPARAM(l,h)                   ((WPARAM)MAKELONG(l,h))

#define MAX_PATH                          260

#define MAXINTATOM                        0xC000

#define MB_APPLMODAL                      0

#define MB_BEEP                           0xFFFFFFFFL

#define MB_DEFBUTTON1                     0x00000000L
#define MB_DEFBUTTON2                     0x00000100L
#define MB_DEFBUTTON3                     0x00000200L
#define MB_DEFBUTTON4                     0x00000300L

#define MB_ICONASTERISK                   0x00000040L
#define MB_CANCELTRYCONTINUE              0x00000006L
#define MB_ICONERROR                      0x00000010L
#define MB_ICONEXCLAMATION                0x00000030L
#define MB_ICONHAND                       0x00000010L
#define MB_ICONINFORMATION                0x00000040L
#define MB_ICONQUESTION                   0x00000020L
#define MB_ICONSTOP                       0x00000010L
#define MB_ICONWARNING                    0x00000030L
#define MB_OK                             0x00000000L
#define MB_OKCANCEL                       0x00000001L
#define MB_RETRYCANCEL                    0x00000005L
#define MB_SETFOREGROUND                  0x00010000L
#define MB_SYSTEMMODAL                    0x00001000L
#define MB_YESNO                          0x00000004L
#define MB_YESNOCANCEL                    0x00000003L

#define MF_BYCOMMAND                      0
#define MF_CHECKED                        8
#define MF_ENABLED                        0
#define MF_GRAYED                         1
#define MF_UNCHECKED                      0

#define MK_CONTROL                        0x0008
#define MK_LBUTTON                        0x0001
#define MK_MBUTTON                        0x0010
#define MK_RBUTTON                        0x0002
#define MK_SHIFT                          0x0004
#define MK_XBUTTON1                       0x0020
#define MK_XBUTTON2                       0x0040

#ifndef NULL
#define NULL                              0
#endif

#define NULLREGION                        1

#define OBJ_FONT                          6

#define ODA_DRAWENTIRE                    1
#define ODA_FOCUS                         4
#define ODA_SELECT                        2

#define ODS_FOCUS                         16
#define ODS_SELECTED                      1

#define ODT_BUTTON                        0x0004
#define ODT_COMBOBOX                      0x0003
#define ODT_LISTBOX                       0x0002

#define OFN_CREATEPROMPT                  0x00002000
#define OFN_ENABLETEMPLATE                0x00000040
#define OFN_FILEMUSTEXIST                 0x00001000
#define OFN_FORCESHOWHIDDEN               0x10000000
#define OFN_HIDEREADONLY                  0x00000004
#define OFN_OVERWRITEPROMPT               0x00000002
#define OFN_PATHMUSTEXIST                 0x00000800

#define OPAQUE                            0x0002

#define OUT_DEFAULT_PRECIS                0

#define PASCAL

#define PBT_APMPOWERSTATUSCHANGE          0x000A
#define PBT_APMRESUMEAUTOMATIC            0x0012
#define PBT_APMRESUMESUSPEND              0x0007
#define PBT_APMSUSPEND                    0x0004
#define PBT_POWERSETTINGCHANGE            0x8013
#define PBT_APMBATTERYLOW                 0x0009
#define PBT_APMOEMEVENT                   0x000B
#define PBT_APMQUERYSUSPEND               0x0000
#define PBT_APMQUERYSUSPENDFAILED         0x0002
#define PBT_APMRESUMECRITICAL             0x0006

#define PROOF_QUALITY                     2

#define PS_SOLID                          0

#define RASTER_FONTTYPE                   0x0001

#define RDH_RECTANGLES                    0x0001

#define RDW_ALLCHILDREN                   0x0080
#define RDW_ERASE                         0x0004
#define RDW_ERASENOW                      0x0200
#define RDW_FRAME                         0x0400
#define RDW_INTERNALPAINT                 0x0002
#define RDW_INVALIDATE                    0x0001
#define RDW_NOCHILDREN                    0x0040
#define RDW_NOERASE                       0x0020
#define RDW_NOFRAME                       0x0800
#define RDW_NOINTERNALPAINT               0x0010
#define RDW_UPDATENOW                     0x0100
#define RDW_VALIDATE                      0x0008

#define REFERENCE                         *

#define RT_CURSOR_VAL                     1
#define RT_CURSOR                         MAKEINTRESOURCE(RT_CURSOR_VAL)

#define RT_BITMAP_VAL                     2
#define RT_BITMAP                         MAKEINTRESOURCE(RT_BITMAP_VAL)

#define RT_ICON_VAL                       3
#define RT_ICON                           MAKEINTRESOURCE(RT_ICON_VAL)

#define RT_MENU_VAL                       4
#define RT_MENU                           MAKEINTRESOURCE(RT_MENU_VAL)

#define RT_DIALOG_VAL                     5
#define RT_DIALOG                         MAKEINTRESOURCE(RT_DIALOG_VAL)

#define RT_STRING_VAL                     6
#define RT_STRING                         MAKEINTRESOURCE(RT_STRING_VAL)

#define RT_FONTDIR                        MAKEINTRESOURCE(7)

#define RT_FONT_VAL                       8
#define RT_FONT                           MAKEINTRESOURCE(8)

#define RT_ACCELERATOR                    MAKEINTRESOURCE(9)

#define RT_RCDATA                         MAKEINTRESOURCE(10)

#define RT_MESSAGETABLE                   MAKEINTRESOURCE(11)

#define RT_GROUP_DIFFERENCE               11
#define RT_GROUP_CURSOR                   MAKEINTRESOURCE((DWORD)RT_CURSOR+RT_GROUP_DIFFERENCE)
#define RT_GROUP_ICON_VAL                 14
#define RT_GROUP_ICON                     MAKEINTRESOURCE((DWORD)RT_ICON+RT_GROUP_DIFFERENCE)

#define RT_VERSION_VAL                    16
#define RT_VERSION                        MAKEINTRESOURCE(RT_VERSION_VAL)
#define RT_DLGINCLUDE                     MAKEINTRESOURCE(17)
#define RT_PLUGPLAY                       MAKEINTRESOURCE(19)
#define RT_VXD                            MAKEINTRESOURCE(20)
#define RT_ANICURSOR                      MAKEINTRESOURCE(21)
#define RT_ANIICON                        MAKEINTRESOURCE(22)
#define RT_HTML                           MAKEINTRESOURCE(23)

// #define RT_REGION_VAL                     25

#define S_OK                              ((HRESULT)0L)

#define SB_HORZ                           0
#define SB_VERT                           1
#define SB_CTL                            2
#define SB_BOTH                           3

#define SB_LINEUP                         0
#define SB_LINEDOWN                       1
#define SB_LINELEFT                       0
#define SB_LINERIGHT                      1
#define SB_PAGEUP                         2
#define SB_PAGEDOWN                       3
#define SB_PAGELEFT                       2
#define SB_PAGERIGHT                      3
#define SB_THUMBPOSITION                  4
#define SB_THUMBTRACK                     5
#define SB_ENDSCROLL                      8
#define SB_LEFT                           6
#define SB_RIGHT                          7
#define SB_BOTTOM                         7
#define SB_TOP                            6

#define SIF_ALL                           (SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS)
#define SIF_DISABLENOSCROLL               0x0008
#define SIF_PAGE                          0x0002
#define SIF_POS                           0x0004
#define SIF_RANGE                         0x0001
#define SIF_TRACKPOS                      0x0010

#define SIMPLEREGION                      2

#define SIZE_MAXHIDE                      4
#define SIZE_MAXIMIZED                    2
#define SIZE_MAXSHOW                      3
#define SIZE_MINIMIZED                    1
#define SIZE_RESTORED                     0

#define SM_CXBORDER                       5
#define SM_CXDLGFRAME                     7
#define SM_CXDOUBLECLK                    36
#define SM_CXEDGE                         45
#define SM_CXFIXEDFRAME                   7
#define SM_CXFRAME                        32
#define SM_CXHSCROLL                      21
#define SM_CXHTHUMB                       10
#define SM_CXICON                         11
#define SM_CXSCREEN                       0
#define SM_CXSIZEFRAME                    32
#define SM_CXSMICON                       49
#define SM_CXVSCROLL                      2
#define SM_CYBORDER                       6
#define SM_CYCAPTION                      4
#define SM_CYDLGFRAME                     8
#define SM_CYDOUBLECLK                    37
#define SM_CYEDGE                         46
#define SM_CYFIXEDFRAME                   8
#define SM_CYFRAME                        33
#define SM_CYHSCROLL                      3
#define SM_CYICON                         12
#define SM_CYMENU                         15
#define SM_CYMENUSIZE                     55
#define SM_CYSCREEN                       1
#define SM_CYSIZEFRAME                    33
#define SM_CYSMICON                       50
#define SM_CYVSCROLL                      20
#define SM_CYVTHUMB                       9

#define SRCCOPY                           0x00CC0020

#define SS_BITMAP                         14
#define SS_BLACKFRAME                     7
#define SS_BLACKRECT                      4
#define SS_CENTER                         1
#define SS_CENTERIMAGE                    512
#define SS_GRAYFRAME                      8
#define SS_GRAYRECT                       5
#define SS_ICON                           3
#define SS_LEFT                           0
#define SS_NOPREFIX                       128
#define SS_NOTIFY                         256
#define SS_RIGHT                          2
#define SS_WHITEFRAME                     9
#define SS_WHITERECT                      6

#define STM_GETICON                       0x0171
#define STM_SETICON                       0x0170

#define SUCCEEDED(hr)                     (((HRESULT) (hr)) >= 0)

#define SW_HIDE                           0
#define SW_MAXIMIZE                       3
#define SW_RESTORE                        9
#define SW_SHOW                           5

#define SYSTEM_FONT                       13

#define TA_BASELINE                       24
#define TA_BOTTOM                         8
#define TA_CENTER                         6
#define TA_LEFT                           0
#define TA_NOUPDATECP                     0
#define TA_RIGHT                          2
#define TA_RTLREADING                     256
#define TA_TOP                            0
#define TA_UPDATECP                       1

#ifdef UNICODE
#ifndef TEXT
#define TEXT(string)                      L##string
#endif
#else
#ifndef TEXT
#define TEXT(string)                      string
#endif
#endif
#define _T(x)                             TEXT(x)

#define TPM_LEFTALIGN                     0x0000
#define TPM_NONOTIFY                      0x0080
#define TPM_RETURNCMD                     0x0100
#define TPM_TOPALIGN                      0x0000

#define TRANSPARENT                       0x0001

#ifndef TRUE
#define TRUE                              1
#endif

#ifndef _TRUNCATE
#define _TRUNCATE                         ((size_t)-1)
#endif

#define UnlockResource( h )

#define USER_TIMER_MINIMUM                0x0000000A

#define VFT_APP                           1
#define VFT2_DRV_NETWORK                  6


#ifndef VOID
#define VOID void
#endif

#define VOS__WINDOWS16                    1
#define VOS__WINDOWS32                    4

#define VS_FF_DEBUG                       1
#define VS_FF_INFOINFERRED                16
#define VS_FF_PRERELEASE                  2
#define VS_FF_PRIVATEBUILD                8
#define VS_FF_SPECIALBUILD                32

#define WAIT_FAILED                       (DWORD)0xFFFFFFFF
#define WAIT_TIMEOUT                      0x00000102L
#define WAIT_OBJECT_0                     0x00000000L

#define WINAPI

#define WM_APP                            0x8000

#define WM_CHAR                           0x0102

#define WM_CHARTOITEM                     0x002F

#define WM_COMMAND                        0x0111

#define WM_COMPAREITEM                    0x0039

#define WM_CLEAR                          0x0303

#define WM_CLOSE                          0x0010

#define WM_CONTEXTMENU                    0x007B

#define WM_COPYDATA                       0x004A
#define WM_CREATE                         0x0001

#define WM_CTLCOLORBTN                    0x0135
#define WM_CTLCOLORDLG                    0x0136
#define WM_CTLCOLOREDIT                   0x0133
#define WM_CTLCOLORLISTBOX                0x0134
#define WM_CTLCOLORMSGBOX                 0x0132
#define WM_CTLCOLORSCROLLBAR              0x0137
#define WM_CTLCOLORSTATIC                 0x0138

#define WM_DELETEITEM                     0x002D
#define WM_DESTROY                        0x0002

#define WM_DEVICECHANGE                   0x0219

#define WM_DISPLAYCHANGE                  0x007E

#define WM_DRAWITEM                       0x002B

#define WM_ENABLE                         0x000A

#define WM_ERASEBKGND                     0x0014

#define WM_GETFONT                        0x0031

#define WM_GETICON                        0x007F

#define WM_HSCROLL                        0x0114

#define WM_INITDIALOG                     0x0110

#define WM_INITMENUPOPUP                  0x0117

#define WM_KEYDOWN                        0x0100
#define WM_KEYUP                          0x0101

#define WM_KILLFOCUS                      0x0008

#define WM_LBUTTONDBLCLK                  0x0203
#define WM_LBUTTONDOWN                    0x0201
#define WM_LBUTTONUP                      0x0202

#define WM_MBUTTONDBLCLK                  0x0209
#define WM_MBUTTONDOWN                    0x0207
#define WM_MBUTTONUP                      0x0208

#define WM_MOUSEMOVE                      0x0200

#define WM_MOVE                           0x0003

#define WM_NCCREATE                       0x0081

#define WM_NCHITTEST                      0x0084

#define WM_NCLBUTTONDBLCLK                0x00A3
#define WM_NCLBUTTONDOWN                  0x00A1
#define WM_NCLBUTTONUP                    0x00A2

#define WM_NCMBUTTONDBLCLK                0x00A9
#define WM_NCMBUTTONDOWN                  0x00A7
#define WM_NCMBUTTONUP                    0x00A8

#define WM_NCMOUSEMOVE                    0x00A0

#define WM_NCPAINT                        0x0085

#define WM_NCRBUTTONDBLCLK                0x00A6
#define WM_NCRBUTTONDOWN                  0x00A4
#define WM_NCRBUTTONUP                    0x00A5

#define WM_NCXBUTTONDOWN                  0x00AB
#define WM_NCXBUTTONDBLCLK                0x00AD
#define WM_NCXBUTTONUP                    0x00AC

#define WM_NOTIFY                         0x004E

#define WM_NULL                           0x0000

#define WM_PAINT                          0x000F

#define WM_PARENTNOTIFY                   0x0210

#define WM_POWERBROADCAST                 0x0218

#define WM_QUERYDRAGICON                  0x0037

#define WM_QUIT                           0x0012

#define WM_RBUTTONDBLCLK                  0x0206
#define WM_RBUTTONDOWN                    0x0204
#define WM_RBUTTONUP                      0x0205

#define WM_SETFOCUS                       0x0007

#define WM_SETREDRAW                      0x000B

#define WM_SETTEXT                        0x000C

#define WM_SETTINGCHANGE                  WM_WININICHANGE

#define WM_SIZE                           0x0005

#define WM_SYSKEYDOWN                     0x0104
#define WM_SYSKEYUP                       0x0105

#define WM_SYSTEMERROR                    0x0017

#define WM_TIMER                          0x0113

#define WM_USER                           0x0400

#define WM_VKEYTOITEM                     0x002E

#define WM_VSCROLL                        0x0115

#define WM_XBUTTONDBLCLK                  0x020D
#define WM_XBUTTONDOWN                    0x020B
#define WM_XBUTTONUP                      0x020C

#define WM_WININICHANGE                   0x001A

#define WS_BORDER                         0x00800000
#define WS_CAPTION                        0x00C00000
#define WS_CHILD                          0x40000000
#define WS_CLIPCHILDREN                   0x02000000
#define WS_CLIPSIBLINGS                   0x04000000
#define WS_DISABLED                       0x08000000
#define WS_DLGFRAME                       0x00400000

#define WS_EX_CLIENTEDGE                  0x00000200
#define WS_EX_STATICEDGE                  0x00020000
#define WS_EX_TOPMOST                     0x00000008
#define WS_EX_TRANSPARENT                 0x00000020

#define WS_GROUP                          0x00020000
#define WS_MAXIMIZEBOX                    0x00010000
#define WS_MINIMIZE                       0x20000000
#define WS_MINIMIZEBOX                    0x00020000
#define WS_OVERLAPPED                     0x00000000
#define WS_POPUP                          0x80000000
#define WS_SYSMENU                        0x00080000
#define WS_TABSTOP                        0x00010000
#define WS_THICKFRAME                     0x00040000
#define WS_VISIBLE                        0x10000000
#define WS_HSCROLL                        0x00100000
#define WS_VSCROLL                        0x00200000


#define GetWindowLong(hwnd, nIndex ) ((LONG)GetWindowLongPtr(hwnd,nIndex))

#define SetWindowLong(hwnd, nIndex, l ) ((LONG)SetWindowLongPtr(hwnd,nIndex,(LONG_PTR)(l)))


#define LocalLock( h )   ( (PVOID)h )
#define LocalHandle( p ) ( (HANDLE)p )
#define LocalUnlock( h ) ( 0 != h )

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
