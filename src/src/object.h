#ifndef YW_OBJECT_H
#define YW_OBJECT_H


#include <windows.h>


#define RT_GDI_VAL 0x0FEFE

#ifndef RT_CURSOR_VAL
#define RT_CURSOR_VAL 1
#endif /* ! RT_CURSOR_VAL */

#ifndef RT_BITMAP_VAL
#define RT_BITMAP_VAL 2
#endif /* ! RT_BITMAP_VAL */

#ifndef RT_ICON_VAL
#define RT_ICON_VAL 3
#endif /* ! RT_ICON_VAL */

#ifndef RT_MENU_VAL
#define RT_MENU_VAL 4
#endif /* ! RT_MENU_VAL */

#ifndef RT_FONT_VAL
#define RT_FONT_VAL 8
#endif /* ! RT_FONT_VAL */

#ifndef RT_REGION_VAL
#define RT_REGION_VAL 25
#endif /* ! RT_REGION_VAL */


typedef enum {

    OBJECT_TYPE_EVENT,
    OBJECT_TYPE_IO,
    OBJECT_TYPE_FF,
    OBJECT_TYPE_MODULE,

    OBJECT_TYPE_GDI            /* = RT_GDI_VAL */,
    OBJECT_TYPE_USERBITMAP     /* = RT_BITMAP_VAL */,
    OBJECT_TYPE_RESOURCEBITMAP /* = RT_BITMAP_VAL */,
    OBJECT_TYPE_CURSOR         /* = RT_CURSOR_VAL */,
    OBJECT_TYPE_FONT           /* = RT_FONT_VAL */,
    OBJECT_TYPE_ICON           /* = RT_ICON_VAL */,
    OBJECT_TYPE_MENU           /* = RT_MENU_VAL */,
    OBJECT_TYPE_REGION         /* = RT_REGION_VAL */,

    OBJECT_TYPE_RESOURCE

} ywObjectType;


class IObject {

    public:

        virtual ~IObject() {}

        virtual ywObjectType type() = 0;

};


class ywObject : public IObject {

        ywObjectType uType;

    public:

        unsigned uLockingCount;


        ywObject( void ) {

            uLockingCount = 0;

        }

        ywObjectType type( void ) /* override */ {

            return uType;

        }

        void setType( ywObjectType typ ) {

            uType = typ;

        }

};


#endif /* YW_OBJECT_H */
