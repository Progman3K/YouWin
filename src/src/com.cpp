

#include "ywin.h"


HRESULT CoInitialize( LPVOID pvReserved ) {

    return S_OK;

}


void CoUninitialize( void ) {
}


HRESULT CoCreateInstance( REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID * ppv ) {

    return E_NOTIMPL;

}
