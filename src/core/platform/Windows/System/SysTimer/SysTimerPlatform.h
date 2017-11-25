#ifndef SYSTIMER_PLATFORM_H
#define SYSTIMER_PLATFORM_H

#include "crossplatform/System/SysTimer/SysTimer.h"

class SysTimerPlatform : public SysTimer
{
public:
    uint32_t valueUsec();
};

#endif // SYSTIMER_PLATFORM_H
