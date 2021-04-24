#ifndef __KEYMOUSE_H__
#define __KEYMOUSE_H__


#include <cstring>
#include <map>
#include <sys/ioctl.h>
#include <unistd.h>


#include <ASCII.h>
#include <tstring.h>



#include "eventq.h"


static std::map<std::basic_string<char>,class VirtualKey *> vk_list;


class VirtualKey {

    public:

        VirtualKey( std::basic_string<char> escape_sequence, std::map<std::basic_string<char>,class VirtualKey *> * pMap, const TCHAR * pszName, UINT key ) {

            pMap->insert( std::pair<std::basic_string<char>,class VirtualKey *>( escape_sequence, this ) );

            name.assign( pszName );
            vkey = key;

        }

        const TCHAR * GetName() {

            return name.c_str();

        }

        UINT GetVKey() {

            return vkey;

        }

    private:

        TSTRING     name;
        UINT        vkey;

};


static const VirtualKey

    vk_backtab( "\x5B\x5A",         &vk_list, TEXT( "VK_BACKTAB" ), VK_BACKTAB ),

    vk_f1(      "\x4F\x50",         &vk_list, TEXT( "VK_F1" ),      VK_F1      ),
    vk_f2(      "\x4F\x51",         &vk_list, TEXT( "VK_F2" ),      VK_F2      ),
    vk_f3(      "\x4F\x52",         &vk_list, TEXT( "VK_F3" ),      VK_F3      ),
    vk_f4(      "\x4F\x53",         &vk_list, TEXT( "VK_F4" ),      VK_F4      ),

    vk_f5(      "\x5B\x31\x35\x7E", &vk_list, TEXT( "VK_F5" ),      VK_F5      ),
    vk_f6(      "\x5B\x31\x37\x7E", &vk_list, TEXT( "VK_F6" ),      VK_F6      ),
    vk_f7(      "\x5B\x31\x38\x7E", &vk_list, TEXT( "VK_F7" ),      VK_F7      ),
    vk_f8(      "\x5B\x31\x39\x7E", &vk_list, TEXT( "VK_F8" ),      VK_F8      ),

    vk_f9(      "\x5B\x32\x30\x7E", &vk_list, TEXT( "VK_F9" ),      VK_F9      ),
    vk_f10(     "\x5B\x32\x31\x7E", &vk_list, TEXT( "VK_F10" ),     VK_F10     ),
    vk_f11(     "\x5B\x32\x33\x7E", &vk_list, TEXT( "VK_F11" ),     VK_F11     ),
    vk_f12(     "\x5B\x32\x34\x7E", &vk_list, TEXT( "VK_F12" ),     VK_F12     ),

    vk_insert(  "\x5B\x32\x7E",     &vk_list, TEXT( "VK_INSERT" ),  VK_INSERT  ),
    vk_delete(  "\x5B\x33\x7E",     &vk_list, TEXT( "VK_DELETE" ),  VK_DELETE  ),

    vk_home(    "\x5B\x48",         &vk_list, TEXT( "VK_HOME" ),    VK_HOME    ),
    vk_end(     "\x5B\x46",         &vk_list, TEXT( "VK_END" ),     VK_END     ),

    vk_prior(   "\x5B\x35\x7E",     &vk_list, TEXT( "VK_PRIOR" ),   VK_PRIOR   ),
    vk_next(    "\x5B\x36\x7E",     &vk_list, TEXT( "VK_NEXT" ),    VK_NEXT    ),

    vk_up(      "\x5B\x41",         &vk_list, TEXT( "VK_UP" ),      VK_UP      ),
    vk_left(    "\x5B\x44",         &vk_list, TEXT( "VK_LEFT" ),    VK_LEFT    ),
    vk_down(    "\x5B\x42",         &vk_list, TEXT( "VK_DOWN" ),    VK_DOWN    ),
    vk_right(   "\x5B\x43",         &vk_list, TEXT( "VK_RIGHT" ),   VK_RIGHT   ),

    vk_numpad5( "\x5B\x45",         &vk_list, TEXT( "VK_NUMPAD5" ), VK_NUMPAD5 )


//    vk_shift_insert( "\x6C\x6C\x6F",         &vk_list, TEXT( "VK_SHIFT_INSERT" ), VK_SHIFT_INSERT )

;

#define LENGTH_OF_TYPICAL_CURSOR_POS_UPDATE 5

#if 0

// Top-left (0,0)     5B 4D 20 21 21                [M !!
// Bottom-right       5B 4D 20 DD 52                [M ÝR

// NORTHWEST ARROW    5B 31 7E                      [1~
// SOUTHWEST ARROW    5B 34 7E                      [4~

#endif


class KeyMouse : public Handler {

    public:

        KeyMouse( EventQ * pThreadEventQ, SOCKET session ) : Handler( session, pThreadEventQ ) {

        }


        bool EventHandler() override {

            char    c;
            int     iRet;
            int     iInQ = 0;

            /* iRet = */ ioctl( getsocket(), FIONREAD, &iInQ );

            if ( 1 > iInQ ) {

                DBG_MSG( DBG_ERROR, TEXT( "Keyboard input queue hosed" ) );
                return false;

            }

            if ( 1 < iInQ ) {

                DBG_MSG( DBG_CONSOLE, TEXT( "Multiple key input %u" ), (unsigned)iInQ );

            }

            iRet = read( getsocket(), &c, sizeof( c ) );

            if ( sizeof( c ) != iRet ) {

                DBG_MSG( DBG_ERROR, TEXT( "Error reading stdin" ) );
                return false;

            }

            char EscapeSequence[7];

            if ( ( 1 == iInQ ) || (! ( iInQ <= ( (int)sizeof( EscapeSequence ) - 1 ) ) ) ) {

                switch( c ) {

                    case CARRIAGERETURN:

                        FORWARD_WM_KEYDOWN( NULL, VK_RETURN, 0, 0, PostMessage );
                        break;

                    case DEL:

                        FORWARD_WM_KEYDOWN( NULL, VK_BACK, 0, 0, PostMessage );
                        break;

                    case ESC:

                        FORWARD_WM_KEYDOWN( NULL, VK_ESCAPE, 0, 0, PostMessage );
                        break;

                    case ' ':

                        FORWARD_WM_KEYDOWN( NULL, VK_SPACE, 0, 0, PostMessage );
                        break;

                    case TAB:

                        FORWARD_WM_KEYDOWN( NULL, VK_TAB, 0, 0, PostMessage );
                        break;

                    default:

                        FORWARD_WM_CHAR( NULL, c, 0, PostMessage );
                        break;

                }

                return true;

            }

            /* Find the escape sequence and convert to virtual keys */

            if ( ! ( iInQ <= ( (int)sizeof( EscapeSequence ) - 1 ) ) ) {

                /* punt */
                DBG_MSG( DBG_ERROR, TEXT( "Keyboard events overflowing" ) );
                return true;

            }

            ZeroMemory( EscapeSequence, sizeof( EscapeSequence ) );
            iRet = read( getsocket(), EscapeSequence, sizeof( EscapeSequence ) - 1 );

            if ( 1 > iRet ) {

                DBG_MSG( DBG_ERROR, TEXT( "ERROR READING ESCAPE SEQUENCE (%d)" ), iRet );
                return true;

            }

            if ( 1 == iRet  ) {

                DBG_MSG( DBG_CONSOLE, TEXT( "ALT-%c" ), EscapeSequence[0] );
                FORWARD_WM_SYSKEYDOWN( NULL, VK_MENU,           0, 0, PostMessage );
                FORWARD_WM_SYSKEYDOWN( NULL, EscapeSequence[0], 0, 0, PostMessage );
                FORWARD_WM_SYSKEYUP(   NULL, EscapeSequence[0], 0, 0, PostMessage );
                FORWARD_WM_KEYUP(      NULL, VK_MENU,           0, 0, PostMessage );
                return true;

            }

            if ( ( LENGTH_OF_TYPICAL_CURSOR_POS_UPDATE == iRet ) && ( '[' == EscapeSequence[0] ) ) {

                switch( EscapeSequence[1] ) {

                    case '1':

                        DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-something %c,%c,%c" ), EscapeSequence[2], EscapeSequence[3], EscapeSequence[4] );

                        if ( ( ';' == EscapeSequence[2] ) && ( '2' == EscapeSequence[3] ) ) {

                            switch( EscapeSequence[4] ) {

                                case 'A': DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-UP ARROW" ) );

                                    FORWARD_WM_KEYDOWN( NULL, VK_SHIFT, 0, 0, PostMessage );
                                    FORWARD_WM_KEYDOWN( NULL, VK_UP,    0, 0, PostMessage );
                                    FORWARD_WM_KEYUP(   NULL, VK_SHIFT, 0, 0, PostMessage );
                                    break;

                                case 'B': DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-DOWN ARROW" ) );

                                    FORWARD_WM_KEYDOWN( NULL, VK_SHIFT, 0, 0, PostMessage );
                                    FORWARD_WM_KEYDOWN( NULL, VK_DOWN,  0, 0, PostMessage );
                                    FORWARD_WM_KEYUP(   NULL, VK_SHIFT, 0, 0, PostMessage );
                                    break;

                                case 'C': DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-RIGHT ARROW" ) );

                                    FORWARD_WM_KEYDOWN( NULL, VK_SHIFT, 0, 0, PostMessage );
                                    FORWARD_WM_KEYDOWN( NULL, VK_RIGHT, 0, 0, PostMessage );
                                    FORWARD_WM_KEYUP(   NULL, VK_SHIFT, 0, 0, PostMessage );
                                    break;

                                case 'D': DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-LEFT ARROW" ) );

                                    FORWARD_WM_KEYDOWN( NULL, VK_SHIFT, 0, 0, PostMessage );
                                    FORWARD_WM_KEYDOWN( NULL, VK_LEFT,  0, 0, PostMessage );
                                    FORWARD_WM_KEYUP(   NULL, VK_SHIFT, 0, 0, PostMessage );
                                    break;

                            }

                        }

                        DBG_MSG( DBG_CONSOLE, TEXT( "SHIFT-something LOST %c,%c,%c" ), EscapeSequence[2], EscapeSequence[3], EscapeSequence[4] );
                        break;

                    case 'M':

                        int x = EscapeSequence[3] - 33, y = EscapeSequence[4] - 33;

                        if ( 0 > x ) {

                            x = ( 160 + x ) + 96;

                        }

                        switch( EscapeSequence[2] ) {

                            case ' ':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Left-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_LBUTTON, MK_LBUTTON );
                                break;

                            case '!':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Middle-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_MBUTTON, MK_MBUTTON );
                                break;

                            case '"':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Right-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_RBUTTON, MK_RBUTTON );
                                break;

                            case '0':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Ctrl Left-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_LBUTTON, MK_CONTROL | MK_LBUTTON );
                                break;

                            case '1':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Ctrl Middle-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_MBUTTON, MK_CONTROL | MK_MBUTTON );
                                break;

                            case '2':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Ctrl Right-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_RBUTTON, MK_CONTROL | MK_RBUTTON );
                                break;

                            case '&':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Shift Right-click (%d,%d)" ), x, y );
                                pQ->PostMouseMsg( false, x, y, VK_RBUTTON, MK_SHIFT | MK_RBUTTON );
                                break;

                            case '`':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Middle mouse-button scroll up (%d,%d)" ), x, y );
                                FORWARD_WM_KEYDOWN( NULL, VK_UP, 0, 0, PostMessage );
                                break;

                            case 'a':

                                DBG_MSG( DBG_CONSOLE, TEXT( "Middle mouse-button scroll down (%d,%d)" ), x, y );
                                FORWARD_WM_KEYDOWN( NULL, VK_DOWN, 0, 0, PostMessage );
                                break;

                            default:

                                DBG_MSG( DBG_ERROR, TEXT( "UKNOWN CLICK-IDENTIFIER 0x%X (%d,%d)" ), EscapeSequence[2], x, y );
                                break;

                        }

                        break;

                }

                return true;

            }

            const std::map<std::basic_string<char>,class VirtualKey *>::iterator Item = vk_list.find( EscapeSequence );

            if ( vk_list.end() == Item ) {

                DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN CONSOLE ESCAPE SEQUENCE" ) );
                DBG_DMP( DBG_ERROR, EscapeSequence, iRet );
                return true;

            }

            DBG_MSG( DBG_CONSOLE, TEXT( "Virtual key %s (%X) generated" ), Item->second->GetName(), Item->second->GetVKey() );

/*
            switch( uiVKey ) {

                case VK_F1:
                case VK_F2:
                case VK_F3:
                case VK_F4:

                case VK_F5:
                case VK_F6:
                case VK_F7:
                case VK_F8:

                case VK_F9:
                case VK_F10:
                case VK_F11:
                case VK_F12:

                    ;

            }
*/

            FORWARD_WM_KEYDOWN( NULL, Item->second->GetVKey(), 0, 0, PostMessage );
            return true;

        }

};


#endif  /* __KEYMOUSE_H__ */
