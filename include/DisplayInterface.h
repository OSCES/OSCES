#ifndef _DISPLAY_INTERFACE_h_
#define _DISPLAY_INTERFACE_h_

#include <stdint.h>

struct PixelStruct_t
{
  uint8_t Red   : 3;
  uint8_t Green : 3;
  uint8_t Blue  : 2;
};

class DisplayInterface_t
{
public:
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ) = 0;
    virtual void Flip() = 0;
    virtual void Clear() = 0;
};

#endif