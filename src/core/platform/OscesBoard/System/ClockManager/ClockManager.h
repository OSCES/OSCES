#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include "NonCopyable.h"
#include <stdint.h>

class ClockManager : NonCopyable
{
private:
    ClockManager();

public:
    enum SystemClock
    {
        SysClock_24MHz,
        SysClock_120MHz,
    };

    enum GpioClock
    {
        PortA = 0x00000001,
        PortB = 0x00000002,
        PortC = 0x00000004,
        PortD = 0x00000008,
        PortE = 0x00000010,
        PortF = 0x00000020,
        PortG = 0x00000040,
        PortH = 0x00000080,
        PortI = 0x00000100,
    };

    static ClockManager& instance();

    void setSystemClock(SystemClock clock);
    void enableGpioClock(GpioClock clock);

private:
    uint32_t m_gpioClockEnabled;
};

#endif // SYSTIMER_H
