#ifndef FNTC_H
#define FNTC_H


#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif


#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


#include <stdio.h>
#include <cstring>
#include <stdlib.h>


#include <ASCII.h>
#include <DbgTrace.h>


#include "../src/font.h"


extern int ReadFontData( FILE * pFile, Font_Header * & pHdr, unsigned & uSize );
extern int WriteFontData( FILE * pFile, ywFont * pFont, unsigned uSize );
extern int ReadCharset( FILE * pFile, ywFont * pFont );

#endif /* FNTC_H */
