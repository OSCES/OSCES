#include "leds.h"

static const PinInfo LedInfo[SystemLedCount] =
{
    {PortD, Pin8 }, // Led 1
    {PortE, Pin11}, // Led 2
    {PortE, Pin12}, // Led 3
    {PortE, Pin13}  // Led 4
};

SystemLed::SystemLed(SystemLedType led) :
    m_led(0)
{
    m_led = new GpioPin(LedInfo[led].port, LedInfo[led].pin);
    m_led->makeOut();
    m_led->clear();
}

SystemLed::~SystemLed()
{
    delete m_led;
}

void SystemLed::on()
{
    m_led->set();
}

void SystemLed::off()
{
    m_led->clear();
}
