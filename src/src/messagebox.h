#ifndef YW_MESSAGEBOX__H
#define YW_MESSAGEBOX__H


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


#include <vector>
#include <classatoms.h>
#include <DlgWnd.h>
#include <tstring.h>
#include <windowsx.h>
#include <UTF16.h>


#define LONIBBLE(b) (b & 0x0F)
#define HINIBBLE(b) (b & 0xF0)

#define IDST_ICON 0x14


typedef struct tagMsgBoxParams {

    LPCTSTR lpszText;
    LPCTSTR lpszTitle;
    UINT    uType;

    tagMsgBoxParams() {

        lpszText  = 0;
        lpszTitle = 0;
        uType     = 0;

    }

} MsgBoxParams;


class MessageBoxDlg : public DlgWnd<MessageBoxDlg> {

    HWND hMessageWnd;
    HWND hIconWnd;

    std::vector<HWND> buttons;

    public:

        MessageBoxDlg() {

            hMessageWnd        = NULL;
            hIconWnd           = NULL;

            Icon.cy = 0;
            Icon.cy = 0;

            iButtonCY = 0;
            lButtonMaxLabelCX = 0;
            iMaxCXLine = 0;

            r.bottom = 0;
            r.left = 0;
            r.right = 0;
            r.top = 0;

        }


        virtual ~MessageBoxDlg() {

            hMessageWnd        = NULL;
            hIconWnd           = NULL;

        }

        INT_PTR         bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override;

    private:

        TSTRING         Title;
        TSTRING         Text;

        SIZE            Icon;

        int             iButtonCY;

        LONG            lButtonMaxLabelCX;
        LONG            iMaxCXLine;
        RECT            r;

        MsgBoxParams    Params;

        /* stuff that only needs to be calculated once */
        void            init( HWND hWnd, HDC hDC, MsgBoxParams & Params );
        HWND            makebutton( HWND hParentWnd, unsigned short uCtlType, unsigned short uID, int iStringID, unsigned uFlags, LPCTSTR lpszText, const TCHAR * pParam );
        void            buttonselect( unsigned );

        /* Whenever screen-geometry changes */
        void            Layout( HWND hWnd, HDC hDC );

        void            OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        void            OnDisplayChange( HWND hWnd, UINT, UINT, UINT );
        BOOL            OnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );

        typedef struct tagbutton_def {

            HWND           hParentWnd;
            unsigned short uCtlType;
            unsigned short uID;
            int            iStringID;
            unsigned       uFlags;
            LPCTSTR        lpszText;
            LPCTSTR        pParam;

            tagbutton_def( HWND hWnd, unsigned short uType, unsigned short ID, int iSID, unsigned uF, LPCTSTR pszText, LPCTSTR Param ) {

                hParentWnd = hWnd;
                uCtlType   = uType;
                uID        = ID;
                iStringID  = iSID;
                uFlags     = uF;
                lpszText   = pszText;
                pParam     = Param;

            }

        } button_def;

        template <class button_def> bool makebuttons( std::initializer_list<button_def> list ) {

            for( auto btn : list ) {

                if ( ! makebutton( btn.hParentWnd, btn.uCtlType, btn.uID, btn.iStringID, btn.uFlags, btn.lpszText, btn.pParam ) ) {

                    return false;

                }

            }

            return true;

        }

};


#endif  /* YW_MESSAGEBOX__H */
