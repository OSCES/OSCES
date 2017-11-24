#include "SysTimerPlatform.h"
#include "SysTimerDriver.h"

SysTimerPlatform::SysTimerPlatform() :
    m_sysTimerDriver(0)
{
}

SysTimerPlatform::~SysTimerPlatform()
{
    delete m_sysTimerDriver;
}

SysTimerPlatformInitStatus SysTimerPlatform::init()
{
    SysTimerPlatformInitStatus status = SYSTIMER_PLATFORM_INIT_SUCCESS;

    // TODO: do we relay need it try catch block?
    try
    {
        m_sysTimerDriver = new SysTimerDriver();
        m_sysTimerDriver->init();
    }
    catch (...)
    {
        status = SYSTIMER_PLATFORM_INIT_FAIL;
    }

    return status;
}

uint32_t SysTimerPlatform::valueUsec()
{
    return m_sysTimerDriver->valueUsec();
}
