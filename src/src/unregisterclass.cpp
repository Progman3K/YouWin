

#include "ywin.h"


BOOL UnregisterClass( LPCTSTR lpszClassName, HINSTANCE hInst ) {

    TSTRING s;

    s.ToUpper( lpszClassName );

    ClassList::iterator i = classes.find( s.c_str() );

    if ( classes.end() == i ) {

        DBG_MSG( DBG_ERROR, TEXT( "Error - UnregisterClass: class '%s' NOT FOUND" ), lpszClassName );
        return false;

    }

    UserWindowClass * pClass = reinterpret_cast<UserWindowClass *>( i->second );

    if ( CS_SYSTEM & pClass->GetClassStyles() ) {

        /* System classes cannot be unregistered */
        DBG_MSG( DBG_ERROR, TEXT( "System class '%s' not unregistered" ), lpszClassName );
        return false;

    }

    // Do any windows of said class exist?
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "User class '%s' unregistered" ), lpszClassName );

    delete pClass;

    classes.erase( i );

    return true;

}
