#ifndef SYSTIMER_PLATFORM_H
#define SYSTIMER_PLATFORM_H

#include "crossplatform/System/SysTimer/SysTimer.h"

class SysTimerPlatform_t : public SysTimer_t
{
public:
    uint32_t GetValueUsec();


};

#endif // SYSTIMER_PLATFORM_H
