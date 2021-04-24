

#include <tchar.h>
#include <windowsx.h>
#include <windows.h>

#include <string>

#if 0
#ifdef _WIN32
#ifdef _tcsncpy
#undef _tcsncpy
#endif
#define _tcsncpy _tcsncpy_s
#ifdef _tcsncat
#undef _tcsncat
#endif
#define _tcsncat _tcsncat_s
#ifdef _sntprintf
#undef _sntprintf
#endif
#define _sntprintf _sntprintf_s
#endif
#endif


typedef std::basic_string<TCHAR> tstring;


static LPCTSTR GetHitCode( int ht ) {

    switch( ht ) {

        case HTBORDER:      return TEXT( "HTBORDER"             );
        case HTBOTTOM:      return TEXT( "HTBOTTOM"             );
        case HTBOTTOMLEFT:  return TEXT( "HTBOTTOMLEFT"         );
        case HTBOTTOMRIGHT: return TEXT( "HTBOTTOMRIGHT"        );
        case HTCAPTION:     return TEXT( "HTCAPTION"            );
        case HTCLIENT:      return TEXT( "HTCLIENT"             );
        case HTCLOSE:       return TEXT( "HTCLOSE"              );
        case HTERROR:       return TEXT( "HTERROR"              );
        case HTGROWBOX:     return TEXT( "HTGROWBOX/HTSIZE"     );
        case HTHELP:        return TEXT( "HTHELP"               );
        case HTHSCROLL:     return TEXT( "HTHSCROLL"            );
        case HTLEFT:        return TEXT( "HTLEFT"               );
        case HTMENU:        return TEXT( "HTMENU"               );
        case HTMAXBUTTON:   return TEXT( "HTMAXBUTTON/HTZOOM"   );
        case HTMINBUTTON:   return TEXT( "HTMINBUTTON/HTREDUCE" );
        case HTNOWHERE:     return TEXT( "HTNOWHERE"            );
        case HTRIGHT:       return TEXT( "HTRIGHT"              );
        case HTSYSMENU:     return TEXT( "HTSYSMENU"            );
        case HTTOP:         return TEXT( "HTTOP"                );
        case HTTOPLEFT:     return TEXT( "HTTOPLEFT"            );
        case HTTOPRIGHT:    return TEXT( "HTTOPRIGHT"           );
        case HTTRANSPARENT: return TEXT( "HTTRANSPARENT"        );
        case HTVSCROLL:     return TEXT( "HTVSCROLL"            );

    }

    static TCHAR szError[32];

    memset( szError, 0, sizeof( szError ) );

    _sntprintf( szError, Dim( szError ) - 1, TEXT( "UNKNOWN HIT-CODE %d" ), ht );

    return szError;

}


static LPCTSTR GetMKAttribs( unsigned uMK ) {

//    static TCHAR szAttribs[128];
    static tstring szAttribs;

//    ZeroMemory( szAttribs, sizeof( szAttribs ) );
    szAttribs.clear();

    if ( MK_CONTROL & uMK ) {

        szAttribs.append( TEXT( "MK_CONTROL" ) );

    }

    if ( MK_LBUTTON & uMK ) {

        szAttribs.append( TEXT( "MK_LBUTTON" ) );

    }

    if ( MK_MBUTTON & uMK ) {

        szAttribs.append( TEXT( "MK_MBUTTON" ) );

    }

    if ( MK_RBUTTON & uMK ) {

        szAttribs.append( TEXT( "MK_RBUTTON" ) );

    }

    if ( MK_SHIFT & uMK ) {

        szAttribs.append( TEXT( "MK_SHIFT" ) );

    }

    if ( MK_XBUTTON1 & uMK ) {

        szAttribs.append( TEXT( "MK_XBUTTON1" ) );

    }

    if ( MK_XBUTTON2 & uMK ) {

        szAttribs.append( TEXT( "MK_XBUTTON2" ) );

    }

    return szAttribs.c_str();

}


static LPCTSTR GetVKeyName( UINT vk ) {

    switch( vk ) {

        case VK_LBUTTON:             return TEXT( "VK_LBUTTON" );
        case VK_RBUTTON:             return TEXT( "VK_RBUTTON" );
        case VK_CANCEL:              return TEXT( "VK_CANCEL" );
        case VK_MBUTTON:             return TEXT( "VK_MBUTTON" );
        case VK_BACK:                return TEXT( "VK_BACK" );
        case VK_TAB:                 return TEXT( "VK_TAB" );
        case VK_CLEAR:               return TEXT( "VK_CLEAR" );
        case VK_RETURN:              return TEXT( "VK_RETURN" );
        case VK_SHIFT:               return TEXT( "VK_SHIFT" );
        case VK_CONTROL:             return TEXT( "VK_CONTROL" );
        case VK_MENU:                return TEXT( "VK_MENU" );
        case VK_PAUSE:               return TEXT( "VK_PAUSE" );
        case VK_CAPITAL:             return TEXT( "VK_CAPITAL" );

//        case VK_KANA:
//            return "VK_KANA";

//        case VK_HANGEUL:
//            return "VK_HANGEUL";

        case VK_HANGUL:              return TEXT( "VK_HANGEUL or VK_HANGUL or VK_KANA" );
        case VK_JUNJA:               return TEXT( "VK_JUNJA" );
        case VK_FINAL:               return TEXT( "VK_FINAL" );

//        case VK_HANJA:
//            return "VK_HANJA";

        case VK_KANJI:               return TEXT( "VK_KANJI or VK_HANJA" );
        case VK_ESCAPE:              return TEXT( "VK_ESCAPE" );
        case VK_CONVERT:             return TEXT( "VK_CONVERT" );
        case VK_NONCONVERT:          return TEXT( "VK_NONCONVERT" );
        case VK_ACCEPT:              return TEXT( "VK_ACCEPT" );
        case VK_MODECHANGE:          return TEXT( "VK_MODECHANGE" );
        case VK_SPACE:               return TEXT( "VK_SPACE" );
        case VK_PRIOR:               return TEXT( "VK_PRIOR" );
        case VK_NEXT:                return TEXT( "VK_NEXT" );
        case VK_END:                 return TEXT( "VK_END" );
        case VK_HOME:                return TEXT( "VK_HOME" );
        case VK_LEFT:                return TEXT( "VK_LEFT" );
        case VK_UP:                  return TEXT( "VK_UP" );
        case VK_RIGHT:               return TEXT( "VK_RIGHT" );
        case VK_DOWN:                return TEXT( "VK_DOWN" );
        case VK_SELECT:              return TEXT( "VK_SELECT" );
        case VK_PRINT:               return TEXT( "VK_PRINT" );
        case VK_EXECUTE:             return TEXT( "VK_EXECUTE" );
        case VK_SNAPSHOT:            return TEXT( "VK_SNAPSHOT" );
        case VK_INSERT:              return TEXT( "VK_INSERT" );
        case VK_DELETE:              return TEXT( "VK_DELETE" );
        case VK_HELP:                return TEXT( "VK_HELP" );
        case VK_LWIN:                return TEXT( "VK_LWIN" );
        case VK_RWIN:                return TEXT( "VK_RWIN" );
        case VK_APPS:                return TEXT( "VK_APPS" );
        case VK_SLEEP:               return TEXT( "VK_SLEEP" );
        case VK_NUMPAD0:             return TEXT( "VK_NUMPAD0" );
        case VK_NUMPAD1:             return TEXT( "VK_NUMPAD1" );
        case VK_NUMPAD2:             return TEXT( "VK_NUMPAD2" );
        case VK_NUMPAD3:             return TEXT( "VK_NUMPAD3" );
        case VK_NUMPAD4:             return TEXT( "VK_NUMPAD4" );
        case VK_NUMPAD5:             return TEXT( "VK_NUMPAD5" );
        case VK_NUMPAD6:             return TEXT( "VK_NUMPAD6" );
        case VK_NUMPAD7:             return TEXT( "VK_NUMPAD7" );
        case VK_NUMPAD8:             return TEXT( "VK_NUMPAD8" );
        case VK_NUMPAD9:             return TEXT( "VK_NUMPAD9" );
        case VK_MULTIPLY:            return TEXT( "VK_MULTIPLY" );
        case VK_ADD:                 return TEXT( "VK_ADD" );
        case VK_SEPARATOR:           return TEXT( "VK_SEPARATOR" );
        case VK_SUBTRACT:            return TEXT( "VK_SUBTRACT" );
        case VK_DECIMAL:             return TEXT( "VK_DECIMAL" );
        case VK_DIVIDE:              return TEXT( "VK_DIVIDE" );
        case VK_F1:                  return TEXT( "VK_F1" );
        case VK_F2:                  return TEXT( "VK_F2" );
        case VK_F3:                  return TEXT( "VK_F3" );
        case VK_F4:                  return TEXT( "VK_F4" );
        case VK_F5:                  return TEXT( "VK_F5" );
        case VK_F6:                  return TEXT( "VK_F6" );
        case VK_F7:                  return TEXT( "VK_F7" );
        case VK_F8:                  return TEXT( "VK_F8" );
        case VK_F9:                  return TEXT( "VK_F9" );
        case VK_F10:                 return TEXT( "VK_F10" );
        case VK_F11:                 return TEXT( "VK_F11" );
        case VK_F12:                 return TEXT( "VK_F12" );
        case VK_F13:                 return TEXT( "VK_F13" );
        case VK_F14:                 return TEXT( "VK_F14" );
        case VK_F15:                 return TEXT( "VK_F15" );
        case VK_F16:                 return TEXT( "VK_F16" );
        case VK_F17:                 return TEXT( "VK_F17" );
        case VK_F18:                 return TEXT( "VK_F18" );
        case VK_F19:                 return TEXT( "VK_F19" );
        case VK_F20:                 return TEXT( "VK_F20" );
        case VK_F21:                 return TEXT( "VK_F21" );
        case VK_F22:                 return TEXT( "VK_F22" );
        case VK_F23:                 return TEXT( "VK_F23" );
        case VK_F24:                 return TEXT( "VK_F24" );
        case VK_NUMLOCK:             return TEXT( "VK_NUMLOCK" );
        case VK_SCROLL:              return TEXT( "VK_SCROLL" );
        case VK_LSHIFT:              return TEXT( "VK_LSHIFT" );
        case VK_RSHIFT:              return TEXT( "VK_RSHIFT" );
        case VK_LCONTROL:            return TEXT( "VK_LCONTROL" );
        case VK_RCONTROL:            return TEXT( "VK_RCONTROL" );
        case VK_LMENU:               return TEXT( "VK_LMENU" );
        case VK_RMENU:               return TEXT( "VK_RMENU" );

#ifdef YOU_WIN

        case VK_XBUTTON1:            return TEXT( "VK_XBUTTON1" );
        case VK_XBUTTON2:            return TEXT( "VK_XBUTTON2" );
        case VK_BACKTAB:             return TEXT( "VK_BACKTAB" );
        case VK_BROWSER_BACK:        return TEXT( "VK_BROWSER_BACK" );
        case VK_BROWSER_FORWARD:     return TEXT( "VK_BROWSER_FORWARD" );
        case VK_BROWSER_REFRESH:     return TEXT( "VK_BROWSER_REFRESH" );
        case VK_BROWSER_STOP:        return TEXT( "VK_BROWSER_STOP" );
        case VK_BROWSER_SEARCH:      return TEXT( "VK_BROWSER_SEARCH" );
        case VK_BROWSER_FAVORITES:   return TEXT( "VK_BROWSER_FAVORITES" );
        case VK_BROWSER_HOME:        return TEXT( "VK_BROWSER_HOME" );
        case VK_VOLUME_MUTE:         return TEXT( "VK_VOLUME_MUTE" );
        case VK_VOLUME_DOWN:         return TEXT( "VK_VOLUME_DOWN" );
        case VK_VOLUME_UP:           return TEXT( "VK_VOLUME_UP" );
        case VK_MEDIA_NEXT_TRACK:    return TEXT( "VK_MEDIA_NEXT_TRACK" );
        case VK_MEDIA_PREV_TRACK:    return TEXT( "VK_MEDIA_PREV_TRACK" );
        case VK_MEDIA_STOP:          return TEXT( "VK_MEDIA_STOP" );
        case VK_MEDIA_PLAY_PAUSE:    return TEXT( "VK_MEDIA_PLAY_PAUSE" );
        case VK_LAUNCH_MAIL:         return TEXT( "VK_LAUNCH_MAIL" );
        case VK_LAUNCH_MEDIA_SELECT: return TEXT( "VK_LAUNCH_MEDIA_SELECT" );
        case VK_LAUNCH_APP1:         return TEXT( "VK_LAUNCH_APP1" );
        case VK_LAUNCH_APP2:         return TEXT( "VK_LAUNCH_APP2" );
        case VK_OEM_PLUS:            return TEXT( "VK_OEM_PLUS" );
        case VK_OEM_COMMA:           return TEXT( "VK_OEM_COMMA" );
        case VK_OEM_MINUS:           return TEXT( "VK_OEM_MINUS" );
        case VK_OEM_PERIOD:          return TEXT( "VK_OEM_PERIOD" );
        case VK_OEM_102:             return TEXT( "VK_OEM_102" );
        case VK_PACKET:              return TEXT( "VK_PACKET" );

#endif /* YOU_WIN */

        case VK_OEM_1:               return TEXT( "VK_OEM_1" );
        case VK_OEM_2:               return TEXT( "VK_OEM_2" );
        case VK_OEM_3:               return TEXT( "VK_OEM_3" );
        case VK_OEM_4:               return TEXT( "VK_OEM_4" );
        case VK_OEM_5:               return TEXT( "VK_OEM_5" );
        case VK_OEM_6:               return TEXT( "VK_OEM_6" );
        case VK_OEM_7:               return TEXT( "VK_OEM_7" );
        case VK_OEM_8:               return TEXT( "VK_OEM_8" );
        case VK_PROCESSKEY:          return TEXT( "VK_PROCESSKEY" );
        case VK_ATTN:                return TEXT( "VK_ATTN" );
        case VK_CRSEL:               return TEXT( "VK_CRSEL" );
        case VK_EXSEL:               return TEXT( "VK_EXSEL" );
        case VK_EREOF:               return TEXT( "VK_EREOF" );
        case VK_PLAY:                return TEXT( "VK_PLAY" );
        case VK_ZOOM:                return TEXT( "VK_ZOOM" );
        case VK_NONAME:              return TEXT( "VK_NONAME" );
        case VK_PA1:                 return TEXT( "VK_PA1" );
        case VK_OEM_CLEAR:           return TEXT( "VK_OEM_CLEAR" );

    }

    static TCHAR szUnknown[128];

    memset( szUnknown, 0, sizeof( szUnknown ) );

    _sntprintf( szUnknown, Dim( szUnknown ) - 1, TEXT( "UNKNOWN VIRTUAL KEY 0x%X (%u)" ), vk, vk );

    return szUnknown;

}


extern "C" void DBGTRACE_API traceMSG( unsigned long dwDebugChannelsBitmap, unsigned uLineNo, const char * pszFile, long lNest, const TCHAR * pszPrefix, void * hWnd, unsigned uiMsg, unsigned wParam, intptr_t lParam ) {

    TCHAR   szMsgParams[128];
    TCHAR   szMsg[64];

    memset( szMsg, 0, sizeof( szMsg ) );

    switch( uiMsg ) {

/* Most widely-defined messages */

#if defined( WIN32 ) || defined( _WIN32_WCE ) || defined( ANDROID ) || defined( linux ) || defined( TARGET_OS_MAC ) || defined( YOU_WIN )

        case BM_GETCHECK:          _tcsncpy( szMsg, TEXT( "BM_GETCHECK" ),        Dim( szMsg ) - 1 ); break;
        case EM_LIMITTEXT:         _tcsncpy( szMsg, TEXT( "EM_LIMITTEXT" ),       Dim( szMsg ) - 1 ); break;
        case EM_REPLACESEL:        _tcsncpy( szMsg, TEXT( "EM_REPLACESEL" ),      Dim( szMsg ) - 1 ); break;
        case EM_SETREADONLY:       _tcsncpy( szMsg, TEXT( "EM_SETREADONLY" ),     Dim( szMsg ) - 1 ); break;
        case EM_SETSEL:            _tcsncpy( szMsg, TEXT( "EM_SETSEL" ),          Dim( szMsg ) - 1 ); break;
        case LB_ADDSTRING:         _tcsncpy( szMsg, TEXT( "LB_ADDSTRING" ),       Dim( szMsg ) - 1 ); break;
        case LB_DELETESTRING:      _tcsncpy( szMsg, TEXT( "LB_DELETESTRING" ),    Dim( szMsg ) - 1 ); break;
        case LB_GETCOUNT:          _tcsncpy( szMsg, TEXT( "LB_GETCOUNT" ),        Dim( szMsg ) - 1 ); break;
        case LB_GETCURSEL:         _tcsncpy( szMsg, TEXT( "LB_GETCURSEL" ),       Dim( szMsg ) - 1 ); break;
        case LB_SETCURSEL:         _tcsncpy( szMsg, TEXT( "LB_SETCURSEL" ),       Dim( szMsg ) - 1 ); break;
        case LB_GETITEMDATA:       _tcsncpy( szMsg, TEXT( "LB_GETITEMDATA" ),     Dim( szMsg ) - 1 ); break;
        case LB_GETTEXT:           _tcsncpy( szMsg, TEXT( "LB_GETTEXT" ),         Dim( szMsg ) - 1 ); break;
        case LB_GETTEXTLEN:        _tcsncpy( szMsg, TEXT( "LB_GETTEXTLEN" ),      Dim( szMsg ) - 1 ); break;
        case LB_RESETCONTENT:      _tcsncpy( szMsg, TEXT( "LB_RESETCONTENT" ),    Dim( szMsg ) - 1 ); break;
        case LB_SETITEMDATA:       _tcsncpy( szMsg, TEXT( "LB_SETITEMDATA" ),     Dim( szMsg ) - 1 ); break;
        case STM_GETICON:          _tcsncpy( szMsg, TEXT( "STM_GETICON" ),        Dim( szMsg ) - 1 ); break;
        case STM_SETICON:          _tcsncpy( szMsg, TEXT( "STM_SETICON" ),        Dim( szMsg ) - 1 ); break;
        case WM_CHAR:              _tcsncpy( szMsg, TEXT( "WM_CHAR" ),            Dim( szMsg ) - 1 ); break;
        case WM_CLOSE:             _tcsncpy( szMsg, TEXT( "WM_CLOSE" ),           Dim( szMsg ) - 1 ); break;
        case WM_COMMAND:           _tcsncpy( szMsg, TEXT( "WM_COMMAND" ),         Dim( szMsg ) - 1 ); break;
        case WM_COMPAREITEM:       _tcsncpy( szMsg, TEXT( "WM_COMPAREITEM" ),     Dim( szMsg ) - 1 ); break;
        case WM_COPYDATA:          _tcsncpy( szMsg, TEXT( "WM_COPYDATA" ),        Dim( szMsg ) - 1 ); break;
        case WM_CREATE:            _tcsncpy( szMsg, TEXT( "WM_CREATE" ),          Dim( szMsg ) - 1 ); break;
        case WM_CTLCOLORLISTBOX:   _tcsncpy( szMsg, TEXT( "WM_CTLCOLORLISTBOX" ), Dim( szMsg ) - 1 ); break;
        case WM_DELETEITEM:        _tcsncpy( szMsg, TEXT( "WM_DELETEITEM" ),      Dim( szMsg ) - 1 ); break;
        case WM_DESTROY:           _tcsncpy( szMsg, TEXT( "WM_DESTROY" ),         Dim( szMsg ) - 1 ); break;
        case WM_DEVICECHANGE:      _tcsncpy( szMsg, TEXT( "WM_DEVICECHANGE" ),    Dim( szMsg ) - 1 ); break;
        case WM_DISPLAYCHANGE:     _tcsncpy( szMsg, TEXT( "WM_DISPLAYCHANGE" ),   Dim( szMsg ) - 1 ); break;
        case WM_ENABLE:            _tcsncpy( szMsg, TEXT( "WM_ENABLE" ),          Dim( szMsg ) - 1 ); break;
        case WM_ERASEBKGND:        _tcsncpy( szMsg, TEXT( "WM_ERASEBKGND" ),      Dim( szMsg ) - 1 ); break;
        case WM_GETICON:           _tcsncpy( szMsg, TEXT( "WM_GETICON" ),         Dim( szMsg ) - 1 ); break;
        case WM_HSCROLL:           _tcsncpy( szMsg, TEXT( "WM_HSCROLL" ),         Dim( szMsg ) - 1 ); break;
        case WM_INITDIALOG:        _tcsncpy( szMsg, TEXT( "WM_INITDIALOG" ),      Dim( szMsg ) - 1 ); break;

        case WM_KEYDOWN: {

            _tcsncpy( szMsg, TEXT( "WM_KEYDOWN " ), Dim( szMsg ) - 1 );
            _tcsncat( szMsg, GetVKeyName( wParam ), Dim( szMsg ) - 1 );
            break;

        }

        case WM_KEYUP:             _tcsncpy( szMsg, TEXT( "WM_KEYUP" ),           Dim( szMsg ) - 1 ); break;
        case WM_KILLFOCUS:         _tcsncpy( szMsg, TEXT( "WM_KILLFOCUS" ),       Dim( szMsg ) - 1 ); break;
        case WM_LBUTTONDBLCLK:     _tcsncpy( szMsg, TEXT( "WM_LBUTTONDBLCLK" ),   Dim( szMsg ) - 1 ); break;

        case WM_LBUTTONDOWN: {

            _sntprintf( szMsg, Dim( szMsg ) - 1, TEXT( "WM_LBUTTONDOWN (%d,%d)" ), GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
//            _tcsncpy( szMsg, TEXT( "WM_LBUTTONDOWN" ),     Dim( szMsg ) - 1 );
            break;

        }

        case WM_LBUTTONUP:         _tcsncpy( szMsg, TEXT( "WM_LBUTTONUP" ),       Dim( szMsg ) - 1 ); break;
        case WM_MBUTTONDBLCLK:     _tcsncpy( szMsg, TEXT( "WM_MBUTTONDBLCLK" ),   Dim( szMsg ) - 1 ); break;
        case WM_MBUTTONDOWN:       _tcsncpy( szMsg, TEXT( "WM_MBUTTONDOWN" ),     Dim( szMsg ) - 1 ); break;
        case WM_MBUTTONUP:         _tcsncpy( szMsg, TEXT( "WM_MBUTTONUP" ),       Dim( szMsg ) - 1 ); break;

#ifndef _WIN32_WCE

        case WM_MOUSEMOVE: {       _tcsncpy( szMsg, TEXT( "WM_MOUSEMOVE" ),       Dim( szMsg ) - 1 );

            const TCHAR * pszCode = GetMKAttribs( wParam );

            TCHAR szCrackMsg[1024];

            memset( szCrackMsg, 0, sizeof( szCrackMsg ) );

            _sntprintf( szCrackMsg, Dim( szCrackMsg ) - 1, TEXT( " %s (%d,%d)" ), pszCode, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

            _tcsncat( szMsg, szCrackMsg, Dim( szMsg ) - 1 );

            }
            break;

        case WM_NCCREATE:          _tcsncpy( szMsg, TEXT( "WM_NCCREATE" ),        Dim( szMsg ) - 1 ); break;
        case WM_NCHITTEST:         _tcsncpy( szMsg, TEXT( "WM_NCHITTEST" ),       Dim( szMsg ) - 1 ); break;
        case WM_NCLBUTTONDBLCLK:   _tcsncpy( szMsg, TEXT( "WM_NCLBUTTONDBLCLK" ), Dim( szMsg ) - 1 ); break;
        case WM_NCLBUTTONDOWN:     _tcsncpy( szMsg, TEXT( "WM_NCLBUTTONDOWN" ),   Dim( szMsg ) - 1 ); break;
        case WM_NCLBUTTONUP:       _tcsncpy( szMsg, TEXT( "WM_NCLBUTTONUP" ),     Dim( szMsg ) - 1 ); break;
        case WM_NCMBUTTONDBLCLK:   _tcsncpy( szMsg, TEXT( "WM_NCMBUTTONDBLCLK" ), Dim( szMsg ) - 1 ); break;
        case WM_NCMBUTTONDOWN:     _tcsncpy( szMsg, TEXT( "WM_NCMBUTTONDOWN" ),   Dim( szMsg ) - 1 ); break;
        case WM_NCMBUTTONUP:       _tcsncpy( szMsg, TEXT( "WM_NCMBUTTONUP" ),     Dim( szMsg ) - 1 ); break;

        case WM_NCMOUSEMOVE: {     _tcsncpy( szMsg, TEXT( "WM_NCMOUSEMOVE" ),     Dim( szMsg ) - 1 );

            const TCHAR * pszCode = GetHitCode( (int)wParam );

            TCHAR szCrackMsg[1024];

            memset( szCrackMsg, 0, sizeof( szCrackMsg ) );

            _sntprintf( szCrackMsg, Dim( szCrackMsg ) - 1, TEXT( " hit: %s (%d,%d)" ), pszCode, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

            _tcsncat( szMsg, szCrackMsg, Dim( szMsg ) - 1 );

            }
            break;

        case WM_NCPAINT:           _tcsncpy( szMsg, TEXT( "WM_NCPAINT" ),         Dim( szMsg ) - 1 ); break;
        case WM_NCRBUTTONDBLCLK:   _tcsncpy( szMsg, TEXT( "WM_NCRBUTTONDBLCLK" ), Dim( szMsg ) - 1 ); break;
        case WM_NCRBUTTONDOWN:     _tcsncpy( szMsg, TEXT( "WM_NCRBUTTONDOWN" ),   Dim( szMsg ) - 1 ); break;
        case WM_NCRBUTTONUP:       _tcsncpy( szMsg, TEXT( "WM_NCRBUTTONUP" ),     Dim( szMsg ) - 1 ); break;
        case WM_NCXBUTTONDOWN:     _tcsncpy( szMsg, TEXT( "WM_NCXBUTTONDOWN" ),   Dim( szMsg ) - 1 ); break;
        case WM_NCXBUTTONDBLCLK:   _tcsncpy( szMsg, TEXT( "WM_NCXBUTTONDBLCLK" ), Dim( szMsg ) - 1 ); break;

#endif

        case WM_NULL:              _tcsncpy( szMsg, TEXT( "WM_NULL" ),            Dim( szMsg ) - 1 ); break;
        case WM_PAINT:             _tcsncpy( szMsg, TEXT( "WM_PAINT" ),           Dim( szMsg ) - 1 ); break;
        case WM_POWERBROADCAST:    _tcsncpy( szMsg, TEXT( "WM_POWERBROADCAST" ),  Dim( szMsg ) - 1 ); break;
        case WM_QUIT:              _tcsncpy( szMsg, TEXT( "WM_QUIT" ),            Dim( szMsg ) - 1 ); break;
        case WM_RBUTTONDBLCLK:     _tcsncpy( szMsg, TEXT( "WM_RBUTTONDBLCLK" ),   Dim( szMsg ) - 1 ); break;
        case WM_RBUTTONDOWN:       _tcsncpy( szMsg, TEXT( "WM_RBUTTONDOWN" ),     Dim( szMsg ) - 1 ); break;
        case WM_RBUTTONUP:         _tcsncpy( szMsg, TEXT( "WM_RBUTTONUP" ),       Dim( szMsg ) - 1 ); break;
        case WM_SETFOCUS:          _tcsncpy( szMsg, TEXT( "WM_SETFOCUS" ),        Dim( szMsg ) - 1 ); break;
        case WM_SETREDRAW:         _tcsncpy( szMsg, TEXT( "WM_SETREDRAW" ),       Dim( szMsg ) - 1 ); break;
        case WM_SETTEXT:           _tcsncpy( szMsg, TEXT( "WM_SETTEXT" ),         Dim( szMsg ) - 1 ); break;
        case WM_SETTINGCHANGE:     _tcsncpy( szMsg, TEXT( "WM_SETTINGCHANGE" ),   Dim( szMsg ) - 1 ); break;
        case WM_SYSKEYDOWN:        _tcsncpy( szMsg, TEXT( "WM_SYSKEYDOWN" ),      Dim( szMsg ) - 1 ); break;
        case WM_SYSKEYUP:          _tcsncpy( szMsg, TEXT( "WM_SYSKEYUP" ),        Dim( szMsg ) - 1 ); break;

#ifdef WM_SYSTEMERROR
        case WM_SYSTEMERROR:       _tcsncpy( szMsg, TEXT( "WM_SYSTEMERROR" ),     Dim( szMsg ) - 1 ); break;
#endif

        case WM_TIMER:             _tcsncpy( szMsg, TEXT( "WM_TIMER" ),           Dim( szMsg ) - 1 ); break;
        case WM_VSCROLL:           _tcsncpy( szMsg, TEXT( "WM_VSCROLL" ),         Dim( szMsg ) - 1 ); break;

#endif

#if defined( WIN32 ) && ( ! defined( _WIN32_WCE ) )

        case WM_CONTEXTMENU:       _tcsncpy( szMsg, TEXT( "WM_CONTEXTMENU" ), Dim( szMsg ) - 1 ); break;
        case WM_DEVMODECHANGE:     _tcsncpy( szMsg, TEXT( "WM_DEVMODECHANGE" ), Dim( szMsg ) - 1 ); break;
        case WM_TIMECHANGE:        _tcsncpy( szMsg, TEXT( "WM_TIMECHANGE" ), Dim( szMsg ) - 1 ); break;
        case WM_PENWINFIRST:       _tcsncpy( szMsg, TEXT( "WM_PENWINFIRST" ), Dim( szMsg ) - 1 ); break;
        case WM_PENWINLAST:        _tcsncpy( szMsg, TEXT( "WM_PENWINLAST" ), Dim( szMsg ) - 1 ); break;
        case WM_POWER:             _tcsncpy( szMsg, TEXT( "WM_POWER" ), Dim( szMsg ) - 1 ); break;
        case WM_QUERYENDSESSION:   _tcsncpy( szMsg, TEXT( "WM_QUERYENDSESSION" ), Dim( szMsg ) - 1 ); break;
        case WM_ENDSESSION:        _tcsncpy( szMsg, TEXT( "WM_ENDSESSION" ), Dim( szMsg ) - 1 ); break;
        case WM_NCDESTROY:         _tcsncpy( szMsg, TEXT( "WM_NCDESTROY" ), Dim( szMsg ) - 1 ); break;
        case WM_WINDOWPOSCHANGING: _tcsncpy( szMsg, TEXT( "WM_WINDOWPOSCHANGING" ), Dim( szMsg ) - 1 ); break;
        case WM_QUERYOPEN:         _tcsncpy( szMsg, TEXT( "WM_QUERYOPEN" ), Dim( szMsg ) - 1 ); break;
        case WM_GETMINMAXINFO:     _tcsncpy( szMsg, TEXT( "WM_GETMINMAXINFO" ), Dim( szMsg ) - 1 ); break;
        case WM_ICONERASEBKGND:    _tcsncpy( szMsg, TEXT( "WM_ICONERASEBKGND" ), Dim( szMsg ) - 1 ); break;
        case WM_NCCALCSIZE:        _tcsncpy( szMsg, TEXT( "WM_NCCALCSIZE" ), Dim( szMsg ) - 1 ); break;
        case WM_DROPFILES:         _tcsncpy( szMsg, TEXT( "WM_DROPFILES" ), Dim( szMsg ) - 1 ); break;
        case WM_ACTIVATEAPP:       _tcsncpy( szMsg, TEXT( "WM_ACTIVATEAPP" ), Dim( szMsg ) - 1 ); break;

//      case WM_NCACTIVATE:        _tcsncpy( szMsg, TEXT( "WM_NCACTIVATE" ), Dim( szMsg ) - 1 ); break;

        case WM_MOUSEACTIVATE:     _tcsncpy( szMsg, TEXT( "WM_MOUSEACTIVATE" ), Dim( szMsg ) - 1 ); break;
        case WM_INITMENU:          _tcsncpy( szMsg, TEXT( "WM_INITMENU" ), Dim( szMsg ) - 1 ); break;
        case WM_MENUSELECT:        _tcsncpy( szMsg, TEXT( "WM_MENUSELECT" ), Dim( szMsg ) - 1 ); break;
        case WM_DRAWCLIPBOARD:     _tcsncpy( szMsg, TEXT( "WM_DRAWCLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_PAINTCLIPBOARD:    _tcsncpy( szMsg, TEXT( "WM_PAINTCLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_CTLCOLORBTN:       _tcsncpy( szMsg, TEXT( "WM_CTLCOLORBTN" ), Dim( szMsg ) - 1 ); break;
        case WM_CTLCOLORSTATIC:    _tcsncpy( szMsg, TEXT( "WM_CTLCOLORSTATIC" ), Dim( szMsg ) - 1 ); break;
        case WM_SHOWWINDOW:        _tcsncpy( szMsg, TEXT( "WM_SHOWWINDOW" ), Dim( szMsg ) - 1 ); break;
        case WM_SIZECLIPBOARD:     _tcsncpy( szMsg, TEXT( "WM_SIZECLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_VSCROLLCLIPBOARD:  _tcsncpy( szMsg, TEXT( "WM_VSCROLLCLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_HSCROLLCLIPBOARD:  _tcsncpy( szMsg, TEXT( "WM_HSCROLLCLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_ASKCBFORMATNAME:   _tcsncpy( szMsg, TEXT( "WM_ASKCBFORMATNAME" ), Dim( szMsg ) - 1 ); break;
        case WM_CHANGECBCHAIN:     _tcsncpy( szMsg, TEXT( "WM_CHANGECBCHAIN" ), Dim( szMsg ) - 1 ); break;
        case WM_MDICREATE:         _tcsncpy( szMsg, TEXT( "WM_MDICREATE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIDESTROY:        _tcsncpy( szMsg, TEXT( "WM_MDIDESTROY" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIACTIVATE:       _tcsncpy( szMsg, TEXT( "WM_MDIACTIVATE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIRESTORE:        _tcsncpy( szMsg, TEXT( "WM_MDIRESTORE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDINEXT:           _tcsncpy( szMsg, TEXT( "WM_MDINEXT" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIMAXIMIZE:       _tcsncpy( szMsg, TEXT( "WM_MDIMAXIMIZE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDITILE:           _tcsncpy( szMsg, TEXT( "WM_MDITILE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDICASCADE:        _tcsncpy( szMsg, TEXT( "WM_MDICASCADE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIICONARRANGE:    _tcsncpy( szMsg, TEXT( "WM_MDIICONARRANGE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDIGETACTIVE:      _tcsncpy( szMsg, TEXT( "WM_MDIGETACTIVE" ), Dim( szMsg ) - 1 ); break;
        case WM_MDISETMENU:        _tcsncpy( szMsg, TEXT( "WM_MDISETMENU" ), Dim( szMsg ) - 1 ); break;
        case WM_CHILDACTIVATE:     _tcsncpy( szMsg, TEXT( "WM_CHILDACTIVATE" ), Dim( szMsg ) - 1 ); break;
        case WM_PARENTNOTIFY:      _tcsncpy( szMsg, TEXT( "WM_PARENTNOTIFY" ), Dim( szMsg ) - 1 ); break;
        case WM_ENTERIDLE:         _tcsncpy( szMsg, TEXT( "WM_ENTERIDLE" ), Dim( szMsg ) - 1 ); break;
        case WM_QUEUESYNC:         _tcsncpy( szMsg, TEXT( "WM_QUEUESYNC" ), Dim( szMsg ) - 1 ); break;

#endif /* WIN32 but NOT _WIN32_WCE */

#ifdef _WIN32

        case WM_QUERYNEWPALETTE:   _tcsncpy( szMsg, TEXT( "WM_QUERYNEWPALETTE" ), Dim( szMsg ) - 1 ); break;
        case WM_QUERYUISTATE:      _tcsncpy( szMsg, TEXT( "WM_QUERYUISTATE" ), Dim( szMsg ) - 1 ); break;
        case WM_CAPTURECHANGED:    _tcsncpy( szMsg, TEXT( "WM_CAPTURECHANGED" ), Dim( szMsg ) - 1 ); break;
        case WM_CTLCOLORDLG:       _tcsncpy( szMsg, TEXT( "WM_CTLCOLORDLG" ), Dim( szMsg ) - 1 ); break;
        case WM_CTLCOLOREDIT:      _tcsncpy( szMsg, TEXT( "WM_CTLCOLOREDIT" ), Dim( szMsg ) - 1 ); break;
        case WM_SETICON:           _tcsncpy( szMsg, TEXT( "WM_SETICON" ), Dim( szMsg ) - 1 ); break;
        case WM_UPDATEUISTATE:     _tcsncpy( szMsg, TEXT( "WM_UPDATEUISTATE" ), Dim( szMsg ) - 1 ); break;
        case WM_GETTEXT:           _tcsncpy( szMsg, TEXT( "WM_GETTEXT" ), Dim( szMsg ) - 1 ); break;
        case WM_GETTEXTLENGTH:     _tcsncpy( szMsg, TEXT( "WM_GETTEXTLENGTH" ), Dim( szMsg ) - 1 ); break;
        case WM_WINDOWPOSCHANGED:  _tcsncpy( szMsg, TEXT( "WM_WINDOWPOSCHANGED" ), Dim( szMsg ) - 1 ); break;
        case WM_MOVE:              _tcsncpy( szMsg, TEXT( "WM_MOVE" ), Dim( szMsg ) - 1 ); break;
        case WM_SIZE:              _tcsncpy( szMsg, TEXT( "WM_SIZE" ), Dim( szMsg ) - 1 ); break;
        case WM_QUERYDRAGICON:     _tcsncpy( szMsg, TEXT( "WM_QUERYDRAGICON" ), Dim( szMsg ) - 1 ); break;
        case WM_ACTIVATE:          _tcsncpy( szMsg, TEXT( "WM_ACTIVATE" ), Dim( szMsg ) - 1 ); break;
        case WM_DEADCHAR:          _tcsncpy( szMsg, TEXT( "WM_DEADCHAR" ), Dim( szMsg ) - 1 ); break;
        case WM_SYSCHAR:           _tcsncpy( szMsg, TEXT( "WM_SYSCHAR" ), Dim( szMsg ) - 1 ); break;
        case WM_SYSDEADCHAR:       _tcsncpy( szMsg, TEXT( "WM_SYSDEADCHAR" ), Dim( szMsg ) - 1 ); break;
        case WM_CANCELMODE:        _tcsncpy( szMsg, TEXT( "WM_CANCELMODE" ), Dim( szMsg ) - 1 ); break;
        case WM_INITMENUPOPUP:     _tcsncpy( szMsg, TEXT( "WM_INITMENUPOPUP" ), Dim( szMsg ) - 1 );  break;
        case WM_MENUCHAR:          _tcsncpy( szMsg, TEXT( "WM_MENUCHAR" ), Dim( szMsg ) - 1 ); break;
        case WM_CUT:               _tcsncpy( szMsg, TEXT( "WM_CUT" ), Dim( szMsg ) - 1 ); break;
        case WM_COPY:              _tcsncpy( szMsg, TEXT( "WM_COPY" ), Dim( szMsg ) - 1 ); break;
        case WM_PASTE:             _tcsncpy( szMsg, TEXT( "WM_PASTE" ), Dim( szMsg ) - 1 ); break;
        case WM_CLEAR:             _tcsncpy( szMsg, TEXT( "WM_CLEAR" ), Dim( szMsg ) - 1 ); break;
        case WM_UNDO:              _tcsncpy( szMsg, TEXT( "WM_UNDO" ), Dim( szMsg ) - 1 ); break;
        case WM_RENDERFORMAT:      _tcsncpy( szMsg, TEXT( "WM_RENDERFORMAT" ), Dim( szMsg ) - 1 ); break;
        case WM_RENDERALLFORMATS:  _tcsncpy( szMsg, TEXT( "WM_RENDERALLFORMATS" ), Dim( szMsg ) - 1 ); break;
        case WM_DESTROYCLIPBOARD:  _tcsncpy( szMsg, TEXT( "WM_DESTROYCLIPBOARD" ), Dim( szMsg ) - 1 ); break;
        case WM_SYSCOMMAND:        _tcsncpy( szMsg, TEXT( "WM_SYSCOMMAND" ), Dim( szMsg ) - 1 ); break;
        case WM_NEXTDLGCTL:        _tcsncpy( szMsg, TEXT( "WM_NEXTDLGCTL" ), Dim( szMsg ) - 1 ); break;
        case WM_GETDLGCODE:        _tcsncpy( szMsg, TEXT( "WM_GETDLGCODE" ), Dim( szMsg ) - 1 ); break;

//        case WM_CTLCOLOR:          _tcsncpy( szMsg, TEXT( "WM_CTLCOLOR" ), Dim( szMsg ) - 1 ); break;

        case WM_SETFONT:           _tcsncpy( szMsg, TEXT( "WM_SETFONT" ), Dim( szMsg ) - 1 ); break;
        case WM_GETFONT:           _tcsncpy( szMsg, TEXT( "WM_GETFONT" ), Dim( szMsg ) - 1 ); break;
        case WM_DRAWITEM:          _tcsncpy( szMsg, TEXT( "WM_DRAWITEM" ), Dim( szMsg ) - 1 ); break;
        case WM_MEASUREITEM:       _tcsncpy( szMsg, TEXT( "WM_MEASUREITEM" ), Dim( szMsg ) - 1 ); break;
        case WM_VKEYTOITEM:        _tcsncpy( szMsg, TEXT( "WM_VKEYTOITEM" ), Dim( szMsg ) - 1 ); break;
        case WM_CHARTOITEM:        _tcsncpy( szMsg, TEXT( "WM_CHARTOITEM" ), Dim( szMsg ) - 1 ); break;

        case WM_NOTIFY: {

                                    TCHAR szCrackMsg[1024];
                                    const TCHAR * pszCode;

                                    _tcsncpy( szMsg, TEXT( "WM_NOTIFY:" ), Dim( szMsg ) - 1 );

                                    int iCtlID = wParam;

                                    LPNMHDR lpNMHdr = (NMHDR *)lParam;

                                    switch( lpNMHdr->code ) {

                                        case TCN_SELCHANGE:

                                            pszCode = TEXT( "TCN_SELCHANGE" );
                                            break;

                                        case TCN_SELCHANGING:

                                            pszCode = TEXT( "TCN_SELCHANGING" );
                                            break;

                                        case NM_CHAR:

                                            pszCode = TEXT( "NM_CHAR" );
                                            break;

                                        case NM_CLICK:

                                            pszCode = TEXT( "NM_CLICK" );
                                            break;

                                        case NM_CUSTOMDRAW:

                                            pszCode = TEXT( "NM_CUSTOMDRAW" );
                                            break;

                                        //case NM_CUSTOMTEXT:

                                        //  pszCode = "NM_CUSTOMTEXT";
                                        //  break;

                                        //case NM_FONTCHANGED:

                                        //  pszCode = "NM_FONTCHANGED";
                                        //  break;

                                        //case NM_GETCUSTOMSPLITRECT:

                                        //  pszCode = "NM_GETCUSTOMSPLITRECT";
                                        //  break;

                                        case NM_HOVER:

                                            pszCode = TEXT( "NM_HOVER" );
                                            break;

                                        case NM_KEYDOWN:

                                            pszCode = TEXT( "NM_KEYDOWN" );
                                            break;

                                        case NM_KILLFOCUS:

                                            pszCode = TEXT( "NM_KILLFOCUS" );
                                            break;

                                        //case NM_LDOWN:

                                        //  pszCode = "NM_LDOWN";
                                        //  break;

                                        case NM_NCHITTEST:

                                            pszCode = TEXT( "NM_NCHITTEST" );
                                            break;

                                        case NM_OUTOFMEMORY:

                                            pszCode = TEXT( "NM_OUTOFMEMORY" );
                                            break;

                                        //case NM_RDOWN:

                                        //  pszCode = "NM_RDOWN";
                                        //  break;

                                        case NM_RELEASEDCAPTURE:

                                            pszCode = TEXT( "NM_RELEASEDCAPTURE" );
                                            break;

                                        case NM_RETURN:

                                            pszCode = TEXT( "NM_RETURN" );
                                            break;

                                        case NM_SETCURSOR:

                                            pszCode = TEXT( "NM_SETCURSOR" );
                                            break;

                                        case NM_SETFOCUS:

                                            pszCode = TEXT( "NM_SETFOCUS" );
                                            break;

                                        //case NM_THEMECHANGED:

                                        //  pszCode = "NM_THEMECHANGED";
                                        //  break;

                                        case NM_TOOLTIPSCREATED:

                                            pszCode = TEXT( "NM_TOOLTIPSCREATED" );
                                            break;

                                        //case NM_TVSTATEIMAGECHANGING:

                                        //  pszCode = "NM_TVSTATEIMAGECHANGING";
                                        //  break;

                                        default:

                                            pszCode = TEXT( "UNKNOWN" );
                                            break;


                                    }

                                    wsprintf( szCrackMsg, TEXT( "CtlID %d: code %s" ), iCtlID, pszCode );
                                    _tcsncat( szMsg, szCrackMsg, Dim( szMsg ) - 1 );

                                                                                                } break;

        case WM_IME_SETCONTEXT:    _tcsncpy( szMsg, TEXT( "WM_IME_SETCONTEXT" ), Dim( szMsg ) - 1 ); break;
        case WM_IME_NOTIFY:        _tcsncpy( szMsg, TEXT( "WM_IME_NOTIFY" ),     Dim( szMsg ) - 1 ); break;
        case WM_NCACTIVATE:        _tcsncpy( szMsg, TEXT( "WM_NCACTIVATE" ),     Dim( szMsg ) - 1 ); break;
        case WM_SETCURSOR:         _tcsncpy( szMsg, TEXT( "WM_SETCURSOR" ),      Dim( szMsg ) - 1 ); break;

#endif /* _WIN32 */

        default:

            memset( szMsg, 0, sizeof( szMsg ) );

            if ( ( uiMsg >= WM_USER ) && ( uiMsg <= 0x7FFF ) ) {

                _sntprintf( szMsg, Dim( szMsg ) - 1, TEXT( "WM_USER + 0x%lX" ), (long unsigned)( uiMsg - WM_USER ) );

            } else if ( ( uiMsg >= WM_APP ) && ( uiMsg <= 0xBFFF ) ) {

                _sntprintf( szMsg, Dim( szMsg ) - 1, TEXT( "WM_APP + 0x%lX" ), (long unsigned)( uiMsg - WM_APP ) );

            } else {

                _sntprintf( szMsg, Dim( szMsg ) - 1, TEXT( "WM_UNKNOWN (0x%04lX)" ), (long unsigned)uiMsg );

            }

    }

    memset( szMsgParams, 0, sizeof( szMsgParams ) );

    if ( 0 == lNest ) {

        _sntprintf( szMsgParams, Dim( szMsgParams ) - 1, TEXT( "%s%llX %s %lX %lX" ), NULL == pszPrefix ? TEXT( "" ) : pszPrefix, (long long)hWnd, (TCHAR *)szMsg, (long)wParam, (long)lParam );

    } else {

        _sntprintf( szMsgParams, Dim( szMsgParams ) - 1, TEXT( "(%lX)-> %s%llX %s %lX %lX" ), (long)lNest, NULL == pszPrefix ? TEXT( "" ) : pszPrefix, (long long)hWnd, (TCHAR *)szMsg, (long)wParam, (long)lParam );

    }

    DBG_TRACE( uLineNo, pszFile, dwDebugChannelsBitmap, szMsgParams );

}
