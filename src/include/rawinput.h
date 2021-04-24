#ifndef __H_RAWINPUT_H__
#define __H_RAWINPUT_H__


/* Protocol: */


typedef struct __attribute__ ((__packed__)) {

    typedef enum {

        Type_VKey,
        Type_Keyboard,
        Type_Orientation,
        Type_Paint,

        Type_Count

    } RawInputType;

    unsigned short Length;
    unsigned short Type;        /* RawInputType_xxxx */

} MsgHeader;


typedef struct __attribute__ ((__packed__)) {

    MsgHeader      Header;

    int            cx;
    int            cy;

} OrientationMsg;


typedef struct __attribute__ ((__packed__)) {

    MsgHeader      Header;

    typedef enum {

        ActionDown,
        ActionUp,
        ActionMove,

        FlagCount

    } Flags;

    unsigned short flags; // Action

    unsigned short vKey;  // VK_xxx

    int            x;
    int            y;

} VKMsg;


typedef struct __attribute__ ((__packed__)) {

    MsgHeader      Header;

    typedef enum {

        Show,
        Hide,
        Char,

        FlagCount

    } Flags;

    unsigned short flags; // Action

    TCHAR          c;

} KeyboardMsg;


typedef struct __attribute__ ((__packed__)) {

    MsgHeader      Header;

    RECT           r[];

} PaintMsg;


typedef union {

    MsgHeader      Header;
    VKMsg          vKey;
    KeyboardMsg    keyboard;
    PaintMsg       paint;
    OrientationMsg orientation;

} RawPacket;


class RawInput {

    public:

        int       iOffset;
        RawPacket packet;


        RawInput() {

            iOffset = 0;

        }


        typedef void (* PACKETPROC)( const RawPacket *, LPARAM );


        static int ProcessRecv( int s, RawInput * raw, PACKETPROC Handler, LPARAM lParam ) {

            size_t i;

            if ( sizeof( raw->packet.Header ) > raw->iOffset ) {

                i = recv( s, ( (char *)&raw->packet.Header ) + raw->iOffset, sizeof( raw->packet.Header ) - raw->iOffset, 0 );

                if ( ( 0 == i ) || ( (size_t)-1 == i ) ) {

                    // Connection error or Session closed
                    return -1;

                }

                raw->iOffset += i;

            }

            /* Evaluate true size */
            if ( raw->iOffset < raw->packet.Header.Length ) {

                // Packet incomplete, read more
                i = recv( s, ( (char *)&raw->packet.Header ) + raw->iOffset, raw->packet.Header.Length - raw->iOffset, 0 );

                if ( 0 >= i ) {

                    // Connection error or Session closed
                    return -1;

                }

                raw->iOffset += i;

            }

            if ( raw->iOffset >= raw->packet.Header.Length ) {

                // Process packet, reset for next.
                Handler( &raw->packet, lParam );

                raw->iOffset -= raw->packet.Header.Length;

            }

            return 0;

        }


};


#endif /* __H_RAWINPUT_H__ */
