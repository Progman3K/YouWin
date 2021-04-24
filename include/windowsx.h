#ifndef YOUWIN_WINDOWSX_H
#define YOUWIN_WINDOWSX_H


#define HANDLE_WM_CHAR(hwnd, wParam, lParam, fn)   ((fn)((hwnd), (UINT)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define FORWARD_WM_CHAR(hwnd, ch, cRepeat, fn)     (void)(fn)((hwnd), WM_CHAR, (WPARAM)(UINT)(ch), MAKELPARAM((cRepeat),0))

#define HANDLE_WM_CHARTOITEM(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(int)(fn)((hwnd),(UINT)LOWORD(wParam),(HWND)(lParam),(int)(short)HIWORD(wParam))
#define FORWARD_WM_CHARTOITEM(hwnd,ch,hwndListBox,iCaret,fn) (int)(DWORD)(fn)((hwnd),WM_CHARTOITEM,MAKEWPARAM((UINT)(iCaret),(UINT)(ch)),(LPARAM)(hwndListBox))

#define HANDLE_WM_COMMAND(hwnd, wParam, lParam, fn) ((fn)((hwnd), (int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L)
#define FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn) (void)(fn)((hwnd), WM_COMMAND, MAKEWPARAM((UINT)(id),(UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl))

#define HANDLE_WM_COMPAREITEM(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(int)(fn)((hwnd),(const COMPAREITEMSTRUCT*)(lParam))
#define FORWARD_WM_COMPAREITEM(hwnd,lpCompareItem,fn) (int)(DWORD)(fn)((hwnd),WM_COMPAREITEM,(WPARAM)(((const COMPAREITEMSTRUCT*)(lpCompareItem))->CtlID),(LPARAM)(const COMPAREITEMSTRUCT*)(lpCompareItem))

#define FORWARD_WM_CLEAR(hwnd,fn) (void)(fn)((hwnd),WM_CLEAR,0,0)
#define HANDLE_WM_CLEAR(hwnd,wParam,lParam,fn) ((fn)(hwnd),0)

#define HANDLE_WM_CLOSE(hwnd,wParam,lParam,fn) ((fn)(hwnd),0)
#define FORWARD_WM_CLOSE(hwnd,fn) (void)(fn)((hwnd),WM_CLOSE,0,0)

#define HANDLE_WM_CONTEXTMENU(hwnd,wParam,lParam,fn) (fn)((hwnd),(HWND)(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam))
#define FORWARD_WM_CONTEXTMENU(hwnd, hwndContext, xPos, yPos, fn) (fn)((hwnd), WM_CONTEXTMENU, (WPARAM)(HWND)(hwndContext), MAKELPARAM((UINT)(xPos), (UINT)(yPos)))

#define HANDLE_WM_CREATE(hwnd,wParam,lParam,fn) ((fn)((hwnd),(LPCREATESTRUCT)(lParam)) ? 0 : (LRESULT)-1L)
#define FORWARD_WM_CREATE(hwnd,lpCreateStruct,fn) (BOOL)(DWORD)(fn)((hwnd),WM_CREATE,0,(LPARAM)(LPCREATESTRUCT)(lpCreateStruct))

#define FORWARD_WM_CTLCOLORBTN(hwnd,hdc,hwndChild,fn) (HBRUSH)(DWORD)(fn)((hwnd),WM_CTLCOLORBTN,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORBTN(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_BTN)

#define FORWARD_WM_CTLCOLORDLG(hwnd,hdc,hwndChild,fn) (HBRUSH)(UINT)(DWORD)(fn)((hwnd),WM_CTLCOLORDLG,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORDLG(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_DLG)

#define FORWARD_WM_CTLCOLORLISTBOX(hwnd,hdc,hwndChild,fn) (HBRUSH)(UINT)(DWORD)(fn)((hwnd),WM_CTLCOLORLISTBOX,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORLISTBOX(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_LISTBOX)

#define FORWARD_WM_CTLCOLORMSGBOX(hwnd,hdc,hwndChild,fn) (HBRUSH)(UINT)(DWORD)(fn)((hwnd),WM_CTLCOLORMSGBOX,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORMSGBOX(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_MSGBOX)

#define FORWARD_WM_CTLCOLORSCROLLBAR(hwnd,hdc,hwndChild,fn) (HBRUSH)(UINT)(DWORD)(fn)((hwnd),WM_CTLCOLORSCROLLBAR,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORSCROLLBAR(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_SCROLLBAR)

#define FORWARD_WM_CTLCOLORSTATIC(hwnd,hdc,hwndChild,fn) (HBRUSH)(UINT)(DWORD)(fn)((hwnd),WM_CTLCOLORSTATIC,(WPARAM)(HDC)(hdc),(LPARAM)(HWND)(hwndChild))
#define HANDLE_WM_CTLCOLORSTATIC(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd),(HDC)(wParam),(HWND)(lParam),CTLCOLOR_STATIC)

#define FORWARD_WM_DELETEITEM(hwnd,lpDeleteItem,fn) (void)(fn)((hwnd),WM_DELETEITEM,(WPARAM)(((const DELETEITEMSTRUCT*)(lpDeleteItem))->CtlID),(LPARAM)(const DELETEITEMSTRUCT*)(lpDeleteItem))
#define HANDLE_WM_DELETEITEM(hwnd,wParam,lParam,fn) ((fn)((hwnd),(const DELETEITEMSTRUCT*)(lParam)),0)

#define HANDLE_WM_DESTROY(hwnd,wParam,lParam,fn) ((fn)(hwnd),0)
#define FORWARD_WM_DESTROY(hwnd, fn) (void)(fn)((hwnd), WM_DESTROY, 0L, 0L)

#define HANDLE_WM_DISPLAYCHANGE(hwnd, wParam, lParam, fn) ((fn)((hwnd), (UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_DISPLAYCHANGE(hwnd, bitsPerPixel, cxScreen, cyScreen, fn) (void)(fn)((hwnd), WM_DISPLAYCHANGE, (WPARAM)(UINT)(bitsPerPixel), (LPARAM)MAKELPARAM((UINT)(cxScreen), (UINT)(cyScreen)))

#define HANDLE_WM_DRAWITEM(hwnd,wParam,lParam,fn) ((fn)((hwnd),(const DRAWITEMSTRUCT*)(lParam)),0)
#define FORWARD_WM_DRAWITEM(hwnd,lpDrawItem,fn) (void)(fn)((hwnd),WM_DRAWITEM,(WPARAM)(((const DRAWITEMSTRUCT*)lpDrawItem)->CtlID),(LPARAM)(const DRAWITEMSTRUCT*)(lpDrawItem))

#define FORWARD_WM_ENABLE(hwnd,fEnable,fn) (void)(fn)((hwnd),WM_ENABLE,(WPARAM)(BOOL)(fEnable),0)
#define HANDLE_WM_ENABLE(hwnd,wParam,lParam,fn) ((fn)((hwnd),(BOOL)(wParam)),0)

#define HANDLE_WM_ERASEBKGND(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(BOOL)(fn)((hwnd),(HDC)(wParam))
#define FORWARD_WM_ERASEBKGND(hwnd,hdc,fn) (BOOL)(DWORD)(fn)((hwnd),WM_ERASEBKGND,(WPARAM)(HDC)(hdc),0)

#define HANDLE_WM_GETFONT(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(HFONT)(fn)(hwnd)
#define FORWARD_WM_GETFONT(hwnd,fn) (HFONT)(UINT)(DWORD)(fn)((hwnd),WM_GETFONT,0,0)

#define HANDLE_WM_HSCROLL(hwnd,wParam,lParam,fn) ((fn)((hwnd),(HWND)(lParam),(UINT)(LOWORD(wParam)),(int)(short)HIWORD(wParam)),0)
#define FORWARD_WM_HSCROLL(hwnd,hwndCtl,code,pos,fn) (void)(fn)((hwnd),WM_HSCROLL,MAKEWPARAM((UINT)(int)(code),(UINT)(int)(pos)),(LPARAM)(UINT)(hwndCtl))

#define HANDLE_WM_INITDIALOG(hwnd, wParam, lParam, fn) (LRESULT)(DWORD)(UINT)(BOOL)(fn)((hwnd), (HWND)(wParam), lParam)
#define FORWARD_WM_INITDIALOG(hwnd, hwndFocus, lParam, fn)  (BOOL)(DWORD)(fn)((hwnd), WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam))

#define FORWARD_WM_INITMENUPOPUP(hwnd,hMenu,item,fSystemMenu,fn) (void)(fn)((hwnd),WM_INITMENUPOPUP,(WPARAM)(HMENU)(hMenu),MAKELPARAM((item),(fSystemMenu)))
#define HANDLE_WM_INITMENUPOPUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(HMENU)(wParam),(UINT)LOWORD(lParam),(BOOL)HIWORD(lParam)),0)

#define HANDLE_WM_KEYDOWN(hwnd, wParam, lParam, fn) ((fn)((hwnd), (UINT)(wParam), 1, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_KEYDOWN(hwnd, vk, cRepeat, flags, fn) (void)(fn)((hwnd), WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

#define HANDLE_WM_KEYUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(UINT)(wParam),0,(int)(short)LOWORD(lParam),(UINT)HIWORD(lParam)),0)
#define FORWARD_WM_KEYUP(hwnd,vk,cRepeat,flags,fn) (void)(fn)((hwnd),WM_KEYUP,(WPARAM)(UINT)(vk),MAKELPARAM((cRepeat),(flags)))

#define HANDLE_WM_KILLFOCUS(hwnd, wParam, lParam, fn) ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_KILLFOCUS(hwnd, hwndNewFocus, fn) (void)(fn)((hwnd), WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L)

#define HANDLE_WM_LBUTTONDBLCLK(hwnd,wParam,lParam,fn) ((fn)((hwnd),1,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define HANDLE_WM_LBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_LBUTTONDOWN(hwnd,fDoubleClick,x,y,keyFlags,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_LBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_LBUTTONUP(hwnd,x,y,keyFlags,fn) (void)(fn)((hwnd),WM_LBUTTONUP,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_MBUTTONDBLCLK(hwnd,wParam,lParam,fn) ((fn)((hwnd),1,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define HANDLE_WM_MBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_MBUTTONDOWN(hwnd,fDoubleClick,x,y,keyFlags,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_MBUTTONDBLCLK : WM_MBUTTONDOWN,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_MBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_MBUTTONUP(hwnd,x,y,keyFlags,fn) (void)(fn)((hwnd),WM_MBUTTONUP,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_MOUSEMOVE(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_MOUSEMOVE(hwnd,x,y,keyFlags,fn) (void)(fn)((hwnd),WM_MOUSEMOVE,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_MOVE(hwnd, wParam, lParam, fn) ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define FORWARD_WM_MOVE(hwnd, x, y, fn) (void)(fn)((hwnd), WM_MOVE, 0L, MAKELPARAM((x), (y)))

#define HANDLE_WM_NCHITTEST(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam))
#define FORWARD_WM_NCHITTEST(hwnd,x,y,fn) (UINT)(DWORD)(fn)((hwnd),WM_NCHITTEST,0,MAKELPARAM((x),(y)))

#define HANDLE_WM_NCLBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCLBUTTONDOWN(hwnd,fDoubleClick,x,y,codeHitTest,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_NCLBUTTONDBLCLK : WM_NCLBUTTONDOWN,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)))

#define HANDLE_WM_NCLBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCLBUTTONUP(hwnd,x,y,codeHitTest,fn) (void)(fn)((hwnd),WM_NCLBUTTONUP,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)))

#define HANDLE_WM_NCMBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCMBUTTONUP(hwnd,x,y,codeHitTest,fn) (void)(fn)((hwnd),WM_NCMBUTTONUP,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_NCMBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCMBUTTONDOWN(hwnd,fDoubleClick,x,y,codeHitTest,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_NCMBUTTONDBLCLK : WM_NCMBUTTONDOWN,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_NCMOUSEMOVE(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCMOUSEMOVE(hwnd,x,y,codeHitTest,fn) (void)(fn)((hwnd),WM_NCMOUSEMOVE,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)))

#define HANDLE_WM_NCPAINT(hwnd,wParam,lParam,fn) ((fn)((hwnd),(HRGN)(wParam)),0)
#define FORWARD_WM_NCPAINT(hwnd,hrgn,fn) (void)(fn)((hwnd),WM_NCPAINT,(WPARAM)(HRGN)(hrgn),0)

#define HANDLE_WM_NCRBUTTONDBLCLK(hwnd,wParam,lParam,fn) ((fn)((hwnd),1,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)

#define HANDLE_WM_NCRBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCRBUTTONDOWN(hwnd,fDoubleClick,x,y,codeHitTest,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_NCRBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCRBUTTONUP(hwnd,x,y,codeHitTest,fn) (void)(fn)((hwnd),WM_NCRBUTTONUP,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_NCXBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCXBUTTONDOWN(hwnd,fDoubleClick,x,y,codeHitTest,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_NCXBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_NCXBUTTONUP(hwnd,x,y,codeHitTest,fn) (void)(fn)((hwnd),WM_NCRBUTTONUP,(WPARAM)(UINT)(codeHitTest),MAKELPARAM((x),(y)) )

#define HANDLE_WM_PAINT(hwnd,wParam,lParam,fn) ((fn)(hwnd),0)
#define FORWARD_WM_PAINT(hwnd,fn) (void)(fn)((hwnd),WM_PAINT,0,0)

#define FORWARD_WM_POWERBROADCAST(hwnd,code,pbsettings,fn) (void)(fn)((hwnd),WM_POWERBROADCAST,(WPARAM)(int)(code),(LPARAM)pbsettings)
#define HANDLE_WM_POWERBROADCAST(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(wParam),(POWERBROADCAST_SETTING *)(lParam)),0)

#define FORWARD_WM_QUERYDRAGICON(hwnd,fn) (HICON)(UINT)(DWORD)(fn)((hwnd),WM_QUERYDRAGICON,0,0)
#define HANDLE_WM_QUERYDRAGICON(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(UINT)(fn)(hwnd)

#define HANDLE_WM_RBUTTONDBLCLK(hwnd,wParam,lParam,fn) ((fn)((hwnd),1,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define HANDLE_WM_RBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_RBUTTONDOWN(hwnd,fDoubleClick,x,y,keyFlags,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_RBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_RBUTTONUP(hwnd,x,y,keyFlags,fn) (void)(fn)((hwnd),WM_RBUTTONUP,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_SETFOCUS(hwnd, wParam, lParam, fn) ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_SETFOCUS(hwnd, hwndOldFocus, fn) (void)(fn)((hwnd), WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L)

#define FORWARD_WM_SETREDRAW(hwnd,fRedraw,fn) (void)(fn)((hwnd),WM_SETREDRAW,(WPARAM)(BOOL)(fRedraw),0)
#define HANDLE_WM_SETREDRAW(hwnd,wParam,lParam,fn) ((fn)((hwnd),(BOOL)(wParam)),0)

#define HANDLE_WM_SETTEXT(hwnd, wParam, lParam, fn) ((fn)((hwnd), (LPCTSTR)(lParam)), 0L)
#define FORWARD_WM_SETTEXT(hwnd, lpszText, fn) (void)(fn)((hwnd), WM_SETTEXT, 0L, (LPARAM)(LPCTSTR)(lpszText))

#define FORWARD_WM_SIZE(hwnd,state,cx,cy,fn) (void)(fn)((hwnd),WM_SIZE,(WPARAM)(UINT)(state),MAKELPARAM((cx),(cy)))
#define HANDLE_WM_SIZE(hwnd,wParam,lParam,fn) ((fn)((hwnd),(UINT)(wParam),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam)),0)

#define HANDLE_WM_SYSKEYDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),(UINT)(wParam),1,(int)(short)LOWORD(lParam),(UINT)HIWORD(lParam)),0)
#define FORWARD_WM_SYSKEYDOWN(hwnd,vk,cRepeat,flags,fn) (void)(fn)((hwnd),WM_SYSKEYDOWN,(WPARAM)(UINT)(vk),MAKELPARAM((cRepeat),(flags)))

#define HANDLE_WM_SYSKEYUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(UINT)(wParam),0,(int)(short)LOWORD(lParam),(UINT)HIWORD(lParam)),0)
#define FORWARD_WM_SYSKEYUP(hwnd,vk,cRepeat,flags,fn) (void)(fn)((hwnd),WM_SYSKEYUP,(WPARAM)(UINT)(vk),MAKELPARAM((cRepeat),(flags)))

#define HANDLE_WM_TIMER(hwnd, wParam, lParam, fn) ((fn)((hwnd), (UINT)(wParam)), 0L)
#define FORWARD_WM_TIMER(hwnd, id, fn) (void)(fn)((hwnd), WM_TIMER, (WPARAM)(UINT)(id), 0L)

#define FORWARD_WM_VKEYTOITEM(hwnd,vk,hwndListBox,iCaret,fn) (int)(DWORD)(fn)((hwnd),WM_VKEYTOITEM,MAKEWPARAM((vk),(iCaret)),(LPARAM)(hwndListBox))
#define HANDLE_WM_VKEYTOITEM(hwnd,wParam,lParam,fn) (LRESULT)(DWORD)(int)(fn)((hwnd),(UINT)LOWORD(wParam),(HWND)(lParam),(int)(short)HIWORD(wParam))

#define HANDLE_WM_VSCROLL(hwnd,wParam,lParam,fn) ((fn)((hwnd),(HWND)(lParam),(UINT)(LOWORD(wParam)),(int)(short)HIWORD(wParam)),0)
#define FORWARD_WM_VSCROLL(hwnd,hwndCtl,code,pos,fn) (void)(fn)((hwnd),WM_VSCROLL,MAKEWPARAM((UINT)(int)(code),(UINT)(int)(pos)),(LPARAM)(HWND)(hwndCtl))

#define HANDLE_WM_XBUTTONDBLCLK(hwnd,wParam,lParam,fn) ((fn)((hwnd),1,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define HANDLE_WM_XBUTTONDOWN(hwnd,wParam,lParam,fn) ((fn)((hwnd),0,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_XBUTTONDOWN(hwnd,fDoubleClick,x,y,keyFlags,fn) (void)(fn)((hwnd),(fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define HANDLE_WM_XBUTTONUP(hwnd,wParam,lParam,fn) ((fn)((hwnd),(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),(UINT)(wParam)),0)
#define FORWARD_WM_XBUTTONUP(hwnd,x,y,keyFlags,fn) (void)(fn)((hwnd),WM_RBUTTONUP,(WPARAM)(UINT)(keyFlags),MAKELPARAM((x),(y)))

#define IsMinimized(hwnd)                 IsIconic(hwnd)

#define GET_WM_VSCROLL_CODE(wp,lp)        LOWORD(wp)
#define GET_WM_VSCROLL_HWND(wp,lp)        (HWND)(lp)
#define GET_WM_VSCROLL_MPS(code,pos,hwnd) (WPARAM)MAKELONG(code,pos),(LONG)(hwnd)
#define GET_WM_VSCROLL_POS(wp,lp)         HIWORD(wp)

#define GET_X_LPARAM(lp)                  ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                  ((int)(short)HIWORD(lp))

#define DeleteBrush(hbr)                  DeleteObject((HGDIOBJ)(HBRUSH)(hbr))

#define GetStockBrush(i)                  ((HBRUSH)GetStockObject(i))

#define GetWindowFont(hwnd)               FORWARD_WM_GETFONT((hwnd),SendMessage)
#define GetWindowInstance(hwnd)           ((HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE))
#define GetWindowStyle(hwnd)              ((DWORD)GetWindowLongPtr(hwnd,GWL_STYLE))
#define GetWindowExStyle(hwnd)            ((DWORD)GetWindowLongPtr(hwnd,GWL_EXSTYLE))

#define SelectBitmap(hdc,hbm)             ((HBITMAP)SelectObject((hdc),(HGDIOBJ)(HBITMAP)(hbm)))
#define SelectFont(hdc,hfont)             ((HFONT)SelectObject((hdc),(HGDIOBJ)(HFONT)(hfont)))
#define SelectPen(hdc, hpen)              ((HPEN)SelectObject((hdc), (HGDIOBJ)(HPEN)(hpen)))

#define SetDlgMsgResult(hwnd,msg,result)  (( (msg) == WM_CTLCOLORMSGBOX || (msg) == WM_CTLCOLOREDIT || (msg) == WM_CTLCOLORLISTBOX || (msg) == WM_CTLCOLORBTN || (msg) == WM_CTLCOLORDLG || (msg) == WM_CTLCOLORSCROLLBAR || (msg) == WM_CTLCOLORSTATIC || (msg) == WM_COMPAREITEM || (msg) == WM_VKEYTOITEM || (msg) == WM_CHARTOITEM || (msg) == WM_QUERYDRAGICON || (msg) == WM_INITDIALOG ) ? (BOOL)(result) : (SetWindowLong((hwnd),DWL_MSGRESULT,(LPARAM)(LRESULT)(result)),(0 != 1) ))

#define SetWindowRedraw(hwnd,fRedraw)     ((void)SendMessage(hwnd,WM_SETREDRAW,(WPARAM)(BOOL)(fRedraw),0))

#define SubclassDialog(hwndDlg,lpfn)      ((DLGPROC)SetWindowLong(hwndDlg,DWL_DLGPROC,(LPARAM)(DLGPROC)(lpfn)))
#define SubclassWindow(hwnd,lpfn)         ((WNDPROC)SetWindowLong((hwnd),GWL_WNDPROC,(LPARAM)(WNDPROC)(lpfn)))


#define Button_Enable(hwndCtl,fEnable)    EnableWindow((hwndCtl),(fEnable))
#define Button_GetCheck(hwndCtl)          ((int)(DWORD)SendMessage((hwndCtl),BM_GETCHECK,0,0))
#define Button_SetCheck(hwndCtl,check)    ((void)SendMessage((hwndCtl),BM_SETCHECK,(WPARAM)(int)(check),0))

#define ComboBox_AddItemData(hwndCtl,data) ((int)(DWORD)SendMessage((hwndCtl),CB_ADDSTRING,0,(LPARAM)(data)))
#define ComboBox_AddString(hwndCtl,lpsz) ((int)(DWORD)SendMessage((hwndCtl),CB_ADDSTRING,0,(LPARAM)(LPCTSTR)(lpsz)))
#define ComboBox_DeleteString(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),CB_DELETESTRING,(WPARAM)(int)(index),0))
#define ComboBox_GetCount(hwndCtl) ((int)(DWORD)SendMessage((hwndCtl),CB_GETCOUNT,0,0))
#define ComboBox_GetCurSel(hwndCtl) ((int)(DWORD)SendMessage((hwndCtl),CB_GETCURSEL,0,0))
#define ComboBox_GetItemData(hwndCtl,index) ((LRESULT)(DWORD)SendMessage((hwndCtl),CB_GETITEMDATA,(WPARAM)(int)(index),0))
#define ComboBox_GetItemHeight(hwndCtl) ((int)(DWORD)SendMessage((hwndCtl),CB_GETITEMHEIGHT,0,0))
#define ComboBox_InsertItemData(hwndCtl,index,data) ((int)(DWORD)SendMessage((hwndCtl),CB_INSERTSTRING,(WPARAM)(int)(index),(LPARAM)(data)))
#define ComboBox_InsertString(hwndCtl,index,lpsz) ((int)(DWORD)SendMessage((hwndCtl),CB_INSERTSTRING,(WPARAM)(int)(index),(LPARAM)(LPCTSTR)(lpsz)))
#define ComboBox_ResetContent(hwndCtl) ((int)(DWORD)SendMessage((hwndCtl),CB_RESETCONTENT,0,0))
#define ComboBox_SetCurSel(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),CB_SETCURSEL,(WPARAM)(int)(index),0))
#define ComboBox_SetItemData(hwndCtl,index,data) ((int)(DWORD)SendMessage((hwndCtl),CB_SETITEMDATA,(WPARAM)(int)(index),(LPARAM)(data)))

#define DeleteBitmap(hbm) DeleteObject((HGDIOBJ)(HBITMAP)(hbm))
#define DeleteBrush(hbr) DeleteObject((HGDIOBJ)(HBRUSH)(hbr))
#define DeleteFont(hfont) DeleteObject((HGDIOBJ)(HFONT)(hfont))
#define DeletePen(hpen) DeleteObject((HGDIOBJ)(HPEN)(hpen))

#define Edit_GetHandle(hwndCtl) ((HLOCAL)(UINT)(DWORD)SendMessage((hwndCtl),EM_GETHANDLE,0,0))
#define Edit_GetModify(hwndCtl) ((BOOL)(DWORD)SendMessage((hwndCtl),EM_GETMODIFY,0,0))
#define Edit_GetSel(hwndCtl) ((DWORD)SendMessage((hwndCtl),EM_GETSEL,0,0))
#define Edit_GetTextLength(hwndCtl) GetWindowTextLength(hwndCtl)
#define Edit_LimitText(hwndCtl, cchMax) ((void)SendMessage((hwndCtl), EM_LIMITTEXT, (WPARAM)(UINT)(cchMax), 0L))
#define Edit_SetModify(hwndCtl,fModified) ((void)SendMessage((hwndCtl),EM_SETMODIFY,(WPARAM)(UINT)(fModified),0))
#define Edit_SetReadOnly(hwndCtl,fReadOnly) ((BOOL)(DWORD)SendMessage((hwndCtl),EM_SETREADONLY,(WPARAM)(BOOL)(fReadOnly),0))
#define Edit_SetSel(hwndCtl,ichStart,ichEnd) ((void)SendMessage((hwndCtl),EM_SETSEL,(ichStart),(ichEnd)))
#define Edit_ReplaceSel(hwndCtl,lpszReplace) ((void)SendMessage((hwndCtl),EM_REPLACESEL,0,(LPARAM)(LPCTSTR)(lpszReplace)))

#define ListBox_AddString(hwndCtl, lpsz) ((int)SendMessage((hwndCtl), LB_ADDSTRING, 0L, (LPARAM)(LPCTSTR)(lpsz)))
#define ListBox_DeleteString(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),LB_DELETESTRING,(WPARAM)(int)(index),0))
#define ListBox_GetCount(hwndCtl) ((int)SendMessage((hwndCtl), LB_GETCOUNT, 0L, 0L))
#define ListBox_GetCurSel(hwndCtl) ((int)(DWORD)SendMessage((hwndCtl),LB_GETCURSEL,0,0))
#define ListBox_GetItemData(hwndCtl,index) ((LRESULT)(DWORD)SendMessage((hwndCtl),LB_GETITEMDATA,(WPARAM)(int)(index),0))
#define ListBox_GetItemHeight(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),LB_GETITEMHEIGHT,(WPARAM)(int)(index),0))
#define ListBox_GetText(hwndCtl,index,lpszBuffer) ((int)(DWORD)SendMessage((hwndCtl),LB_GETTEXT,(WPARAM)(int)(index),(LPARAM)(LPCTSTR)(lpszBuffer)))
#define ListBox_GetTextLen(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),LB_GETTEXTLEN,(WPARAM)(int)(index),0))
#define ListBox_InsertItemData(hwndCtl,index,data) ((int)(DWORD)SendMessage((hwndCtl),LB_INSERTSTRING,(WPARAM)(int)(index),(LPARAM)(data)))
#define ListBox_InsertString(hwndCtl,index,lpsz) ((int)(DWORD)SendMessage((hwndCtl),LB_INSERTSTRING,(WPARAM)(int)(index),(LPARAM)(LPCTSTR)(lpsz)))
#define ListBox_ResetContent(hwndCtl) ((BOOL)(DWORD)SendMessage((hwndCtl),LB_RESETCONTENT,0,0))
#define ListBox_SetCurSel(hwndCtl,index) ((int)(DWORD)SendMessage((hwndCtl),LB_SETCURSEL,(WPARAM)(int)(index),0))
#define ListBox_SetItemData(hwndCtl, index, data) ((int)SendMessage((hwndCtl), LB_SETITEMDATA, (WPARAM)(int)(index), (LPARAM)(DWORD)(data)))

#define Static_Enable(hwndCtl,fEnable) EnableWindow((hwndCtl),(fEnable))
#define Static_GetIcon(hwndCtl,hIcon) ((HICON)(DWORD)SendMessage((hwndCtl),STM_GETICON,0,0))
#define Static_GetText(hwndCtl,lpch,cchMax) GetWindowText((hwndCtl),(lpch),(cchMax))
#define Static_GetTextLength(hwndCtl) GetWindowTextLength(hwndCtl)
#define Static_SetIcon(hwndCtl,hIcon) ((HICON)(DWORD)SendMessage((hwndCtl),STM_SETICON,0,(LPARAM)(HICON)(hIcon)))
#define Static_SetText(hwndCtl,lpsz) SetWindowText((hwndCtl),(lpsz))


#endif /* YOUWIN_WINDOWSX_H */

