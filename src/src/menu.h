#ifndef YW_MENU_H
#define YW_MENU_H


#include <windows.h>
#include <tstring.h>
#include "resource.h"


/*
Menu Resources

Menu resources are composed of a menu header followed by a sequential
list of menu items.  There are two types of menu items:  popups and
normal menu items.  The MENUITEM SEPARATOR is a special case of a
normal menu item with an empty name, zero ID, and zero flags. The
format for these types is shown here:

    [Resource header (type = 4)]

struct MenuHeader {
  WORD   wVersion;           // Currently zero
  WORD   cbHeaderSize;       // Also zero
};

These next items are repeated for every menu item.

Popup menu items (signalled by fItemFlags & POPUP):

struct PopupMenuItem {
  WORD   fItemFlags;
  WCHAR  szItemText[];
};

Normal menu items (signalled by !(fItemFlags & POPUP)):

struct NormalMenuItem {
  WORD   fItemFlags;
  WORD   wMenuID;
  WCHAR  szItemText[];
};

The wVersion and cbHeaderSize structure members identify the version
of the menu template.  They are both zero for Windows 3.0 but may be
incremented with future changes to the menu template.

The WORD fItemFlags is a set of flags describing the menu item.  If
the POPUP bit is set, the item is a POPUP.  Otherwise, it is a normal
menu component.  There are several other flag bits that may be set.
Their values are as follows:

    #define    GRAYED         0x0001   // 'GRAYED' keyword
    #define    INACTIVE       0x0002   // 'INACTIVE' keyword
    #define    BITMAP         0x0004   // 'BITMAP' keyword
    #define    OWNERDRAW      0x0100   // 'OWNERDRAW' keyword
    #define    CHECKED        0x0008   // 'CHECKED' keyword
    #define    POPUP          0x0010   // Used internally
    #define    MENUBARBREAK   0x0020   // 'MENUBARBREAK' keyword
    #define    MENUBREAK      0x0040   // 'MENUBREAK' keyword
    #define    ENDMENU        0x0080   // Used internally

The fItemFlags portion of the last menu item in a given POPUP is
flagged by OR'ing it with ENDMENU.  It is important to note that
since popups can be nested, there may be multiple levels of items
with ENDMENU set.  When menus are nested, the items are inserted
sequentially.  A program can traverse this hierarchy by checking for
the item with the ENDMENU flag set.
*/


#define    GRAYED         0x0001   // 'GRAYED' keyword
#define    INACTIVE       0x0002   // 'INACTIVE' keyword
#define    BITMAP         0x0004   // 'BITMAP' keyword
#define    CHECKED        0x0008   // 'CHECKED' keyword
#define    POPUP          0x0010   // Used internally
#define    MENUBARBREAK   0x0020   // 'MENUBARBREAK' keyword
#define    MENUBREAK      0x0040   // 'MENUBREAK' keyword
#define    ENDMENU        0x0080   // Used internally
#define    OWNERDRAW      0x0100   // 'OWNERDRAW' keyword


typedef struct __attribute__ ((__packed__)) {

    WORD wVersion;     // Currently zero
    WORD cbHeaderSize; // Also zero

} MENUHEADER;


typedef struct __attribute__ ((__packed__)) {

    WORD  fItemFlags;

} POPUPMENUITEM;


typedef struct __attribute__ ((__packed__)) {

    WORD  fItemFlags;
    WORD  wMenuID;
    WCHAR szItemText[];

} NORMALMENUITEM;


typedef struct __attribute__ ((__packed__)) {

    POPUPMENUITEM  p;
    union {
    NORMALMENUITEM i1;
    WCHAR szItemText[0];
    };

} MENU_ITEMS;


typedef struct __attribute__ ((__packed__)) {

    MENUHEADER hdr;
    MENU_ITEMS items[];

} MENU_RESOURCE;



class Menu : public Object {


    public:


        Menu() : Object( OBJECT_TYPE_MENU ) {}


        virtual ~Menu() override {}



};


typedef struct {

    unsigned uType;
    unsigned uFlags;
    int      iID;
    TSTRING  Text;

} MENU_ITEM;


class MyMenu : public std::vector<MENU_ITEM> {


    public:

        MyMenu() {}

        ~MyMenu() {}

};


#endif /* YW_MENU_H */
