#ifndef SCHEDULER_PLATFORM_H
#define SCHEDULER_PLATFORM_H

#include <stdint.h>

#include "ThreadInterface.h"

class Context;

class SchedulerPlatform
{
public:
    SchedulerPlatform();
    void start();

    Context* currentThreadContext();
    Context* nextThreadContext();

// ----------- Thread methods ----------------//
    static uint32_t threadCreate(uint32_t stackSize, ThreadRoutine pThreadRoutine, void *contextA, void *contextB);
    static void threadYield(uint32_t threadId);

    void threadDestroy(uint32_t threadId);
    void threadStart(uint32_t threadId);
    void threadStop(uint32_t threadId);
    void threadSleep(uint32_t threadId, uint32_t seconds);
    void threadSleepMsec(uint32_t threadId, uint32_t mSeconds);
    void threadSetPriority(uint32_t threadId, uint8_t priority);
// -------------------------------------------//

public:
    static uint32_t getSysTick();
    //static void SysTimerInterruptRoutine();
    //static void pendSvInterruptRoutine();
    static void trap();

private:
   // uint32_t GetNextThreadIdx();

private:
    static SchedulerPlatform* g_scheduler;

private:
//    uint32_t              m_SysTickValue;
//    SysTimerIntRoutine_t  m_fpSysTimerIntRoutine;
//    Context *m_context;
};


#endif // SCHEDULER_PLATFORM_H
