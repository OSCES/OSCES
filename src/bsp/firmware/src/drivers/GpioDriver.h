#ifndef GpioDriver_h
#define GpioDriver_h


#include <stdint.h>
#include "stm32f2xx_gpio.h"
#include "GpioTypes.h"


class GpioPin_t
{
public:
    GpioPin_t( Port_t port, Pin_t pin );
    ~GpioPin_t();

    void MakeOut( void );
    void MakeOutOd( void );
    void MakeInNonPull( void );
    void MakeInPullUp( void );
    void MakeInPullDown( void );

    void    Set( void );
    void    Clear( void );
    uint8_t Read( void );

private:
    void InitPin( PinMode_t pinMode, OutType_t outType, PullType_t pullType );

private:  
    GPIO_TypeDef* m_Port;
    Pin_t         m_Pin;

}; 

#endif // GpioDriver_h
