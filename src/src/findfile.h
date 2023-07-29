#ifndef YW_FINDFILE_H
#define YW_FINDFILE_H


#include "object.h"


class CFindFirst : public Object {

    public:

        DIR *           pDir;
//        struct dirent   entry;
        struct dirent * pEntry;
        struct stat     Stat;

        TCHAR szDir[MAX_PATH];

        WIN32_FIND_DATA fdata;

        CFindFirst() {

            setType( OBJECT_TYPE_FF );
            pDir   = 0;
            pEntry = 0;
            ZeroMemory( szDir, sizeof( szDir ) );
            ZeroMemory( &fdata, sizeof( fdata ) );

        }


        virtual ~CFindFirst() override {

            if ( 0 != pDir )  {

                closedir( pDir );
                pDir = 0;

            }

        }

};


#endif /* YW_FINDFILE_H */
