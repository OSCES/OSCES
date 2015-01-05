#include "GraphicalPrimitives/Line.h"
#include <math.h>

Line_t::Line_t( Surface_t* pSurface )
{
	m_pSurface = pSurface;
}

void Line_t::SetColor( Color_t& color )
{

}


void Line_t::Draw( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos )
{
   /* if( xStartPos > m_WindowSizeX - 1 || 
        xEndPos   > m_WindowSizeX - 1 || 
        yStartPos > m_WindowSizeY - 1 || 
        yEndPos   > m_WindowSizeY - 1 )
        return;*/

    int deltax = ( int )abs( (long double)(xEndPos - xStartPos) ); //The difference between the x's
    int deltay = ( int )abs( (long double)(yEndPos - yStartPos) ); //The difference between the y's
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
        //!!!DrawPixel( x % m_WindowSizeX, y % m_WindowSizeY, color );  //Draw the current pixel
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


void Line_t::DrawVertical( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos )
{
    // Swap yStartPos and yEndPos
    if( yEndPos < yStartPos ) 
    { 
        yStartPos ^= yEndPos; 
        yEndPos   ^= yStartPos; 
        yStartPos ^= yEndPos;
    } 

    //no single point of the line is on screen
    /*if( yEndPos < 0 || yStartPos >= m_WindowSizeY || 
        xPos    < 0 || xPos      >= m_WindowSizeX ) 
        return;*/

    for( uint16_t yPos = yStartPos; yPos <= yEndPos; yPos++ )
    {
        //!!!DrawPixel( xPos, yPos, color );
    }
}

void Line_t::DrawHorizontal322To888( uint16_t xPos, uint16_t yPos, uint16_t size )
{

}


void Line_t::DrawHorizontal( uint16_t xPos, uint16_t yPos, uint16_t size )
{
    // Swap yStartPos and yEndPos
    /*if( xEndPos < xStartPos ) 
    { 
        xStartPos ^= xEndPos; 
        xEndPos   ^= xStartPos; 
        xStartPos ^= xEndPos;
    } */

    //no single point of the line is on screen
    /*if( xEndPos >= m_WindowSizeX || xStartPos >= m_WindowSizeX || 
        yPos    >= m_WindowSizeY || yPos      >= m_WindowSizeY ) 
        return;*/

	DisplayPixelStruct_t* pPixel = static_cast< PixelStruct_t* >( m_pSurface->GetFrameBuffer() );

    
	pPixel += 800;// ( xPos + 400 * yPos );

    for( uint32_t idx = 0; idx < /*size*/ 400 * 300; idx++ )
    {
		pPixel->Red   = 0xFF;
		pPixel->Green = 0xFF;
		pPixel->Blue  = 0xFF;

		pPixel++;
        //!!!DrawPixel(xPos, yPos, color);
    }
}