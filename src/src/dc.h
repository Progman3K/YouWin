#ifndef YW_H_DC_H
#define YW_H_DC_H


//#include "font.h"
#include "iwindow.h"
#include "syscolors.h"


typedef struct {

    COLORREF fg; // Foreground color.
    COLORREF bg; // Background color.

} COLOR_PAIR;


class DC {

    public:

        typedef enum {

            StaticToWindow = 0x0001,
            EntireScreen   = 0x0002,
            EntireWindow   = 0x0004,
            Memory         = 0x0008

        } Flags;

//        unsigned  flags;        // Bitfield of DC::Flags
        Flags flags;

        COLOR_PAIR text;          // Current fg/bg color of text.

        DC( IWindow * pFromWnd, Region * pRegion, IBitmap * pixels, Flags uflags );

        int AddIntersection( Region * pRgn );

        int AddExclusion( Region * pRgn );

        void copy( const POINT & pt, DC * pDC, const RECT & r );

        /**
         *  Fill a rectangle with a colour
         */
        void fill( const RECT & r, COLORREF cFill );

        void Invert( const RECT & r );

        void paint( const POINT & pt, COLORREF c );

        bool GetPixel( const POINT & pt, COLORREF & c );

        bool SetPixel( POINT pt, COLORREF c, COLORREF /* pixel */ );

        void SetSize( unsigned cx, unsigned cy );

        void SetShape( Region * pRegion );

        bool In( POINT & pt ) const;

        int TypeByteAt( HFONT hFont, POINT pt, UINT uFlags, UINT uFormat, TCHAR c, const RECT * pr );

        void      Out( const POINT & pt, COLORREF c );

        IWindow * pWnd;

        HFONT     hFont;

        POINT     ptPen;           // Current Position of text pen

//      HBRUSH      hbrBackground;
        int       iBkMode;
        UINT      uiTextAlignMode;

        bool      bInDrawText;
        UINT      uiDTMode;     // 0 unless DC is being used by a DrawTextCall, in which case the flags are copied here.

        IBitmap * pPixels;

        Region    shape;        // Output functions use to clip.

        Region    intersect;    // Output functions use to clip.
        Region    exclude;      // Output functions use to clip.

    private:

        unsigned  uXScroll;
        unsigned  uYScroll;

};


#endif /* YW_H_DC_H */
