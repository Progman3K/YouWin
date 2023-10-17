#ifndef YW_PEN_H
#define YW_PEN_H


#include "gdi.h"
#include "bitmap.h"


class Pen : public GDIObject {

    LOGPEN lp;

    public:

        Pen() : GDIObject( pen, true ) {}

        void set( const LOGPEN * plp ) {

            lp = *plp;

        }

        virtual ~Pen() override {}

};


#endif /* YW_PEN_H */
