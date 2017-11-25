#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "Kernel/SchedulerPlatform.h"

class DisplayPlatform;
class KeyboardPlatform;
class SysTimerPlatform;
class SchedulerPlatform;

class OscesFramework : public OscesFrameworkInterface
{
public:
    OscesFramework();
    ~OscesFramework();

    DisplayInterface* display();
    KeyboardInterface* keyboard();
    SysTimerInterface* sysTimer();
    bool applicationRunning();

    OscesFrameworkStatus init();
    void deInit();

    ThreadInterface* threadCreate(uint32_t stackSize, ThreadRoutine fpThreadRoutine, void *context);
    void threadDestroy(ThreadInterface *thread);
    void threadYield();

private:
    DisplayPlatform *m_display;
    KeyboardPlatform *m_keyboard;
    SysTimerPlatform *m_sysTimer;
    SchedulerPlatform *m_scheduler;
    bool m_applicationRunning;
};

#endif // OSCES_FRAMEWORK_H
