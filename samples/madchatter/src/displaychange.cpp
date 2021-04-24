

#include "chatter.h"


void CChatterMainWnd::OnDisplayChange( HWND hWnd, UINT uiBitsPerPixel, UINT cx, UINT cy ) {

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Desktop resized to %ux%u" ), cx, cy );

    RECT r;

    GetWindowRect( hWnd, &r );

    /* Make sure the progress-bar changes style */
    HWND hPBWnd = GetDlgItem( hWnd, IDPB_FILEXFER );

    DWORD_PTR dwStyle = GetWindowStyle( hPBWnd );

    if ( cy > cx ) {

        /* Portrait */
//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Dialog set to portrait mode (%ux%u) [%d,%d,%d,%d]" ), portrait.cx, portrait.cy, r.left, r.top, r.left + portrait.cx, r.top + portrait.cy );

        SetWindowLongPtr( hPBWnd, GWL_STYLE, (LONG_PTR)( dwStyle | PBS_VERTICAL ) );

        portrait.MoveTo( hWnd, (int)r.left, (int)r.top );

    } else {

        /* Landscape */
//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Dialog set to landscape mode (%ux%u) [%d,%d,%d,%d]" ), landscape.cx, landscape.cy, r.left, r.top, r.left + landscape.cx, r.top + landscape.cy );

        SetWindowLongPtr( hPBWnd, GWL_STYLE, (LONG_PTR)( ( ~PBS_VERTICAL ) & dwStyle ) );

        landscape.MoveTo( hWnd, (int)r.left, (int)r.top );

    }

}
