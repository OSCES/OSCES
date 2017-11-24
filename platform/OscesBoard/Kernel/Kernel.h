#ifndef KERNEL_H
#define KERNEL_H

#include "SchedulerPlatform.h"

class ContextSwitcher;

class Kernel
{
public:
    Kernel();

    void Init();
    void yield();
    void deInit();

private:
    static void pentSvInterruptRoutine(void *context);

private:
    ContextSwitcher *m_contextSwitcher;
    SchedulerPlatform m_schedulerPlatform;
};

#endif // KERNEL_H
