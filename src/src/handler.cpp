

#include "ywin.h"


int Handler::PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    MetaMSG Msg;

    Msg.Msg.hwnd    = hWnd;
    Msg.Msg.message = uiMsg;
    Msg.Msg.wParam  = wParam;
    Msg.Msg.lParam  = lParam;

    return pQ->PostToQ( pQ->MsgQ, &Msg );

}
