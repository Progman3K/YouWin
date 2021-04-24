#ifndef YW_ATOM_H
#define YW_ATOM_H


#include <windows.h>
#include <map>
#include <tstring.h>


class atomdescriptor {

    public:

        TSTRING val;    // The string.
        ATOM    id;
        DWORD   flags;

        atomdescriptor() {

            id    = 0;
            flags = 0;

        }

};


typedef std::pair<atomdescriptor,ATOM> nucleusString;
typedef std::pair<ATOM,const TCHAR *> nucleusID;
typedef std::map<ATOM,const TCHAR *> idmap;


struct cmpatomdescriptorstring {

    bool operator()( const atomdescriptor & a, const atomdescriptor & b ) const {

        return 0 > a.val.comparei( b.val.c_str() );

    }

};


typedef std::map<atomdescriptor,ATOM,cmpatomdescriptorstring> atom;


class AtomTable : public atom {

    public:

        ATOM next;

        idmap byID;

        AtomTable() {

            next = 0;

        }

};


#endif /* YW_ATOM_H */
