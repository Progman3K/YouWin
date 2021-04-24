#ifndef YW_DSHOW_H
#define YW_DSHOW_H


#include <windows.h>


#define OAFALSE (0)
#define OATRUE  (-1)


#define EC_COMPLETE                         0x01
#define EC_PAUSED                           0x0E


typedef GUID REFIID;
typedef long OAFilterState;
typedef LONGLONG REFERENCE_TIME;
typedef HWND OAHWND;


typedef enum AM_SEEKING_SeekingFlags {
    AM_SEEKING_NoPositioning = 0x0,
    AM_SEEKING_AbsolutePositioning = 0x1,
    AM_SEEKING_RelativePositioning = 0x2,
    AM_SEEKING_IncrementalPositioning = 0x3,
    AM_SEEKING_PositioningBitsMask = 0x3,
    AM_SEEKING_SeekToKeyFrame = 0x4,
    AM_SEEKING_ReturnTime = 0x8,
    AM_SEEKING_Segment = 0x10,
    AM_SEEKING_NoFlush = 0x20
} AM_SEEKING_SEEKING_FLAGS;


typedef enum _FilterState {
    State_Stopped = 0,
    State_Paused = 1,
    State_Running = 2
} FILTER_STATE;


typedef enum _VMR9Mode {
    VMR9Mode_Windowed = 0x1,
    VMR9Mode_Windowless = 0x2,
    VMR9Mode_Renderless = 0x4,
    VMR9Mode_Mask = 0x7
} VMR9Mode;


class IUnknown {

    public:

        HRESULT QueryInterface( REFIID /* riid */, void * * /* ppvObject */ ) { return E_NOTIMPL; }

        ULONG AddRef() { return E_NOTIMPL; }
        ULONG Release() { return E_NOTIMPL; }

};
typedef IUnknown *LPUNKNOWN;


class IBaseFilter : public IUnknown {
};


class IGraphBuilder : public IUnknown {

    public:

        HRESULT AddFilter( IBaseFilter * /* pFilter */, LPCTSTR /* pName */ ) { return E_NOTIMPL; }
        HRESULT RenderFile( LPCTSTR /* lpwstrFile */, LPCTSTR /* lpwstrPlayList */ ) { return E_NOTIMPL; }

};


class IVMRFilterConfig : public IUnknown {

    public:

        HRESULT SetNumberOfStreams( DWORD /* dwMaxStreams */ ) { return E_NOTIMPL; }
        HRESULT SetRenderingMode( DWORD /* Mode */ ) { return E_NOTIMPL; }

};


class IVideoWindow : public IUnknown {

    public:

        HRESULT get_FullScreenMode( long * /* FullScreenMode */ ) { return E_NOTIMPL; }

        HRESULT NotifyOwnerMessage( HWND /* hWnd */, UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */ ) { return E_NOTIMPL; }

        HRESULT put_FullScreenMode( long /* FullScreenMode */ ) { return E_NOTIMPL; }

        HRESULT put_MessageDrain( OAHWND /* Drain */ ) { return E_NOTIMPL; }

        HRESULT put_Owner( OAHWND /* Owner */ ) { return E_NOTIMPL; }

        HRESULT put_WindowStyle( long /* WindowStyle */ ) { return E_NOTIMPL; }

        HRESULT SetWindowPosition( long /* Left */, long /* Top */, long /* Width */, long /* Height */ ) { return E_NOTIMPL; }

};


class IMediaControl : public IUnknown {

    public:

        HRESULT GetState( LONG /* msTimeout */, OAFilterState * /* pfs */ ) { return E_NOTIMPL; }

        HRESULT Pause() { return E_NOTIMPL; }

        HRESULT Stop() { return E_NOTIMPL; }

        HRESULT Run() { return E_NOTIMPL; }

};


class IMediaEventEx : public IUnknown {

    public:

        HRESULT GetEvent( long * /* lEventCode */, LONG_PTR * /* lParam1 */, LONG_PTR * /* lParam2 */, long /* msTimeout */ ) { return E_NOTIMPL; }
        HRESULT SetNotifyWindow( OAHWND /* hWnd */, long /* lMsg */, LONG_PTR /* lInstanceData */ ) { return E_NOTIMPL; }

};


class IMediaSeeking : public IUnknown {

    public:

        HRESULT GetCurrentPosition( LONGLONG * /* pCurrent */ ) { return E_NOTIMPL; }

        HRESULT GetDuration( LONGLONG * /* pDuration */ ) { return E_NOTIMPL; }

        HRESULT SetPositions( LONGLONG * /* pCurrent */, DWORD /* dwCurrentFlags */, LONGLONG * /* pStop */, DWORD /* dwStopFlags */ ) { return E_NOTIMPL; }

        HRESULT SetTimeFormat( const GUID * /* pFormat */ ) { return E_NOTIMPL; }

};


class IVMRWindowlessControl9 : public IUnknown {

    public:

        HRESULT SetVideoClippingWindow( HWND /* hWnd */ ) { return E_NOTIMPL; }
        HRESULT SetVideoPosition( const LPRECT /* lpSRCRect */, const LPRECT /* lpDSTRect */ ) { return E_NOTIMPL; }
        HRESULT GetAspectRatioMode( DWORD * /* mode */ ) { return E_NOTIMPL; }
        HRESULT SetAspectRatioMode( DWORD /* mode */ ) { return E_NOTIMPL; }

};


class IVMRMixerBitmap9 : public IUnknown {

    public:


};


typedef struct _VMR9NormalizedRect {

    float left;
    float top;
    float right;
    float bottom;

} VMR9NormalizedRect;


typedef struct _VMR9AlphaBitmap {

  DWORD              dwFlags;
  HDC                hdc;
//  IDirect3DSurface9  *pDDS;
  RECT               rSrc;
  VMR9NormalizedRect rDest;
  float              fAlpha;
  COLORREF           clrSrcKey;
  DWORD              dwFilterMode;

} VMR9AlphaBitmap;



#define DEFINE_KNOWN_REFIID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)


DEFINE_KNOWN_REFIID( IID_IMediaControl,           0x56A868B1, 0x0AD4, 0x11CE, 0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IMediaEventEx,           0x56A868C0, 0x0AD4, 0x11CE, 0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IVideoWindow,            0x56A868B4, 0x0AD4, 0x11CE, 0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IMediaSeeking,           0x56A868B5, 0x0AD4, 0x11CE, 0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( CLSID_FilterGraph,           0xE436EBB3, 0x524F, 0x11CE, 0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IGraphBuilder,           0x56A868A9, 0x0AD4, 0x11CE, 0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IBaseFilter,             0x56a86895, 0x0ad4, 0x11ce, 0xb0, 0x3a, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70 );
DEFINE_KNOWN_REFIID( IID_IVMRFilterConfig9,       0x5a804648, 0x4f66, 0x4867, 0x9c, 0x43, 0x4f, 0x5c, 0x82, 0x2c, 0xf1, 0xb8 );
DEFINE_KNOWN_REFIID( CLSID_VideoMixingRenderer9,  0x51b4abf3, 0x748f, 0x4e3b, 0xa2, 0x76, 0xc8, 0x28, 0x33, 0x0e, 0x92, 0x6a );
DEFINE_KNOWN_REFIID( IID_IVMRWindowlessControl9,  0x8f537d09, 0xf85e, 0x4414, 0xb2, 0x3b, 0x50, 0x2e, 0x54, 0xc7, 0x99, 0x27 );
DEFINE_KNOWN_REFIID( IID_IVMRMixerBitmap9,        0xced175e5, 0x1935, 0x4820, 0x81, 0xbd, 0xff, 0x6a, 0xd0, 0x0c, 0x91, 0x08 );
DEFINE_KNOWN_REFIID( IID_IVMRAspectRatioControl9, 0x00d96c29, 0xbbde, 0x4efc, 0x99, 0x01, 0xbb, 0x50, 0x36, 0x39, 0x21, 0x46 );
DEFINE_KNOWN_REFIID( TIME_FORMAT_MEDIA_TIME,      0x7b785574, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6 );


HRESULT CoCreateInstance( REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv );


#endif /* YW_DSHOW_H */
