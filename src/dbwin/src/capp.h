

#include <string>


typedef struct {

	HWND			hOutputWnd;
	FILE *          hOutputFile;
	DWORD			dwMaxFileSize;
	BOOL			bNoOutput;
	HFONT			hFont;
	int				nCmdShow;
	CUDPTrace       UDP;
#ifndef	_WIN32_WCE
    FINDREPLACE     FR;
#endif	/* ! _WIN32_WCE */

    std::string     sCmdLine;
    TCHAR           szFindData[1024];

} DBWIN_DATA;
typedef DBWIN_DATA * PDBWIN_DATA;
typedef DBWIN_DATA * LPDBWIN_DATA;


class CApp {

	public:

		static	int		iInit( HINSTANCE hInst, HINSTANCE hPrevInst );
		static	void	CleanUp( void );

	private:

		static	BOOL	bRegisterClasses( HINSTANCE hInst );

};
typedef CApp * PCAPP;
typedef CApp * LPCAPP;
