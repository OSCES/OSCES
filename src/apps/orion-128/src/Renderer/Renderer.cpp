#include "Renderer.h"


void Renderer_t::SetPresentLineCallBack( void* pContext, PresentLineCallBack_t presentLineCallBack )
{
    fp_PresentLineCallBack = presentLineCallBack;
    m_pContext = pContext;
}

void Renderer_t::RunFrame( uint8_t* memPage0, uint8_t* memPage1 )
{
    uint8_t nPixel = 7;
                  
    uint16_t addr = 0xC000;

    for(int y = 0; y < 256; y ++ )
    { 
        for( int x = 0; x < 384; x++ )
        { 
               
            if( 0 == x % 8)
            {
                addr = 0xC000 + y + 0x100 * ( x / 8 );
                nPixel = 7;
            }
                
            uint8_t color = (memPage0[addr] >> nPixel  ) & 0x01;
            color *= 200;
            nPixel--;
                
            m_LineBuff[ 3 * x + 0 ] = color;
            m_LineBuff[ 3 * x + 1 ] = color;
            m_LineBuff[ 3 * x + 2 ] = color;
                
        } 

        fp_PresentLineCallBack( m_pContext, m_LineBuff, y ); 
    } 

    fp_PresentLineCallBack( m_pContext, 0, 0 );
}

void Renderer_t::SwitchDisplay( uint8_t display )
{
    uint8_t a = 0;
}

void Renderer_t::SetVideoMode( uint8_t mode )
{
    uint8_t a = 0;
}