/*
    NES Emulator Project
    Created by Igor Belorus
    06/11/2012
*/

#include "Emulator.h"
#include <stdio.h>
#include "OscesFrameworkInterface.h"

extern uint8_t GameFile[];
extern OscesFrameworkInterface_t* System;

void Emulator_t::Init()
{
    m_GameConsoleStarted = false;

    m_GameConsole.SetPresentFrameCallBack( PresentFrame, this );
    m_GameConsole.SetRomFileAccesCallBack( RomFileAcces, this );
//    m_GameConsole.SetAudioSamplingRate( AUDIO_DAC_SAMPLING_RATE );  
    m_GameConsole.Init();
}

uint32_t frames = 0;
volatile uint32_t fps = 0;

bool Emulator_t::Run()
{
    bool isExit = false;
    
	uint32_t msec = System->GetSysTimer()->GetValueUsec();
        
    m_GameConsole.Run( msec );

    frames++;
    
	fps = m_GameConsole.GetFramesPerSecond();
				
	char fpsStr[20];
	//sprintf( fpsStr, "FPS = %d", fps );
		
	//System->GetDisplay()->SetTitle( fpsStr );

    return isExit;
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

//#ifndef WIN32

//	static uint8_t* pPixel = ( uint8_t* )System->GetDisplay()->GetFrameBuffer();
//    static uint8_t* pPalette = GetPalettePixel332();
//    static uint32_t displayAlign = System->GetDisplay()->GetSizeHorizontal() - PPU_HORIZONTAL_RESOLUTION;

//    if( 0 == posInFrame )
//	{
//		System->GetDisplay()->Flip();
//	    pPixel = ( uint8_t* )System->GetDisplay()->GetFrameBuffer();
//	}
    	
//    for( uint16_t xVisible = 0; xVisible < PPU_HORIZONTAL_RESOLUTION; xVisible++ )
//    {
//		*pPixel ++= pPalette[ *pData++ ];
//	}

//	pPixel += displayAlign;

//#else

	static uint32_t* pPixel = ( uint32_t* )System->GetDisplay()->GetFrameBuffer();
	static uint32_t* pPalette = GetPalettePixel8888();
    static uint32_t displayAlign = System->GetDisplay()->GetSizeHorizontal() - PPU_HORIZONTAL_RESOLUTION;

    if( 0 == posInFrame )
	{
		System->GetDisplay()->Flip();
        pPixel = ( uint32_t* )  System->GetDisplay()->GetFrameBuffer();
	}
    
    for( uint16_t xVisible = 0; xVisible < PPU_HORIZONTAL_RESOLUTION; xVisible++ ) 
    {
		*pPixel ++= pPalette[ *pData++ ];
	}

	pPixel += displayAlign;

//#endif

}
