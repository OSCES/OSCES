/*
    NES Emulator Project
    Created by Igor Belorus
    06/11/2012
*/

#ifndef EMULATOR_H
#define EMULATOR_H

#include  "GameConsole/GameConsole.h"

class Emulator_t
{
public:
    void Init();
    bool Run();

    static void JoysticEvent( void * pContext, uint8_t joysticA, uint8_t joysticB );
private:
    static void RomFileAcces( void * pContext, uint8_t* pData, uint32_t offset, uint16_t bytesCnt );
    static void PresentFrame( void * pContext, uint8_t* pData, uint16_t len, uint16_t posInFrame );
    static void AudioDacQueryFrame( void * pContext, int16_t* pData, uint16_t bytesCnt );
    //    static void GameConsoleControl( void * pContext, ConsoleCommand_t command );

private:
    //    FileManager_t     m_RomManager;
    GameConsole_t     m_GameConsole;
    //    Display_t         m_Display;
    //    AudioDac_t        m_AudioDac;
    //    InputManager_t    m_InputManager;
    bool	          m_GameConsoleStarted;
};

#endif
