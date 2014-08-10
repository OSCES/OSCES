#include "OscesFramework.h"
#include "GpioDriver.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"

#include "ClockManager/ClockManager.h"
#include "Drivers/InterruptManager.h"
#include <stdlib.h>

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
    OscesFramework_t*  m_pOscesFramework = new OscesFramework_t();

    m_pOscesFramework->Init();

    osces_main( m_pOscesFramework );

    SysTimerInterface_t* timer = m_pOscesFramework->GetSysTimer();
    
//    for( ;; )
//    {
//        volatile uint32_t msec = timer->GetValueUsec();  
//        asm("nop");
//    
//        if( msec )
//        {
//            asm("nop");
//        }
//    }
    
    
    m_pOscesFramework->DeInit();

    return 0;
}


bool OscesFramework_t::IsApplicationRun()
{
    return m_IsApplicationRun;
}

OscesFrameworkStatus_t OscesFramework_t::Init()
{
    OscesFrameworkStatus_t status = OSCES_FRAMEWORK_INIT_SUCCESS;

    __disable_interrupt();
    InterruptManager_t::Init();
    
    
    ClockManager_t clockManager;
        
    clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz ); 
    
   
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );

    
    SystemLed_t* led0 = 0;
    SystemLed_t* led1 = 0;
    
    try
    {
        led0 = new SystemLed_t( SYSTEM_LED_1 );
        led1 = new SystemLed_t( SYSTEM_LED_2 );

      
        m_pDisplay  = new DisplayPlatform_t;
        m_pKeyboard = new KeyboardPlatform_t;
        m_pSysTimer = new SysTimerPlatform_t;
        
        
        m_pKeyboard->Init();
    }
    catch(...)
    {
    
      
    }
    
    m_pDisplay->Init( 400, 300);

    m_pDisplay->Clear();
    m_pDisplay->Flip();
    m_pDisplay->Clear();
    m_pDisplay->Flip();

    m_pSysTimer->Init();


    
    led0->Off();
    led1->Off();
   

    __enable_interrupt();
    
    return status;
}


void OscesFramework_t::DeInit()
{
    delete m_pSysTimer;
    delete m_pKeyboard;
    delete m_pDisplay;
}