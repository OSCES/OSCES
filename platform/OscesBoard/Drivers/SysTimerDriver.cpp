#include "SysTimerDriver.h"
//#include "stm32fxx_tim.h"
#include "InterruptManager.h"

void SysTimerDriver_t::Init()
{
    m_Usec = 0;
    m_SysTickValue = 0;
    
    InterruptManager_t::RegisterInterrupt( this, INTERRUPT_SYSTICK_VECTOR, SysTimerInterruptRoutine );
  
    RCC_ClocksTypeDef freq;    
    RCC_GetClocksFreq( &freq );
      
    m_SysTickValue = freq.SYSCLK_Frequency / SYS_TICK_TIMER_INT_FREQ;
    
    if( SysTick_Config( m_SysTickValue ) )
    { 
        while( true ){}; /* Capture error trap */ 
    }
}

uint32_t SysTimerDriver_t::GetValueUsec()
{
    uint64_t value = m_Usec + ( m_SysTickValue - SysTick->VAL );
    
    value /= m_SysTickValue / ( HZ_IN_MHZ / SYS_TICK_TIMER_INT_FREQ );
    
    return value;
}

void SysTimerDriver_t::SysTimerInterruptRoutine( void* pContext )
{
    SysTimerDriver_t* pSysTimerDriver = static_cast< SysTimerDriver_t* >( pContext );
    pSysTimerDriver->m_Usec += pSysTimerDriver->m_SysTickValue;
}
