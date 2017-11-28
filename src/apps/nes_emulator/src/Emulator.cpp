/*
    NES Emulator Project
    Created by Igor Belorus
    06/11/2012
*/

#include "OscesCore.h"
#include "VideoSystem.h"
#include "AbstractDisplay.h"
#include "PaintEngine.h"
#include "Emulator.h"
#include <stdio.h>

extern uint8_t GameFile[];

void Emulator_t::Init()
{
    m_GameConsoleStarted = false;

    m_GameConsole.SetPresentFrameCallBack( PresentFrame, this );
    m_GameConsole.SetRomFileAccesCallBack( RomFileAcces, this );
    //    m_GameConsole.SetAudioSamplingRate( AUDIO_DAC_SAMPLING_RATE );
    m_GameConsole.Init();
}

bool Emulator_t::Run()
{
    uint32_t msec = OscesCore::tickCount();
    m_GameConsole.Run(msec);

    static uint32_t frames = 0;
    static uint32_t fps = 0;

    frames++;
    fps = m_GameConsole.GetFramesPerSecond();
    OscesCore::videoSystem()->display()->updateFpsInfo(fps);

    return false;
}

void Emulator_t::AudioDacQueryFrame( _out_ void* pContext, _out_ int16_t* pData, _in_ uint16_t bytesCnt )
{
    Emulator_t* emulator = static_cast<Emulator_t *>(pContext);
    emulator->m_GameConsole.GetAudioFrame( pData, bytesCnt );
}

void Emulator_t::JoysticEvent( _in_ void* pContext, _in_ uint8_t joysticA, _in_ uint8_t joysticB )
{
    Emulator_t* emulator = static_cast<Emulator_t *>(pContext);
    emulator->m_GameConsole.SetButtonJoysticA( joysticA );
    emulator->m_GameConsole.SetButtonJoysticB( joysticB );
}

void Emulator_t::RomFileAcces( _in_ void * pContext, _out_ uint8_t* pData, _in_ uint32_t offset, _in_ uint16_t bytesCnt )
{
    //Emulator_t* emulator = static_cast<Emulator_t *>(pContext);
    uint8_t* pSource = ( uint8_t* )&GameFile[ offset ];

    for( uint16_t i = 0; i != bytesCnt; i++ ) // Подгружаем bytesCnt байт из файла игры в картридж
    {
        *pData++ = *pSource++;
    }
}

void Emulator_t::PresentFrame( _in_ void * pContext, uint8_t* pData, uint16_t len, uint16_t posInFrame )
{
    static uint32_t* pPalette = GetPalettePixelRGBA();
    static int y = 0;
    static PaintEngine paintEngine;
    static AbstractDisplay *display = OscesCore::videoSystem()->display();
    static int xOffset = (display->width() - PPU_HORIZONTAL_RESOLUTION) / 2;
    static int yOffset = (display->height() - PPU_VERTICAL_PAL_RESOLUTION) / 2;

    if (posInFrame == 0)
    {
        paintEngine.drawEnd();
        y = yOffset;
    }

    paintEngine.drawBegin(display);
    for (int x = xOffset; x < PPU_HORIZONTAL_RESOLUTION + xOffset; ++x)
    {
        uint32_t rgb = pPalette[*pData++];
        uint8_t r = (rgb >> 24) & 0xFF;
        uint8_t g = (rgb >> 16) & 0xFF;
        uint8_t b = (rgb >> 8) & 0xFF;
        Color color(r, g, b);
        paintEngine.setPenColor(color);
        paintEngine.drawPixel(x, y);
    }
    ++y;
}
