



#ifndef __DBWIN_API_H__

#define __DBWIN_API_H__





typedef struct {



    unsigned int dwData;

    unsigned int cbData;

    char         cData[1];



} DEBUGMSGDATASTRUCT;





#define MAXIMUM_MTU_SIZE                    32768



#define ID_DBGDLL_DATAGRAM_BROADCAST_PORT   7659





#endif /* __DBWIN_API_H__ */

