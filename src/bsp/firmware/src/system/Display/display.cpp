#include "Display.h"

Display_t::Display_t()
{
}

Display_t::~Display_t()
{
//delete m_pFrame;
}

void Display_t::Init( uint16_t xSize, uint16_t ySize )
{ 
    m_DisplayBuffer = DISPLAY_PRIMARY_BUFFER;
    m_WindowSizeX = xSize;
    m_WindowSizeY = ySize;

    m_ExtSram.SetMemoryDataWidth( MEMORY_DATA_WITH_8BIT );
    m_ExtSram.SramControllerInit();

    m_FrameSize    = m_WindowSizeX * m_WindowSizeY;
}

void Display_t::DrawPixel(uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_FrameSize * m_DisplayBuffer;
    pData += m_WindowSizeX * yPos + xPos;
    
    *pData =  ConvertRGB( red, green, blue );
}

void Display_t::Fill( uint8_t red, uint8_t green, uint8_t blue )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_FrameSize * m_DisplayBuffer;

    uint8_t data = ConvertRGB( red, green, blue );

    for( uint32_t idx = 0; idx < m_FrameSize; idx ++ )
    {
        *pData = data;
        pData++;
    }
}

void Display_t::Flip( void )
{
    m_DisplayBuffer = ( DISPLAY_PRIMARY_BUFFER == m_DisplayBuffer ) ? DISPLAY_BACK_BUFFER : DISPLAY_PRIMARY_BUFFER;
    SelectBuffer( m_DisplayBuffer );
}

void Display_t::Clear( void )
{
    Fill( 0x00,  0x00,  0x00 );
}

void Display_t::SelectBuffer( DisplayBuffer_t buffer )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1();
    pData += 0x0007FFFF;
    
    if( DISPLAY_PRIMARY_BUFFER == buffer )
    {
        *pData |= 0x01;
    }
    else
    {
        *pData &= ~0x01;
    }
}

uint8_t Display_t::ConvertRGB( uint8_t red, uint8_t green, uint8_t blue )
{
    PixelStruct_t pixel;

    if( red < 32 )
        red = 0;
    else
        if( red >= 32 && red < 64 )
            red = 1;
        else
            if( red >= 64 && red < 96 )
                red = 2;
            else
                if( red >= 96 && red < 128 )
                    red = 3;
                else
                    if( red >= 128 && red < 160 )
                        red = 4;
                    else
                        if( red >= 160 && red < 192 )
                            red = 5;
                        else
                            if( red >= 192 && red < 224 )
                                red = 6;
                            else
                                if( red >= 224 )
                                    red = 7;

    if( green < 32 )
        green = 0;
    else
        if( green >= 32 && green < 64 )
            green = 1;
        else
            if( green >= 64 && green < 96 )
                green = 2;
            else
                if( green >= 96 && green < 128 )
                    green = 3;
                else
                    if( green >= 128 && green < 160 )
                        green = 4;
                    else
                        if( green >= 160 && green < 192 )
                            green = 5;
                        else
                            if( green >= 192 && green < 224 )
                                green = 6;
                            else
                                if( green >= 224 )
                                    green = 7;

    if( blue < 64 )
        blue = 0;
    else
        if( blue >= 64 && blue < 128 )
            blue = 1;
        else
            if( blue >= 128 && blue < 192 )
                blue = 2;
            else
                if( blue >= 192 )
                    blue = 3;


    pixel.Red   = red;
    pixel.Green = green;
    pixel.Blue  = blue;

    return ( *( uint8_t* )&pixel );
}

void Display_t::SetMousePos( uint16_t xPos, uint16_t yPos )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1();
    pData += 0x0007FFFE;
    *pData = xPos;
}
 
