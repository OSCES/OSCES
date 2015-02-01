#include "ContextSwitcher.h"
#include <string.h>
#include <intrinsics.h>
#include "MemoryManager.h"
#include "misc.h"

ContextSwitcher_t::ContextSwitcher_t( SchedulerPlatform_t* pScheduler )
{
    m_pScheduler = pScheduler;
}

void ContextSwitcher_t::ForceSwitchContext()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void ContextSwitcher_t::SwitchToThreadMode()
{
    __set_PSP( AllocateThreadStack( 128 ) );
    
    uint32_t* pMainStack = ( uint32_t* )__get_MSP();
    uint32_t* pProcessStack = ( uint32_t* )__get_PSP();
    
    
    for( uint32_t idx = 0; idx < 8; idx++ )
    {
        pProcessStack[ idx ] = pMainStack[ idx ];
    }
    
    __set_CONTROL( 0x02 );  
}

void ContextSwitcher_t::PendSvInterruptRoutine()
{
    asm( "MRS R0, PSP" );
    asm( "STMDB R0!, {R4-R11}" );
  
    m_pScheduler->GetCurrentThreadContext()->SaveStackPointer( __get_PSP() );
    
    __set_PSP( m_pScheduler->GetNextThreadContext()->RetrieveStackPointer() );

    asm( "MRS R0, PSP" );
    asm( "LDMIA R0!, {R4-R11}" );

}

uint32_t ContextSwitcher_t::PrepareExeptionStackFrame( uint32_t stackAddr )
{

}

void ContextSwitcher_t::SysTimerInterruptRoutine()
{
}