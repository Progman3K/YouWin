#ifndef YW_MESSAGEBOX__H
#define YW_MESSAGEBOX__H


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


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
    HWND hOKButtonWnd;
    HWND hYesButtonWnd;
    HWND hNoButtonWnd;
    HWND hCancelButtonWnd;
    HWND hIconWnd;

    public:

        MessageBoxDlg() {

            hMessageWnd      = NULL;
            hOKButtonWnd     = NULL;
            hYesButtonWnd    = NULL;
            hNoButtonWnd     = NULL;
            hCancelButtonWnd = NULL;
            hIconWnd         = NULL;

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

            hMessageWnd      = NULL;
            hOKButtonWnd     = NULL;
            hYesButtonWnd    = NULL;
            hNoButtonWnd     = NULL;
            hCancelButtonWnd = NULL;

        }

        INT_PTR         bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override;

    private:

        TSTRING         Title;
        TSTRING         Text;

        utf16string     OK;
        utf16string     Cancel;
        utf16string     Yes;
        utf16string     No;

        SIZE            Icon;

        int             iButtonCY;

        LONG            lButtonMaxLabelCX;
        LONG            iMaxCXLine;
        RECT            r;

        MsgBoxParams    Params;

        /* stuff that only needs to be calculated once */
        void            init( HWND hWnd, HDC hDC, MsgBoxParams & Params );

        void            Layout( HWND hWnd, HDC hDC );

        void            OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        void            OnDisplayChange( HWND hWnd, UINT, UINT, UINT );
        BOOL            OnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );

};


#endif  /* YW_MESSAGEBOX__H */
