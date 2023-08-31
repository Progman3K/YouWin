

#include "ywin.h"


static ResourceList userresources;


HMODULE GetModuleHandle( LPCTSTR lpModuleName ) {

    if ( NULL != lpModuleName ) {

        return NULL;

    }

    return &userresources;

}


#if defined( ANDROID ) && defined( YOU_WIN_GRAPHICAL )
void android_main( struct android_app * app ) {
    LPARAM lParam = reinterpret_cast<LPARAM>( app );
    int iArgCount = 0;
    const char * pszApp = "";
    char ** argv = { 0 };
#else

#ifdef YOU_WIN_GRAPHICAL

#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE

extern "C" int iOSMain( iOSApp * app ) {

    LPARAM lParam = reinterpret_cast<LPARAM>( app );
    g.app = app;
    g.iCX = app->cx;
    g.iCY = app->cy;

    const TCHAR * pszApp = app->argv[0];

#else /* linux/generic gl or Darwin */

int main( int iArgCount, char * argv[] ) {

    LPARAM lParam = 0;

#ifdef UNICODE
//    TSTRING App;
//    App.absorb( argv[0] );
//    char * pszApp = (TCHAR *)App.c_str();
#else
    char * pszApp = argv[0];
#endif

#endif

#else /* TEXT MODE MAIN HERE */
int main( int iArgCount, char * argv[] ) {

    LPARAM lParam = 0;

    char * pszApp = argv[0];
#endif

#endif

    int iRet = -1;

    int     nCmdShow    = SW_SHOW;

    HINSTANCE hInstance = NULL;

    LPCTSTR lpszApp;
#ifdef UNICODE
    TSTRING t;
    t.absorb( argv[0] );
    lpszApp = t.c_str();
#else
    lpszApp = pszApp;
#endif

    if ( OpenYW_OK != OpenWindowLib( 0, NULL ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing WindowLib" ) );
        goto Outtahere;

    }

    iRet = ywDisplay::Init( g.iCX, g.iCY, g.Q, iArgCount, /* reinterpret_cast<const char **>( */ argv /* ) */, lParam );

    if ( 0 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing display" ) );
        goto Outtahere;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Display layer started" ) );

//    PostRefresh();
//    RasterUpdate();

    /* Computer platforms use the system window-manager and don't have a YouWin desktop window */

//#if ! defined( YOU_WIN_GRAPHICAL_XWIN )

    if ( ( g.pTopWnd = Desktop::Create( 0, TEXT( "DESKTOP" ), TEXT( "" ), WS_VISIBLE, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), NULL, NULL, hYouWinModule, 0 ) ) == NULL ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing: unable to create desktop window" ) );
        goto Outtahere;

    }

    RedrawWindow( (HWND)g.pTopWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

//#endif /* ! YOU_WIN_GRAPHICAL_XWIN */

    hInstance = &userresources;
    ResourceList::LoadStaticResources( userresources, USER_RESOURCE_SEGMENT_START, USER_RESOURCE_SEGMENT_SIZE );

#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iRet = app->_tWinMain( hInstance, NULL, (LPTSTR)pszApp, nCmdShow );
#else
    iRet = _tWinMain( hInstance, NULL, (LPTSTR)lpszApp, nCmdShow );
#endif

Outtahere:

    ywDisplay::Destroy();

    CloseWindowLib();

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "'%s' - Shutdown (%d)" ), lpszApp, iRet );

#ifndef ANDROID
    return iRet;
#endif

}

