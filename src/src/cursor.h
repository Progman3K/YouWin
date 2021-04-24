#ifndef YW_CURSOR_H
#define YW_CURSOR_H


#include <windows.h>


#include "resource.h"


class Cursor : public Object {

    public:

        Cursor() : Object( OBJECT_TYPE_CURSOR ) {}
        virtual ~Cursor() override {}

};


#endif /* YW_CURSOR_H */
