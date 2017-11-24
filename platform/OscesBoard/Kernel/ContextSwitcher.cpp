#include "ContextSwitcher.h"
#include "MemoryManager.h"
#include "misc.h"
#include <string.h>
#include <intrinsics.h>

ContextSwitcher::ContextSwitcher(SchedulerPlatform *scheduler) :
    m_scheduler(scheduler)
{
}

void ContextSwitcher::forceSwitchContext()
{
    // not portable
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void ContextSwitcher::switchToThreadMode()
{
    // __set* __get* functions should be as HAL
    __set_PSP(AllocateThreadStack(28));

    uint32_t *mainStack = static_cast<uint32_t *>(__get_MSP());
    uint32_t *processStack = static_cast<uint32_t *>(__get_PSP());

    // 8 - some magic? why 8?
    for (uint32_t i = 0; i < 8; ++i)
        processStack[i] = mainStack[i];

    __set_CONTROL(0x02);
}

void ContextSwitcher::pendSvInterruptRoutine()
{
    // not portable
    asm("MRS R0, PSP");
    asm("STMDB R0!, {R4-R11}");

    m_scheduler->currentThreadContext()->saveStackPointer(__get_PSP());

    __set_PSP( m_scheduler->nextThreadContext()->retrieveStackPointer());

    asm("MRS R0, PSP");
    asm("LDMIA R0!, {R4-R11}");
}

uint32_t ContextSwitcher::prepareExeptionStackFrame(uint32_t stackAddr)
{
}

void ContextSwitcher::sysTimerInterruptRoutine()
{
}
