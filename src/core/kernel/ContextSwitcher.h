#ifndef CONTEXT_SWITCHER_H
#define CONTEXT_SWITCHER_H

#include <stdint.h>
#include "SchedulerPlatform.h"

class ContextSwitcher
{
public:
    ContextSwitcher(SchedulerPlatform *scheduler);

    void switchToThreadMode();
    void forceSwitchContext();
    uint32_t prepareExeptionStackFrame(uint32_t stackAddr);

public:
    void pendSvInterruptRoutine();
    void sysTimerInterruptRoutine();

private:
    SchedulerPlatform *m_scheduler;
};

#endif // CONTEXT_SWITCHER_H
