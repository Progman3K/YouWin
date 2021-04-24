

#include "ywin.h"


SysColorList SysColors;


DWORD GetSysColor( int nIndex ) {

    const SysColorList::iterator i = SysColors.find( nIndex );

    if ( SysColors.end() != i ) {

        return i->second->GetColor();

    }

    DBG_MSG( DBG_ERROR, TEXT( "Unknown system color %d requested" ), nIndex );
    return 0;

}


HBRUSH GetSysColorBrush( int nIndex ) {

    const SysColorList::iterator i = SysColors.find( nIndex );

    if ( SysColors.end() != i ) {

        return i->second;

    }

    DBG_MSG( DBG_ERROR, TEXT( "Unknown system color brush %d requested" ), nIndex );
    return NULL;

}


BOOL SetSysColors( int cElements, const INT * lpaElements, const COLORREF * lpaRgbValues ) {

    if ( 1 > cElements ) {

        return false;

    }

    SysColorList::iterator i;

    for( ; 0 < cElements; cElements-- ) {

        i = SysColors.find( *lpaElements + ( cElements - 1 ) );

        if ( SysColors.end() != i ) {

            i->second->SetColor( *lpaRgbValues + ( cElements - 1 ) );

        }

    }

    return true;

}
