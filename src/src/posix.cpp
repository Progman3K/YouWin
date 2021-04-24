

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
    const char * pszApp = ""; 
#else

#ifdef YOU_WIN_GRAPHICAL

#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE

extern "C" int iOSMain( iOSApp * app ) {

    g.app = app;
    g.iCX = app->cx;
    g.iCY = app->cy;

    const TCHAR * pszApp = app->argv[0];

#else /* linux/generic gl or Darwin */

int main( int iArgCount, char * argv[] ) {

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

#ifdef YOU_WIN_TXT

    iRet = TerminalInit();

#else /* YOU_WIN_GRAPHICAL */


#ifdef ANDROID
    iRet = droidInit( app, &pszApp );
#else
#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iRet = iOSInit( app );
#else
    iRet = GL::glInit( g.iCX, g.iCY, g.Q, iArgCount, argv );
#endif
#endif

#endif /* YOU_WIN_GRAPHICAL */

    if ( 0 != iRet ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing display" ) );
        goto Outtahere;

    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Display layer started" ) );

    if ( ( g.pTopWnd = Desktop::Create( 0, TEXT( "DESKTOP" ), TEXT( "" ), WS_VISIBLE, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), NULL, NULL, hYouWinModule, 0 ) ) == NULL ) {

        DBG_MSG( DBG_ERROR, TEXT( "FATAL - Error initializing: unable to create desktop window" ) );
        goto Outtahere;

    }

    RedrawWindow( (HWND)g.pTopWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    hInstance = &userresources;
    ResourceList::LoadStaticResources( userresources, USER_RESOURCE_SEGMENT_START, USER_RESOURCE_SEGMENT_SIZE );

#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iRet = app->_tWinMain( hInstance, NULL, (LPTSTR)pszApp, nCmdShow );
#else
    iRet = _tWinMain( hInstance, NULL, (LPTSTR)lpszApp, nCmdShow );
#endif

Outtahere:

    CloseWindowLib();

#ifdef YOU_WIN_TXT
    TerminalCleanup();
#endif
#if defined( TARGET_OS_MAC ) && TARGET_OS_IPHONE
    iOSCleanup( app );
#endif

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "'%s' - Shutdown (%d)" ), lpszApp, iRet );

#ifndef ANDROID
    return iRet;
#endif

}

