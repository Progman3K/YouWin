#ifndef YW_PEN_H
#define YW_PEN_H


#include "gdi.h"

#include "bitmap.h"


class Pen : public GDIObject {

    public:

        Pen() : GDIObject( pen, true ) {}

        virtual ~Pen() override {}

};


#endif /* YW_PEN_H */
