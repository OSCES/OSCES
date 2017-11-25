#ifndef LEDS_H
#define LEDS_H


#include "GpioDriver.h"


enum SystemLeds_t
{
    SYSTEM_LED_1 = 0,   // TODO: set led name (LED__SYSTEM_LOAD, LED__SYSTEM_IDLE and so on)
    SYSTEM_LED_2,
    SYSTEM_LED_3,
    SYSTEM_LED_4
};

static const PinInfo g_LedInfo[] =
{
    {PORTD, PIN_8 },    // Led 1
    {PORTE, PIN_11},    // Led 2
    {PORTE, PIN_12},    // Led 3
    {PORTE, PIN_13}     // Led 4
};


class SystemLed_t
{
public:
    SystemLed_t( SystemLeds_t led );
    ~SystemLed_t();

    void On( void );
    void Off( void );

private:
    GpioPin_t* m_led;
};


#endif // LEDS_H
