#include "Leds.h"


SystemLed_t::SystemLed_t( SystemLeds_t led )
{
    Port_t port;
    Pin_t  pin;

    port = g_LedInfo[led].port;
    pin  = g_LedInfo[led].pin;

    m_led = new GpioPin_t(port, pin);

    m_led->MakeOut();
    m_led->Clear();

}

SystemLed_t::~SystemLed_t()
{
    delete m_led;
}

void SystemLed_t::On( void )
{
    m_led->Set();
}

void SystemLed_t::Off( void )
{
    m_led->Clear();
}
