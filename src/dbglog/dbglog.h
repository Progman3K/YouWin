

#include <string>
#include <cstring>


#include <strings.h>
#include <stdio.h>
#include <arpa/inet.h>


#define EOL "\n"


#include <dbwinapi.h>


typedef int SOCKET;


typedef struct {

    unsigned int dwData;
    unsigned int cbData;
    void *       lpData;

} COPYDATASTRUCT;
