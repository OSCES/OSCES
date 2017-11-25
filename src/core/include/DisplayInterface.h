#ifndef _DISPLAY_INTERFACE_h_
#define _DISPLAY_INTERFACE_h_

#include <stdint.h>
#include "DisplayTypes.h"

class DisplayInterface
{
public:
    virtual bool init(uint16_t width, uint16_t height, bool vsyncEnabled) = 0;
    virtual void drawPixel(uint16_t x, uint16_t y) = 0;
    virtual void drawPixel(uint16_t x, uint16_t y, const Color &color) = 0;
    virtual void drawPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) = 0; // compability issue
    virtual void* frameBuffer() = 0;
    virtual uint32_t height() const = 0;
    virtual uint32_t width() const = 0;
    virtual void setTitle(const char* title) = 0; // TODO: remove

public:
    //virtual void CopyBitmapToSurface( const DisplayBitmap_t* pDestinationRect, uint32_t xPosInSurface, uint32_t yPosInSurface ) = 0;
    virtual void flip() = 0;
    virtual void clear() = 0;
};


#endif //_DISPLAY_INTERFACE_h_
