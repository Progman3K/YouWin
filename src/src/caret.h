#ifndef YW_CARET_H
#define YW_CARET_H


#include <windows.h>


class Caret {

    public:

        Caret() {

            clear();

        }

        // Resettable items grouped together here.
        void clear() {

            cx            = 0;
            cy            = 0;
            pt.x          = 0;
            pt.y          = 0;

            Cur_LineCol.x = 0;
            Cur_LineCol.y = 0;

            iVisible      = 0;

            bVisible      = false;

            hShapeBMP     = NULL;

        }

        void Invert( HWND hWnd );

        bool hide( HWND hWnd ) {

            if ( bVisible ) {

                Invert( hWnd );
                return true;

            }

            return false;

        }

        unsigned cx;
        unsigned cy;

        POINT    pt;          // Relative to the client area.
        POINT    Cur_LineCol; // First visible line.
        int      iVisible;    // Positive if caret should be visible.
        bool     bVisible;    // True if caret visible.

        HBITMAP  hShapeBMP;

};


#endif /* YW_CARET_H */
