#include "GraphicalPrimitives/Line.h"
#include <math.h>

Line_t::Line_t( Surface_t* pSurface )
{
    m_pSurface = pSurface;

    fp_DrawHorizontal = &Line_t::DrawHorizontal322To888;
    fp_DrawVertical   = &Line_t::DrawVertical322To888;
	
    m_Color = Color_t( COLOR_DEFAULT_RED, COLOR_DEFAULT_GREEN, COLOR_DEFAULT_BLUE, 0, DISPLAY_PIXEL_FORMAT_DEFAULT );
}

void Line_t::SetColor( Color_t& color )
{
    m_Color = color;
}

uint32_t Line_t::GetAbs( int32_t value )
{
    uint32_t result = value;

    if( value < 0 )
    {
        result = - value;
    }

    return result;
}


void Line_t::Draw( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos )
{
    uint32_t sizeHorizontal = m_pSurface->GetSizeHorizontal();
    uint32_t sizeVertical= m_pSurface->GetSizeVertical();
	
    uint32_t deltax = GetAbs( xEndPos - xStartPos );
    uint32_t deltay = GetAbs( yEndPos - yStartPos );
	   
    int denumerator, numerator, numadd;
		   
    int xinc1 = ( xEndPos >= xStartPos ) ? 1: -1;
    int yinc1 = ( yEndPos >= yStartPos ) ? 1: -1;

    int xinc2 = xinc1;
    int yinc2 = yinc1;
	    
    uint32_t numpixels = 0;

    if( deltax >= deltay ) //There is at least one x-value for every y-value
    {
        xinc1 = 0; //Don't change the x when numerator >= denominator
        yinc2 = 0; //Don't change the y for every iteration
        denumerator = deltax;
        numerator = deltax / 2;
        numadd = deltay;
        numpixels = deltax; //There are more x-values than y-values
    }
    else //There is at least one y-value for every x-value
    {
        xinc2 = 0; //Don't change the x for every iteration
        yinc1 = 0; //Don't change the y when numerator >= denominator
        denumerator = deltay;
        numerator = deltay / 2;
        numadd = deltax;
        numpixels = deltay; //There are more y-values than x-values
    }

    PixelStructRGB888_t pixel =  { m_Color.GetRed(), m_Color.GetGreen(), m_Color.GetBlue() };
    PixelStructRGB888_t* pPixel = static_cast< PixelStructRGB888_t* >( m_pSurface->GetFrameBuffer() );
	
    int xPos = xStartPos;
    int yPos = yStartPos;

    for( uint32_t idx = 0; idx <= numpixels; idx++ )
    {
        uint32_t index = xPos % sizeHorizontal + sizeHorizontal * ( yPos % sizeVertical );

        pPixel[ index ] = pixel;
		
        numerator += numadd;  //Increase the numerator by the top of the fraction

        if( numerator >= denumerator )
        {
            numerator -= denumerator; //Calculate the new numerator value
            xPos += xinc1;
            yPos += yinc1;
        }
        xPos += xinc2;
        yPos += yinc2;
    }
}


void Line_t::DrawVertical( uint16_t xPos, uint16_t yPos, uint16_t size )
{
    ( this->*fp_DrawVertical )( xPos, yPos, size );
}

void Line_t::DrawHorizontal( uint16_t xPos, uint16_t yPos, uint16_t size )
{
    ( this->*fp_DrawHorizontal )( xPos, yPos, size );
}

// ----------------------------------------- Drawing factory -----------------------------------------

void Line_t::DrawHorizontal888To888( uint16_t xPos, uint16_t yPos, uint16_t size )
{

}

void Line_t::DrawHorizontal322To322( uint16_t xPos, uint16_t yPos, uint16_t size )
{

}

void Line_t::DrawHorizontal322To888( uint16_t xPos, uint16_t yPos, uint16_t size )
{
    PixelStructRGB888_t* pPixel = static_cast< PixelStructRGB888_t* >( m_pSurface->GetFrameBuffer() );

    pPixel += xPos + yPos * m_pSurface->GetSizeHorizontal();

    PixelStructRGB888_t pixel =  { m_Color.GetRed(), m_Color.GetGreen(), m_Color.GetBlue() };

    for( uint32_t idx = 0; idx < size; idx++ )
    {
        *pPixel ++= pixel;
    }
}

void Line_t::DrawVertical322To888( uint16_t xPos, uint16_t yPos, uint16_t size )
{
    PixelStructRGB888_t* pPixel = static_cast< PixelStructRGB888_t* >( m_pSurface->GetFrameBuffer() );

    uint32_t sizeHorizontal = m_pSurface->GetSizeHorizontal();

    pPixel += xPos + yPos * sizeHorizontal;

    PixelStructRGB888_t pixel =  { m_Color.GetRed(), m_Color.GetGreen(), m_Color.GetBlue() };

    for( uint32_t idx = 0; idx < size; idx++ )
    {
        *pPixel = pixel;
        pPixel += sizeHorizontal;
    }
}

void Line_t::DrawVertical888To888( uint16_t xPos, uint16_t yPos, uint16_t size )
{

}

void Line_t::DrawVertical322To322( uint16_t xPos, uint16_t yPos, uint16_t size )
{

}