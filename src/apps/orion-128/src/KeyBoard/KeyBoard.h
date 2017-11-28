#ifndef _KeyBoard_h_
#define _KeyBoard_h_


#include <stdint.h>
#include "../Ppi/Ppi.h"

#define KEYBOARD_RESET_TIME 10

class KeyBoard_t
{
    public:
		  void PressKey( uint8_t scanCode );		
          void UnPressKey( uint8_t scanCode );	
		  void Init( void );
          void Write( uint16_t addr, uint8_t data );
          uint8_t Read( uint16_t addr );


    private:
        static void    PpiPortWrite( void* pContext, PpiPortAddr_t port, uint8_t data );
        static uint8_t PpiPortRead ( void* pContext, PpiPortAddr_t port );


    private:
        uint8_t GetKeyFromMatrix( uint8_t scanLine/*, uint8_t row */);


    private:
        Ppi_t      m_KeyboardPpi;
        uint8_t    m_ScanLine;
        uint16_t   m_ResetCounter;
        uint8_t    m_PressedKeys;

};

#endif