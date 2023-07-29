

#include "ywin.h"


#ifndef YOU_WIN_TXT

// GRAPHICAL
DECLARE_SYSTEM_COLOR( SysColor3DDkShadow,              COLOR_3DDKSHADOW,              RGB( 64, 64, 64),         "COLOR_3DDKSHADOW"              );
DECLARE_SYSTEM_COLOR( SysColor3DFace,                  COLOR_3DFACE,                  RGB(212,208,200),         "COLOR_3DFACE"                  );
DECLARE_SYSTEM_COLOR( SysColor3DHighLight,             COLOR_3DHIGHLIGHT,             RGB(255,255,255),         "COLOR_3DHIGHLIGHT"             );
DECLARE_SYSTEM_COLOR( SysColor3DLight,                 COLOR_3DLIGHT,                 RGB(212,208,200),         "COLOR_3DLIGHT"                 );
DECLARE_SYSTEM_COLOR( SysColor3DShadow,                COLOR_3DSHADOW,                RGB(128,128,128),         "COLOR_3DSHADOW"                );
DECLARE_SYSTEM_COLOR( SysColorInactiveCaptionText,     COLOR_INACTIVECAPTIONTEXT,     RGB(212,208,200),         "COLOR_INACTIVECAPTIONTEXT"     );
DECLARE_SYSTEM_COLOR( SysColorInfoBk,                  COLOR_INFOBK,                  RGB(255,255,255),         "COLOR_INFOBK"                  );
DECLARE_SYSTEM_COLOR( SysColorInfoText,                COLOR_INFOTEXT,                RGB(  0,  0,  0),         "COLOR_INFOTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorHotLight,                COLOR_HOTLIGHT,                RGB(  0,  0,128),         "COLOR_HOTLIGHT"                );
DECLARE_SYSTEM_COLOR( SysColorGradientActiveCaption,   COLOR_GRADIENTACTIVECAPTION,   RGB(166,202,240),         "COLOR_GRADIENTACTIVECAPTION"   );
DECLARE_SYSTEM_COLOR( SysColorGradientInactiveCaption, COLOR_GRADIENTINACTIVECAPTION, RGB(192,192,192),         "COLOR_GRADIENTINACTIVECAPTION" );
DECLARE_SYSTEM_COLOR( SysColorActiveBorder,            COLOR_ACTIVEBORDER,            RGB(212,208,200),         "COLOR_ACTIVEBORDER"            );
DECLARE_SYSTEM_COLOR( SysColorActiveCaption,           COLOR_ACTIVECAPTION,           RGB( 10, 36,106),         "COLOR_ACTIVECAPTION"           );
DECLARE_SYSTEM_COLOR( SysColorAppWorkspace,            COLOR_APPWORKSPACE,            RGB(128,128,128),         "COLOR_APPWORKSPACE"            );
DECLARE_SYSTEM_COLOR( SysColorBackground,              COLOR_BACKGROUND,              RGB( 58,110,165),         "COLOR_BACKGROUND"              );
DECLARE_SYSTEM_COLOR( SysColorBtnText,                 COLOR_BTNTEXT,                 RGB(  0,  0,  0),         "COLOR_BTNTEXT"                 );
DECLARE_SYSTEM_COLOR( SysColorCaptionText,             COLOR_CAPTIONTEXT,             RGB(255,255,255),         "COLOR_CAPTIONTEXT"             );
DECLARE_SYSTEM_COLOR( SysColorGrayText,                COLOR_GRAYTEXT,                RGB(128,128,128),         "COLOR_GRAYTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorHighLight,               COLOR_HIGHLIGHT,               RGB( 10, 36,106),         "COLOR_HIGHLIGHT"               );
DECLARE_SYSTEM_COLOR( SysColorHighLightText,           COLOR_HIGHLIGHTTEXT,           RGB(255,255,255),         "COLOR_HIGHLIGHTTEXT"           );
DECLARE_SYSTEM_COLOR( SysColorInactiveBorder,          COLOR_INACTIVEBORDER,          RGB(212,208,200),         "COLOR_INACTIVEBORDER"          );
DECLARE_SYSTEM_COLOR( SysColorInactiveCaption,         COLOR_INACTIVECAPTION,         RGB(128,128,128),         "COLOR_INACTIVECAPTION"         );
DECLARE_SYSTEM_COLOR( SysColorMenu,                    COLOR_MENU,                    RGB(212,208,200),         "COLOR_MENU"                    );
DECLARE_SYSTEM_COLOR( SysColorMenuText,                COLOR_MENUTEXT,                RGB(  0,  0,  0),         "COLOR_MENUTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorScrollbar,               COLOR_SCROLLBAR,               RGB(212,208,200),         "COLOR_SCROLLBAR"               );
DECLARE_SYSTEM_COLOR( SysColorWindow,                  COLOR_WINDOW,                  RGB(255,255,255),         "COLOR_WINDOW"                  );
DECLARE_SYSTEM_COLOR( SysColorWindowFrame,             COLOR_WINDOWFRAME,             RGB(  0,  0,  0),         "COLOR_WINDOWFRAME"             );
DECLARE_SYSTEM_COLOR( SysColorWindowText,              COLOR_WINDOWTEXT,              RGB(  0,  0,  0),         "COLOR_WINDOWTEXT"              );

glyph   faces[128];

UINT uiCXDoubleClk = 4;
UINT uiCYDoubleClk = 4;

#endif

#ifndef YOU_WIN_GRAPHICAL
DECLARE_SYSTEM_COLOR( SysColor3DDkShadow,              COLOR_3DDKSHADOW,              COLORREF_COLOR_BLACK,     "COLOR_3DDKSHADOW"              );
DECLARE_SYSTEM_COLOR( SysColor3DFace,                  COLOR_3DFACE,                  COLORREF_COLOR_BLACK,     "COLOR_3DFACE"                  );
DECLARE_SYSTEM_COLOR( SysColor3DHighLight,             COLOR_3DHIGHLIGHT,             COLORREF_COLOR_WHITE,     "COLOR_3DHIGHLIGHT"             );
DECLARE_SYSTEM_COLOR( SysColor3DLight,                 COLOR_3DLIGHT,                 COLORREF_COLOR_LIGHTGRAY, "COLOR_3DLIGHT"                 );
DECLARE_SYSTEM_COLOR( SysColor3DShadow,                COLOR_3DSHADOW,                COLORREF_COLOR_GRAY,      "COLOR_3DSHADOW"                );
DECLARE_SYSTEM_COLOR( SysColorInactiveCaptionText,     COLOR_INACTIVECAPTIONTEXT,     COLORREF_COLOR_LIGHTGRAY, "COLOR_INACTIVECAPTIONTEXT"     );
DECLARE_SYSTEM_COLOR( SysColorInfoBk,                  COLOR_INFOBK,                  COLORREF_COLOR_WHITE,     "COLOR_INFOBK"                  );
DECLARE_SYSTEM_COLOR( SysColorInfoText,                COLOR_INFOTEXT,                COLORREF_COLOR_BLACK,     "COLOR_INFOTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorHotLight,                COLOR_HOTLIGHT,                COLORREF_COLOR_BLUE,      "COLOR_HOTLIGHT"                );
DECLARE_SYSTEM_COLOR( SysColorGradientActiveCaption,   COLOR_GRADIENTACTIVECAPTION,   COLORREF_COLOR_WHITE,     "COLOR_GRADIENTACTIVECAPTION"   );
DECLARE_SYSTEM_COLOR( SysColorGradientInactiveCaption, COLOR_GRADIENTINACTIVECAPTION, COLORREF_COLOR_BLACK,     "COLOR_GRADIENTINACTIVECAPTION" );
DECLARE_SYSTEM_COLOR( SysColorActiveBorder,            COLOR_ACTIVEBORDER,            COLORREF_COLOR_LIGHTGRAY, "COLOR_ACTIVEBORDER"            );
DECLARE_SYSTEM_COLOR( SysColorActiveCaption,           COLOR_ACTIVECAPTION,           COLORREF_LIGHTBLUE,       "COLOR_ACTIVECAPTION"           );
DECLARE_SYSTEM_COLOR( SysColorAppWorkspace,            COLOR_APPWORKSPACE,            COLORREF_COLOR_BLUE,      "COLOR_APPWORKSPACE"            );
DECLARE_SYSTEM_COLOR( SysColorBackground,              COLOR_BACKGROUND,              COLORREF_COLOR_BLUE,      "COLOR_BACKGROUND"              );
DECLARE_SYSTEM_COLOR( SysColorBtnText,                 COLOR_BTNTEXT,                 COLORREF_COLOR_BLACK,     "COLOR_BTNTEXT"                 );
DECLARE_SYSTEM_COLOR( SysColorCaptionText,             COLOR_CAPTIONTEXT,             COLORREF_COLOR_WHITE,     "COLOR_CAPTIONTEXT"             );
DECLARE_SYSTEM_COLOR( SysColorGrayText,                COLOR_GRAYTEXT,                COLORREF_COLOR_LIGHTGRAY, "COLOR_GRAYTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorHighLight,               COLOR_HIGHLIGHT,               COLORREF_COLOR_BLUE,      "COLOR_HIGHLIGHT"               );
DECLARE_SYSTEM_COLOR( SysColorHighLightText,           COLOR_HIGHLIGHTTEXT,           COLORREF_COLOR_YELLOW,    "COLOR_HIGHLIGHTTEXT"           );
DECLARE_SYSTEM_COLOR( SysColorInactiveBorder,          COLOR_INACTIVEBORDER,          COLORREF_COLOR_GRAY,      "COLOR_INACTIVEBORDER"          );
DECLARE_SYSTEM_COLOR( SysColorInactiveCaption,         COLOR_INACTIVECAPTION,         COLORREF_COLOR_GRAY,      "COLOR_INACTIVECAPTION"         );
DECLARE_SYSTEM_COLOR( SysColorMenu,                    COLOR_MENU,                    COLORREF_COLOR_WHITE,     "COLOR_MENU"                    );
DECLARE_SYSTEM_COLOR( SysColorMenuText,                COLOR_MENUTEXT,                COLORREF_COLOR_BLACK,     "COLOR_MENUTEXT"                );
DECLARE_SYSTEM_COLOR( SysColorScrollbar,               COLOR_SCROLLBAR,               COLORREF_COLOR_LIGHTGRAY, "COLOR_SCROLLBAR"               );
DECLARE_SYSTEM_COLOR( SysColorWindow,                  COLOR_WINDOW,                  COLORREF_COLOR_WHITE,     "COLOR_WINDOW"                  );
DECLARE_SYSTEM_COLOR( SysColorWindowFrame,             COLOR_WINDOWFRAME,             COLORREF_COLOR_GRAY,      "COLOR_WINDOWFRAME"             );
DECLARE_SYSTEM_COLOR( SysColorWindowText,              COLOR_WINDOWTEXT,              COLORREF_COLOR_BLACK,     "COLOR_WINDOWTEXT"              );

UINT uiCXDoubleClk = 2;
UINT uiCYDoubleClk = 2;

#endif


#define DEFAULT_DOUBLECLICK_INTERVAL 500
#define MAXIMUM_DOUBLECLICK_INTERVAL 5000


UINT uDoubleClickInterval = DEFAULT_DOUBLECLICK_INTERVAL;


UINT GetDoubleClickTime( void ) {

    return uDoubleClickInterval;

}


BOOL SetDoubleClickTime( UINT uInterval ) {

    if ( 0 == uInterval ) {

        uDoubleClickInterval = DEFAULT_DOUBLECLICK_INTERVAL;
        return true;

    }

    if ( uInterval > MAXIMUM_DOUBLECLICK_INTERVAL ) {

        uDoubleClickInterval = MAXIMUM_DOUBLECLICK_INTERVAL;

    } else {

        uDoubleClickInterval = uInterval;

    }

    return true;

}


#ifdef YOU_WIN_GRAPHICAL


LONG GetDialogBaseUnits( void ) {

    return MAKELONG( 8, 16 );

}


int GetSystemMetrics( int nIndex ) {

    switch( nIndex ) {

        case SM_CXBORDER:     return 1;

        case SM_CXDOUBLECLK:  return uiCXDoubleClk;

        case SM_CXFIXEDFRAME: return 3; // SM_CXDLGFRAME:

        case SM_CXHSCROLL:    return 16;

        case SM_CXICON:       return 32;

        case SM_CXHTHUMB:     return 18;

        case SM_CXSCREEN:     return g.iCX;

        case SM_CXSIZEFRAME:  return 4; // SM_CXFRAME:

        case SM_CXSMICON:     return 16;

        case SM_CXVSCROLL:    return 16;

        case SM_CYBORDER:     return 1;

        case SM_CYCAPTION:    return 19;

        case SM_CYDOUBLECLK:  return uiCYDoubleClk;

        case SM_CYFIXEDFRAME: return 3; // SM_CYDLGFRAME:

        case SM_CYHSCROLL:    return 16;

        case SM_CYICON:       return 32;

        case SM_CYMENU:       return 19;

        case SM_CYMENUSIZE:   return 18;

        case SM_CYSCREEN:     return g.iCY;

        case SM_CYSIZEFRAME:  return 4; // SM_CYFRAME:

        case SM_CYSMICON:     return 16;

        case SM_CYVSCROLL:    return 16;

        case SM_CYVTHUMB:     return 18;

    }

    return 0;

}


#endif /* YOU_WIN_GRAPHICAL */


#ifdef YOU_WIN_TXT


LONG GetDialogBaseUnits( void ) {

    return MAKELONG( 1, 1 );

}


int GetSystemMetrics( int nIndex ) {

    switch( nIndex ) {

        case SM_CXBORDER:     return 1;

        case SM_CXDOUBLECLK:  return uiCXDoubleClk;

        case SM_CXFIXEDFRAME: return 0; // SM_CXDLGFRAME:

        case SM_CXHSCROLL:    return 1;

        case SM_CXHTHUMB:     return 1;

        case SM_CXICON:       return 4;

        case SM_CXSCREEN:     return g.iCX; // 132

        case SM_CXSIZEFRAME:  return 1; // SM_CXFRAME:

        case SM_CXSMICON:     return 2;

        case SM_CXVSCROLL:    return 1;

        case SM_CYBORDER:     return 1;

        case SM_CYCAPTION:    return 1;

        case SM_CYFIXEDFRAME: return 0; // SM_CYDLGFRAME:

        case SM_CYDOUBLECLK:  return uiCYDoubleClk;

        case SM_CYHSCROLL:    return 1;

        case SM_CYICON:       return 4;

        case SM_CYSCREEN:     return g.iCY; // 43

        case SM_CYSIZEFRAME:  return 1; // case SM_CYFRAME:

        case SM_CYSMICON:     return 2;

        case SM_CYVSCROLL:    return 1;

        case SM_CYVTHUMB:     return 1;

    }

    return 0;

}

#endif
