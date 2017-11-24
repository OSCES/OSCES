#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H


#include <stdint.h>
#include <stdarg.h>

#include "VirtualPortTypes.h"


/*************************************************************************\
 *                                                                       *
 *  Format of input parameter for VirtualPort constructor:               *
 *                                                                       *
 *  0x6B                                                                 *
 *    ||                                                                 *
 *    |+--- Pin number  ( B ~ Pin_11)                                    *
 *    |                                                                  *
 *    +---- Port number ( 6 ~ PORTG )                                    *
 *                                                                       *
 *                                                                       *
\*************************************************************************/

class GpioPin;

class VirtualPort
{
public:
    VirtualPort(uint8_t numOfPins, ...);
    ~VirtualPort();

public:
    uint32_t read();
    void write(uint32_t value);

private:
    union arg
    {
        struct access
        {
            uint8_t pin  : 4;
            uint8_t port : 4;
        };
        uint8_t value;
    };

    uint8_t  m_numOfPins;
    GpioPin *m_pins;
};


#endif // VIRTUALPORT_H
