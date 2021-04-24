#ifndef H_TSTRING_H
#define H_TSTRING_H


#include <string>
#include <tchar.h>
#include <windows.h>


class TSTRING : public std::basic_string<TCHAR> {

#if defined( UNICODE ) || defined( _UNICODE )
    std::basic_string<char> s;
#endif

    public:


        TSTRING() {
        }


        TSTRING( const unsigned short * psz ) {

            absorb( psz );

#if 0
            clear();

            for( ; *psz; psz++ ) {

                TCHAR c = *psz;

                append( &c, 1 );

            }
#endif
        }


        void absorb( const unsigned short * psz ) {

            clear();

            for( ; *psz; psz++ ) {

                TCHAR c = *psz;

                append( &c, 1 );

            }

        }


        TSTRING( const TCHAR * psz ) {

            assign( psz );

        }


        int comparei( const TCHAR * psz ) const  {

            const TCHAR * p;

            p = c_str();

            for ( ;; ) {

                TCHAR c1,c2;

                c1 = toupper( *p++ );
                c2 = toupper( *psz++ );

                if ( ( 0 == c1 ) || ( 0 == c2 ) || ( c1 != c2 ) ) {

                    return c1 - c2;

                }

            }

        }


        void replacewith( TCHAR c, TCHAR cWith ) {

            for ( size_t i = 0; i < size(); i++ ) {

                if ( c == at( i ) ) {

                    at( i ) = cWith;

                }

            }

        }

        TCHAR up( TCHAR c ) {

            if ( ( 'a' <= c ) && ( 'z' >= c ) ) {

                c -= 32;

            }

            return c;

        }

        void ToUpper( const TCHAR * psz ) {

            clear();
//            s.clear();

            for( ; *psz; psz++ ) {

                TCHAR c = up( *psz );

                append( &c, 1 );

            }

        }


        const char * charz_str() {
#if ! defined( UNICODE ) && ! defined( _UNICODE )
//    printf( "Begin charz_str NOT Unicode\n" );
            return c_str();
#else
//    printf( "Begin charz_str Unicode\n" );
            s.clear();

            for( size_t u = 0; u < size(); u++ ) {

                s.push_back( (char)at( u ) );

            }

            return s.c_str();
#endif

        }


        void absorb( const char * psz ) {

            clear();

            for ( ; *psz; psz++ ) {

                char  c = *psz;
                TCHAR wc = c;
                append( &wc, 1 );

            }

        }


};


#endif /* H_TSTRING_H */
