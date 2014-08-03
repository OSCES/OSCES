#ifndef SYSTIMER_PLATFORM_H
#define SYSTIMER_PLATFORM_H

#include "SysTimerInterface.h"

class SysTimerPlatform_t : public SysTimerInterface_t
{
public:
    SysTimerPlatform_t();
    virtual ~SysTimerPlatform_t();
public:
    uint32_t GetSysTick();

};

#endif // SYSTIMER_PLATFORM_H
