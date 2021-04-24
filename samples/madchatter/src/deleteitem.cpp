

#include "chatter.h"


void CChatterMainWnd::OnDeleteItem( HWND hDlg, const DELETEITEMSTRUCT * pdi ) {

    CWho * pYou = reinterpret_cast<CWho *>( pdi->itemData );

    delete pYou;

}
