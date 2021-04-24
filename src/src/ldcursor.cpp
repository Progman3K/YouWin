

#include "ywin.h"


/*
Cursor Resources 
 
Cursor resources are very much like icon resources.  They are formed 
in groups with the components preceding the header.  This header also 
employs a fixed-length component index that allows random access of 
the individual components.  The structure of the cursor header is as 
follows: 
 
    [Resource header (type = 12)] 
*/
struct CursorHeader {

    WORD    wReserved;  // Currently zero 
    WORD    wType;      // 2 for cursors 
    WORD    cwCount;    // Number of components 
    WORD    padding;    // filler for DWORD alignment 

};

/*  
The next portion is repeated for each component resource, and starts 
on a DWORD boundary. 
*/
#if 0 // Commented out for now because of collision with icon resource definition.
struct ResourceDirectory { 

    WORD    wWidth; 
    WORD    wHeight; 
    WORD    wPlanes; 
    WORD    wBitCount; 
    DWORD   lBytesInRes; 
    WORD    wNameOrdinal;   // Points to component 
    WORD    padding;        // filler for DWORD alignment 

};
#endif

/*
Each cursor component is also similar to each icon component.  There 
is, however, one significant difference between the two:  cursors 
have the concept of a `hotspot' where icons do not.  Here is the 
component structure: 
 
    [Resource header (Type = 1)] 
*/

struct CursorComponent {

    short   xHotspot; 
    short   yHotspot;
    
};
/*  
    [Monochrome XOR mask] 
    [Monochrome AND mask] 
     
These masks are bitmaps copied from the .CUR file.  The main 
difference from icons in this regard is that cursors do not have 
color DIBs used for XOR masks like cursors.  Although the bitmaps are 
monochrome and do not have DIB headers or color tables, the bits are 
still in DIB format with respect to alignment and direction.  See the 
SDK Reference for more information on DIB formats. 
 
*/
HCURSOR LoadCursor( HINSTANCE hInst, LPCTSTR lpszName ) {

    if ( ( NULL == hInst ) && ( 0 == HIWORD( lpszName ) ) ) {

        // return code as actual stock object for now
        return (HCURSOR)(unsigned long)LOWORD( lpszName );

    }

//    Resource * h = new Resource( RT_CURSOR_VAL );
//    Cursor * h; //  = new Cursor();

// TODO: CONNECT CURSOR
#if 0
    BOOL bLoaded = Resource::bLoad( hInst, RT_CURSOR, lpszName, h );

    if ( ! bLoaded ) {

        delete h;
        return NULL;

    }
#endif
    return 0;

}


BOOL DestroyCursor( HCURSOR h ) {

    if ( NULL == h ) {

        return false;

    }

    if ( 0 == HIWORD( h ) ) {

        // Destroying stock object not permitted
        return false;

    }

    delete reinterpret_cast<Cursor *>( h );

    return true;

}
