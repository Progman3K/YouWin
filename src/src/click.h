#ifndef YW_H_CLICK_H
#define YW_H_CLICK_H


#include <windows.h>


class Click {

    public:

        Click() {

             reset();

        }

        void reset( void ) {

            hWnd   = NULL;
            dwWhen = 0;

            pt.x = -1;
            pt.y = -1;

        }

        HWND  hWnd;
        DWORD dwWhen;
        POINT pt;

};


#endif /* YW_H_CLICK_H */
