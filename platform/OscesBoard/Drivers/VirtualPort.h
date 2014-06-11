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

class VirtualPort_t
{
public:
    VirtualPort_t( uint8_t numOfPins, ... );
    ~VirtualPort_t();

public:
    uint32_t Read( void );
    void     Write( uint32_t value );

    void     operator  = ( uint32_t value );
    uint32_t operator << ( uint8_t  shift );
    uint32_t operator >> ( uint8_t  shift );
    //uint32_t operator  ! ( void );

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

    uint8_t    m_numOfPins;
    uint32_t*  m_Pins;
};


#endif // VIRTUALPORT_H
