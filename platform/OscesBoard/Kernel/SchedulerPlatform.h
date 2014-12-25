#ifndef SCHEDULER_PLATFORM_H
#define SCHEDULER_PLATFORM_H

#include <stdint.h>

#include "ThreadInterface.h"

#include "Context.h"

class SchedulerPlatform_t
{
public:
    SchedulerPlatform_t();
    void Start();

    
    Context_t* GetCurrentThreadContext();
    Context_t* GetNextThreadContext();
    
// ----------- Thread methods ----------------//
    static uint32_t ThreadCreate( uint32_t stackSize, ThreadRoutine_t pThreadRoutine, void* pContextA, void* pContextB );
    void ThreadDestroy( uint32_t threadId );
    void ThreadStart( uint32_t threadId );
    void ThreadStop( uint32_t threadId );
    void ThreadSleep( uint32_t threadId, uint32_t seconds );
    void ThreadSleepMsec( uint32_t threadId, uint32_t mSeconds );
    void ThreadSetPriority( uint32_t threadId, uint8_t priority );
    static void ThreadYield( uint32_t threadId );
// -------------------------------------------//    
    
public:
    static uint32_t GetSysTick();
    //static void SysTimerInterruptRoutine();
    //static void PendSvInterruptRoutine();
    static void Trap();
    
private:
   // uint32_t GetNextThreadIdx();
    
private:  
    static SchedulerPlatform_t* g_pScheduler;    

private:
//    uint32_t              m_SysTickValue;
//    SysTimerIntRoutine_t  m_fpSysTimerIntRoutine;
    void*                 m_pContext;
    
};


#endif // SCHEDULER_PLATFORM_H
