#ifndef YW_RESOURCE_H
#define YW_RESOURCE_H


#include <UTF16.h>
#include <tstring.h>


#include "object.h"


typedef struct {

    unsigned int    uiSize;
    unsigned int    uiSizeOfHeader;
    UTF_16          TypeName[12];
    char            cData[];

} RES_HEADER;


typedef struct tagResourceId {

    const RES_HEADER * pHeader;

    const UTF_16 * pszType;
    const UTF_16 * pszName;

    uint16_t uType;
    uint16_t uName;

    const char * pData;

//    uintptr_t uSize;

    tagResourceId() {

        pHeader = 0;
        pszName = 0;
        pszType = 0;
        uName   = 0;
        uType   = 0;
        pData   = 0;

    }

} ResourceId;


class Resource : public Object {

    public:

        ResourceId Id;

        virtual ~Resource() override {}

        Resource() : Object( OBJECT_TYPE_RESOURCE ) {}

//        static BOOL bLoad( HINSTANCE hInst, const TCHAR * Type, const TCHAR * ResID, byte_array * buffer );

};


class ResourceList : public std::vector <Resource> {

    public:

        static void LoadStaticResources( ResourceList & resources, const char * pStart, uintptr_t uSize );

        const Resource * find( LPCTSTR resname, LPCTSTR restype ) const {

            for ( const Resource & resource : *this ) {

                if ( 0 == HIWORD( restype ) ) {

                    // Type must be numerical
                    if ( 0 == resource.Id.uType ) continue; // Type not numerical

                    if ( LOWORD( restype ) != resource.Id.uType ) continue; // Not right type

                } else {

                    // Type must be alphanumerical
                    if ( 0 != resource.Id.uType ) continue; // Not alphanumerical type

                    TSTRING tType( resource.Id.pszType );

//                    if ( 0 != _tcscmp( restype, resource.Id.pszType ) ) continue; // Not right type
                    if ( 0 != tType.comparei( restype ) ) continue; // Not right type

                }

                // type OK

                if ( 0 == HIWORD( resname ) ) {

                    // Name must be numerical
                    if ( 0 == resource.Id.uName ) continue; // Name not numerical

                    if ( LOWORD( resname ) != resource.Id.uName ) continue; // Not right name

                } else {

                    // Name must be alphanumerical
                    if ( 0 != resource.Id.uName ) continue; // Name not alphanumerical

                    TSTRING tName( resource.Id.pszName );

//                    if ( 0 != _tcscmp( resname, resource.Id.pszName ) ) continue; // Not right name
                    if ( 0 != tName.comparei( resname ) ) continue; // Not right name

                }

                return &resource;

            }

            return 0;

        }

};


class ResourceLocator {

    public:

        /* The three things that define the resource: */
        HMODULE     hModule;    // Resource located in.
        ObjectType  uType;
        long        lOffset;    // Location inside module.
        unsigned    uSize;      // Size in bytes of the resource.


};


#endif /* YW_RESOURCE_H */
