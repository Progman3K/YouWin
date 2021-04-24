

#include "ywin.h"


#ifdef YOU_WIN_TXT
BOOLEAN IsColor( COLORREF color ) {

    if ( color > COLOR_NUM_COLORS ) {

        return false;

    }

    return true;

}
#endif
