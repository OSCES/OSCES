#ifndef _Renderer_h_
#define _Renderer_h_

#include <stdint.h>

typedef  void ( *PresentLineCallBack_t )( void* pContext, uint8_t* pData, uint16_t lineNumber );    

enum RendererColorMode
{   
    RENDERER_MONOCHROME_PALETTE1_MODE = 0, //Green, black
    RENDERER_MONOCHROME_PALETTE2_MODE = 1, //Yellow, blue
    RENDERER_MONOCHROME_SHADOW_MODE1  = 2,
    RENDERER_MONOCHROME_SHADOW_MODE2  = 3,
    RENDERER_COLOR4_PALETE1_MODE      = 4,
    RENDERER_COLOR4_PALETE2_MODE      = 5,
    RENDERER_COLOR16_MODE1            = 6,
    RENDERER_COLOR16_MODE2            = 7, 
};


class Renderer_t
{
public:
    void RunFrame( uint8_t* memPage0, uint8_t* memPage1 );
    void SetPresentLineCallBack( void* pContext, PresentLineCallBack_t presentLineCallBack );
    void SwitchDisplay( uint8_t display );
    void SetVideoMode( uint8_t mode );


private:

    void*   m_pContext;
    uint8_t m_LineBuff[ 384 * 3];

private:
    PresentLineCallBack_t fp_PresentLineCallBack;

        
};

#endif