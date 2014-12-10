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

void DisplayPlatform_t::Init( uint16_t xSize, uint16_t ySize )
{ 
    m_DisplayBuffer = DISPLAY_PRIMARY_BUFFER;
    m_WindowSizeX = xSize;
    m_WindowSizeY = ySize;

    m_ExtSram.SetMemoryDataWidth( MEMORY_DATA_WITH_8BIT );
    m_ExtSram.SramControllerInit();
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos )
{
    Color_t color( 255, 255, 255 );
    DrawPixel( xPos, yPos, color );
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color )
{
    DrawPixel( xPos, yPos, color.Red, color.Green, color.Blue );
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

void DisplayPlatform_t::DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos )
{
    Color_t color( 255, 255, 255 );
    DrawLine( xStartPos, yStartPos, xEndPos, yEndPos, color );
}

void DisplayPlatform_t::DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos, Color_t& color )
{
    // Display RAM
    uint8_t *pDisplayRam = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;

    if( xStartPos > m_WindowSizeX - 1 || 
        xEndPos   > m_WindowSizeX - 1 || 
        yStartPos > m_WindowSizeY - 1 || 
        yEndPos   > m_WindowSizeY - 1 )
        return;

    int deltax = abs( (long double)(xEndPos - xStartPos) ); //The difference between the x's
    int deltay = abs( (long double)(yEndPos - yStartPos) ); //The difference between the y's
    int x = xStartPos; //Start x off at the first pixel
    int y = yStartPos; //Start y off at the first pixel
    int xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel;

    if( xEndPos >= xStartPos ) //The x-values are increasing
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else //The x-values are decreasing
    {
        xinc1 = -1;
        xinc2 = -1;
    }
    if( yEndPos >= yStartPos ) //The y-values are increasing
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else //The y-values are decreasing
    {
        yinc1 = -1;
        yinc2 = -1;
    }
    if( deltax >= deltay ) //There is at least one x-value for every y-value
    {
        xinc1 = 0; //Don't change the x when numerator >= denominator
        yinc2 = 0; //Don't change the y for every iteration
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax; //There are more x-values than y-values
    }
    else //There is at least one y-value for every x-value
    {
        xinc2 = 0; //Don't change the x for every iteration
        yinc1 = 0; //Don't change the y when numerator >= denominator
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay; //There are more y-values than x-values
    }
    for( curpixel = 0; curpixel <= numpixels; curpixel++ )
    {
        uint8_t *pCanvas = pDisplayRam;
        pCanvas += m_WindowSizeX * (y % m_WindowSizeY) + (x % m_WindowSizeX);

        PixelStruct_t pixel;

        pixel.Red   = RED_GREEN[ color.Red ];
        pixel.Green = RED_GREEN[ color.Green ];
        pixel.Blue  = BLUE[ color.Blue ];

        *pCanvas = *( uint8_t* )&pixel; //Draw the current pixel

        num += numadd;  //Increase the numerator by the top of the fraction
        if( num >= den ) //Check if numerator >= denominator
        {
            num -= den; //Calculate the new numerator value
            x += xinc1; //Change the x as appropriate
            y += yinc1; //Change the y as appropriate
        }
        x += xinc2; //Change the x as appropriate
        y += yinc2; //Change the y as appropriate
    }
}

void DisplayPlatform_t::DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos )
{
    Color_t color( 255, 255, 255 );
    DrawVerticalLine( xPos, yStartPos, yEndPos, color );
}

void DisplayPlatform_t::DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos, Color_t& color )
{
    // Display RAM
    uint8_t *pDisplayRam = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;

    // Swap yStartPos and yEndPos
    if( yEndPos < yStartPos ) 
    { 
        yStartPos ^= yEndPos; 
        yEndPos   ^= yStartPos; 
        yStartPos ^= yEndPos;
    } 

    //no single point of the line is on screen
    if( yEndPos >= m_WindowSizeY || yStartPos >= m_WindowSizeY || 
        xPos    >= m_WindowSizeX || xPos      >= m_WindowSizeX ) 
        return;

    for( uint16_t yPos = yStartPos; yPos <= yEndPos; yPos++ )
    {
        uint8_t *pCanvas = pDisplayRam;
        pCanvas += m_WindowSizeX * yPos + xPos;

        PixelStruct_t pixel;

        pixel.Red   = RED_GREEN[ color.Red ];
        pixel.Green = RED_GREEN[ color.Green ];
        pixel.Blue  = BLUE[ color.Blue ];

        *pCanvas = *( uint8_t* )&pixel; //Draw the current pixel
    }
}

void DisplayPlatform_t::DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos )
{
    Color_t color( 255, 255, 255 );
    DrawHorizontalLine( yPos, xStartPos, xEndPos, color );
}

void DisplayPlatform_t::DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos, Color_t& color )
{
    // Display RAM
    uint8_t *pDisplayRam = m_ExtSram.GetPointerBank1() + m_WindowSizeX * m_WindowSizeY * m_DisplayBuffer;

    // Swap yStartPos and yEndPos
    if( xEndPos < xStartPos ) 
    { 
        xStartPos ^= xEndPos; 
        xEndPos   ^= xStartPos; 
        xStartPos ^= xEndPos;
    } 

    //no single point of the line is on screen
    if( xEndPos >= m_WindowSizeX || xStartPos >= m_WindowSizeX || 
        yPos    >= m_WindowSizeY || yPos      >= m_WindowSizeY ) 
        return;

    for( uint16_t xPos = xStartPos; xPos <= xEndPos; xPos++ )
    {
        uint8_t *pCanvas = pDisplayRam;
        pCanvas += m_WindowSizeX * yPos + xPos;

        PixelStruct_t pixel;

        pixel.Red   = RED_GREEN[ color.Red ];
        pixel.Green = RED_GREEN[ color.Green ];
        pixel.Blue  = BLUE[ color.Blue ];

        *pCanvas = *( uint8_t* )&pixel; //Draw the current pixel
    }
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

