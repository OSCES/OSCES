#ifndef CONTEXT_SWITCHER_H
#define CONTEXT_SWITCHER_H

#include <stdint.h>
#include "SchedulerPlatform.h"

class ContextSwitcher_t
{
public:
    ContextSwitcher_t( SchedulerPlatform_t* pScheduler );
      
    void SwitchToThreadMode();
    void ForceSwitchContext();
    uint32_t PrepareExeptionStackFrame( uint32_t stackAddr );
    
public:
    void PendSvInterruptRoutine();    
    void SysTimerInterruptRoutine();
    
private:
    SchedulerPlatform_t* m_pScheduler;

};




#endif // CONTEXT_SWITCHER_H
