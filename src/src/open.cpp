

#include "ywin.h"


GLOBALS g = {

    false           // Has library passed initialization.


#ifdef YOU_WIN_TXT
    ,156
    ,50
#else
#ifdef ANDROID
    ,480
    ,800
#else
    ,800
    ,600
#endif
#endif

                    //    {0,0},
    ,SIGNATURE      // Signature for sanity checks on handles.
    ,NULL           // Bottom-most window. (Desktop)
    ,NULL           // focus window. (none)
    ,0              // Private data passed back to user at pTerminal I/O
//    ,0x7FFF         // Auto-ID timer ID
    ,NULL           // Raw output goes here
#ifdef ANDROID
    ,NULL           // Android-specific data
#endif
#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    ,NULL           // iOS-specific data
#endif

};


SolidBrush  brDesktop( SysColorBackground.GetColor(), true );
SolidBrush  br3DFace( SysColor3DFace.GetColor(), true );
SolidBrush  brWindow( SysColorWindow.GetColor(), true );

SolidBrush  brBlack( RGB( 0, 0, 0 ), true );

DesktopClass     CDesktop(     TEXT( "DESKTOP" ), Desktop::WndProc,     (HBRUSH)&brDesktop, CS_SYSTEM, NULL              );

DialogClass      CDialog(      TEXT( "DIALOG" ),  DefDlgProc,           (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );

ButtonClass      CButton(      WC_BUTTON,         Button::WndProc,      (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );
EditClass        CEdit(        WC_EDIT,           Edit::WndProc,        (HBRUSH)&brWindow,  CS_SYSTEM | CS_DBLCLKS, NULL );
ListboxClass     CListbox(     WC_LISTBOX,        Listbox::WndProc,     (HBRUSH)&brWindow,  CS_SYSTEM | CS_DBLCLKS, NULL );
ComboboxClass    CCombobox(    WC_COMBOBOX,       Combobox::WndProc,    (HBRUSH)&brWindow,  CS_SYSTEM | CS_DBLCLKS, NULL );
StaticClass      CStatic(      WC_STATIC,         Static::WndProc,      (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );

ProgressbarClass CProgressbar( PROGRESS_CLASS,    Progressbar::WndProc, (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );
AnimateClass     CAnimate(     ANIMATE_CLASS,     Animate::WndProc,     (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );
TrackbarClass    CTrackbar(    TRACKBAR_CLASS,    Trackbar::WndProc,    (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );
TabcontrolClass  CTabcontrol(  WC_TABCONTROL,     Tabcontrol::WndProc,  (HBRUSH)&br3DFace,  CS_SYSTEM, NULL              );
TreeviewClass    CTreeview(    WC_TREEVIEW,       Treeview::WndProc,    (HBRUSH)&brWindow,  CS_SYSTEM, NULL              );
ListviewClass    CListview(    WC_LISTVIEW,       Listview::WndProc,    (HBRUSH)&brWindow,  CS_SYSTEM, NULL              );


ClassList    classes;
ResourceList systemresources;

FontList fonts;
IconList icons;


#ifdef YOU_WIN_TXT
static union tagTextFont {

    Font_Header font;
    
    char cData[ sizeof( Font_Header ) + sizeof( IDSZ_SYSTEM ) ];
    
    tagTextFont() {

        font.uWeight        = 0;

        font.flags          = 0; // 32-bit bitfield:
                                 // Indicates a monochrome font. Grayscale if not.
                                 // Indicates fixed-width.

        font.uAvgCharHeight = 1;
        font.uAvgCharWidth  = 1;
        font.uMaxCharHeight = 1;
        font.uMaxCharWidth  = 1;
        font.uLeading       = 0;

        strcpy( font.szName, IDSZ_SYSTEM );

    }

} TextFont;
#endif


HFONT    hSystemFont = NULL;
HMODULE  hYouWinModule = NULL;


HRSRC FindResource( HMODULE hInst, LPCTSTR resname, LPCTSTR restype ) {

    const ResourceList * pResources = reinterpret_cast<const ResourceList *>( hInst );

    return (HRSRC)pResources->find( resname, restype );

}


HGLOBAL LoadResource( HMODULE hInst, HRSRC hRes ) {

    if ( 0 == hRes ) {

        return 0;

    }

    Resource * pRes = reinterpret_cast<Resource *>( hRes );

    return (HGLOBAL)pRes->Id.pData;

}


LPVOID LockResource( HGLOBAL hRes ) {

    return (LPVOID)hRes;

}


BOOL FreeResource( HGLOBAL h ) {

    return false;

}


DWORD SizeofResource( HMODULE hModule, HRSRC hRes ) {

    if ( 0 == hRes ) {

        return 0;

    }

    Resource * pRes = reinterpret_cast<Resource *>( hRes );

    return I386PE_INT32_TO_HOST( &pRes->Id.pHeader->uiSize );

}


BOOL EnumResourceNames( HMODULE hModule, LPCSTR restype, ENUMRESNAMEPROC lpEnumFunc, LONG_PTR lParam ) {

    TSTRING tType;
    TSTRING tName;

    const ResourceList * pResources = reinterpret_cast<const ResourceList *>( hModule );

    BOOL bSuccess = false;

    for ( const Resource & resource : *pResources ) {

        if ( 0 == HIWORD( restype ) ) {

            // Type must be numerical
            if ( 0 == resource.Id.uType ) continue; // Type not numerical

            if ( LOWORD( restype ) != resource.Id.uType ) continue; // Not right type

        } else {

            // Type must be alphanumerical
            if ( 0 != resource.Id.uType ) continue; // Not alphanumerical type

            tType.absorb( resource.Id.pszType );

            if ( 0 != tType.comparei( restype ) ) continue; // Not right type

        }

        if ( 0 != resource.Id.pszName ) {

            tName.absorb( resource.Id.pszName );

        }

        // Type OK
        bSuccess++;

        if ( ! lpEnumFunc( hModule, restype, resource.Id.pszName ? (LPTSTR)tName.c_str() : (LPTSTR)MAKEINTRESOURCE( resource.Id.uName ), lParam ) ) {

            break;

        }

    }

    return bSuccess;

}


static void recordresource( const RES_HEADER * pHeader, ResourceList & Resources ) {

    Resource resource;

    resource.Id.pHeader = pHeader;

    if ( (UTF_16)-1 != pHeader->TypeName[0] ) {

        /* This resource's type is NOT stored numerically. */
//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's type is NOT stored numerically:" ) );
        resource.Id.pszType = pHeader->TypeName;

        unsigned ulen = wcharlen( resource.Id.pszType );
//        DBG_DMP( DBG_GENERAL_INFORMATION, resource.Id.pszType, ulen * sizeof( UTF_16 ) );

        const UTF_16 * pName = resource.Id.pszType + ulen + 1;

        if ( (UTF_16)-1 != pName[0] ) {

            resource.Id.pszName = pName;

#ifdef DEBUG
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's name is NOT stored numerically:" ) );
            unsigned ulen = wcharlen( resource.Id.pszName );
            DBG_DMP( DBG_GENERAL_INFORMATION, resource.Id.pszName, ulen * sizeof( UTF_16 ) );
#endif

        } else {

            resource.Id.uName = pName[1];
//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's name IS stored numerically: %d" ), resource.Id.uName );

        }

    } else {

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's type IS stored numerically: %d" ), I386PE_INT16_TO_HOST( pHeader->TypeName[1] ) );

        resource.Id.uType = I386PE_INT16_TO_HOST( &pHeader->TypeName[1] );

        switch( I386PE_INT16_TO_HOST( &pHeader->TypeName[1] ) ) {

            case RESTYP_FONT:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Internal font" ) );
                break;

            case RT_BITMAP_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Bitmap" ) );
                break;

            case RT_CURSOR_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Cursor" ) );
                break;

            case RT_DIALOG_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Dialog" ) );
                break;

            case RT_FONT_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Font" ) );
                break;

            case RT_GROUP_ICON_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icongroup" ) );
                break;

            case RT_ICON_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Icon" ) );
                break;

            case RT_STRING_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "String" ) );
                break;

            case RT_VERSION_VAL:

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "VersionInfo" ) );
                break;

            default:

                /* ID must match exactly */
                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's TypeName not handled: %d" ), I386PE_INT16_TO_HOST( &pHeader->TypeName[1] ) );
                break;

        }

        if ( (UTF_16)-1 != pHeader->TypeName[2] ) {

            /* This resource's name is NOT stored numerically. */
            resource.Id.pszName = &pHeader->TypeName[2];

#ifdef DEBUG
            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's name is NOT stored numerically:" ) );
            unsigned ulen = wcharlen( resource.Id.pszName );
            DBG_DMP( DBG_GENERAL_INFORMATION, resource.Id.pszName, ulen * sizeof( UTF_16 ) );
#endif

        } else {

            /* Resource name IS stored numerically */
//            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource's name IS stored numerically: %d" ), I386PE_INT16_TO_HOST( pHeader->TypeName[3] ) );

            resource.Id.uName = I386PE_INT16_TO_HOST( &pHeader->TypeName[3] );

        }

    }

    resource.Id.pData = ((const char *)pHeader) + I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader );

    Resources.push_back( resource );

}


void ResourceList::LoadStaticResources( ResourceList & resources, const char * pStart, uintptr_t uSize ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Parse resource-segment at %lX, sized %lu bytes" ), (uintptr_t)pStart, uSize );

    /* Seek to right after the first (fake) header */
    const RES_HEADER * pHeader = (const RES_HEADER *)( pStart + sizeof( RES_HEADER ) );
    uintptr_t uRead = sizeof( RES_HEADER );

    unsigned u = 0;
    for ( ;; u++ ) {

        if ( ( sizeof( RES_HEADER ) != I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader ) ) || ( ( uRead + I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader ) + I386PE_INT32_TO_HOST( &pHeader->uiSize ) ) > uSize ) ) {

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Done parsing resource segment" ) );
            break;

        }

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Resource - Size of header %u, size %u" ), I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader ), I386PE_INT32_TO_HOST( &pHeader->uiSize ) );

        recordresource( pHeader, resources );

        unsigned uNext = I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader ) + I386PE_INT32_TO_HOST( &pHeader->uiSize );

        if ( 0 != ( uNext % sizeof( uint32_t ) ) ) {

            uNext += sizeof( uint32_t ) - ( uNext % sizeof( uint32_t ) );

        }

        uRead += uNext;

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "First (max 256) bytes of resource: " ) );
        DBG_DMP( DBG_GENERAL_INFORMATION, ((const char *)pHeader) + I386PE_INT32_TO_HOST( &pHeader->uiSizeOfHeader ), I386PE_INT32_TO_HOST( &pHeader->uiSize ) < 256 ? I386PE_INT32_TO_HOST( &pHeader->uiSize ) : 256 );

        pHeader = (const RES_HEADER *)( ( (const char *)pHeader ) + uNext );

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Walked %u resources" ), u );

}


OpenYWStatus OpenWindowLib( intptr_t lParam, TERMINALOUTPUTFUNC pTerminal ) {

    if ( g.bInit ) {

        return OpenYW_OK;

    }

    g.bInit = true;

    SysColors.insert( SysColors.end(), SysColorPair( COLOR_3DDKSHADOW,              &SysColor3DDkShadow              ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_3DFACE,                  &SysColor3DFace                  ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_3DHIGHLIGHT,             &SysColor3DHighLight             ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_3DLIGHT,                 &SysColor3DLight                 ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_3DSHADOW,                &SysColor3DShadow                ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_INACTIVECAPTIONTEXT,     &SysColorInactiveCaptionText     ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_INFOBK,                  &SysColorInfoBk                  ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_INFOTEXT,                &SysColorInfoText                ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_HOTLIGHT,                &SysColorHotLight                ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_GRADIENTACTIVECAPTION,   &SysColorGradientActiveCaption   ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_GRADIENTINACTIVECAPTION, &SysColorGradientInactiveCaption ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_ACTIVEBORDER,            &SysColorActiveBorder            ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_ACTIVECAPTION,           &SysColorActiveCaption           ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_APPWORKSPACE,            &SysColorAppWorkspace            ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_BACKGROUND,              &SysColorBackground              ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_BTNTEXT,                 &SysColorBtnText                 ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_CAPTIONTEXT,             &SysColorCaptionText             ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_GRAYTEXT,                &SysColorGrayText                ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_HIGHLIGHT,               &SysColorHighLight               ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_HIGHLIGHTTEXT,           &SysColorHighLightText           ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_INACTIVEBORDER,          &SysColorInactiveBorder          ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_INACTIVECAPTION,         &SysColorInactiveCaption         ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_MENU,                    &SysColorMenu                    ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_MENUTEXT,                &SysColorMenuText                ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_SCROLLBAR,               &SysColorScrollbar               ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_WINDOW,                  &SysColorWindow                  ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_WINDOWFRAME,             &SysColorWindowFrame             ) );
    SysColors.insert( SysColors.end(), SysColorPair( COLOR_WINDOWTEXT,              &SysColorWindowText              ) );

    brDesktop.SetColor( SysColorBackground.GetColor() );
    br3DFace.SetColor( SysColor3DFace.GetColor() );
    brWindow.SetColor( SysColorWindow.GetColor() );

    classes[ CDesktop.ClassName ]          = &CDesktop;
    classes[ CDialog.GetClassName() ]      = &CDialog;
    classes[ CButton.GetClassName() ]      = &CButton;
    classes[ CEdit.GetClassName() ]        = &CEdit;
    classes[ CListbox.GetClassName() ]     = &CListbox;
    classes[ CCombobox.GetClassName() ]    = &CCombobox;
    classes[ CStatic.GetClassName() ]      = &CStatic;
    classes[ CProgressbar.GetClassName() ] = &CProgressbar;
    classes[ CAnimate.GetClassName() ]     = &CAnimate;
    classes[ CTrackbar.GetClassName() ]    = &CTrackbar;
    classes[ CTabcontrol.GetClassName() ]  = &CTabcontrol;
    classes[ CTreeview.GetClassName() ]    = &CTreeview;
    classes[ CListview.GetClassName() ]    = &CListview;

    union {

        uint16_t      x;
        unsigned char c[sizeof(uint16_t)];

    } endian;

    endian.x = 0xFF00;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "%s, %s: charsize %lu, TCHAR size %lu, widechar size %lu, longsize %lu, pointersize %lu, Byte order=%s, font header size=%lu, chardef size=%lu, COLORREF size=%lu" ), __DATE__, __TIME__, (long)sizeof( char ), (long)sizeof( TCHAR ), (long)sizeof( wchar_t ), (long)sizeof( long ), (long)sizeof( char * ), ( 0xFF == endian.c[0] ) ? TEXT( "big" ) : TEXT( "little" ), (long)sizeof( Font_Header ), (long)sizeof( chardef ), (long)sizeof( COLORREF ) );

    hYouWinModule = (HMODULE)&systemresources;
    ResourceList::LoadStaticResources( systemresources, SYSTEM_RESOURCE_SEGMENT_START, SYSTEM_RESOURCE_SEGMENT_SIZE );

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Startup instance %lX, resource size %d" ), hYouWinModule, SYSTEM_RESOURCE_SEGMENT_SIZE );


#ifdef YOU_WIN_TXT

    Font font( &TextFont.font );
    auto f = fonts.emplace( IDSZ_SYSTEM, font );

    DBG_MSG( DBG_ERROR, TEXT( "Make System font: %s" ), f.second ? "Success" : "Failed" );

    if ( f.second ) {

        hSystemFont = (HFONT)&f.first->second;

    }

#else // defined( YOU_WIN_GRAPHICAL )

    hSystemFont = (HFONT)fonts.open( systemresources, TEXT( IDSZ_SYSTEM ) );

#endif

    if ( NULL == hSystemFont ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "RESOURCE LOAD FAILED" ) );
        return OpenYW_SYSTEM_FONT_CREATION_ERROR;

    }

    return OpenYW_OK;

}
