#include "SchedulerPlatform.h"
#include <string.h>
#include <intrinsics.h>
#include <misc.h>
#include "MemoryManager.h"

uint32_t Stack[ 4096 ];


Context_t m_Context[ 5 ];

uint32_t ThreadIdx = 0;
uint32_t ThreadsCount = 1;




// --------------------------------
SchedulerPlatform_t* SchedulerPlatform_t::g_pScheduler; 


SchedulerPlatform_t::SchedulerPlatform_t()
{
    //m_SysTickValue = 0;
    g_pScheduler = this;
    
//    NVIC_InitTypeDef NVIC_InitStruct;
//    /* Enable and set EXTI Line Interrupt to the lowest priority */
//    NVIC_InitStruct.NVIC_IRQChannel                   = PendSV_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0;
//    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
//    NVIC_Init(&NVIC_InitStruct);
    
}

uint32_t SchedulerPlatform_t::GetSysTick()
{
    return 0;
}

void SchedulerPlatform_t::Start()
{
 
}

uint32_t ThreadId = 0;

uint32_t SchedulerPlatform_t::ThreadCreate( uint32_t stackSize, ThreadRoutine_t pThreadRoutine, void* pContextA, void* pContextB )
{
    uint32_t threadId = ThreadId;
  
    ThreadId++;
    
   //__disable_interrupt();
    
    uint32_t* pStack = ( uint32_t* )AllocateThreadStack( stackSize );
      
// ---------------------- Exeption Frame ----------------------   
    *pStack --= 0x01000000;                 // xPSR
    *pStack --= ( uint32_t )pThreadRoutine; // Return Address                   
    *pStack --= ( uint32_t )Trap;           // LR
    *pStack --= 0x00000000;                 // R12
    *pStack --= 0x00000000;                 // R3
    *pStack --= 0x00000000;                 // R2
    *pStack --= 0xBBBBBBBB;//( uint32_t )pContextB;      // R1
    *pStack --= 0xAAAAAAAA;//( uint32_t )pContextA;      // R0   
// ----------------------------------------------------------- 
 
    for( uint32_t idx = 0; idx < 7; idx ++ ) // R11 - R4
    {
        *pStack --= 0xAAAAAAAA;
    }
    
    pStack += 8;
    
    m_Context[ ThreadsCount ].SaveStackPointer( ( uint32_t )pStack );
   // m_Context[ ThreadsCount ].SetRoutine( ( Routine_t* )pThreadRoutine );
   
    ThreadsCount++; 
    
    return threadId;
}


void SchedulerPlatform_t::ThreadDestroy( uint32_t threadId )
{
     asm("nop");
}

void SchedulerPlatform_t::ThreadStart( uint32_t threadId )
{
    asm("nop");
}

void SchedulerPlatform_t::ThreadStop( uint32_t threadId )
{
    asm("nop");
}

void SchedulerPlatform_t::ThreadSleepMsec( uint32_t threadId, uint32_t mSeconds )
{
    //SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; 
    asm("nop");
}

void SchedulerPlatform_t::ThreadSetPriority( uint32_t threadId, uint8_t priority )
{
    asm("nop");
}

void SchedulerPlatform_t::ThreadYield( uint32_t threadId )
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    asm("nop");
}

void SchedulerPlatform_t::Trap()
{
    asm("nop");
}

uint32_t FindNextThreadIdx()
{
    ThreadIdx ++;
    
    if( ThreadIdx >= ThreadsCount )
    {
        ThreadIdx = 0;
    }
    
    return ThreadIdx;
}

Context_t* SchedulerPlatform_t::GetCurrentThreadContext()
{
    return &m_Context[ ThreadIdx ];
}
 
Context_t* SchedulerPlatform_t::GetNextThreadContext()
{
    uint32_t threadIdx = FindNextThreadIdx();
    return &m_Context[ threadIdx ];
}