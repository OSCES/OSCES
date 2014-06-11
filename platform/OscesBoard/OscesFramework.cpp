#include "include/OscesFramework.h"



#include "Display/DisplayPlatform.h"
#include "Keyboard/KeyboardPlatform.h"
#include <stdio.h>


#include "GpioDriver.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"
#include "ClockManager/ClockManager.h"
#include "SysTimer/SysTimerPlatform.h"

#include "InterruptManager.h"


static DisplayPlatform_t  Display;
static KeyboardPlatform_t Keyboard;
static SysTimerPlatform_t SysTimer;

static OscesFramework_t   OscesFramework;
static bool IsApplicationRunEnable = true;

DisplayInterface_t* OscesFramework_t::GetDisplay()
{
    return &Display;
}

KeyboardInterface_t* OscesFramework_t::GetKeyboard()
{
    return &Keyboard;
}

SysTimerInterface_t* OscesFramework_t::GetSysTimer()
{ 
    return &SysTimer;
}

int main()
{
    OscesFrameworkInit();

    osces_main( &OscesFramework );
    
    OscesFrameworkDeInit();

    return 0;
}


bool OscesFramework_t::IsApplicationRun()
{

    return IsApplicationRunEnable;
}


OscesFrameworkStatus_t OscesFrameworkInit()
{
    OscesFrameworkStatus_t status = OSCES_FRAMEWORK_INIT_SUCCESS;

    ClockManager_t clockManager;
    
    clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz ); 
    
   
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );


    SystemLed_t* led0 = new SystemLed_t( SYSTEM_LED_1 );
    SystemLed_t* led1 = new SystemLed_t( SYSTEM_LED_2 );
    
    RCC_ClocksTypeDef freq;    
    RCC_GetClocksFreq( &freq );
    
    if( SysTick_Config( freq.HCLK_Frequency / 100 ) )
    { 
        while( 1 ){}; /* Capture error trap */ 
    }
    
    __disable_interrupt();
    
//    Button_t button( BUTTON_1 );
//    
//    Button_t buttonA( BUTTON_2 );
//    
//    Button_t buttonB( BUTTON_3 );
    
    Display.Init( 400, 300 );

    Display.Clear();
    Display.Flip();
    Display.Clear();
    Display.Flip();

    return status;
}


void OscesFrameworkDeInit()
{

}