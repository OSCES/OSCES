#include "ClockManager.h"


void ClockManager_t::SetSystemClock( SystemClock_t clock )
{
    RCC_DeInit();
    //RCC_HSEConfig(uint8_t RCC_HSE);
    //ErrorStatus RCC_WaitForHSEStartUp(void);
  
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq( &RCC_Clocks );

    uint8_t source = RCC_GetSYSCLKSource();
    RCC_HSEConfig( RCC_HSE_ON );
    asm("nop");
}