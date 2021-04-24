

#ifndef WIN32
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <termios.h>
typedef int SOCKET;
#endif

#ifdef WIN32
#include <windowsx.h>

#ifndef DT_HIDEPREFIX
#define DT_HIDEPREFIX                     0x00100000
#endif

#ifndef DT_PREFIXONLY
#define DT_PREFIXONLY                     0x00200000
#endif

#include <tchar.h>
#define bzero ZeroMemory
#endif


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <vector>
#include <errno.h>
#include <unistd.h>

#include <ws2x.h>
#include <commctrl.h>

#include <DbgTrace.h>

#include "resource.h"

#include "defines.h"

#include "mainwnd.h"
