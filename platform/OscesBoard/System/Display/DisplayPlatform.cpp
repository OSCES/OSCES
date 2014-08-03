#include "DisplayPlatform.h"

DisplayPlatform_t::DisplayPlatform_t()
{
}

DisplayPlatform_t::~DisplayPlatform_t()
{
    //delete m_pFrame;
}

void DisplayPlatform_t::Init( uint16_t xSize, uint16_t ySize )
{ 
    m_DisplayBuffer = DISPLAY_PRIMARY_BUFFER;
    m_WindowSizeX = xSize;
    m_WindowSizeY = ySize;

    m_ExtSram.SetMemoryDataWidth( MEMORY_DATA_WITH_8BIT );
    m_ExtSram.SramControllerInit();
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;
    pData += m_WindowSizeX * yPos + xPos;
    PixelStruct_t pixel;
    pixel.Red   = red;
    pixel.Green = green;
    pixel.Blue  = blue;
    
    *pData = *( uint8_t* )&pixel;
}

void DisplayPlatform_t::Flip( void )
{
    m_DisplayBuffer = ( DISPLAY_PRIMARY_BUFFER == m_DisplayBuffer ) ? DISPLAY_BACK_BUFFER : DISPLAY_PRIMARY_BUFFER;
    SelectBuffer( m_DisplayBuffer );
}

void DisplayPlatform_t::Clear()
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;
    uint32_t len = m_WindowSizeX * m_WindowSizeY;

    for( uint32_t idx = 0; idx < len; idx++ )
    {
            *pData++ = 0;
    }
}

void DisplayPlatform_t::SelectBuffer( DisplayBuffer_t buffer )
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

void DisplayPlatform_t::SetMousePos( uint16_t xPos, uint16_t yPos )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1();
    pData += 0x0007FFFE;
    *pData = xPos;
}

