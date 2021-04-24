

#include "chatter.h"


LPCTSTR INet_NToT( in_addr addr ) {

    static TCHAR szAddr[32];

    ZeroMemory( szAddr, sizeof( szAddr ) );

//    unsigned u = addr.S_un.S_un_b.s_b1;

//s_host  S_un.S_un_b.s_b2
//s_net   S_un.S_un_b.s_b1
//s_impno S_un.S_un_b.s_b4
//s_lh    S_un.S_un_b.s_b3
    unsigned host  = addr.s_addr & 0xFF;
    unsigned net   = ( addr.s_addr & 0xFF00 ) >> 8;
    unsigned impno = ( addr.s_addr & 0xFF0000 ) >> 16;
    unsigned lh    = ( addr.s_addr & 0xFF000000 ) >> 24;

    _stprintf( szAddr, TEXT( "%u.%u.%u.%u" ), host, net, impno, lh );

    return szAddr;

}


CWho * CChatterMainWnd::GetYou( Entity entity, sockaddr_in sin, int * piListBoxIndex ) {

    CWho * pYou = NULL;
    int    i    = 0;

    /* Prepare to look through the list of conversation partners */
    if ( LB_ERR == ( i = ListBox_GetCount( hUserListWnd ) ) ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Internal error accessing peer listbox: %lX" ), (uintptr_t)hUserListWnd );
        return NULL;

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Looking through %u peers" ), (unsigned)i );

    unsigned uDOSCount = 0;

    /* Look for the partner who sent the data */
    for( int j = 0; j < i; j++ ) {

        pYou = (CWho *)ListBox_GetItemData( hUserListWnd, j );

        if ( entity != pYou->GetEntity() ) {

            /* Not this one */
            continue;

        }

        /* Sanity check: should be from the same IP:PORT combo as last time... */
        sockaddr_in YourSin = pYou->GetSin();

        if ( ! ( ( YourSin.sin_addr.s_addr == sin.sin_addr.s_addr ) && ( YourSin.sin_port == sin.sin_port ) && ( YourSin.sin_family == sin.sin_family ) ) ) {

//            DBG_MSG( DBG_WARNING, TEXT( "Peer imposter? entity %lX, IP changed: %s:%u AF:%u != %s:%u AF:%u" ), (long)entity, INet_NToT( YourSin.sin_addr ), (unsigned)ntohs( YourSin.sin_port ), (unsigned)YourSin.sin_family, INet_NToT( sin.sin_addr ), (unsigned)ntohs( sin.sin_port ), (unsigned)sin.sin_family );

            /* Could be an attack... */
            uDOSCount++;
            continue;

        }

        /* We have found the host who sent the data. */
        if ( NULL != piListBoxIndex ) {

            /* User wants us to return the listbox ID also. */
            *piListBoxIndex = j;

        }

        return pYou;

    }

    if ( NULL == piListBoxIndex ) {

        /* User does NOT want us to create a new one. */
        return NULL;

    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Not found, create" ) );

    if ( NULL == ( pYou = new CWho( entity, sin ) ) ) {

        return NULL;

    }

    TCHAR szTemp[128];

    _stprintf( szTemp, TEXT( "%s:%u" ), INet_NToT( sin.sin_addr ), (unsigned)ntohs( sin.sin_port ) );

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Adding '%s' to list" ), szTemp );

    if ( LB_ERR == ( i = ListBox_AddString( hUserListWnd, szTemp ) ) ) {

        delete pYou;
        return NULL;

    }

    if ( LB_ERR == ListBox_SetItemData( hUserListWnd, i, pYou ) ) {

        ListBox_DeleteString( hUserListWnd, i );

        delete pYou;
        return NULL;

    }

    /* Return the new listbox item ID also. */
    *piListBoxIndex = i;

    /* Introduce yourself */
    FORWARD_WM_TIMER( m_hDlg, ID_CHATTER_BROADCAST_TIMER, PostMessage );

    return pYou;

}
