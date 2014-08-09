#ifndef KEYBOARD_PLATFORM_H
#define KEYBOARD_PLATFORM_H


#include <stdint.h>
#include "GpioDriver.h"
#include "crossplatform/System/Keyboard/Keyboard.h"

class KeyboardPlatform_t : public Keyboard_t
{   
public:
    void Init( void );

    void OnInterrupt( void );
    static void InterruptHandler( void* pContext );

private:
    void DecodeData( uint8_t data );

private:
    GpioPin_t *m_DataPin;
    GpioPin_t *m_ClockPin;

};

#endif // KEYBOARD_H
