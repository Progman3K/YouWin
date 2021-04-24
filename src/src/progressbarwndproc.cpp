

#include "ywin.h"


void Progressbar::OnPaint( HWND hWnd, PAINTSTRUCT * pPS ) {

    RECT r;

    GetClientRect( hWnd, &r );

    if ( 0 != dwPosition ) {

        RECT r2 = r;

        // Percent complete
        float pct = (float)dwHigh / (float)dwPosition;

        if ( PBS_VERTICAL & dwStyle ) {

            r2.top = r2.bottom - ( (int)( r2.bottom / pct ) );
            FillRect( pPS->hdc, &r2, GetSysColorBrush( COLOR_HIGHLIGHT ) );

        } else {

            r2.right = (int)( r2.right / pct );
            FillRect( pPS->hdc, &r2, GetSysColorBrush( COLOR_HIGHLIGHT ) );

        }

    }

#ifndef YOU_WIN_TXT
    DrawEdge( pPS->hdc, &r, BDR_SUNKENINNER, BF_RECT );
#endif

}


DWORD Progressbar::OnSetRange32( HWND hWnd, unsigned uNewLow, DWORD dwNewHigh ) {

    DWORD dwOldRange;

    dwOldRange = MAKELONG( uLow, dwHigh );

    uLow   = uNewLow;
    dwHigh = dwNewHigh;

    return dwOldRange;

}


unsigned Progressbar::OnSetStep( HWND hWnd, unsigned uStep ) {

    unsigned uOldStepIncrement;

    uOldStepIncrement = uStepIncrement;

    uStepIncrement = uStep;

    return uOldStepIncrement;

}



DWORD Progressbar::OnStepIt( HWND hWnd ) {

    DWORD dwOldPosition;

    dwOldPosition = dwPosition;

    dwPosition += uStepIncrement;

    if ( dwPosition > dwHigh ) {

        dwPosition = dwPosition % dwHigh;

    }

    if ( dwOldPosition != dwPosition ) {

        RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    }

    return dwOldPosition;

}


DWORD Progressbar::OnSetPos( HWND hWnd, unsigned uPos ) {

    DWORD dwOldPosition = dwPosition;

    dwPosition = uPos;

    if ( dwPosition > dwHigh ) {

        dwPosition = dwPosition % dwHigh;

    }

    if ( dwOldPosition != dwPosition ) {

        RedrawWindow( hWnd, NULL, NULL, RDW_ERASE | RDW_ERASENOW | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW );

    }

    return dwOldPosition;

}


LRESULT Progressbar::WndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    Progressbar * pWnd = reinterpret_cast<Progressbar *>( hWnd );

    switch( uiMsg ) {

        case PBM_SETPOS:

            return HANDLE_PBM_SETPOS( hWnd, wParam, lParam, pWnd->OnSetPos );

        case PBM_SETRANGE32:

            return HANDLE_PBM_SETRANGE32( hWnd, wParam, lParam, pWnd->OnSetRange32 );

        case PBM_SETSTEP:

            return HANDLE_PBM_SETSTEP( hWnd, wParam, lParam, pWnd->OnSetStep );

        case PBM_STEPIT:

            return HANDLE_PBM_STEPIT( hWnd, wParam, lParam, pWnd->OnStepIt );

        case WM_PAINT: {

                PAINTSTRUCT ps;

                ZeroMemory( &ps, sizeof( ps ) );

                BeginPaint( hWnd, &ps );

                pWnd->OnPaint( hWnd, &ps );

                EndPaint( hWnd, &ps );

            }
            return true;

    }

    return DefWindowProc( hWnd, uiMsg, wParam, lParam );

}
