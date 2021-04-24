

#ifndef H_UTF16STRING_H_INCLUDED
#define H_UTF16STRING_H_INCLUDED


#include <tchar.h>
#include <windows.h>
#include <string>

#include <stringlocator.h>

typedef unsigned short UTF_16;


#ifndef Dim
#define Dim( array ) ( sizeof( array ) / sizeof( array[0] ) )
#endif


#define I386PE_INT16_TO_HOST( pu16 ) ((((unsigned char *)pu16)[0]<<0) | (((unsigned char *)pu16)[1]<<8))
#define I386PE_INT32_TO_HOST( pu32 ) ((((unsigned char *)pu32)[0]<<0) | (((unsigned char *)pu32)[1]<<8) | (((unsigned char *)pu32)[2]<<16) | (((unsigned char *)pu32)[3]<<24))


inline size_t wcharlen( const WCHAR * p ) {

    size_t len = 0;

    for( ; *p; p++, len++ );

    return len;

}


class utf16string : public std::basic_string<UTF_16> {

    public:

        std::basic_string<TCHAR> tcharz;

        bool LoadString( HINSTANCE hInst, UINT uID ) {

            resourcestringlocator string;

            string.us = uID;

            HRSRC hString = FindResource( hInst, MAKEINTRESOURCE( string.ID.blocknumber + 1 ), RT_STRING );

            if ( NULL == hString ) {

                return false;

            }

            HGLOBAL hRes = LoadResource( hInst, hString );

            StringEntry * pSE = (StringEntry *)LockResource( hRes );

            for ( unsigned u = 0; u <= string.ID.blockposition; u++ ) {

                if ( u == string.ID.blockposition ) {

                    /* Found string we are looking for */
                    append_from_resource( pSE->Text, I386PE_INT16_TO_HOST( &pSE->wLen ) );

                    /* Convert */
                    tcharz.clear();
                    tcharz_str();
                    break;

                } else {

                    /* Skip over to next string */
                    pSE = (StringEntry *)( &pSE->Text[ I386PE_INT16_TO_HOST( &pSE->wLen ) ] );

                }

            }

            FreeResource( hRes );

            return size() > 0;

        }


        const TCHAR * tcharz_str() {

            /* Only perform conversion once */
            if ( 0 == tcharz.size() ) {

                for( size_t u = 0; u < size(); u++ ) {

                    tcharz.push_back( at( u ) );

                }

            }

            return tcharz.c_str();

        }


        const UTF_16 * append_from_native( const UTF_16 * pszSource ) {

            for ( ; *pszSource; pszSource++ ) {

                append_from_native( pszSource, 1 );

            }

            /* Point past caption and its NUL */
            const UTF_16 * p = pszSource + /* size() */ + 1;

            if ( 0 != ( size() % 2 ) ) {

                /* Align on short boundary */
                p++;

            }

            return p;

        }


        const UTF_16 * append_from_native( const UTF_16 * pszSource, unsigned uLen ) {

            for ( unsigned u = 0; u < uLen; u++ ) {

                append( 1, *pszSource );

                pszSource++;

            }

            return pszSource;

        }


        const UTF_16 * append_from_resource( const UTF_16 * pszSource ) {

            for ( ; *pszSource; pszSource++ ) {

                append_from_resource( pszSource, 1 );

            }

            /* Point past the NUL */
            pszSource++;

            return pszSource;

        }


        const UTF_16 * append_from_resource( const UTF_16 * pszSource, unsigned uLen ) {

            for ( unsigned u = 0; u < uLen; u++ ) {

                append( 1, I386PE_INT16_TO_HOST( pszSource ) );
                pszSource++;

            }

            return pszSource;

        }

};


#endif /* H_UTF16STRING_H_INCLUDED */
