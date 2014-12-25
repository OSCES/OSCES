#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "SysTimer/SysTimerPlatform.h"
#include "KeyBoard/PS2KeyBoardPlatform.h"
#include "Display/DisplayPlatform.h"
#include "Kernel/SchedulerPlatform.h"

class OscesFramework_t : public OscesFrameworkInterface_t
{
public:
    OscesFramework_t();
    DisplayInterface_t*  GetDisplay();
    KeyboardInterface_t* GetKeyboard();
    SysTimerInterface_t* GetSysTimer();
    bool                 IsApplicationRun();
    ThreadInterface_t*   CreateThread( uint32_t stackSize, ThreadRoutine_t fpThreadRoutine, void* pContext );
    void                 DestroyThread( ThreadInterface_t* pThread );   
    
    OscesFrameworkStatus_t Init();
    void DeInit();


private:
    DisplayPlatform_t*   m_pDisplay;
    KeyboardPlatform_t*  m_pKeyboard;
    SysTimerPlatform_t*  m_pSysTimer;
    SchedulerPlatform_t* m_pScheduler;
private:
    bool m_IsApplicationRun;

};


#endif // OSCES_FRAMEWORK_H
