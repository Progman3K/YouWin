

#include "ywin.h"


const Menu * MenuList::open( HMODULE hInst, LPCTSTR resname ) {

    /* Look in the resources, and look for this */
    const ResourceList * pResources = reinterpret_cast<const ResourceList *>( hInst );

    const Resource * pResource = pResources->find( resname, RT_MENU );

    /* If found in the resources, look in the list to see if an existing icon is already using this. */
    if ( 0 == pResource ) {

        return 0;

    }

    const auto i = find( pResource );

    if ( end() != i ) {

        return &i->second;

    }

    /* If not found, create it. */
    Menu menu( pResources, pResource );

    auto f = emplace( pResource, menu );

    DBG_MSG( DBG_ERROR, TEXT( "Make menu: %s" ), f.second ? "Success" : "Failed" );

    if ( false == f.second ) {

        return 0;

    }

    return &f.first->second;

}
