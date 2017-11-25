/*
    NES Emulator Project
    Created by Igor Belorus
    06/11/2012
*/

#ifndef DISPLAY_PLATFORM_H
#define DISPLAY_PLATFORM_H

#include <stdint.h>
#include "SDL.h"
#include "crossplatform/System/Display/Display.h"

class DisplayPlatform : public DisplayInterface
{
public:
    bool init(uint16_t xSize, uint16_t ySize, bool isVsyncEnable);
    void init(uint16_t xSize, uint16_t ySize, uint16_t xWindowSize, uint16_t yWindowSize, bool isVsyncEnable);
    void WindowResize( uint16_t xSize, uint16_t ySize );
    void setTitle( const char* pTitle );
    void drawPixel( uint16_t xPos, uint16_t yPos );
    void drawPixel(uint16_t xPos, uint16_t yPos, const Color &color );
    void drawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ); // compability issue
    void flip( void );
    void clear();
    void* frameBuffer();
    uint32_t height() const;
    uint32_t width() const;

    DisplayPlatform();
    ~DisplayPlatform();

private:
    SDL_Window*    m_pWindow;
    SDL_Texture *  m_Texture;
    SDL_Renderer * m_Renderer;

    uint32_t*      m_pFrame[ 2 ];
    uint16_t       m_WindowSizeX;
    uint16_t       m_WindowSizeY;
    uint16_t       m_SurfaceSizeX;
    uint16_t       m_SurfaceSizeY;
    uint8_t        m_CurrentFrame;
};

#endif
