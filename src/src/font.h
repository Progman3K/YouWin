#ifndef YW_FONT_H
#define YW_FONT_H


#include <stdint.h>
#include <map>
#include <tstring.h>


#include "bitmap.h"


#ifndef RT_FONT_VAL
#define RT_FONT_VAL                       8
#endif /* RT_FONT_VAL */


#pragma pack(2)
typedef struct tagchardef /* __attribute__ ((__packed__)) */ {

    uint16_t       c;
    unsigned short cx;
    unsigned short cy;
    unsigned short uscanlinecount;

    COLORREF       uscanlines[0];

    tagchardef() {

        c              = (uint16_t)-1;
        cx             = 0;
        cy             = 0;
        uscanlinecount = 0;

    }

} chardef;
#pragma pack()


class glyph : /* public chardef, */ public IBitmap {

    const chardef * pChardef;

    public:

        glyph( void ) {

            pChardef = 0;

        }

        virtual ~glyph( void ) {}

        BITMAP_FMT getfmt( void ) const override {

            return BITMAP_FMT_FONT;

        }

        void setdef( const chardef * pcd ) { pChardef = pcd; }

        /* IBitmap interface here */
        unsigned getbpp( void ) const override { return 32; }
//        void setbpp( unsigned ) {};
//        bool Create( unsigned cx, unsigned cy, COLORREF c ) { return true; };
//        bool SetPixel( const POINT & pt, COLORREF c ) { return false; };
//        void append( COLORREF c ) {};
        long Width( void ) const override { return pChardef->cx; }
        long Height( void ) const override { return (long)pChardef->cy; }

        bool GetPixel( const POINT & pt, COLORREF & c ) const override {

            c = pChardef->uscanlines[( pt.y * pChardef->cx ) + pt.x ];
            return true;

        }

        const void * data( void ) const override { return pChardef->uscanlines; }

        size_t size( void ) const override { return pChardef->cx * pChardef->cy * sizeof( COLORREF ); }


};

#ifdef __clang__
#define PACKED __attribute__((packed))
#else
#define PACKED __attribute__ ((__packed__))
#endif

typedef struct PACKED tagFont_Header {

    unsigned uWeight;

    typedef enum {

        monochrome = 1,      // Black and white font
        grayscale

    } Flags;

    unsigned flags;             // 32-bit bitfield:
                                // Indicates a monochrome font. Grayscale if not.
                                // Indicates fixed-width.

    unsigned uAvgCharHeight;
    unsigned uAvgCharWidth;
    unsigned uMaxCharHeight;
    unsigned uMaxCharWidth;
    unsigned uLeading;

    char     szName[];

} Font_Header;


class ywFont : public ywObject {

    chardef controlchar;

#ifdef YOU_WIN_TXT
    chardef everychar;
#else
    chardef dimblock;
    chardef spc;
#endif

    glyph tmp;

    public:

        typedef std::map  <uint16_t,const chardef *> Faces;
        typedef std::pair <uint16_t,const chardef *> FacePair;

        Faces       glyphs;
        const Font_Header * pHdr;

        ywFont( const Font_Header * pFontHdr ) {

            setType( OBJECT_TYPE_FONT );
            pHdr = pFontHdr;

#ifdef YOU_WIN_TXT
            everychar.cx = 1;
            everychar.cy = 1;
#endif

        }


        virtual ~ywFont() override {

        }

        void _create( void );

        void GetMetrics( TEXTMETRIC * pTM ) const {

            pTM->tmHeight       = pHdr->uAvgCharHeight;
            pTM->tmAveCharWidth = pHdr->uAvgCharWidth;
            pTM->tmMaxCharWidth = pHdr->uMaxCharWidth;

        }


        const glyph * GetFace( uint16_t c ) {

#ifdef YOU_WIN_TXT
            everychar.c = c;
            tmp.setdef( &everychar );
            return &tmp;
#else
            if ( ' ' >= c ) {

                if ( ' ' == c ) {

                    return 0;

                } else {

                    tmp.setdef( &controlchar );
                    return &tmp;

                }

            }

            const Faces::iterator i = glyphs.find( c );

            if ( glyphs.end() == i ) {

                DBG_MSG( DBG_ERROR, TEXT( "Error: Requested glyph '%u' not found" ), (unsigned)c );
//                tmp.setdef( &dimblock );
                return 0;

            }

//            DBG_DMP( DBG_GENERAL_INFORMATION, i->second.pFace->data(), i->second.pFace->Width() * i->second.pFace->Height() );

            tmp.setdef( i->second );
            return &tmp;
#endif

        }

#if 0
        bool ldfaces( glyph * pGlyph, int n ) {

            for ( ; n > 0; n--, pGlyph++ ) {

                UTF_16 c = pGlyph->c;

                glyphs.insert( glyphs.end(), FacePair( c, *pGlyph ) );

            }

            return true;

        }


        void unld( void ) {

#ifndef YOU_WIN_TXT
            if ( NULL != dimblock.pFace ) {

                Bitmap::discard( dimblock.pFace );
                dimblock.pFace = NULL;

            }

            if ( NULL != spc.pFace ) {

                Bitmap::discard( spc.pFace );
                spc.pFace = NULL;

            }
#endif

            for( ; glyphs.begin() != glyphs.end(); ) {

                Faces::iterator i = glyphs.begin();

                Bitmap::discard( i->second.pFace );

                glyphs.erase( i );

            }

        }


        bool LoadFON( LPCTSTR lpszFONFile );
#endif

//        int open( HMODULE hInst, LPCTSTR ID );


};


typedef std::pair <TSTRING, ywFont> FontPair;


class FontList : public std::map <TSTRING, ywFont> {

    public:

        const ywFont * open( const ResourceList & resource, LPCTSTR pszName );

        const ywFont * Find( LPCTSTR pszName ) {

            const iterator & i = find( pszName );

            if ( end() == i ) {

//                DBG_MSG( DBG_ERROR, TEXT( "Error: Requested font '%s' not found among:" ), pName );
//                for ( iterator i = begin() ; i != end(); i++ ) {
//                    DBG_MSG( DBG_ERROR, TEXT( "'%s'" ), i->first.c_str() );
//                }

                return NULL;

            }

            return &i->second;

        }

};


extern  FontList fonts;


#endif /* YW_FONT_H */
