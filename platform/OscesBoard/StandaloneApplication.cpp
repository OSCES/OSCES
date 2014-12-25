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

void ThreadA( ThreadInterface_t* pContextA, void* pContextB )
{
    for( ;; )
    {
        ThreadACounter++;
        asm("nop");
        SchedulerPlatform_t::ThreadYield( 0 );
        asm("nop");
    }
}

void ThreadB( ThreadInterface_t* pContextA, void* pContextB )
{
    for( ;; )
    {
        ThreadBCounter++;
        asm("nop");
        SchedulerPlatform_t::ThreadYield( 0 );
        asm("nop");
    }
}

void ThreadC( ThreadInterface_t* pContextA, void* pContextB )
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
      
    SchedulerPlatform_t::ThreadCreate( 128, ThreadA, 0, 0 );
    SchedulerPlatform_t::ThreadCreate( 128, ThreadB, 0, 0 );
    SchedulerPlatform_t::ThreadCreate( 128, ThreadC, 0, 0 );
    
    
    //asm volatile("svc 0");
    
     __enable_interrupt();
        
    while( true )
    {
        //uint32_t usec = pSystem->GetSysTimer()->GetValueUsec();
        asm("nop");
        ThreadMCounter++;
        SchedulerPlatform_t::ThreadYield( 0 );
        //ThreadMCounter++;
        //asm("nop");
    }
    
}