#ifndef YOUWIN_WINDEF_H
#define YOUWIN_WINDEF_H


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

//#define IDI_APPLICATION                   32512
#define IDI_HAND                          32513
#define IDI_QUESTION                      32514
#define IDI_EXCLAMATION                   32515
#define IDI_ASTERISK                      32516
//#define IDI_WINLOGO                       32517
//#define IDI_SHIELD                        32518

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


#endif /* YOUWIN_WINDEF_H */
