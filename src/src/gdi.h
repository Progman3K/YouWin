#ifndef YW_GDI_H
#define YW_GDI_H


#include "object.h"


class GDIObject : public ywObject {

    public:

        typedef enum {

            pen,
            solid_brush
//            bitmap

        } GDIObjectType;

        GDIObjectType GDIObjType;
        bool          bStatic;

        GDIObject( GDIObjectType otype, bool bSystem ) {

            setType( OBJECT_TYPE_GDI );
            GDIObjType = otype;
            bStatic    = bSystem;

        }

};


#endif /* YW_GDI_H */
