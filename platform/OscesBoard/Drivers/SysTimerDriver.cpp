#include "SysTimerDriver.h"
//#include "stm32fxx_tim.h"
#include "InterruptManager.h"
#include "stm32f4xx_rcc.h"

// conts has internal linkage by default
const int HzInMhz = 1000000;
const int SysTickTimerIntFreq = 10;

SysTimerDriver::SysTimerDriver() :
    m_usec(0),
    m_sysTickValue(0)
{
}

void SysTimerDriver::init()
{
    InterruptManager::registerInterrupt(this, InterruptVector::SysTickVector, sysTimerInterruptRoutine);

    RCC_ClocksTypeDef freq;
    RCC_GetClocksFreq(&freq);

    m_sysTickValue = freq.SYSCLK_Frequency / SysTickTimerIntFreq;
    if (SysTick_Config(m_sysTickValue))
    {
        while (true)
        {
            /* Capture error trap */
        };
    }
}

uint32_t SysTimerDriver::valueUsec()
{
    uint64_t value = m_usec + (m_sysTickValue - SysTick->VAL);
    return value / m_sysTickValue / (HzInMhz / SysTickTimerIntFreq);
}

void SysTimerDriver::sysTimerInterruptRoutine(void *context)
{
    SysTimerDriver *sysTimerDriver = static_cast<SysTimerDriver *>(context);
    sysTimerDriver->m_usec += sysTimerDriver->m_sysTickValue;
}
