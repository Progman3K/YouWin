

#include "dbwin.h"

#if defined( _WIN32 )
HFONT CMainDlg::hCreateFont( HINSTANCE hInst ) {

    LOGFONT lf;
    HFONT   hFont;

    ZeroMemory( &lf, sizeof( lf ) );

    // GetAppProfileString( hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_NAME ), TEXT( IDSZ_DEFAULT_DISPLAY_FONT_NAME ), lf.lfFaceName, Dim( lf.lfFaceName ), g_szIniFile, TRUE );
    strncpy( lf.lfFaceName, TEXT( IDSZ_DEFAULT_DISPLAY_FONT_NAME ),  Dim( lf.lfFaceName ) - 1 );

    // lf.lfHeight      = GetAppProfileInt( hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_POINT ), -11, g_szIniFile, TRUE, TRUE );
    // lf.lfWidth       = GetAppProfileInt( hInst, ID( IDS_SETTINGS_SECTION ), ID( IDS_DISPLAY_FONT_WIDTH ), 0, g_szIniFile, TRUE, TRUE );
    lf.lfHeight         = -11;
    lf.lfWidth          = 0;
    lf.lfCharSet        = ANSI_CHARSET;
    lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;

    hFont               = CreateFontIndirect( &lf );

    return hFont;

}
#endif /* _WIN32 */
