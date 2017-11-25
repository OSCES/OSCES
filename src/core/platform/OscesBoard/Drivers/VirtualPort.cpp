#include "GpioDriver.h"
#include "VirtualPort.h"

VirtualPort::VirtualPort(uint8_t numOfPins, ...):
    m_numOfPins(numOfPins)
{
    m_pins = new uint32_t[m_numOfPins];

    va_list vl;
    va_start(vl, numOfPins);

    for (uint8_t i = 0; i < m_numOfPins; ++i)
    {
        arg value = va_arg(vl, arg);

       // GpioPin_t* pin = new GpioPin_t( (Port_t)(AHB1PERIPH_BASE + value.access.port * 0x0400),
       //                                 (Pin_t )(1 << value.access.pin) );

        // TODO: implemet port type (Out, In)
        // Default: Out
       // pin->MakeOut();

      //  m_Pins[i] = (uint32_t)pin;
    }

    va_end(vl);
}

VirtualPort::~VirtualPort()
{
    for (uint8_t i = 0; i < m_numOfPins; ++i)
        delete (m_pins + i);

    delete[] m_pins;
}

void VirtualPort::write(uint32_t value)
{
    for (uint8_t i = 0; i < m_numOfPins; ++i)
    {
        if ((1 << i) & value)
            (m_pins + i)->set();
        else
            (m_pins + i)->clear();
    }
}

uint32_t VirtualPort::read()
{
    uint32_t value = 0;
    for (uint8_t i = 0; i < m_numOfPins; ++i)
        value |= (m_pins + i)->read();

    return value;
}
