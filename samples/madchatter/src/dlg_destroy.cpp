

#include "chatter.h"


void CChatterMainWnd::OnDestroy( HWND hDlg ) {

    if ( NULL != hUserListWnd ) {

        for( int i = ListBox_GetCount( hUserListWnd ); 0 < i; i-- ) {

            (void)ListBox_DeleteString( hUserListWnd, i - 1 );

        }

        hUserListWnd = NULL;

    }

    if ( NULL != hAppIcon ) {

        DestroyIcon( hAppIcon );
        hAppIcon = NULL;

    }

    for ( unsigned u = 0; u < Dim( hHatAnimIcon ); u++ ) {

        if ( NULL != hHatAnimIcon[u] ) {

            DestroyIcon( hHatAnimIcon[u] );
            hHatAnimIcon[u] = NULL;

        }

    }

}
