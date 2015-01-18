#ifndef _DISPLAY_INTERFACE_h_
#define _DISPLAY_INTERFACE_h_

#include <stdint.h>
#include "DisplayTypes.h"




class DisplayInterface_t
{
public:
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos ) = 0;
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color ) = 0;
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ) = 0; // compability issue
    virtual void* GetFrameBuffer() = 0;
    virtual uint32_t GetSizeVertical() = 0;
    virtual uint32_t GetSizeHorizontal() = 0;
    virtual void SetTitle( const char* pTitle ) = 0;

public:
    //virtual void CopyBitmapToSurface( const DisplayBitmap_t* pDestinationRect, uint32_t xPosInSurface, uint32_t yPosInSurface ) = 0;
    virtual void Flip() = 0;
    virtual void Clear() = 0;
};


#endif //_DISPLAY_INTERFACE_h_