#include "Kernel.h"
#include "InterruptManager.h"
#include "ContextSwitcher.h"
#include "SchedulerPlatform.h"

Kernel::Kernel() :
    m_contextSwitcher(0),
    m_schedulerPlatform(0)
{
    m_schedulerPlatform = new SchedulerPlatform();
    m_contextSwitcher = new ContextSwitcher(m_schedulerPlatform);
}

Kernel::~Kernel()
{
    delete m_contextSwitcher;
    delete m_schedulerPlatform;
}

void Kernel::init()
{
    InterruptManager::registerInterrupt(this, InterruptVector::PendSvVector, pentSvInterruptRoutine);
    m_contextSwitcher->switchToThreadMode();
}

void Kernel::pentSvInterruptRoutine(void *context)
{
    Kernel *kernel = static_cast<Kernel *>(context);
    kernel->m_contextSwitcher->pendSvInterruptRoutine();
}

void Kernel::yield()
{
    m_schedulerPlatform->threadYield(0);
    m_contextSwitcher->forceSwitchContext();
}
