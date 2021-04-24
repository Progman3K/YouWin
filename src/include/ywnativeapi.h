#ifndef YOUWIN_NATIVE_API_H
#define YOUWIN_NATIVE_API_H


#include <stdint.h>


typedef enum {

   OpenYW_OK
  ,OpenYW_RESOURCES_NOT_FOUND
  ,OpenYW_SYSTEM_FONT_CREATION_ERROR

} OpenYWStatus;


typedef int (* TERMINALOUTPUTFUNC)( intptr_t lParam, const char * pszString, int iLen );


// Returns OpenYW_OK if all went well.
extern "C" OpenYWStatus OpenWindowLib( intptr_t, TERMINALOUTPUTFUNC );


#endif /* YOUWIN_NATIVE_API_H */
