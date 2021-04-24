#ifndef YW_H_DIALOGINFO_H
#define YW_H_DIALOGINFO_H


#include <vector>


#ifndef I386PE_INT16_TO_HOST
#define I386PE_INT16_TO_HOST( pu16 ) ((((unsigned char *)pu16)[0]<<0) | (((unsigned char *)pu16)[1]<<8))
#endif /* ! I386PE_INT16_TO_HOST */


typedef struct {

    uint16_t iCtlID;

    POINT    pt;

    unsigned cx;
    unsigned cy;

} ChildDimensions;


class DialogInfo {


        std::vector<ChildDimensions> child;


        void MoveChildren( HWND hDlg ) {

            for ( unsigned u = 0; u < child.size(); u++ ) {

                HWND hWnd = GetDlgItem( hDlg, child.at( u ).iCtlID );

                if ( NULL != hWnd ) {

                    MoveWindow( hWnd, (int)child.at( u ).pt.x, (int)child.at( u ).pt.y, (int)child.at( u ).cx, (int)child.at( u ).cy, false );

                } else {

//                    DBGTRACE( "Dialog ID %d not found!", child.at( u ).iCtlID );

                }

            }

        }


        const uint16_t * skip_over( const uint16_t * p ) {

			unsigned u = 0;

			for ( u = 0;; u++ ) {

				if ( 0 == *p ) {

					break;

				}

				p++;

			}

			/* Point past the NUL */
			p++;

			if ( 0 != u % 2 ) {

				p++;

			}

			return p;

		}


        void AdjustForFont( HWND hWnd, int x, int y, unsigned CX, unsigned CY, RECT & r ) {

            r.left   =          x;
            r.top    =          y;
            r.right  = r.left + CX;
            r.bottom = r.top  + CY;

            MapDialogRect( hWnd, &r );

        }


    public:


        unsigned cx;
        unsigned cy;


        DialogInfo() {

            cx = 0;
            cy = 0;

        }


        void MoveTo( HWND hWnd, int x, int y ) {

            MoveWindow( hWnd, x, y, cx, cy, false );

            MoveChildren( hWnd );

        }


        bool Record( HINSTANCE hInst, LPCTSTR lpszDlgID, HWND hWnd ) {

			HRSRC hRes = FindResource( hInst, lpszDlgID, RT_DIALOG );

			if ( (HRSRC)0 == hRes ) {

				return false;

			}

			HGLOBAL hData = LoadResource( hInst, hRes );

			if ( (HGLOBAL)0 == hData ) {

				return false;

			}

			DLGTEMPLATE * pDlgHeader = (DLGTEMPLATE *)LockResource( hData );

			if ( 0 == pDlgHeader ) {

				FreeResource( hData );
				return false;

			}

			RECT r;

//			DBGTRACE( "Recorded parent %d: (%d,%d,%u,%u) - %d children", LOWORD( reinterpret_cast<uintptr_t>( lpszDlgID ) ), pDlgHeader->x, pDlgHeader->y, pDlgHeader->cx, pDlgHeader->cy, (unsigned)pDlgHeader->cdit );

			AdjustForFont( hWnd, I386PE_INT16_TO_HOST( &pDlgHeader->x ), I386PE_INT16_TO_HOST( &pDlgHeader->y ), I386PE_INT16_TO_HOST( &pDlgHeader->cx ), I386PE_INT16_TO_HOST( &pDlgHeader->cy ), r );

			cx = (unsigned long)( r.right - r.left );
			cy = (unsigned long)( r.bottom - r.top );

			/* Add non-client area dimensions */
			cy += GetSystemMetrics( SM_CYCAPTION );
			cy += GetSystemMetrics( SM_CYMENUSIZE );
			cy += ( GetSystemMetrics( SM_CYDLGFRAME ) * 2 );
			cy += ( GetSystemMetrics( SM_CYBORDER ) * 2 );

			cx += ( GetSystemMetrics( SM_CXDLGFRAME ) * 2 );
			cx += ( GetSystemMetrics( SM_CXBORDER ) * 2 );

			child.clear();

			if ( 0 == pDlgHeader->cdit ) {

				FreeResource( hData );
				return true;

			}

			/* Access first 16-bit word immediately following the dialog header */
			const unsigned short * p = (const uint16_t *)&pDlgHeader->cy;
			p++;

			// Is there a MenuName
			switch ( *p ) {

				case 0:

					// There is no menu
					p++;
					break;

				case 0xFFFF:

					// The following short is the menu resource ID
					p++;

		//            DBGTRACE( "Dialog numerical menu ID %u", *p );

					p++;
					break;

				default:

					// What follows is an alphanumeric string of the resource ID.
					p = skip_over( p );
					break;

			}

			// Is there a class name
			switch ( *p ) {

				case 0:

					// There is no class string
					p++;
					break;

				case 0xFFFF:

					// The following short is the window-class ID
					p++;

		//            DBGTRACE( "Dialog numerical menu ID %u", *p );

					p++;
					break;

				default:

					// What follows is an alphanumeric string of the class ID.
					p = skip_over( p );
					break;

			}

			// Jump over caption
			p = skip_over( p );

			// Jump over font
			p = skip_over( p );

			DLGITEMTEMPLATE * pControlData = (DLGITEMTEMPLATE *)p;


			for ( WORD u = 0; u < I386PE_INT16_TO_HOST( &pDlgHeader->cdit ); u++ ) {

		//        DBGTRACE( "Detected child %d: (%d,%d,%u,%u)", pControlData->id, pControlData->x, pControlData->y, pControlData->cx, pControlData->cy );

				AdjustForFont( hWnd, I386PE_INT16_TO_HOST( &pControlData->x  ), I386PE_INT16_TO_HOST( &pControlData->y  ), I386PE_INT16_TO_HOST( &pControlData->cx ), I386PE_INT16_TO_HOST( &pControlData->cy ), r );

				ChildDimensions cd;

				cd.pt.x   = r.left;
				cd.pt.y   = r.top;
				cd.cx     = (unsigned long)( r.right - r.left );
				cd.cy     = (unsigned long)( r.bottom - r.top );

				cd.iCtlID = I386PE_INT16_TO_HOST( &pControlData->id );

				child.push_back( cd );

				uintptr_t ulOffset;

				p = (const uint16_t *)&pControlData->id;

				p++;

				/* Control classname */
				switch( *p ) {

					case 0xFFFF:

						/* What follows is a numerical class-ID */
						p++;

						p++;
						break;

					default:

						/* What follows is an alphanumeric string of the class ID. */
						p = skip_over( p );

						break;

				}

				switch( *p ) {

					case 0xFFFF:

						/* Unidentified */
						/* What follows is a numerical class-ID */
						p++;

						p++;
						break;

					default:

						// Jump over Text
						p = skip_over( p );

						break;

				}

				// Increment over nExtraStuff
				p++;

		//        DBGTRACE( "Calculate address: %p. Modulo remainder: by two %u, by four %u, by 8 %u", p, reinterpret_cast<uintptr_t>( p ) % 2, reinterpret_cast<uintptr_t>( p ) % 4, reinterpret_cast<uintptr_t>( p ) % 8 );
				ulOffset = reinterpret_cast<uintptr_t>( p ) % (uintptr_t)( sizeof( uint32_t ) );

				if ( 0 != ulOffset ) {

					  p = reinterpret_cast<const unsigned short *>(reinterpret_cast<uintptr_t>( p ) + ulOffset );

				}

				pControlData = (DLGITEMTEMPLATE *)p;

			}

			FreeResource( hData );

		//    DBGTRACE( "Recorded %u child-controls", child.size() );

			return true;

		}	

};


#endif /* YW_H_DIALOGINFO_H */
