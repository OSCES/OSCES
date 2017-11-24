#ifndef SYSTIMER_DRIVER_H
#define SYSTIMER_DRIVER_H

#include <stdint.h>

class SysTimerDriver
{
public:
    SysTimerDriver();

    void init();
    uint32_t valueUsec();

private:
    static void sysTimerInterruptRoutine(void *context);

private:
    uint64_t m_usec;
    uint32_t m_sysTickValue;
};

#endif // SYSTIMER_DRIVER_H
