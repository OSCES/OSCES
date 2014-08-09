#ifndef _DISPLAY_INTERFACE_h_
#define _DISPLAY_INTERFACE_h_

#include <stdint.h>

struct PixelStruct_t
{
  uint8_t Red   : 3;
  uint8_t Green : 3;
  uint8_t Blue  : 2;
};

struct PixelStructRGBA8888_t
{
  uint32_t Red   : 8;
  uint32_t Green : 8;
  uint32_t Blue  : 8;
  uint32_t Alpha : 8;
};

enum DisplayPixelFormat_t
{
    DISPLAY_PIXEL_FORMAT_RGB888  ,
    DISPLAY_PIXEL_FORMAT_RGBA8888,
    DISPLAY_PIXEL_FORMAT_RGB332
};

enum DisplayRectFormat_t
{

 
};

struct DisplayBitmap_t
{
    DisplayPixelFormat_t PixelFormat;
    uint32_t             Height;
    uint32_t             Width;

    union
    {
        uint32_t* pDataUint32;
        void*     pBitmap;
        PixelStructRGBA8888_t* pBitmapRGBA8888;

    };

};


class DisplayInterface_t
{
public:
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ) = 0;
    //virtual void CopyBitmapToSurface( const DisplayBitmap_t* pDestinationRect, uint32_t xPosInSurface, uint32_t yPosInSurface ) = 0;
    virtual void Flip() = 0;
    virtual void Clear() = 0;
};


#endif