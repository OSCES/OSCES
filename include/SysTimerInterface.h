#ifndef SYSTIMER_INTERFACE_H
#define SYSTIMER_INTERFACE_H

#include <stdint.h>

class SysTimerInterface
{
public:
    virtual uint32_t valueUsec() = 0;
    virtual ~SysTimer() {}
};

#endif // SYSTIMER_INTERFACE_H
