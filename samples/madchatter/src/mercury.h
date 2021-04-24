#ifndef __H_MERCURY_H__
#define __H_MERCURY_H__


/* Chat protocol */
/* UDP Broadcast ClientID every x minutes at inactivity timeout */

/* Protocol: */
#define MERCURY_DGRAM_PORT 6789
#define MAX_DATA_LENGTH    4096
#define TYPICAL_CHUNK_SIZE ( 3 * 1024 )



typedef unsigned long long FileID;


typedef enum {

    MsgType_Status,
    MsgType_Chat,
//    MsgType_FileXfer,
    MsgType_FileXfer_Offer,
    MsgType_FileXfer_Request,
    MsgType_FileXfer_Chunk,
    MsgType_FileXfer_Ack,

    MsgType_Count

} MsgType;


typedef unsigned long long Entity;

#ifndef PACKED
#ifdef _MSC_VER
#pragma pack(1)
#pragma warning( disable : 4200 )
#define PACKED
#else
#define PACKED __attribute__ ((__packed__))
#endif
#endif /* ! PACKED */


typedef struct PACKED {

    Entity         entity;
    unsigned short Length;
    unsigned short Type;        /* MsgType_xxxx */
    char           UserData[];

} MsgHeader;


typedef struct PACKED {

    MsgHeader   Header;

//    char        cBuffer[];

/*  unsigned short  Checksum; */

} Exchange_t;
//typedef Exchange_t * LPEXCHANGE_T;


/* Follows a standard header */
typedef struct PACKED {

    FileID         entityfileID;
    unsigned short Length;
    unsigned short Type;

} file_xfer_header;


typedef struct PACKED {

    FileID         entityfileID;
    unsigned short Length;
    unsigned short flags;
    unsigned int   auiChunkNos[];

} file_xfer_ack;


typedef struct PACKED {

    FileID         entityfileID;
    unsigned short Length;
    unsigned short flags;
    unsigned int   uiVerificationHash;
    unsigned int   uiChunkNo;
    char           cData[];

} file_xfer_chunk;


typedef enum {

    MsgType_FileXfer_Offer_Query,
    MsgType_FileXfer_Offer_Accept,
    MsgType_FileXfer_Offer_Reject

} MsgType_FileXfer_Offer_Type;


typedef struct PACKED {

    enum {
        TCP_SEND = 1
    };

    FileID             entityfileID;
    unsigned long long ullFilelength;
    unsigned short     usFlags;            // Can have flag saying connect to offering peer at port in uiParam.
                                           // other permissible flag means file chunks will arrive
                                           // as regular udp fragments

    unsigned short     usRequest;          // One of the MsgType_FileXfer_Offer_Type
    unsigned int       uiParam;            // Port to connect to for filestream.
    unsigned int       uiVerificationHash;
    unsigned short     usChunksize;
    char               szFilename[];

} file_xfer_info;


typedef struct PACKED {

//    file_xfer_header hdr;

    union PACKED {

        file_xfer_ack   ack;
        file_xfer_info  info;
        file_xfer_chunk chunk;
        char            cBuffer[0];

    };

} Exchange_f;


#ifdef _MSC_VER
#pragma pack()
#endif


#endif /* __H_MERCURY_H__ */
