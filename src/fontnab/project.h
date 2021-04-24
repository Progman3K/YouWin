

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tchar.h>

#include <windows.h>
#include <windowsx.h>

#include "../include/ASCII.h"
#include "../include/DbgTrace.h"
#include "../include/tstring.h"

#include <getopt.h>

#ifndef WIN32
#define EOL TEXT( "\r\n" )
#else
#define EOL TEXT( "\n" )
#endif

#include "../src/font.h"
