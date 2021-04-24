#ifndef YW_SHLOBJ_H
#define YW_SHLOBJ_H


#include <windows.h>


#define CSIDL_PERSONAL                    5


#ifdef __cplusplus
extern "C" {
#endif


HRESULT SHGetFolderPath( HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath );


#ifdef __cplusplus
}   /* ! extern "C" */
#endif


#endif /* YW_SHLOBJ_H */
