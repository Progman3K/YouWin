#ifndef __EDIT_TEXT_H__
#define __EDIT_TEXT_H__


#include <windowsx.h>
#include <windows.h>


#ifdef WIN32
#define EOL TEXT( "\r\n" )
#else
#define EOL TEXT( "\n" )
#endif


class EditText {

    public:

        static BOOL DoEdit_ScrollCaret( HWND hEditWnd ) {

            int iLen;

            iLen = GetWindowTextLength( hEditWnd );
            Edit_SetSel( hEditWnd, iLen, iLen );

#if defined( _WIN32 ) || defined( _WIN32_WCE )
            Edit_ScrollCaret( hEditWnd );
#endif

            return true;

        }


        static void AddText( HWND hEditWnd, LPCTSTR lpszText ) {

            int iLen;

            iLen = GetWindowTextLength( hEditWnd );
            Edit_SetSel( hEditWnd, iLen, iLen );
            Edit_ReplaceSel( hEditWnd, lpszText );

        }


        static BOOL AppendTextEx( HINSTANCE hInst, HWND hEditCtl, LPCTSTR lpszText, size_t StringSize, BOOL bOnANewLine, BOOL bScrollCaret ) {

            TCHAR szTemp[1024];

            if ( ! IsWindow( hEditCtl ) ) {

                /* Window does not yet exist or no longer exists. */
                return false;

            }

            if ( 0 == HIWORD( lpszText ) ) {

                ZeroMemory( szTemp, sizeof( szTemp ) );

                if ( 0 == LoadString( hInst, LOWORD( (uintptr_t)lpszText ), szTemp, ( sizeof( szTemp ) / sizeof( szTemp[0] ) ) - 1 ) ) {

                    return false;

                }

                lpszText = szTemp;

            }

            if ( bOnANewLine ) {

                AddText( hEditCtl, EOL );

            }

            AddText( hEditCtl, lpszText );

            if ( bScrollCaret ) {

                DoEdit_ScrollCaret( hEditCtl );
            }

            return true;

        }


        static int AppendText( HINSTANCE hInst, HWND hWnd, const TCHAR * lpszText, size_t StringSize, bool bOnANewLine ) {

            return AppendTextEx( hInst, hWnd, lpszText, StringSize, bOnANewLine, true );

        }

};


#endif  /* __EDIT_TEXT_H__ */
