#ifndef YW_ICON_H
#define YW_ICON_H


#include "bitmap.h"


/*
Icon Resources

The ICON statement in the .RC script does not create a single
resource object, but creates a group of resources.  This allows
Windows programs a degree of device-independence through the use of
different pixel bitmaps on hardware configurations with differing
capabilities.  Icons, most often designed for differing numbers of
pixel planes and pixel counts, are grouped and treated by Windows as
a single resource.  In the .RES and .EXE files, however, they are
stored as a group of resources.  These groups are stored in a .RES
file with the components first (in this case the different icons
[type 3]) and a group header following (Type 14).  The group header
contains the information necessary to allow Windows to select the
proper icon to display.

The components have the following structure:

        [Resource header (type = 3)]

        [DIB Header]
        [Color DIBits of icon XOR mask]
        [Monochrome DIBits of AND mask]

Each component is given an ordinal ID that is unique from all other
icon components.

The Device Independent Bitmap (DIB) header's fields represent the
masks' information separately with two exceptions.  First, the height
field represents both the XOR and AND masks.  Before converting the
two DIBs to Device Dependent Bitmaps (DDB), the height should be
divided by two.  The masks are always the same size and are one-half
the size given in the DIB header.  Second, the number of bits per
pixel and bit count refer to the XOR mask.  The AND mask is always
monochrome and should be interpreted as having one plane and one bit
per pixel.  Before using an icon with Windows refer to the SDK
reference materials for more information on DIBs.  Since the format
of an icon component closely resembles the format of the .ICO file,
the documentation in section 9.2 of the Windows SDK Reference is
useful.  DDBs should not be used for Windows 32 applications.

The group header is described here:

    [Resource header (type = 14)]
*/


typedef struct __attribute__ ((__packed__)) {

    WORD Reserved; // Currently zero 
    WORD ResType;  // 1 for icons
    WORD ResCount; // Number of components

} NEWHEADER;


typedef struct __attribute__ ((__packed__)) {

    BYTE         bWidth;
    BYTE         bHeight;
    BYTE         bColorCount;
    BYTE         bReserved;
    WORD         wPlanes;
    WORD         wBitCount;
    unsigned int lBytesInRes;
    unsigned int uOffset; // ID of icon in resources

} IconHeader;


typedef struct __attribute__ ((__packed__)) {

    NEWHEADER  hdr;
    IconHeader entry[1];

    /*
     * XOR and AND masks follow
     * The height of each is half what is reported.
     */

} IconGroupHeader;


typedef struct __attribute__ ((__packed__)) {

    BYTE Width;
    BYTE Height;
    BYTE ColorCount;
    BYTE reserved;

} ICONRESDIR;


typedef struct __attribute__ ((__packed__)) {

    WORD         wPlanes;
    WORD         wBitCount;
    unsigned int lBytesInRes;
    WORD         wNameOrdinal; // Points to component
    WORD         padding;      // filler for DWORD alignment

} ICONHEADER;

// The next portion is repeated for each component resource:

typedef struct __attribute__ ((__packed__)) {

    BYTE         bWidth;
    BYTE         bHeight;
    BYTE         bColorCount;
    BYTE         bReserved;
    WORD         wPlanes;
    WORD         wBitCount;
    unsigned int lBytesInRes;
    WORD         wNameOrdinal; // ID of icon in resources

} ResourceDirectory;


typedef struct __attribute__ ((__packed__)) {

    NEWHEADER         hdr;
    ResourceDirectory entry[1];

    /*
     * XOR and AND masks follow
     * The height of each is half what is reported.
     */

} IconDirectory;


/*
Notice that the group header consists of a fixed header and data that
repeats for each group component.  Both of these parts are fixed
length allowing for random access of the group component information.

This group header contains all of the data from the .ICO header and
from the individual resource descriptors.
*/


class ResIcon : public IBitmap {

    bool GetPixel1bpp( const POINT & pt, COLORREF & c ) const;
    bool GetPixel4bpp( const POINT & pt, COLORREF & c ) const;
    bool GetPixel8bpp( const POINT & pt, COLORREF & c ) const;
    bool GetPixel24bpp( const POINT & pt, COLORREF & c ) const;
    bool GetPixel32bpp( const POINT & pt, COLORREF & c ) const;

    public:

        const BITMAPINFO * pBI;
        const BYTE *       pDIB;
        const BYTE *       pAND;

        ResIcon( const BITMAPINFO * p );
        virtual ~ResIcon( void ) {}

        /* IBitmap API */
        const void * data( void ) const override { return pBI; }
        long Width( void ) const override { return I386PE_INT32_TO_HOST( &pBI->bmiHeader.biWidth ); }
        long Height( void ) const override { return I386PE_INT32_TO_HOST( &pBI->bmiHeader.biHeight ) / 2; }
        unsigned getbpp( void ) const override { return I386PE_INT16_TO_HOST( &pBI->bmiHeader.biBitCount ); }
        BITMAP_FMT getfmt( void ) const override { return BITMAP_FMT_NONE; }
        size_t size( void ) const override { return ( getbpp() * ( (size_t)Width() * (size_t)Height() ) ) / (size_t)8; }
        bool GetPixel( const POINT &, COLORREF & ) const override;

};


class Icon : public Object {

    void _create( const ResourceList * pResList, const Resource * pRes );

    public:

        const Resource * pResource;

        const ResourceDirectory * pDir;
        const IconDirectory * pIconDir;

        std::vector<ResIcon> BMP;

        const IBitmap * GetBmp( void ) const;

        Icon( const ResourceList * pResList, const Resource * pRes ) {

            setType( OBJECT_TYPE_ICON );
            _create( pResList, pRes );

        }

        virtual ~Icon() override {}


//        void close( void );

};


class IconList : public std::map<const Resource *,Icon> {

    public:

        const Icon * open( HMODULE hInst, LPCTSTR ID );

};


extern  IconList icons;


#endif /* YW_ICON_H */
