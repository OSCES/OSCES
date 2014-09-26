#ifndef KEYBOARD_PLATFORM_H
#define KEYBOARD_PLATFORM_H


#include <stdint.h>
#include "GpioDriver.h"
#include "crossplatform/System/Keyboard/Keyboard.h"

class KeyboardPlatform_t : public Keyboard_t
{   
public:
    void Init();
    void OnInterrupt();

private:
    static void InterruptHandler( void* pContext );    
    
private:
    void DecodeData( uint8_t data );

private:
    GpioPin_t* m_DataPin;
    GpioPin_t* m_ClockPin;

private:
    uint8_t m_started;
    uint8_t m_bitCount;
    uint8_t m_data;
    uint8_t m_parity;
};

#endif // KEYBOARD_H
