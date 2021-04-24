

#include "dbwin.h"


PVOID CMainDlg::Edit_ClaimTextPtr( HWND hEditWnd ) {

	HLOCAL	hMem;
	PBYTE	pucData;

	if ( NULL == ( hMem = Edit_GetHandle( hEditWnd ) ) ) {

		return NULL;

	}

#ifdef _WIN32
#ifdef _WIN32_WCE
	if ( NULL == ( pucData = (PBYTE)LocalLock( hMem ) ) ) {
	
		return NULL;
		
	}
#else	/* All other WIN32 platforms */
	if ( NULL == ( pucData = (PBYTE)GlobalLock( hMem ) ) ) {
	
		return NULL;
		
	}
#endif	/* ! _WIN32_WCE */
#else
	if ( NULL == ( pucData = (PBYTE)LocalLock( hMem ) ) ) {
	
		return NULL;
		
	}
#endif	/* ! _WIN32 */

	return pucData;

}


BOOL CMainDlg::LocalUnlockPtr( PVOID pData ) {

	HLOCAL	hMem;
	BOOL	bRet;

	if ( NULL == ( hMem = LocalHandle( pData ) ) ) {

		return false;

	}

	bRet = LocalUnlock( hMem );

	return bRet;

}
