#ifndef GpioDriver_h
#define GpioDriver_h


#include <stdint.h>
//#include "stm32f2xx_conf.h"
#include "GpioTypes.h"
#include "NonCopyable.h"

class GpioPin : NonCopyable
{
public:
    GpioPin(Port port, Pin pin);
    ~GpioPin();

    void makeOut();
    void makeOutOd();
    void makeInNonPull();
    void makeInPullUp();
    void makeInPullDown();

    void set();
    void clear();
    uint8_t read();

private:
    void initPin(PinMode pinMode, OutType outType, PullType pullType);

private:
    GPIO_TypeDef *m_port;
    Pin m_pin;
};

#endif // GpioDriver_h
