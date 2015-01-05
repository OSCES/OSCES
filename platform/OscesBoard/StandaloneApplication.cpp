#include "OscesFramework.h"
#include "GpioDriver.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"

#include "ClockManager/ClockManager.h"
#include "Drivers/InterruptManager.h"
#include "Drivers/DmaDriver.h"
#include <stdlib.h>

#include <intrinsics.h>
#include <stdio.h>
#include "SysTimerDriver.h"
#include "Kernel/ThreadPlatform.h"
#include "Kernel/Kernel.h"



uint32_t ThreadACounter = 0;
uint32_t ThreadBCounter = 0;
uint32_t ThreadCCounter = 0;
uint32_t ThreadMCounter = 0;

void ThreadA( ThreadInterface_t* pThisThread, void* pContextB )
{
    ThreadInterface_t* pThread = pThisThread;
  
    asm("nop");
  
    for( ;; )
    {
        ThreadACounter++;
        asm("nop");
        
        //pThisThread->Yield();
        SchedulerPlatform_t::ThreadYield( 0 );
        asm("nop");
    }
}

void ThreadB( ThreadInterface_t* pThisThread, void* pContextB )
{
    for( ;; )
    {
        ThreadBCounter++;
        asm("nop");
        SchedulerPlatform_t::ThreadYield( 0 );
        asm("nop");
    }
}

void ThreadC( ThreadInterface_t* pThisThread, void* pContextB )
{
    for( ;; )
    {
        ThreadCCounter++;
        asm("nop");
        SchedulerPlatform_t::ThreadYield( 0 );
        asm("nop");
    }
}

void standalone_main( OscesFramework_t* pSystem )
{
    asm("nop");  
    
    ThreadInterface_t* pThreadA = pSystem->ThreadCreate( 128, ThreadA, 0 );
    ThreadInterface_t* pThreadB = pSystem->ThreadCreate( 128, ThreadB, 0 );
    ThreadInterface_t* pThreadC = pSystem->ThreadCreate( 128, ThreadC, 0 );
    
    pThreadA->Start();
    pThreadB->Start();
    pThreadC->Start();
    
    //asm volatile("svc 0");
    
     __enable_interrupt();
        
    while( true )
    {
        //uint32_t usec = pSystem->GetSysTimer()->GetValueUsec();
        asm("nop");
        ThreadMCounter++;
        pSystem->ThreadYield();
        //ThreadMCounter++;
        //asm("nop");
    }
    
}