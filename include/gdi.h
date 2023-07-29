#ifndef YWGDI_H
#define YWGDI_H


#include <stdint.h>


#define BI_RGB           0
#define BI_BITFIELDS     3


#define RGB(r,g,b)       ((COLORREF)((BYTE)(r)|((BYTE)(g) << 8)|((BYTE)(b) << 16)))
#define RGBA(r,g,b,a)    ((COLORREF)( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b) ))


typedef uint32_t COLORREF;


typedef struct {

    int32_t  bmType;
    int32_t  bmWidth;
    int32_t  bmHeight;
    int32_t  bmWidthBytes;
    uint16_t bmPlanes;
    uint16_t bmBitsPixel;
    void *   bmBits;

} BITMAP, *PBITMAP, *LPBITMAP;


typedef struct tagRGBTRIPLE {

  uint8_t rgbtBlue;
  uint8_t rgbtGreen;
  uint8_t rgbtRed;

} RGBTRIPLE, *PRGBTRIPLE, *NPRGBTRIPLE, *LPRGBTRIPLE;


typedef struct tagRGBQUAD {

    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;

} RGBQUAD;


/* Bitmap v3 */
typedef struct tagBITMAPINFOHEADER {

    uint32_t biSize;          /* Size of this header in bytes */
    int32_t  biWidth;         /* Image width in pixels */
    int32_t  biHeight;        /* Image height in pixels */ /* Divide by 2 ??? */
    uint16_t biPlanes;        /* Number of color planes */
    uint16_t biBitCount;      /* Number of bits per pixel */
    uint32_t biCompression;   /* Compression methods used: BI_RGB BI_BITFIELDS */
    uint32_t biSizeImage;     /* Size of bitmap in bytes */
    int32_t  biXPelsPerMeter; /* Horizontal resolution in pixels per meter */
    int32_t  biYPelsPerMeter; /* Vertical resolution in pixels per meter */
    uint32_t biClrUsed;       /* Number of colors in the image */
    uint32_t biClrImportant;  /* Minimum number of important colors */

} BITMAPINFOHEADER, *PBITMAPINFOHEADER;


typedef struct tagBITMAPINFO {

    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];

} BITMAPINFO, *PBITMAPINFO;


typedef int32_t FXPT2DOT30;


typedef struct tagCIEXYZ {

    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;

} CIEXYZ;

typedef struct tagICEXYZTRIPLE {

    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;

} CIEXYZTRIPLE;


/* Bitmap v4 */
typedef struct {

    uint32_t     bV4Size;
    int32_t      bV4Width;
    int32_t      bV4Height;
    uint16_t     bV4Planes;
    uint16_t     bV4BitCount;
    uint32_t     bV4V4Compression;
    uint32_t     bV4SizeImage;
    int32_t      bV4XPelsPerMeter;
    int32_t      bV4YPelsPerMeter;
    uint32_t     bV4ClrUsed;
    uint32_t     bV4ClrImportant;

    /* Fields added for Windows 4.x follow this line */

    uint32_t     bV4RedMask;       /* Mask identifying bits of red component */
    uint32_t     bV4GreenMask;     /* Mask identifying bits of green component */
    uint32_t     bV4BlueMask;      /* Mask identifying bits of blue component */
    uint32_t     bV4AlphaMask;     /* Mask identifying bits of alpha component */
    uint32_t     bV4CSType;        /* Color space type */

    CIEXYZTRIPLE bV4Endpoints;

    uint32_t     bV4GammaRed;      /* Gamma red coordinate scale value */
    uint32_t     bV4GammaGreen;    /* Gamma green coordinate scale value */
    uint32_t     bV4GammaBlue;     /* Gamma blue coordinate scale value */

} BITMAPV4HEADER;


typedef struct {

    uint32_t     bV5Size;
    int32_t      bV5Width;
    int32_t      bV5Height;
    uint16_t     bV5Planes;
    uint16_t     bV5BitCount;
    uint32_t     bV5Compression;
    uint32_t     bV5SizeImage;
    int32_t      bV5XPelsPerMeter;
    int32_t      bV5YPelsPerMeter;
    uint32_t     bV5ClrUsed;
    uint32_t     bV5ClrImportant;
    uint32_t     bV5RedMask;
    uint32_t     bV5GreenMask;
    uint32_t     bV5BlueMask;
    uint32_t     bV5AlphaMask;
    uint32_t     bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    uint32_t     bV5GammaRed;
    uint32_t     bV5GammaGreen;
    uint32_t     bV5GammaBlue;

    /* Fields added beyond v4 follow this line */

    uint32_t     bV5Intent;
    uint32_t     bV5ProfileData;
    uint32_t     bV5ProfileSize;
    uint32_t     bV5Reserved;

} BITMAPV5HEADER, *LPBITMAPV5HEADER, *PBITMAPV5HEADER;


#endif /* YWGDI_H */
