#ifndef __NATIVE_FILE_H__
#define __NATIVE_FILE_H__


#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>


#define HNATIVEFILE         HANDLE

#ifndef HNATIVEFILE_ERROR
#define HNATIVEFILE_ERROR   INVALID_HANDLE_VALUE
#endif


#ifndef Dim
#define Dim( array ) ( sizeof( array ) / sizeof( array[0] ) )
#endif


class NativeFile {

    public:

        typedef enum {

             FROM_BEGINNING
            ,FROM_CURRENT_POSITION
            ,FROM_END

        } FILE_SEEK_METHOD;

        typedef enum {

             FOR_READING
            ,FOR_WRITING
            ,FOR_UPDATING
            ,FOR_APPEND

        } FILE_OPEN_METHOD;

        static HNATIVEFILE Open( LPCTSTR lpszFile, FILE_OPEN_METHOD mode ) {

            HNATIVEFILE hFile;

            switch( mode ) {

                case FOR_READING:

#ifdef _WIN32

                    if ( INVALID_HANDLE_VALUE == ( hFile = CreateFile( lpszFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }
#else
                    if ( 0 == ( hFile = fopen( lpszFile, "r" ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }

#endif  /* ! WIN32 */
                    return hFile;

                case FOR_WRITING:

#ifdef _WIN32

                    if ( INVALID_HANDLE_VALUE == ( hFile = CreateFile( lpszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }
#else
                    if ( 0 == ( hFile = fopen( lpszFile, "wb" ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }

#endif  /* ! WIN32 */
                    return hFile;


                case FOR_UPDATING:

#ifdef _WIN32

                    if ( INVALID_HANDLE_VALUE == ( hFile = CreateFile( lpszFile, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }
#else
                    { /* Local stack here */

                        struct stat Stat;

                        int iRet = stat( lpszFile, &Stat );

                        if ( 0 != iRet ) {

                            if ( 0 == ( hFile = fopen( lpszFile, "w" ) ) ) {

                                return HNATIVEFILE_ERROR;

                            }

                            fclose( (FILE *)hFile );

                        }

                    }

                    if ( 0 == ( hFile = fopen( lpszFile, "r+w" ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }

#endif  /* ! WIN32 */
                    return hFile;

                case FOR_APPEND:

#ifdef _WIN32

                    if ( INVALID_HANDLE_VALUE == ( hFile = CreateFile( lpszFile, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }

                    Seek( hFile, 0, FROM_END );
#else

                    if ( 0 == ( hFile = fopen( lpszFile, "a" ) ) ) {

                        return HNATIVEFILE_ERROR;

                    }

#endif  /* ! WIN32 */
                    return hFile;

            }

            return HNATIVEFILE_ERROR;

        }


        static void Close( HNATIVEFILE hFile ) {

#if defined( _WIN32 ) || defined( _WIN32_WCE )

            CloseHandle( hFile );

#else
            fclose( (FILE *)hFile );
#endif

        }


        static uintptr_t Read( HNATIVEFILE hFile, LPVOID lpBuffer, size_t iSize ) {

            DWORD   dwNumBytesRead;

#if defined( _WIN32 ) || defined( _WIN32_WCE )
            dwNumBytesRead = 0;
            if ( ! ReadFile( hFile, lpBuffer, (DWORD)iSize, &dwNumBytesRead, NULL ) ) {

                LPVOID lpMsgBuf;

                DWORD Err = GetLastError();

                FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, Err, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR)&lpMsgBuf, 0, NULL );


                LocalFree( lpMsgBuf );

                return (uintptr_t)HNATIVEFILE_ERROR;

            }
#else

            dwNumBytesRead = fread( lpBuffer, 1, iSize, (FILE *)hFile  );

#endif

            return dwNumBytesRead;

        }

        static DWORD Seek( HNATIVEFILE hFile, DWORD dwOffset, FILE_SEEK_METHOD SeekMethod ) {

            DWORD   dwCurrentFilePos;

#if defined( _WIN32 ) || defined( _WIN32_WCE )

            DWORD   dwMoveMethod;

            switch( SeekMethod ) {

                case FROM_BEGINNING:

                    dwMoveMethod = FILE_BEGIN;
                    break;

                case FROM_CURRENT_POSITION:

                    dwMoveMethod = FILE_CURRENT;
                    break;

                case FROM_END:

                    dwMoveMethod = FILE_END;
                    break;

                default:

                    return -1;

            }

            dwCurrentFilePos = SetFilePointer( hFile, dwOffset, NULL, dwMoveMethod );

            if ( INVALID_SET_FILE_POINTER == dwCurrentFilePos ) {

                return -1;

            }

#else

            int iOrigin;

            switch( SeekMethod ) {

                case FROM_BEGINNING:

                    iOrigin = SEEK_SET;
                    break;

                case FROM_CURRENT_POSITION:

                    iOrigin = SEEK_CUR;
                    break;

                case FROM_END:

                    iOrigin = SEEK_END;
                    break;

                default:

                    return -1;

            }

            dwCurrentFilePos = fseek( (FILE *)hFile, dwOffset, iOrigin );

            if ( 0 != (long)dwCurrentFilePos ) {

                return -1;

            }

#endif

            return dwCurrentFilePos;

        }


        static DWORD Tell( HNATIVEFILE hFile ) {

#ifdef _WIN32
            return SetFilePointer( hFile, 0, 0, FILE_CURRENT );
#else
            return ftell( (FILE *)hFile );
#endif

        }


        static DWORD Write( HNATIVEFILE hFile, const void * lpBuffer, size_t iSize ) {

#ifdef _WIN32
            {

                DWORD dwNumBytesWritten;

                if ( ! WriteFile( hFile, lpBuffer, (DWORD)iSize, &dwNumBytesWritten, NULL ) ) {

                    return (DWORD)-1;

                }

                return dwNumBytesWritten;

            }
#else
            {
                size_t iRet;

                iRet = fwrite( lpBuffer, 1, iSize, (FILE *)hFile );

                if ( iSize != iRet ) {

                    return (DWORD)-1;

                }

                return iRet;

            }
#endif  /* ! WIN32 */

        }

        typedef LRESULT (* FNOPENFNAMEHOOK)(HWND, UINT, WPARAM, LPARAM);

        typedef int (* WRITEFILEPROC)( HWND hParentWnd, HNATIVEFILE hFile, LPARAM lParam );

        static int iSaveTo( HWND hParentWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, WRITEFILEPROC lpfnWriteFileProc, LPARAM lParam, HINSTANCE hInst ) {

            HNATIVEFILE hFile;
            int         iRet = IDOK;

            {

//                TCHAR   szFileName[4096];

//                ZeroMemory( szFileName, sizeof ( szFileName ) );

//                _tcsncpy( szFileName, lpszRet, Dim( szFileName ) - 1 );

                if ( ! NativeFile::bFind( hParentWnd, uFileFilter, cSeparator, lpszDialogTitle, lpszRet, uszRetBufSize, dwFlags, lpszInitialDir, lpfnDlgHookProc, hInst ) ) {

                    return IDCANCEL;

                }

//                if ( NULL != lpszRet ) {

//                    _tcsncpy( lpszRet, szFileName, uszRetBufSize );

//                }

#ifdef _WIN32

                if ( NULL == ( hFile = CreateFile( lpszRet, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ) ) ) {

                    return -1;

                }
#else
                {

                    if ( INVALID_HANDLE_VALUE == ( hFile = fopen( lpszRet, "w" ) ) ) {

                        return -1;

                    }

                }
#endif  /* ! WIN32 */

            }   /* Reclaim stack-frame space. */

            if ( NULL != lpfnWriteFileProc ) {

                iRet = lpfnWriteFileProc( hParentWnd, hFile, lParam );

            }

#ifdef _WIN32
            CloseHandle( hFile );
#else
            fclose( (FILE *)hFile );
#endif  /* ! WIN32 */

            return iRet;

        }


        static BOOL bFind( HWND hWnd, unsigned uFileFilter, TCHAR cSeparator, LPCTSTR lpszDialogTitle, LPTSTR lpszRet, unsigned uszRetBufSize, DWORD dwFlags, LPCTSTR lpszInitialDir, LPOFNHOOKPROC lpfnDlgHookProc, HINSTANCE hInst ) {

            OPENFILENAME    ofn;
            BOOL            bRet = false;
            TCHAR           szFilter[1024];
            TCHAR           szTitle[1024];

            if ( ( lpszRet == NULL ) || ( uszRetBufSize == 0 ) ) {

                /* Parameter error. */
                return false;

            }
            
            memset( szFilter, 0, sizeof( szFilter ) );
            memset( szTitle, 0, sizeof( szTitle ) );

            memset( &ofn, 0, sizeof( ofn ) );
            ofn.lStructSize      = sizeof( OPENFILENAME );

            /* Load filtering string from resource table. */
            if ( NULL != hInst ) {

                unsigned uCB;

                if ( ( uCB = LoadString( hInst, uFileFilter, szFilter, Dim( szFilter ) ) ) == 0 ) {

                    return false;

                }

                /* Replace all occurances of separator char with null. */
                while ( 0 != ( --uCB ) ) {

                    if ( szFilter[ uCB ] == cSeparator ) {

                        szFilter[ uCB ] = 0;

                    }

                }

                ofn.lpstrFilter      = szFilter;

                ofn.nFilterIndex     = 1;

                /* Load dialog title string. */
                if ( 0 == HIWORD( (uintptr_t)lpszDialogTitle ) ) {

                    if ( ! LoadString( hInst, LOWORD( (uintptr_t)lpszDialogTitle ), szTitle, Dim( szTitle ) ) ) {

                        return false;

                    }

                    lpszDialogTitle = szTitle;

                }

            }

            ofn.hwndOwner        = hWnd;

            ofn.lpstrTitle       = lpszDialogTitle;

            ofn.lpstrFile        = lpszRet;

            ofn.nMaxFile         = uszRetBufSize;

            ofn.lpstrInitialDir  = lpszInitialDir;

            ofn.Flags            = dwFlags;

            ofn.lpfnHook         = lpfnDlgHookProc;

            bRet = GetOpenFileName( &ofn );

            /* Return the user's choice. */
            return bRet;

        }

};


#endif /* __NATIVE_FILE_H__ */
