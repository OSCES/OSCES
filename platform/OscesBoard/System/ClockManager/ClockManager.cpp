#include "ClockManager.h"
#include "stm32f4xx_rcc.h"

 /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N */
#define PLL_M 25 /* For HSE value equal to 25 MHz */
#define PLL_N 350
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P 2
/* USB OTG FS, SDIO and RNG Clock = PLL_VCO / PLLQ */
#define PLL_Q 5
/* In this example:
PLL_VCO = 240 MHz
SYSCLK = 120 MHz
*/

ClockManager_t::ClockManager_t()
{
    for(uint8_t idx = 0; idx < PORT_COUNT; idx++)
    {
        m_IsEnabledGpioClock[idx] = false;
    }
}

ClockManager_t::~ClockManager_t()
{
}

ClockManager_t::ClockManager_t(const ClockManager_t& value)
{
}

ClockManager_t& ClockManager_t::operator = (const ClockManager_t& value)
{
    return ClockManager_t::GetInstance();
}

ClockManager_t& ClockManager_t::GetInstance()
{
    static ClockManager_t m_Instance;
    return m_Instance;
}

void ClockManager_t::SetSystemClock( SystemClock_t clock )
{
    RCC_DeInit();
    //RCC_HSEConfig(uint8_t RCC_HSE);
    //ErrorStatus RCC_WaitForHSEStartUp(void);
  
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq( &RCC_Clocks );

    uint8_t source = RCC_GetSYSCLKSource();
      /***************************************************************/
    /* PLL (clocked by HSE) used as System clock(SYSCLK) source */
    /***************************************************************/
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;
    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);
    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    
    if (HSEStartUpStatus == SUCCESS)
    {
        /* Flash 3 wait state, prefetch buffer and cache ON */
        FLASH_SetLatency(FLASH_Latency_3);
        FLASH_PrefetchBufferCmd(ENABLE);
        FLASH_InstructionCacheCmd(ENABLE);
        FLASH_DataCacheCmd(ENABLE);
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* PCLK2 = HCLK/2 */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* PCLK1 = HCLK/4 */
        RCC_PCLK1Config(RCC_HCLK_Div1);
        /* Configure the main PLL clock to 120 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE, PLL_M, PLL_N, PLL_P, PLL_Q);
        /* Enable the main PLL */
        RCC_PLLCmd(ENABLE);
        /* Wait till the main PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {}
        /* Select the main PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till the main PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL)
        {}
    }
    else
    { /* If HSE fails to start-up, user can add here some code
    to deal with this error */
    }
    
    RCC_GetClocksFreq( &RCC_Clocks );
   
    asm("nop");
}

void ClockManager_t::EnableGpioClock(GpioClock_t clock)
{
    if( m_IsEnabledGpioClock[clock] )
    {
        return;
    }

    uint32_t GpioPeriph = 0;

    switch (clock)
    {
        case GPIO_CLOCK__PORTA: GpioPeriph = RCC_AHB1Periph_GPIOA; break;
        case GPIO_CLOCK__PORTB: GpioPeriph = RCC_AHB1Periph_GPIOB; break;
        case GPIO_CLOCK__PORTC: GpioPeriph = RCC_AHB1Periph_GPIOC; break;
        case GPIO_CLOCK__PORTD: GpioPeriph = RCC_AHB1Periph_GPIOD; break;
        case GPIO_CLOCK__PORTE: GpioPeriph = RCC_AHB1Periph_GPIOE; break;
        case GPIO_CLOCK__PORTF: GpioPeriph = RCC_AHB1Periph_GPIOF; break;
        case GPIO_CLOCK__PORTG: GpioPeriph = RCC_AHB1Periph_GPIOG; break;
        case GPIO_CLOCK__PORTH: GpioPeriph = RCC_AHB1Periph_GPIOH; break;
        case GPIO_CLOCK__PORTI: GpioPeriph = RCC_AHB1Periph_GPIOI; break;

        default:
            return;
    }

    RCC_AHB1PeriphClockCmd( GpioPeriph, ENABLE );
    m_IsEnabledGpioClock[clock] = true;
}
