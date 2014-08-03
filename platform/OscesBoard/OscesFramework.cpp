#include "OscesFramework.h"
#include "GpioDriver.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"
#include "ClockManager/ClockManager.h"

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
    return m_pPS2Keyboard;
}

int main()
{
    OscesFramework_t*  m_pOscesFramework = new OscesFramework_t();

    m_pOscesFramework->Init();

    osces_main( m_pOscesFramework );

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

    //ClockManager_t clockManager;
        
    //clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz ); 
    
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );


    SystemLed_t* led0 = new SystemLed_t( SYSTEM_LED_1 );
    SystemLed_t* led1 = new SystemLed_t( SYSTEM_LED_2 );
    
    //RCC_ClocksTypeDef freq;    
    //RCC_GetClocksFreq( &freq );
    
    //if( SysTick_Config( freq.HCLK_Frequency / 100 ) )
    //{ 
    //    while( 1 ){}; /* Capture error trap */
    //}
    
    //__disable_interrupt();
    
    do
    {
        m_pInterruptManager = new InterruptManager_t;
        m_pDisplay          = new DisplayPlatform_t;
        m_pPS2Keyboard      = new PS2Keyboard_t;
        m_pSysTimer         = new SysTimerPlatform_t;

    }
    while( false );
    
    m_pInterruptManager->Init();
    m_pInterruptManager->RegisterInterrupt( m_pPS2Keyboard, INTERRUPT_EXTI1_IRQ_VECTOR, PS2Keyboard_t::InterruptHandler );
    
    m_pPS2Keyboard->Init();
    m_pDisplay->Init( 400, 300);

    m_pDisplay->Clear();
    m_pDisplay->Flip();
    m_pDisplay->Clear();
    m_pDisplay->Flip();

    return status;
}

void OscesFramework_t::DeInit()
{
    delete m_pSysTimer;
    delete m_pPS2Keyboard;
    delete m_pDisplay;
    delete m_pInterruptManager;
}