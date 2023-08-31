

#include "ywin.h"


static BOOL ReDrawFamily( HWND hWnd, LPARAM flags ) {

    ywWindow * pWnd = reinterpret_cast<ywWindow *>( hWnd );

    if ( ( 0 == pWnd ) || ( pWnd->bNoRedraw ) ) {

        /* Drawing, re-drawing or erasing of any type not allowed */
        return true;

    }

    ywWindow * pPopuWnd = reinterpret_cast<ywWindow *>( IWindow::GetPopup( pWnd ) );

    if( ( NULL != pPopuWnd ) && pPopuWnd->bNoRedraw ) {

        return true;

    }

    if ( ( RDW_INVALIDATE & flags ) && IsWindowVisible( pWnd ) ) {

        if ( RDW_ERASE & flags ) {

            pWnd->fErase = true;

            if ( RDW_ERASENOW & flags ) {

                /* Clear the background erase flag */
                pWnd->fErase = ! FORWARD_WM_ERASEBKGND( hWnd, (HDC)&pWnd->ClientDC, SendMessage );

            }

        }

        if ( ( RDW_FRAME & flags ) || ( ! pWnd->NonClientArea.IsEmpty() ) ) {

            if ( ( RDW_UPDATENOW & flags ) || ( RDW_ERASENOW & flags ) ) {

                FORWARD_WM_NCPAINT( hWnd, (HRGN)&pWnd->NonClientArea, SendMessage );

            } else {

                FORWARD_WM_NCPAINT( hWnd, (HRGN)&pWnd->NonClientArea, PostMessage );

            }

        }

        if ( RDW_INTERNALPAINT & flags ) {

            if ( RDW_UPDATENOW & flags ) {

                FORWARD_WM_PAINT( hWnd, SendMessage );
                pWnd->bDirty = false;

            } else {

                if ( ! pWnd->bDirty ) {

                    // pWnd->bDirty = true;

                    FORWARD_WM_PAINT( hWnd, PostMessage );

                }

            }

        }

    }

    if ( RDW_ALLCHILDREN & flags ) {

        EnumChildWindows( hWnd, ReDrawFamily, flags );

    }

    return true;

}


BOOL RedrawWindow( HWND hWnd, const RECT * pr, HRGN hRgn, UINT flags ) {

    ywWindow * pWnd;

    if ( ( NULL == hWnd ) || ( HWND_DESKTOP == hWnd ) ) {

        hWnd = g.pTopWnd;

    }

    pWnd = IsWnd( hWnd );

    if ( NULL == pWnd ) {

        return false;

    }

    if ( ! IsWindowVisible( hWnd ) ) {

        return false;

    }

    if ( ! ( ( RDW_INVALIDATE & flags ) || ( RDW_VALIDATE & flags ) ) ) {

        /* Must invalidate OR validate */
        return false;

    }

    if ( ( RDW_INVALIDATE & flags ) && ( RDW_VALIDATE & flags ) ) {

        /* May not do both */
        return false;

    }

    if ( ( NULL != pr ) && ( NULL != hRgn ) ) {

        /* May not supply both */
        return false;

    }

    if ( RDW_FRAME & flags ) {

        /* Entire non-client area to be painted */
        pWnd->NonClientDC.AddIntersection( NULL );
        pWnd->NonClientDC.AddExclusion( NULL );

    }

    if ( RDW_INVALIDATE & flags ) {

         /* Add supplied rectangle/region to intersection in client area */

        if ( ( NULL == pr ) && ( NULL == hRgn ) ) {

            /* Entire client area to be painted */
            pWnd->ClientDC.AddIntersection( NULL );
            pWnd->ClientDC.AddExclusion( NULL );

        } else {

            if ( NULL != pr ) {

                ywRegion region;

                region.add( *pr );

                pWnd->ClientDC.AddIntersection( &region );

            }

            if ( NULL != hRgn ) {

                pWnd->ClientDC.AddIntersection( reinterpret_cast<ywRegion *>( hRgn ) );

            }

        }

    }

    if ( RDW_VALIDATE & flags ) {

         /* Add supplied rectangle/region to exclude in client area */

        if ( ( NULL == pr ) && ( NULL == hRgn ) ) {

            /* Entire client area is painted */
            pWnd->ClientDC.AddIntersection( NULL );
            pWnd->ClientDC.AddExclusion( NULL );

            pWnd->bDirty = false;
            pWnd->fErase = false;

        } else {

            if ( NULL != pr ) {

                ywRegion region;

                region.add( *pr );

                pWnd->ClientDC.AddExclusion( &region );

            }

            if ( NULL != hRgn ) {

                pWnd->ClientDC.AddExclusion( reinterpret_cast<ywRegion *>( hRgn ) );

            }

        }

    }

    BOOL bRet = ReDrawFamily( hWnd, flags );

    if ( ( RDW_ERASENOW & flags ) || ( RDW_UPDATENOW & flags ) ) {

        PostRefresh();
        RasterUpdate();

    }

    return bRet;

}


BOOL InvalidateRect( HWND hWnd, const RECT * pr, BOOL bErase ) {

    return RedrawWindow( hWnd, pr, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | ( bErase ? RDW_ERASE : 0 ) );

}


BOOL InvalidateRgn( HWND hWnd, HRGN hRgn, BOOL bErase ) {

    return RedrawWindow( hWnd, NULL, hRgn, RDW_INTERNALPAINT | RDW_INVALIDATE | ( bErase ? RDW_ERASE : 0 ) );

}


BOOL ValidateRect( HWND hWnd, const RECT * pr ) {

    return RedrawWindow( hWnd, pr, NULL, RDW_VALIDATE );

}


BOOL ValidateRgn( HWND hWnd, HRGN hRgn ) {

    return RedrawWindow( hWnd, NULL, hRgn, RDW_VALIDATE );

}
