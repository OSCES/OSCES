#include "SchedulerPlatform.h"
#include "MemoryManager.h"
#include "Context.h"
#include <string.h>
#include <intrinsics.h>
#include <misc.h>

static Context m_context[5];
static uint32_t Stack[4096];
static uint32_t ThreadId = 0;
static uint32_t ThreadIndex = 0;
static uint32_t ThreadsCount = 1;

// --------------------------------
SchedulerPlatform* SchedulerPlatform::g_scheduler;

SchedulerPlatform::SchedulerPlatform()
{
    //    m_SysTickValue = 0;
    g_scheduler = this;

    //    NVIC_InitTypeDef NVIC_InitStruct;
    //    /* Enable and set EXTI Line Interrupt to the lowest priority */
    //    NVIC_InitStruct.NVIC_IRQChannel                   = PendSV_IRQn;
    //    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    //    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0;
    //    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    //    NVIC_Init(&NVIC_InitStruct);
}

uint32_t SchedulerPlatform::getSysTick()
{
    return 0;
}

void SchedulerPlatform::start()
{
}

uint32_t SchedulerPlatform::threadCreate(uint32_t stackSize, ThreadRoutine pThreadRoutine, void* contextA, void* contextB )
{
    uint32_t threadId = ThreadId;
    ++ThreadId;

    //__disable_interrupt();

    uint32_t* pStack = ( uint32_t* )AllocateThreadStack( stackSize );

    // ---------------------- Exeption Frame ----------------------
    *pStack --= 0x01000000; // xPSR
    *pStack --= static_cast<uint32_t>(pThreadRoutine); // Return Address
    *pStack --= static_cast<uint32_t>(trap); // LR
    *pStack --= 0x00000000; // R12
    *pStack --= 0x00000000; // R3
    *pStack --= 0x00000000; // R2
    *pStack --= 0xBBBBBBBB; //( uint32_t )pContextB; // R1
    *pStack --= 0xAAAAAAAA; //( uint32_t )pContextA; // R0
    // -----------------------------------------------------------

    for (uint32_t idx = 0; idx < 7; ++idx) // R11 - R4
        *pStack --= 0xAAAAAAAA;

    pStack += 8;

    m_context[ThreadsCount].saveStackPointer(static_cast<uint32_t>(pStack));
    // m_context[ThreadsCount].setRoutine(static_castr<Routine>(pThreadRoutine));

    ++ThreadsCount;

    return threadId;
}


void SchedulerPlatform::threadDestroy(uint32_t threadId)
{
    asm("nop");
}

void SchedulerPlatform::threadStart(uint32_t threadId)
{
    asm("nop");
}

void SchedulerPlatform::threadStop(uint32_t threadId)
{
    asm("nop");
}

void SchedulerPlatform::threadSleepMsec(uint32_t threadId, uint32_t mSeconds)
{
    //SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    asm("nop");
}

void SchedulerPlatform::threadSetPriority(uint32_t threadId, uint8_t priority)
{
    asm("nop");
}

void SchedulerPlatform::threadYield(uint32_t threadId)
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    asm("nop");
}

void SchedulerPlatform::trap()
{
    asm("nop");
}

static uint32_t FindNextThreadIdx()
{
    ++ThreadIndex;

    if (ThreadIndex >= ThreadsCount)
        ThreadIndex = 0;

    return ThreadIndex;
}

Context* SchedulerPlatform::currentThreadContext()
{
    return &m_context[ThreadIndex];
}

Context* SchedulerPlatform::nextThreadContext()
{
    uint32_t threadIdx = FindNextThreadIdx();
    return &m_Context[ threadIdx ];
}
