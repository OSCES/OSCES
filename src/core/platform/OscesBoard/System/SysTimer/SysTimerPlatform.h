#ifndef SYSTIMER_PLATFORM_H
#define SYSTIMER_PLATFORM_H

#include "crossplatform/System/SysTimer/SysTimer.h"

// TODO: this is some ugly enum
enum SysTimerPlatformInitStatus
{
    SYSTIMER_PLATFORM_INIT_SUCCESS,
    SYSTIMER_PLATFORM_INIT_FAIL
};

class SysTimerDriver;

class SysTimerPlatform : public SysTimer
{
public:
    SysTimerPlatform();
    ~SysTimerPlatform();

    SysTimerPlatformInitStatus init();
    uint32_t valueUsec();

private:
    SysTimerDriver *m_sysTimerDriver;
};

#endif // SYSTIMER_PLATFORM_H
