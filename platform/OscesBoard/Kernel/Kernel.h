#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "ContextSwitcher.h"
#include "SchedulerPlatform.h"

class Kernel_t
{
public:
    void Init();
    void Yield();
    void DeInit();
    
private:
    static void PentSvInterruptRoutine( void* pContext );

    
private:
    ContextSwitcher_t* m_pContextSwitcher;
    SchedulerPlatform_t m_SchedulerPlatform;
    
};



#endif // KERNEL_H