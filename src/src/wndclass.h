#ifndef YW_WNDCLASS_H
#define YW_WNDCLASS_H


#include <map>
#include <tstring.h>


#include <windows.h>


#include "brush.h"


class WindowClass {

    public:


        WindowClass( LPCTSTR pszName, WNDPROC Wndproc, /* COLOR_PAIR default_colors, */ HBRUSH hBackBrush, UINT styles, HICON hIco ) {

            ClassName.ToUpper( pszName );

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Class created, original name '%s', directory name '%s'" ), pszName, ClassName.c_str() );

            hbrBackground = reinterpret_cast<SolidBrush *>( hBackBrush );
            wndproc       = Wndproc;
            uiClassStyles = styles;
            hIcon         = hIco;

        }


        HICON GetClassIcon( void ) {

            return hIcon;

        }


        HICON SetClassIcon( HICON hIco ) {

            HICON hOldIcon = hIcon;

            hIcon = hIco;

            return hOldIcon;

        }


        WNDPROC GetWindowProc( void ) {

            return wndproc;

        }


        LPCTSTR GetClassName( void ) {

            return ClassName.c_str();

        }


        HBRUSH GetBackgroundBrush( void ) {

            return hbrBackground;

        }


        UINT GetClassStyles( void ) {

            return uiClassStyles;

        }

        virtual class ywWindow * Allocate( HWND hParent, LPCTSTR pWindowName, int x, int y, unsigned int count_x, unsigned int count_y, HMENU MenuOrID, DWORD Style, DWORD ExtStyle, WNDPROC wndproc, HINSTANCE hInst, LPVOID pParam ) = 0;

        virtual void Discard( class ywWindow * ) = 0;

        TSTRING      ClassName;

    private:

        SolidBrush * hbrBackground;
        WNDPROC      wndproc;
        UINT         uiClassStyles;
        HICON        hIcon;

};


typedef std::pair <TSTRING, class WindowClass *> ClassPair;

class ClassList : public std::map <TSTRING, class WindowClass *> {

    public:

        WindowClass * Find( const TCHAR * pClassName ) {

            TSTRING s;

            s.ToUpper( pClassName );

            const iterator i = find( s.c_str() );

            if ( end() == i ) {

                DBG_MSG( DBG_ERROR, TEXT( "Error: Requested class '%s' not found among:" ), s.c_str() );

                for ( iterator j = begin() ; j != end(); ++j ) {

                    DBG_MSG( DBG_ERROR, TEXT( "'%s'" ), j->first.c_str() );

                }

                return NULL;

            }

            return i->second;

        }

};


extern  ClassList   classes;


#endif	/* YW_WNDCLASS_H */
