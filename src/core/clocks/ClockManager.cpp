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

ClockManager::ClockManager() :
    m_gpioClockEnabled(0)
{
}

ClockManager& ClockManager::instance()
{
    static ClockManager instance;
    return instance;
}

void ClockManager::setSystemClock(SystemClock clock)
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
    // Enable HSE
    RCC_HSEConfig(RCC_HSE_ON);
    // Wait till HSE is ready
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        // Flash 3 wait state, prefetch buffer and cache ON
        FLASH_SetLatency(FLASH_Latency_3);
        FLASH_PrefetchBufferCmd(ENABLE);
        FLASH_InstructionCacheCmd(ENABLE);
        FLASH_DataCacheCmd(ENABLE);
        // HCLK = SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // PCLK2 = HCLK/2
        RCC_PCLK2Config(RCC_HCLK_Div1);
        // PCLK1 = HCLK/4
        RCC_PCLK1Config(RCC_HCLK_Div1);
        // Configure the main PLL clock to 120 MHz
        RCC_PLLConfig(RCC_PLLSource_HSE, PLL_M, PLL_N, PLL_P, PLL_Q);
        // Enable the main PLL
        RCC_PLLCmd(ENABLE);
        // Wait till the main PLL is ready
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {}
        // Select the main PLL as system clock source
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        // Wait till the main PLL is used as system clock source
        while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL)
        {}
    }
    else
    {
        // If HSE fails to start-up, user can add here some code
        // to deal with this error
    }

    RCC_GetClocksFreq(&RCC_Clocks);

    asm("nop");
}

void ClockManager::setGpioClockEnabled(ClockManager::GpioClock clock, bool enabled)
{
    // (0 && 0) or (1 && 1)
    if ((enabled ^ (m_gpioClockEnabled & clock)) == 0)
        return;

    uint32_t gpioPeriph = 0;
    switch (clock)
    {
    case PortA: gpioPeriph = RCC_AHB1Periph_GPIOA; break;
    case PortB: gpioPeriph = RCC_AHB1Periph_GPIOB; break;
    case PortC: gpioPeriph = RCC_AHB1Periph_GPIOC; break;
    case PortD: gpioPeriph = RCC_AHB1Periph_GPIOD; break;
    case PortE: gpioPeriph = RCC_AHB1Periph_GPIOE; break;
    case PortF: gpioPeriph = RCC_AHB1Periph_GPIOF; break;
    case PortG: gpioPeriph = RCC_AHB1Periph_GPIOG; break;
    case PortH: gpioPeriph = RCC_AHB1Periph_GPIOH; break;
    case PortI: gpioPeriph = RCC_AHB1Periph_GPIOI; break;
    default:
        return;
    }

    RCC_AHB1PeriphClockCmd(gpioPeriph, ENABLE);
    m_gpioClockEnabled |= clock;
}
