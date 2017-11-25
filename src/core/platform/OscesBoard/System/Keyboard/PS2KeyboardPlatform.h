#ifndef KEYBOARD_PLATFORM_H
#define KEYBOARD_PLATFORM_H

#include "GpioDriver.h"
#include "crossplatform/System/Keyboard/Keyboard.h"
#include <stdint.h>

class KeyboardPlatform : public Keyboard
{
public:
    KeyboardPlatform();
    ~KeyboardPlatform();

    void init();
    void proceedInterrupt();

private:
    static void interruptHandler(void *context);

private:
    void decodeData(uint8_t data);

private:
    GpioPin *m_dataPin;
    GpioPin *m_clockPin;

    bool m_started;
    uint8_t m_bitCount;
    uint8_t m_data;
    uint8_t m_parity;
};

#endif // KEYBOARD_H
