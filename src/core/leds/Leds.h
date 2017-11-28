#ifndef LEDS_H
#define LEDS_H

#include "GpioDriver.h"

enum SystemLedType
{
    SystemLed1, // TODO: set led name (LED__SYSTEM_LOAD, LED__SYSTEM_IDLE and so on)
    SystemLed2,
    SystemLed3,
    SystemLed4,

    SystemLedCount
};

class SystemLed
{
public:
    SystemLed(SystemLedType led);
    ~SystemLed();

    void on();
    void off();

private:
    GpioPin *m_led;
};


#endif // LEDS_H
