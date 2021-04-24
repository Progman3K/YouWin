#ifndef YW_GETOPENFILENAME_H
#define YW_GETOPENFILENAME_H


#include <DlgWnd.h>
#include <shlobj.h>
#include <dialoginfo.h>
#include <dirent.h>
#include <sys/stat.h>


#define IDST_LOOKIN                             1091
#define IDST_FOLDER                             1092
#define IDLB_FOLDERS                            1137
#define IDST_FILES                              1088
#define IDLB_FILES                               100
#define IDST_FILENAME                           1090
#define IDE_FILENAME                            1148
#define IDST_FILETYPE                           1089
#define IDCB_FILETYPES                          1136
#define IDST_ENCODING                            259
#define IDCB_ENCODINGS                           101
#define IDRB_OPEN_AS_READ_ONLY                  1040


class GetOpenFileNameDlg : public DlgWnd<GetOpenFileNameDlg> {

        DIR * pDir;

    public:

        GetOpenFileNameDlg() {

            pDir = NULL;
            pofn = NULL;

        }

        virtual ~GetOpenFileNameDlg() {}

        INT_PTR bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override;

    private:

        DialogInfo     portrait;
        DialogInfo     landscape;

        OPENFILENAME * pofn;

        void           HandleOpen( HWND hDlg );

        int            SetToFolder( HWND hDlg, const TCHAR * pszFolder );

        void           OnCommand( HWND hDlg, int iID, HWND hCtlWnd, UINT uiNotifyCode );
        BOOL           OnInit( HWND hDlg, HWND hFocusWnd, LPARAM lParam );
        void           OnDisplayChange( HWND hDlg, UINT uiBitsPerPixel, UINT cx, UINT cy );

//        int  SetToFolder( HWND hDlg, const TCHAR * pszFolder );

};


#endif /* YW_GETOPENFILENAME_H */
