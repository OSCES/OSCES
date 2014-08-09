#ifndef SYSTIMER_PLATFORM_H
#define SYSTIMER_PLATFORM_H

#include "crossplatform/System/SysTimer/SysTimer.h"

enum SysTimerPlatformInitStatus_t
{
    SYSTIMER_PLATFORM_INIT_SUCCESS = 0,
    SYSTIMER_PLATFORM_INIT_FAIL
};

class SysTimerPlatform_t : public SysTimer_t
{
public:
    SysTimerPlatformInitStatus_t Init();
    uint32_t GetValueUsec();

    
private:
    void* m_pSysTimerDriver;
};

#endif // SYSTIMER_PLATFORM_H
