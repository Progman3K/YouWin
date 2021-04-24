

#include "dbwin.h"


BOOL Sure( HINSTANCE hInst, HWND hFocusWnd, LPCTSTR lpszMessageTitle, LPCTSTR lpszExtra, unsigned uLine, LPCTSTR lpszFile ) {

    TCHAR szString[1024];
    TCHAR szMessage[1024];

    ZeroMemory( szMessage, sizeof( szMessage ) );
    ZeroMemory( szString, sizeof( szString ) );

    if ( NULL != lpszMessageTitle ) {

        if ( HIWORD( lpszMessageTitle ) == 0 ) {

            LoadString( hInst, LOWORD( (DWORD)lpszMessageTitle ), szMessage, Dim( szMessage ) - 1 );

        }
        else {

            strncpy( szMessage, lpszMessageTitle, Dim( szMessage ) - 1 );

        }

    }

    if ( lpszExtra && ( HIWORD( lpszExtra ) == 0 ) ) {

        if ( LoadString( hInst, LOWORD( (DWORD)lpszExtra ), szString, Dim( szString ) - 1 ) ) {

            /* User wants us to access parameter from string table.	*/
            return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, szString, szMessage, MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

        }
        else {

            return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, TEXT( "" ), szMessage, MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

        }

    }

    return MessageBox( IsWindow( hFocusWnd ) ? hFocusWnd : 0, lpszExtra, szMessage, MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND ) == IDYES;

}
