#include "SysTimerPlatform.h"
#include "SysTimerDriver.h"

SysTimerPlatformInitStatus_t SysTimerPlatform_t::Init()
{
    SysTimerPlatformInitStatus_t status = SYSTIMER_PLATFORM_INIT_SUCCESS;  
  
    try
    {
        SysTimerDriver_t* pSysTimerDriver = new SysTimerDriver_t();
        
        m_pSysTimerDriver = pSysTimerDriver;
        
        pSysTimerDriver->Init();        
    }
    catch( ... )
    {
        status = SYSTIMER_PLATFORM_INIT_FAIL;
    }
        
    return status;
}

uint32_t SysTimerPlatform_t::GetValueUsec()
{
    SysTimerDriver_t* pSysTimerDriver = static_cast< SysTimerDriver_t* >( m_pSysTimerDriver );
    uint32_t value = pSysTimerDriver->GetValueUsec();
    return value;  
}