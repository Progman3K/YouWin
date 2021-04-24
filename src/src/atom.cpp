

#include "ywin.h"


AtomTable global;


ATOM GlobalFindAtom( const TCHAR * pszString ) {

    atomdescriptor descriptor;

    descriptor.val   = pszString;

    AtomTable::iterator i = global.find( descriptor );

    if ( global.end() == i ) {

        return 0;

    }

    return (*i).second;

}


ATOM GlobalAddAtom( const TCHAR * pszString ) {

    atomdescriptor descriptor;

    descriptor.val   = pszString;

    AtomTable::iterator i = global.find( descriptor );

    if ( global.end() != i ) {

        return (*i).second;

    }

    ATOM ID;

    /* Check if it's a number literal */
    if ( '#' == *pszString ) {

        // ID = string representation of number
        TCHAR * pErrChar;

        ID = _tcstol( pszString + 1, &pErrChar, 0 );

    } else {

        ID = ++global.next;

    }

    descriptor.id = ID;

//    std::pair<std::map<atomdescriptor,ATOM>::iterator,bool> ret;
    std::pair<atom::iterator,bool> ret;

    ret = global.insert( nucleusString( descriptor, ID ) );

    global.byID.insert( nucleusID( ID, ret.first->first.val.c_str() ) );

    return ret.first->first.id;

}


ATOM GlobalDeleteAtom( ATOM nAtom ) {

    idmap::iterator i = global.byID.find( nAtom );

    if ( global.byID.end() == i ) {

        return 0;

    }

    atomdescriptor descriptor;

    descriptor.val = (*i).second;

    AtomTable::iterator j = global.find( descriptor );

    if ( global.end() == j ) {

        return 0;

    }

    global.byID.erase( i );
    global.erase( j );

    return 0;

}


UINT GlobalGetAtomName( ATOM nAtom, TCHAR * pBuffer, int nSize ) {

    idmap::iterator i = global.byID.find( nAtom );

    if ( global.byID.end() == i ) {

        return 0;

    }

    ZeroMemory( pBuffer, nSize * sizeof( TCHAR ) );

    _tcsncpy( pBuffer, (*i).second, nSize - 1 );

    UINT uiRet = _tcslen( pBuffer );

    return uiRet;

}
