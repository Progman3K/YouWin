#ifndef YOUWIN_TCHAR_H
#define YOUWIN_TCHAR_H


//#include <string.h>


#ifdef UNICODE
//#include <wctype.h>

//#define _tWinMain   wWinMain
//typedef unsigned short TCHAR;
typedef wchar_t TCHAR;
#define _fgetts      fgetws
#define _fputts      fputws
#define _ftprintf    fwprintf
#define _sntprintf   swprintf
#define _stprintf    swprintf
#define _tcscat      wcscat
#define _tcscspn     wcscspn
#define _tcslen      wcslen
#define _tcsncat     wcsncat
#define _tcsncpy     wcsncpy
#define _tcscmp      wcscmp
#define _tcsncmp     wcsncmp
#define _tcsicmp     wcscasecmp
#define _tcstok(a,b) wcstok(a,b,NULL)
#define _tcstol      wcstol
#define _tcsrchr     wcsrchr
#define _tctime      _wctime
#define _tfopen      _wfopen
#define _ttoi(a)     wcstol(a,NULL,10)
#define _topendir    _wopendir
#define _vsntprintf  vswprintf
#define _totupper    towupper
#else
//#include <ctype.h>
//#define _tWinMain   WinMain
typedef char TCHAR;
#define _fgetts      fgets
#define _fputts      fputs
#define _ftprintf    fprintf
#define _sntprintf   snprintf
#define _stprintf    sprintf
#define _tcscat      strcat
#define _tcscspn     strcspn
#define _tcslen      strlen
#define _tcsncat     strncat
#define _tcsncpy     strncpy
#define _tcscmp      strcmp
#define _tcsncmp     strncmp
#define _tcsicmp     strcasecmp
#define _tcstok      strtok
#define _tcstol      strtol
#define _tcsrchr     strrchr
#define _tctime      ctime
#define _tfopen      fopen
#define _ttoi        atoi
#define _topendir    opendir
#define _vsntprintf  vsnprintf
#define _totupper    toupper
#endif


#endif /* YOUWIN_TCHAR_H */
