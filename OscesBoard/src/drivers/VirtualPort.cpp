#include "GpioDriver.h"
#include "VirtualPort.h"


VirtualPort_t::VirtualPort_t( uint8_t numOfPins, ... ):
    m_numOfPins(numOfPins)
{
    m_Pins = new uint32_t[m_numOfPins];

    va_list vl;
    va_start(vl, numOfPins);

    for(uint8_t i = 0; i < m_numOfPins; i++)
    {
        arg value = va_arg(vl, arg);

        GpioPin_t* pin = new GpioPin_t( (Port_t)(AHB1PERIPH_BASE + value.port * 0x0400),
                                        (Pin_t )(1 << value.pin) );

        // TODO: implemet port type (Out, In)
        // Default: Out
        pin->MakeOut();

        m_Pins[i] = (uint32_t)pin;
    }

    va_end(vl);
}

VirtualPort_t::~VirtualPort_t()
{
    while(m_numOfPins--)
    {
        delete (GpioPin_t*)(m_Pins[m_numOfPins]);
    }

    delete[] m_Pins;
}

void VirtualPort_t::Write(uint32_t value )
{
    for(uint8_t i = 0; i < m_numOfPins; i++)
    {
        if( (0x0001 << i) & value )
        {
            ( (GpioPin_t*)(m_Pins[i]) )->Set();
        }
        else
        {
            ( (GpioPin_t*)(m_Pins[i]) )->Clear();
        }
    }
}

uint32_t VirtualPort_t::Read()
{
    uint32_t value = 0x0000;

    for(uint8_t i = 0; i < m_numOfPins; i++)
    {
        value |= ( (GpioPin_t*)(m_Pins[i]) )->Read();
    }

    return value;
}

void VirtualPort_t::operator = (uint32_t value )
{
    Write( value );
}

uint32_t VirtualPort_t::operator << ( uint8_t  shift )
{
    if( shift >= m_numOfPins )
    {
        return 0;
    }

    return Read() << shift;
}

uint32_t VirtualPort_t::operator >> ( uint8_t  shift )
{
    if( shift >= m_numOfPins )
    {
        return 0;
    }

    return Read() >> shift;
}

/*
 uint32_t operator  ! ( void )
 {
     return !Read();
 }
*/
