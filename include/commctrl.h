#ifndef YW_COMMCTRL_H
#define YW_COMMCTRL_H


#include <windows.h>
#include <tchar.h>


#define HANDLE_WM_NOTIFY(h,w,l,f) (f)((h),(int)(w),(NMHDR*)(l))
#define FORWARD_WM_NOTIFY(h,i,p,f) (LRESULT)(f)((h),WM_NOTIFY,(WPARAM)(int)(i),(LPARAM)(NMHDR*)(p))


#define ICC_ANIMATE_CLASS       0x00000080
#define ICC_BAR_CLASSES         0x00000004
#define ICC_COOL_CLASSES        0x00000400
#define ICC_HOTKEY_CLASS        0x00000040
#define ICC_LISTVIEW_CLASSES    0x00000001
#define ICC_PAGESCROLLER_CLASS  0x00001000
#define ICC_PROGRESS_CLASS      0x00000020
#define ICC_TAB_CLASSES         0x00000008
#define ICC_TREEVIEW_CLASSES    0x00000002
#define ICC_USEREX_CLASSES      0x00000200

#define ILC_MASK                1

#define TCM_FIRST               0x1300
#define TCM_INSERTITEM          (TCM_FIRST+7)

#define ANIMATE_CLASS           TEXT( "SysAnimate32" )
#define WC_BUTTON               TEXT( "Button" )
#define WC_STATIC               TEXT( "Static" )
#define WC_EDIT                 TEXT( "Edit" )
#define WC_LISTBOX              TEXT( "ListBox" )
#define WC_LISTVIEW             TEXT( "SysListView32" )
#define WC_COMBOBOX             TEXT( "ComboBox" )
#define WC_SCROLLBAR            TEXT( "ScrollBar" )
#define WC_TABCONTROL           TEXT( "SysTabControl32" )
#define WC_TREEVIEW             TEXT( "SysTreeView32" )


#define LVIF_TEXT               0x0001
#define LVIF_IMAGE              0x0002
#define LVIF_PARAM              0x0004
#define LVIF_STATE              0x0008
#define LVIF_INDENT             0x0010
#define LVIF_GROUPID            0x0100
#define LVIF_COLUMNS            0x0200
#define LVIF_NORECOMPUTE        0x0800
#define LVIF_DI_SETITEM         0x1000
#define LVIF_COLFMT             0x00010000

#define LVIS_FOCUSED            0x0001
#define LVIS_SELECTED           0x0002
#define LVIS_CUT                0x0004
#define LVIS_DROPHILITED        0x0008
#define LVIS_ACTIVATING         0x0020
#define LVIS_OVERLAYMASK        0x0F00
#define LVIS_STATEIMAGEMASK     0xF000

#define LVSIL_NORMAL            0
#define LVSIL_SMALL             1

#define LVM_FIRST               0x1000
#define LVM_ENSUREVISIBLE       (LVM_FIRST+19)
#define LVM_GETITEM             (LVM_FIRST+5)
#define LVM_GETITEMCOUNT        (LVM_FIRST+4)
#define LVM_GETNEXTITEM         (LVM_FIRST+12)
#define LVM_INSERTITEM          (LVM_FIRST+7)
#define LVM_SETIMAGELIST        (LVM_FIRST+3)
#define LVM_SETITEMSTATE        (LVM_FIRST+43)

#define LVNI_SELECTED           2

#define LVS_ICON                0
#define LVS_REPORT              1
#define LVS_SMALLICON           2
#define LVS_LIST                3
#define LVS_TYPEMASK            3
#define LVS_SINGLESEL           4
#define LVS_SHOWSELALWAYS       8
#define LVS_SORTASCENDING       16
#define LVS_SORTDESCENDING      32
#define LVS_SHAREIMAGELISTS     64
#define LVS_NOLABELWRAP         128
#define LVS_AUTOARRANGE         256
#define LVS_EDITLABELS          512
#define LVS_NOSCROLL            0x2000
#define LVS_TYPESTYLEMASK       0xFC00
#define LVS_ALIGNTOP            0
#define LVS_ALIGNLEFT           0x800
#define LVS_ALIGNMASK           0xC00
#define LVS_OWNERDRAWFIXED      0x400
#define LVS_NOCOLUMNHEADER      0x4000
#define LVS_NOSORTHEADER        0x8000
#define LVS_OWNERDATA           4096
#define LVS_EX_CHECKBOXES       4
#define LVS_EX_FULLROWSELECT    32
#define LVS_EX_GRIDLINES        1
#define LVS_EX_HEADERDRAGDROP   16
#define LVS_EX_ONECLICKACTIVATE 64
#define LVS_EX_SUBITEMIMAGES    2
#define LVS_EX_TRACKSELECT      8
#define LVS_EX_TWOCLICKACTIVATE 128
#define LVS_EX_FLATSB           0x00000100
#define LVS_EX_REGIONAL         0x00000200
#define LVS_EX_INFOTIP          0x00000400
#define LVS_EX_UNDERLINEHOT     0x00000800
#define LVS_EX_UNDERLINECOLD    0x00001000
#define LVS_EX_MULTIWORKAREAS   0x00002000
#define LVS_EX_LABELTIP         0x00004000
#define LVS_EX_BORDERSELECT     0x00008000


#define NM_DBLCLK               (NM_FIRST-3)
#define NM_FIRST                0


#define PROGRESS_CLASS          TEXT( "msctls_progress32" )

#define PBM_SETPOS              (WM_USER+2)
#define PBM_SETRANGE32          1030
#define PBM_SETSTEP             (WM_USER+4)
#define PBM_STEPIT              (WM_USER+5)

#define PBS_VERTICAL            0x04
#define PBS_MARQUEE             0x08

#define TB_LINEUP               0
#define TB_LINEDOWN             1
#define TB_PAGEUP               2
#define TB_PAGEDOWN             3
#define TB_THUMBPOSITION        4
#define TB_THUMBTRACK           5
#define TB_TOP                  6
#define TB_BOTTOM               7
#define TB_ENDTRACK             8

#define TBM_GETPOS              (WM_USER)
#define TBM_GETRANGEMIN         (WM_USER+1)
#define TBM_GETRANGEMAX         (WM_USER+2)
#define TBM_GETTIC              (WM_USER+3)
#define TBM_SETTIC              (WM_USER+4)
#define TBM_SETPOS              (WM_USER+5)
#define TBM_SETRANGE            (WM_USER+6)
#define TBM_SETRANGEMIN         (WM_USER+7)
#define TBM_SETRANGEMAX         (WM_USER+8)
#define TBM_CLEARTICS           (WM_USER+9)
#define TBM_SETSEL              (WM_USER+10)
#define TBM_SETSELSTART         (WM_USER+11)
#define TBM_SETSELEND           (WM_USER+12)
#define TBM_GETPTICS            (WM_USER+14)
#define TBM_GETTICPOS           (WM_USER+15)
#define TBM_GETNUMTICS          (WM_USER+16)
#define TBM_GETSELSTART         (WM_USER+17)
#define TBM_GETSELEND           (WM_USER+18)
#define TBM_CLEARSEL            (WM_USER+19)
#define TBM_SETTICFREQ          (WM_USER+20)
#define TBM_SETPAGESIZE         (WM_USER+21)
#define TBM_GETPAGESIZE         (WM_USER+22)
#define TBM_SETLINESIZE         (WM_USER+23)
#define TBM_GETLINESIZE         (WM_USER+24)
#define TBM_GETTHUMBRECT        (WM_USER+25)
#define TBM_GETCHANNELRECT      (WM_USER+26)
#define TBM_SETTHUMBLENGTH      (WM_USER+27)
#define TBM_GETTHUMBLENGTH      (WM_USER+28)
#define TBM_SETTOOLTIPS         (WM_USER+29)
#define TBM_GETTOOLTIPS         (WM_USER+30)
#define TBM_SETTIPSIDE          (WM_USER+31)
#define TBM_SETBUDDY            (WM_USER+32)
#define TBM_GETBUDDY            (WM_USER+33)

#define TCIF_TEXT               1
#define TCIF_IMAGE              2


#define TRACKBAR_CLASS          TEXT( "msctls_trackbar32" )


typedef struct tagINITCOMMONCONTROLSEX {

    DWORD dwSize;
    DWORD dwICC;

} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;


typedef struct {
  UINT   mask;
  int    iItem;
  int    iSubItem;
  UINT   state;
  UINT   stateMask;
  LPTSTR pszText;
  int    cchTextMax;
  int    iImage;
  LPARAM lParam;
#if defined(_WIN32_IE) && (_WIN32_IE >= 0x0300)
  int    iIndent;
#endif 
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0501)
  int    iGroupId;
  UINT   cColumns;
  UINT   puColumns;
#endif 
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
  int    piColFmt;
  int    iGroup;
#endif 
} LVITEM, *LPLVITEM;

#define ListView_EnsureVisible(hwnd,i,fPartialOk) (BOOL)SendMessage((hwnd),LVM_ENSUREVISIBLE,(WPARAM)(INT)i,(LPARAM)(BOOL)fPartialOk)

#define ListView_InsertItem(hwnd,pitem) (int)SendMessage((hwnd),LVM_INSERTITEM,0,(LPARAM)(const LVITEM *)(pitem))
#define ListView_GetItem(w,i) (BOOL)SendMessage((w),LVM_GETITEM,0,(LPARAM)(i))

#define ListView_GetItemCount(hwnd) (INT)SendMessage((hwnd), LVM_GETITEMCOUNT, 0, 0)
#define ListView_SetImageList(w,h,i) (HIMAGELIST)SendMessage((w),LVM_SETIMAGELIST,(i),(LPARAM)(h))

#define ListView_SetItemState(hwnd,i,data,dataMask) { LVITEM _LVi; _LVi.state = data; _LVi.stateMask = dataMask; SendMessage(hwnd, LVM_SETITEMSTATE, (WPARAM)(UINT)i, (LPARAM) (LPLVITEM)&_LVi);}
#define ListView_GetNextItem(hwnd,i,f) (int)SendMessage((hwnd),LVM_GETNEXTITEM,i,MAKELPARAM((f),0))


typedef struct tagTCITEM {

    UINT   mask;
#if defined(_WIN32_IE) && (_WIN32_IE >= 0x0300)
    DWORD  dwState;
    DWORD  dwStateMask;
#else
    UINT   lpReserved1;
    UINT   lpReserved2;
#endif
    LPTSTR pszText;
    int    cchTextMax;
    int    iImage;
    LPARAM lParam;

} TCITEM, *LPTCITEM;


#define TabCtrl_InsertItem(w,i,p) (int)SendMessage((w),TCM_INSERTITEM,i,(LPARAM)(const TCITEM*)(p))


#define ImageList_AddIcon(l,i) ImageList_ReplaceIcon(l,-1,i)


#ifdef __cplusplus
extern "C" {
#endif


int ImageList_ReplaceIcon( HIMAGELIST, int, HICON );

HIMAGELIST ImageList_Create( int, int, UINT, int, int );

BOOL ImageList_Destroy( HIMAGELIST );

BOOL InitCommonControlsEx( const LPINITCOMMONCONTROLSEX );


#ifdef __cplusplus
}   /* ! extern "C" */
#endif


#endif /* YW_COMMCTRL_H */
