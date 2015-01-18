#include "DisplayPlatform.h"
#include <math.h>

/*
#define RED(x)   (8 * (x) / 255)
#define GREEN(x) (8 * (x) / 255)
#define BLUE(x)  (4 * (x) / 255)
*/

static uint8_t RED_GREEN[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static uint8_t BLUE[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

void DisplayPlatform_t::SetTitle( const char* pTitle )
{
    pTitle = pTitle;
}

void DisplayPlatform_t::Init( uint16_t xSize, uint16_t ySize, bool isVsyncEnable )
{ 
    m_DisplayBuffer = DISPLAY_PRIMARY_BUFFER;
    m_WindowSizeX = xSize;
    m_WindowSizeY = ySize;

    m_ExtSram.SetMemoryDataWidth( MEMORY_DATA_WITH_8BIT );
    m_ExtSram.SramControllerInit();
}

void* DisplayPlatform_t::GetFrameBuffer()
{
    return m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;
}

uint32_t DisplayPlatform_t::GetSizeVertical()
{
    return m_WindowSizeY;
}

uint32_t DisplayPlatform_t::GetSizeHorizontal()
{
    return m_WindowSizeX;
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos )
{
    //Color_t color( 255, 255, 255 );
    //DrawPixel( xPos, yPos, color );
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color )
{
    //DrawPixel( xPos, yPos, color.Red, color.Green, color.Blue );
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue )
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;
    pData += m_WindowSizeX * yPos + xPos;
    
    PixelStruct_t pixel;
    
    pixel.Red   = RED_GREEN[ red ];
    pixel.Green = RED_GREEN[ green ];
    pixel.Blue  = BLUE[ blue ];

    *pData = *( uint8_t* )&pixel;
}

void DisplayPlatform_t::Fill( uint16_t xPos, uint16_t yPos )
{
}

void DisplayPlatform_t::Fill( uint16_t xPos, uint16_t yPos, Color_t& color )
{
}

void DisplayPlatform_t::Flip( void )
{
    m_DisplayBuffer = ( DISPLAY_PRIMARY_BUFFER == m_DisplayBuffer ) ? DISPLAY_BACK_BUFFER : DISPLAY_PRIMARY_BUFFER;
    SelectBuffer( m_DisplayBuffer );
}

void DisplayPlatform_t::Clear()
{
    uint8_t* pData = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;
    uint32_t len = m_WindowSizeX * m_WindowSizeY / 10;

    for( uint32_t idx = 0; idx < len; idx ++ )
    {
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 0;
    }
}

DisplayPlatform_t::~DisplayPlatform_t()
{
    //delete m_pFrame;
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

