#ifndef YW_DLG_WND_H
#define YW_DLG_WND_H


#include <windows.h>


#ifndef GWL_USERDATA
#define GWL_USERDATA        (-21)
#endif


template <class T> class DlgWnd {

    public:

        HWND m_hDlg;

        virtual INT_PTR bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) = 0;

        static T * GetThis( HWND hDlg ) {

            return (T *)GetWindowLongPtr( hDlg, GWL_USERDATA );

        }

        static T * SetThis( HWND hDlg, T * pThis ) {

            return (T *)SetWindowLongPtr( hDlg, GWL_USERDATA, (LONG_PTR)pThis );

        }

        static INT_PTR CALLBACK bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

            T * pThis = GetThis( hDlg );

            if ( 0 == pThis ) {

                pThis = new T;

                if ( 0 == pThis ) {

                    return false;

                }

                pThis->m_hDlg = hDlg;

                SetThis( hDlg, pThis );

            }

            switch( uiMsg ) {

#if defined( UNDER_CE ) || defined( linux ) || defined( ANDROID )
                case WM_DESTROY:

                    /* Under Windows CE, the very last message received is WM_DESTROY */
                    BOOL bRet = pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

                    SetThis( hDlg, 0 );

                    delete pThis;

                    return bRet;

#elif defined( WIN32 ) /* ! UNDER_CE */

                case WM_NCDESTROY:

                    /* On regular Windows, the very last message received is WM_NCDESTROY */
                    INT_PTR bRet = pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

                    SetThis( hDlg, 0 );

                    delete pThis;

                    return bRet;
#endif

            }

            return pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

        }

};


#endif /* YW_DLG_WND_H */
