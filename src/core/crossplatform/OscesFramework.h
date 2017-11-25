#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "SysTimer/SysTimerPlatform.h"
#include "PS2KeyboardPlatform.h"
#include "Display/DisplayPlatform.h"
#include "Kernel/SchedulerPlatform.h"

class OscesFramework_t : public OscesFrameworkInterface
{
public:
    OscesFramework_t();
    DisplayInterface*  display();
    KeyboardInterface* keyboard();
    SysTimerInterface* sysTimer();
    bool applicationRunning();
    ThreadInterface *ThreadCreate( uint32_t stackSize, ThreadRoutine_t fpThreadRoutine, void* pContext );
    void ThreadDestroy(ThreadInterface *thread);
    void ThreadYield();


    OscesFrameworkStatus Init();
    void DeInit();


private:
    DisplayPlatform *m_pDisplay;
    KeyboardPlatform *m_pKeyboard;
    SysTimerPlatform *m_pSysTimer;
    SchedulerPlatform *m_pScheduler;
private:
    bool m_IsApplicationRun;
};


#endif // OSCES_FRAMEWORK_H
