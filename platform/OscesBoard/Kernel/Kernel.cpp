#include "Kernel.h"
#include "InterruptManager.h"
#include "ContextSwitcher.h"

Kernel::Kernel() :
    m_contextSwitcher(0)
{
}

void Kernel::Init()
{
    InterruptManager::registerInterrupt(this, InterruptVector::PendSvVector, pentSvInterruptRoutine);

    m_schedulerPlatform.start();
    m_contextSwitcher = new ContextSwitcher(&m_schedulerPlatform);
    m_contextSwitcher->switchToThreadMode();
}

void Kernel::pentSvInterruptRoutine(void* context)
{
    Kernel* kernel = static_cast<Kernel *>(context);
    kernel->m_contextSwitcher->pendSvInterruptRoutine();
}

void Kernel::yield()
{
    m_schedulerPlatform.threadYield(0);
    m_contextSwitcher->forceSwitchContext();
}

void Kernel::deInit()
{
    delete m_contextSwitcher;
    m_contextSwitcher = 0;
}
