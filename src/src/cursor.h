#ifndef YW_CURSOR_H
#define YW_CURSOR_H


#include <windows.h>


#include "resource.h"


class ywCursor : public ywObject {

    public:

        ywCursor() {

            setType( OBJECT_TYPE_CURSOR );

        }

        virtual ~ywCursor() override {}

};


#endif /* YW_CURSOR_H */
