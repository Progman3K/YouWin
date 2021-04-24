

#include "dbwin.h"


void DeleteText( HWND hEditWnd, unsigned uFactorToDelete ) {

    DWORD   dwStyles;
    int     i;
    BOOL    bReadOnly;
    DWORD   dwTemp;

    if ( ! IsWindow( hEditWnd ) ) {

        return;

    }

    if ( 0 == uFactorToDelete ) {

        return;

    }

    dwStyles = GetWindowStyle( hEditWnd );
    dwTemp   = ( ES_READONLY & dwStyles );

    bReadOnly = ( 0 != dwTemp );

    if ( bReadOnly ) {

        Edit_SetReadOnly( hEditWnd, false );

    }

    FORWARD_WM_SETREDRAW( hEditWnd, false, SendMessage );

    i = GetWindowTextLength( hEditWnd );
    i = i / uFactorToDelete;

    Edit_SetSel( hEditWnd, 0, i );

    FORWARD_WM_CLEAR( hEditWnd, SendMessage );

    FORWARD_WM_SETREDRAW( hEditWnd, true, SendMessage );

    if ( bReadOnly ) {

        Edit_SetReadOnly( hEditWnd, true );

    }

}
