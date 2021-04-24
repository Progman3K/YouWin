
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <getopt.h>


#include <ASCII.h>


typedef enum tagAsmFormat {

    AsmFormatFBE,
    AsmFormatGAS,
    AsmFormatOSX

} AsmFormat;
