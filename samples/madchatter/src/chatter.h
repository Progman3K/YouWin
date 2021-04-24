#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NOMINMAX
#ifndef WINVER
#define WINVER 0x0501
#endif
#endif

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstddef>
//#include <random>

#include <windowsx.h>
#include <winsock2.h>

#if defined( WIN32 ) || defined( _WIN32 )
typedef int socklen_t;
#endif

#include <shlobj.h>
#include <commctrl.h>
#include <tchar.h>


#include "nativefile.h"

#include "mercury.h"

#include "xfer.h"

#include "chatwnd.h"


# if __BYTE_ORDER == __LITTLE_ENDIAN

#ifndef htonll
#define    htonll( l )    l
#endif
#ifndef ntohll
#define    ntohll( l )    l
#endif

#else /* __BYTE_ORDER != __LITTLE_ENDIAN */
#define    htonll( l )    __bswap_64( l )
#define    ntohll( l )    __bswap_64( l )
#endif


typedef struct _StartupInfo {

    CWho *          me;

    const TCHAR *   pszCmdLine;
    int             nCmdShow;

    _StartupInfo( CWho * p, const TCHAR * cmdline, int cmd ) {

        me = p;
        pszCmdLine = cmdline;
        nCmdShow = cmd;

    }

} STARTUP_INFO, * PSTARTUP_INFO, * LPSTARTUP_INFO;


/* Functions */
int                     iInit( CWho & me );
extern HICON            WinInit( HINSTANCE hInst, HINSTANCE hPrevInst );
extern bool             bIsTextMode( void );

extern time_t           now( void );

void                    CleanUp( HINSTANCE hInst, CWho & me );
const TCHAR *           lpszMapErrorCode( unsigned short );

Entity                  GenerateEntity( void );

extern FileList         outgoingfiles;
extern FileList         incomingfiles;

extern int iUIBusy;

extern TCPXfers         xfers;


extern TCHAR            g_szChatterHostName[MAX_HOST_NAME_SIZE];
extern HICON            hHatAnimIcon[4];
extern HICON            hMainIcon;
