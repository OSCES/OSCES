#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "FsmcDriver.h"

struct PixelStruct_t
{
    uint8_t Red   : 3;
    uint8_t Green : 3;
    uint8_t Blue  : 2;
};

enum DisplayBuffer_t
{
    DISPLAY_PRIMARY_BUFFER = 0,
    DISPLAY_BACK_BUFFER    = 1,
};

class Display_t
{
public:
    void Init( uint16_t xSize, uint16_t ySize );
    
    void SetMousePos( uint16_t xPos, uint16_t yPos );
  
    void Present( PixelStruct_t* pData );
    void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue );
    void Flip();
    void Clear();
    ~Display_t();

private:
    void SelectBuffer( DisplayBuffer_t buffer );

private:
    DisplayBuffer_t m_DisplayBuffer;
    Fsmc_t          m_ExtSram;
    uint16_t        m_WindowSizeX;
    uint16_t        m_WindowSizeY;
};

#endif // DISPLAY_H
