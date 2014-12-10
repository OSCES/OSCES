/*
    NES Emulator Project
    Created by Igor Belorus
    06/11/2012
*/

#include "DisplayPlatform.h"
#include <SDL_opengl.h>

#include <cmath>

void DisplayPlatform_t::Clear()
{
    uint32_t len = m_SurfaceSizeX * m_SurfaceSizeY;
    
    for( uint32_t idx = 0; idx < len; idx ++ )
    {
        m_pFrame[ m_CurrentFrame ][ idx ].Red   = 0;
        m_pFrame[ m_CurrentFrame ][ idx ].Green = 0;
        m_pFrame[ m_CurrentFrame ][ idx ].Blue  = 0;
    }
}

void DisplayPlatform_t::Init( uint16_t xSize, uint16_t ySize )
{ 
   Init( xSize, ySize, xSize, ySize );
}

void DisplayPlatform_t::Init( uint16_t xSize, uint16_t ySize, uint16_t xWindowSize, uint16_t yWindowSize )
{
    m_SurfaceSizeX = xSize;
    m_SurfaceSizeY = ySize;
    m_CurrentFrame = 0;
    m_pWindow      = 0;
    m_pOpenGLContext = 0;
    /*if( m_pFrame )
    {
        delete m_pFrame;
    }*/

    m_pFrame[ 0 ] = new DisplayPixelStruct_t[ m_SurfaceSizeX * m_SurfaceSizeY ];
    m_pFrame[ 1 ] = new DisplayPixelStruct_t[ m_SurfaceSizeX * m_SurfaceSizeY ];

    SDL_Init( SDL_INIT_VIDEO );
    WindowResize( xWindowSize, yWindowSize );   
}
    

void DisplayPlatform_t::WindowResize( uint16_t xSize, uint16_t ySize )
{
    m_WindowSizeX  = xSize;
    m_WindowSizeY  = ySize;

    if( 0 == m_pWindow )
    {
        m_pWindow = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WindowSizeX, m_WindowSizeY,
                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    }

    if( 0 != m_pWindow )
    {
        SDL_SetWindowSize( m_pWindow, m_WindowSizeX, m_WindowSizeY );
    }

    m_pOpenGLContext = SDL_GL_CreateContext( m_pWindow );

    glViewport(0, 0, m_WindowSizeX, m_WindowSizeY );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_WindowSizeX, m_WindowSizeY, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_SurfaceSizeX, m_SurfaceSizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue )
{
    if( ( xPos <= m_SurfaceSizeX ) && ( yPos <= m_SurfaceSizeY ) )
    {
        DisplayPixelStruct_t* pixel = &m_pFrame[ m_CurrentFrame ][ xPos + m_SurfaceSizeX * yPos ];

        pixel->Red   = red;
        pixel->Green = green;
        pixel->Blue  = blue;
    }
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos )
{
    //DrawPixel( xPos, yPos, Color_t( 255, 255, 255 ));
}

void DisplayPlatform_t::DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color )
{
    DrawPixel( xPos, yPos, color.Red, color.Green, color.Blue );
}

void DisplayPlatform_t::DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos )
{
    //DrawLine( xStartPos, yStartPos, xEndPos, yEndPos, Color_t( 255, 255, 255 ));
}

void DisplayPlatform_t::DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos, Color_t& color )
{
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
        DrawPixel(x % m_WindowSizeX, y % m_WindowSizeY, color);  //Draw the current pixel
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
    //DrawVerticalLine( xPos, yStartPos, yEndPos, Color_t( 255, 255, 255 ));
}

void DisplayPlatform_t::DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos, Color_t& color )
{
    // Swap yStartPos and yEndPos
    if( yEndPos < yStartPos ) 
    { 
        yStartPos ^= yEndPos; 
        yEndPos   ^= yStartPos; 
        yStartPos ^= yEndPos;
    } 

    //no single point of the line is on screen
    if( yEndPos < 0 || yStartPos >= m_WindowSizeY || 
        xPos    < 0 || xPos      >= m_WindowSizeX ) 
        return;

    for( uint16_t yPos = yStartPos; yPos <= yEndPos; yPos++ )
    {
        DrawPixel( xPos, yPos, color );
    }
}

void DisplayPlatform_t::DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos )
{
    Color_t color( 255, 255, 255 );
    DrawHorizontalLine( yPos, xStartPos, xEndPos, color );
}

void DisplayPlatform_t::DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos, Color_t& color )
{
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
        DrawPixel(xPos, yPos, color);
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
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_SurfaceSizeX, m_SurfaceSizeY, GL_RGB, GL_UNSIGNED_BYTE, m_pFrame[ m_CurrentFrame ] );

    glBegin( GL_QUADS );
        glTexCoord2d(0.0, 0.0);  glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);  glVertex2d(m_WindowSizeX, 0.0);
        glTexCoord2d(1.0, 1.0);  glVertex2d(m_WindowSizeX, m_WindowSizeY);
        glTexCoord2d(0.0, 1.0);  glVertex2d(0.0, m_WindowSizeY);
    glEnd();
 
    SDL_GL_SwapWindow( m_pWindow );

    m_CurrentFrame = !m_CurrentFrame;

}

void DisplayPlatform_t::SetTitle( const char* pTitle )
{
    SDL_SetWindowTitle( m_pWindow, pTitle );
}

DisplayPlatform_t::~DisplayPlatform_t()
{
    SDL_GL_DeleteContext( m_pOpenGLContext );
    SDL_DestroyWindow( m_pWindow );
    delete m_pFrame[ 0 ];
    delete m_pFrame[ 1 ];
}