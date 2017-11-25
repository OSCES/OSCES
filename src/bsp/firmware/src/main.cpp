#include "GpioDriver.h"
#include "Display/Display.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"
#include "KeyCodes.h"
#include "Keyboard/PS2Keyboard.h"
#include "ClockManager/ClockManager.h"
#include "InterruptManager.h"
#include <stdint.h>
#include  "Snake.h"
#include "FsmcDriver.h"
#include "MemTest.h"

InterruptManager_t InterruptManager;
PS2Keyboard_t      PS2Keyboard;
Display_t          Display;
SystemLed_t        *Led_1;
SystemLed_t        *Led_2;
SystemLed_t        *Led_3;
SystemLed_t        *Led_4;

void LedOnOff( void* pContext, Key_t key );

int main()
{
    InterruptManager.Init();
    PS2Keyboard.Init();
    Display.Init( 400, 300 );
    
    InterruptManager.RegisterInterrupt( &PS2Keyboard, INTERRUPT_EXTI1_IRQ_VECTOR, PS2Keyboard_t::InterruptHandler );
    PS2Keyboard.RegisterCallBack( 0, LedOnOff );

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
    
    Led_1 = new SystemLed_t( SYSTEM_LED_1 );
    Led_2 = new SystemLed_t( SYSTEM_LED_2 );
    Led_3 = new SystemLed_t( SYSTEM_LED_3 );
    Led_4 = new SystemLed_t( SYSTEM_LED_4 );
    
    while( 1 )
    { 
      
    }
}

void LedOnOff( void* pContext, Key_t key )
{
  if( key.KeyCode == KEY_LEFT  && key.Event == KEY_PRESSED  ) Led_1->On();
  if( key.KeyCode == KEY_LEFT  && key.Event == KEY_RELEASED ) Led_1->Off();
  
  if( key.KeyCode == KEY_UP    && key.Event == KEY_PRESSED  ) Led_2->On();
  if( key.KeyCode == KEY_UP    && key.Event == KEY_RELEASED ) Led_2->Off();
  
  if( key.KeyCode == KEY_RIGHT && key.Event == KEY_PRESSED  ) Led_3->On();
  if( key.KeyCode == KEY_RIGHT && key.Event == KEY_RELEASED ) Led_3->Off();
  
  if( key.KeyCode == KEY_DOWN  && key.Event == KEY_PRESSED  ) Led_4->On();
  if( key.KeyCode == KEY_DOWN  && key.Event == KEY_RELEASED ) Led_4->Off();
}