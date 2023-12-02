#ifndef YW_H_SYSCOLORS_H
#define YW_H_SYSCOLORS_H


#include <map>
#include <string>
#include <windows.h>


#include "brush.h"


class SysColor : public SolidBrush {

        int         iID;
//        COLORREF    cr;

#ifdef DEBUG
        std::string Name;
#endif

    public:

#ifdef DEBUG
        SysColor( int i, COLORREF c, bool bSystem, const char * pszName ) : SolidBrush( c, bSystem ) {
#else
        SysColor( int i, COLORREF c, bool bSystem ) : SolidBrush( c, bSystem ) {
#endif

            iID  = i;
//            cr   = c;

#ifdef DEBUG
            Name = pszName;

            // DBG_MSG( DBG_GRAPHICAL, TEXT( "Initialized color %s: %08lX, instance %08lX" ), Name.c_str(), cr, this );
#endif

        }

};

using SysColorPair = std::pair<int, SysColor *>;
using SysColorList = std::map<int, SysColor *>;

#ifdef DEBUG
#define DECLARE_SYSTEM_COLOR( VarName, ID, cr, text ) SysColor VarName( ID, cr, true, text )
#else
#define DECLARE_SYSTEM_COLOR( VarName, ID, cr, text ) SysColor VarName( ID, cr, true )
#endif

extern SysColor SysColor3DDkShadow;
extern SysColor SysColor3DFace;
extern SysColor SysColor3DHighLight;
extern SysColor SysColor3DLight;
extern SysColor SysColor3DShadow;
extern SysColor SysColorInactiveCaptionText;
extern SysColor SysColorInfoBk;
extern SysColor SysColorInfoText;
extern SysColor SysColorHotLight;
extern SysColor SysColorGradientActiveCaption;
extern SysColor SysColorGradientInactiveCaption;
extern SysColor SysColorActiveBorder;
extern SysColor SysColorActiveCaption;
extern SysColor SysColorAppWorkspace;
extern SysColor SysColorBackground;
extern SysColor SysColorBtnText;
extern SysColor SysColorCaptionText;
extern SysColor SysColorGrayText;
extern SysColor SysColorHighLight;
extern SysColor SysColorHighLightText;
extern SysColor SysColorInactiveBorder;
extern SysColor SysColorInactiveCaption;
extern SysColor SysColorMenu;
extern SysColor SysColorMenuText;
extern SysColor SysColorScrollbar;
extern SysColor SysColorWindow;
extern SysColor SysColorWindowFrame;
extern SysColor SysColorWindowText;

extern SysColorList SysColors;

#endif /* YW_H_SYSCOLORS_H */
