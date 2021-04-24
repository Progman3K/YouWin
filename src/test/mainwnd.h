

#include <DlgWnd.h>
#include <windowsx.h>
#include <string>
#include <dialoginfo.h>

#include "defines.h"


class CMainWnd : public DlgWnd<CMainWnd> {

//        DialogInfo dlginfo;

#if 0
        BOOL OnEraseBackground( HWND hWnd, HDC hDC ) {

            SetBkColor( hDC, GetSysColor( COLOR_HIGHLIGHT ) );
            SetTextColor( hDC, GetSysColor( COLOR_HIGHLIGHTTEXT ) );
#define SELECTED_TEXT "selected text"
            LONG lBaseUnits = GetDialogBaseUnits();

            TextOut( hDC, LOWORD( lBaseUnits ), HIWORD( lBaseUnits ), SELECTED_TEXT, Dim( SELECTED_TEXT ) );

            HBRUSH  hbr = CreateSolidBrush( RGB( 255, 0, 0 ) );

            RECT r;

            if ( GetClientRect( hWnd, &r ) ) {

                ExcludeClipRect( hDC, 10, r.top + ( r.bottom / 2 ), r.left + 50, r.bottom - 10 );

                FillRect( hDC, &r, hbr );

            }

            DeleteBrush( hbr );
            return true;

        }
#endif


        BOOL OnInit( HWND hWnd, HWND hFocusWnd, LPARAM lParam ) {

//            ShowWindow( GetDlgItem( hWnd, IDE_TEST ), SW_HIDE );

//            dlginfo.InstantiateAndRecord( GetWindowInstance( hWnd ), MAKEINTRESOURCE( IDD_MAIN ), HWND_DESKTOP );
            return true;

        }


        void OnCommand( HWND hWnd, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {

            switch( iID ) {

                case IDCANCEL:

                    if ( BN_CLICKED == uiNotifyCode ) {

                        EndDialog( hWnd, iID );

                    }
                    break;

                case IDB_TEST: {

                        RECT r;

//                        GetWindowRect( hWnd, &r );
                        r.left   = 1;
                        r.top    = 1;
                        r.right  = r.left + 10;
                        r.bottom = r.top + 10;
                        
                        HDC hDC;
                        
                        hDC = GetDC( hWnd );
                        
                        filledcircle( 30, 30, 20, hDC );

//                        DrawCircle( 0, 0, 20, hDC );
//                        DrawCircle( 10, 10, 20, hDC );
//                        DrawFilledCircle( 30, 30, 30, hDC );

//                        DrawFrameControl( hDC, &r, DFC_BUTTON, DFCS_BUTTONRADIO ); 
                        
                        ReleaseDC( hWnd, hDC );

//                        dlginfo.MoveTo( hWnd, r.left, r.top );

                    }
                    break;

            }

//            FORWARD_WM_SETREDRAW( GetDlgItem( hDlg, IDE_TEST ), true, SendMessage );

        }
        
#if 0        
        void Circle( int Radius, int xC, int yC ) {
            
            int P;
            int x,y;
            
//        void Draw(int x,int y,int xC,int yC);
        
            P = 1 - Radius;
            x = 0;
            y = Radius;
            
            draw( x, y, xC, yC );

            while ( x <= y ) {

                x++;

                if ( P < 0 ) {
                    
                    P += 2 * x + 1;
                    
                } else {
                    
                    P += 2 * ( x - y ) + 1;
                    y--;
                    
                }
                
                draw( x, y, xC, yC );

            }

        }


        void draw( int x, int y, int xC, int yC ) {

            putpixel( xC + x, yC + y, 12 );
            putpixel( xC + x, yC - y, 12 );
            putpixel( xC - x, yC + y, 12 );
            putpixel( xC - x, yC - y, 12 );
            putpixel( xC + y, yC + x, 12 );
            putpixel( xC - y, yC + x, 12 );
            putpixel( xC + y, yC - x, 12 );
            putpixel( xC - y, yC - x, 12 );

        }        
        
#endif
        void DrawFilledCircle( int x, int y, int r, HDC hDC ) {

            for ( ; r > 0; r-- ) {

                DrawCircle( x, y, r, hDC );

            }

        }
        
        void DrawCircle( int x0, int y0, int radius, HDC hDC ) {

            // int x = radius, y = 0;
            float x = radius, y = 0;
//            int radiusError = 1 - x;
            float radiusError = 1 - x;

            while( x >= y ) {

                SetPixel( hDC,  x + x0,  y + y0, 0 );
                SetPixel( hDC,  y + x0,  x + y0, 0 );
                SetPixel( hDC, -x + x0,  y + y0, 0 );
                SetPixel( hDC, -y + x0,  x + y0, 0 );
                SetPixel( hDC, -x + x0, -y + y0, 0 );
                SetPixel( hDC, -y + x0, -x + y0, 0 );
                SetPixel( hDC,  x + x0, -y + y0, 0 );
                SetPixel( hDC,  y + x0, -x + y0, 0 );
                
                y++;
                
                if ( radiusError < 0 ) {
                    
                    radiusError += 2 * y + 1;

                } else {
                    
                    x--;
                    radiusError += 2 * ( y - x + 1 );

                }

            }

        }        


        void circleA( int rx, int ry, int r, HDC hDC ) {
            
            int x, y;
            
            for( x = rx - r; x <= rx + r; x++ )
                for( y = ry - r; y <= ry + r; y++ )
                    if ( ( ( x * x ) + ( y * y ) ) == ( r * r ) )
                        SetPixel( hDC, x, y, 0 );

        }
        
        void circleB( int rx, int ry, int r, int f, HDC hDC ) {
            
            int x, y;
            
            for( x = rx - r; x <= rx + r; x++ )
                for( y = ry - r; y <= ry + r; y++ )
                    if ( ( ( ( x * x ) + ( y * y ) ) > ( r * r ) - ( f / 2 ) ) && ( ( ( x * x ) + ( y * y ) ) < ( r * r ) + ( f / 2 ) ) )
                        SetPixel( hDC, x, y, 0 );

        }
        
        void filledcircle( int oldx, int oldy, int r, HDC hDC ) {
            
            int x, y;
            int rx = 0;
            int ry = 0;
            
            for( x = rx - r; x <= rx + r; x++ )
                for( y = ry - r; y <= ry + r; y++ )
                    if ( ( ( x * x ) + ( y * y ) ) < ( r * r ) )
                        SetPixel( hDC, oldx + x, oldy + y, 0 );
                    
        }        

    public:

        virtual ~CMainWnd() {}

        INT_PTR bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

            TRACE_MESSAGE( (DWORD)-1, hWnd, uiMsg, wParam, lParam );

            switch( uiMsg ) {

                case WM_INITDIALOG:

                    HANDLE_WM_INITDIALOG( hWnd, wParam, lParam, OnInit );
                    return true;

                case WM_CLOSE:

                    // EndDialog( hDlg, 0 );
                    PostQuitMessage( 0 );
                    return true;

                case WM_COMMAND:

                    HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
                    return false;

//                case WM_ERASEBKGND:

//                    HANDLE_WM_ERASEBKGND( hWnd, wParam, lParam, OnEraseBackground );
//                    return true;

            }

            return false;

        }

};
