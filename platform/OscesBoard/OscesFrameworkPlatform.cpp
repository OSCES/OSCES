#include "OscesFrameworkPlatform.h"
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


extern OscesApplicationStatus_t osces_main( void );// OscesFrameworkInterface_t* system );
Kernel_t m_Kernel;
uint8_t ProcessStack[ 512 ];
RCC_ClocksTypeDef freq;
OscesFramework_t  m_pOscesFramework;

namespace Sys
{
    DisplayInterface_t*  GetDisplay()
    {
        return m_pOscesFramework.GetDisplay();
    }

    KeyboardInterface_t* GetKeyboard()
    {
        return m_pOscesFramework.GetKeyboard();
    }

    SysTimerInterface_t* GetSysTimer()
    {
        return m_pOscesFramework.GetSysTimer();
    }

    bool IsApplicationRun()
    {
        return m_pOscesFramework.IsApplicationRun();
    }
};

OscesFramework_t::OscesFramework_t()
{
    m_IsApplicationRun = true;
}

SysTimerInterface_t* OscesFramework_t::GetSysTimer()
{
    return m_pSysTimer;
}

DisplayInterface_t* OscesFramework_t::GetDisplay()
{
    return m_pDisplay;
}

KeyboardInterface_t* OscesFramework_t::GetKeyboard()
{
    return m_pKeyboard;
}

ThreadInterface_t*  OscesFramework_t::ThreadCreate( uint32_t stackSize, ThreadRoutine_t fpThreadRoutine, void* pContext )
{
    ThreadPlatform_t* pThreadPlatform = new ThreadPlatform_t( &m_Kernel );

    uint32_t threadId = m_pScheduler->ThreadCreate( stackSize, fpThreadRoutine, pThreadPlatform, pContext );
  
    pThreadPlatform->SetId( threadId );
    
    return pThreadPlatform;
}

void  OscesFramework_t::ThreadDestroy( ThreadInterface_t* pThread )
{
    ThreadPlatform_t* pThreadPlatform = static_cast< ThreadPlatform_t* >( pThread ); //TODO: delete cast !!!
    
    uint32_t threadId = pThreadPlatform->GetId();
    
    m_pScheduler->ThreadDestroy( threadId );
 
    delete pThread;// pThreadPlatform;
}

void OscesFramework_t::ThreadYield()
{
    uint32_t currentThreadId = 0;
    m_pScheduler->ThreadYield( currentThreadId );
}
 

void *operator new( size_t size )
{
    return malloc( size );
}
void operator delete(void *p)
{
    free( p );
}

int main()
{
  
    ClockManager_t clockManager;
        
    clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz ); 
  
    //__svc(SVC_00);
  
    //__svc( 0 );
    
    asm("nop");
    
    
    //m_Kernel.Init();
    
    m_pOscesFramework.Init();
    
    osces_main();
   
    m_pOscesFramework.DeInit();
    
    return 0;
}

//$PROJ_DIR$\..\..\..\thirdparty\STM32F4\STM32F4xx_StdPeriph_Driver\stm32f4xx_conf.h
bool OscesFramework_t::IsApplicationRun()
{
    return m_IsApplicationRun;
}

OscesFrameworkStatus_t OscesFramework_t::Init()
{
    OscesFrameworkStatus_t status = OSCES_FRAMEWORK_INIT_SUCCESS;

    //DmaInit();
    
    __disable_interrupt();
    InterruptManager_t::Init();
    
    
//    ClockManager_t clockManager;
        
//    clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz ); 
    
   
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    
    //SystemLed_t* led0 = 0;
    //SystemLed_t* led1 = 0;
    
    try
    {
        //led0 = new SystemLed_t( SYSTEM_LED_1 );
        //led1 = new SystemLed_t( SYSTEM_LED_2 );

      
        m_pDisplay         = new DisplayPlatform_t;
        //m_pKeyboard        = new KeyboardPlatform_t;
        //m_pSysTimer        = new SysTimerPlatform_t;
       // m_pScheduler       = new SchedulerPlatform_t();
        
        //m_pKeyboard->Init();
    }
    catch(...)
    {
    
        asm( "nop" );
        asm( "nop" );
        asm( "nop" );
        asm( "nop" );
        asm( "nop" );
    }
    
   // led0->Off();
   // led1->Off();
    
   // __enable_interrupt();
    
    m_pDisplay->Init( 400, 300, false );
//
    m_pDisplay->Clear();
    m_pDisplay->Flip();
    m_pDisplay->Clear();
    m_pDisplay->Flip();
   
  //  m_pSysTimer->Init();
    
    
    //m_pScheduler->Start( 10 );    
   
    //__enable_interrupt();
    
    return status;
}


void OscesFramework_t::DeInit()
{
    delete m_pScheduler;
    delete m_pSysTimer;
    delete m_pKeyboard;
    delete m_pDisplay;
}