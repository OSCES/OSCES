#include "Kernel.h"
#include "InterruptManager.h"

void Kernel_t::Init()
{
    InterruptManager_t::RegisterInterrupt( this, INTERRUPT_PENDSV_VECTOR, PentSvInterruptRoutine );
    
    m_SchedulerPlatform.Start();

    m_pContextSwitcher = new ContextSwitcher_t( &m_SchedulerPlatform );
    
    m_pContextSwitcher->SwitchToThreadMode();
  
}

void Kernel_t::PentSvInterruptRoutine( void* pContext )
{
    Kernel_t* pKernel = static_cast< Kernel_t* >( pContext );
    pKernel->m_pContextSwitcher->PendSvInterruptRoutine();
}

void Kernel_t::Yield()
{
    m_pContextSwitcher->ForceSwitchContext();
}

void Kernel_t::DeInit()
{
    if( 0 != m_pContextSwitcher )
    {
        delete m_pContextSwitcher;
        m_pContextSwitcher = 0;
    }
}