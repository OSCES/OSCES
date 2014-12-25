#ifndef THREAD_PLATFORM_H
#define THREAD_PLATFORM_H

#include <stdint.h>

#include "ThreadInterface.h"
#include "Kernel.h"

class ThreadPlatform_t : public ThreadInterface_t
{
public:
    //virtual void SetRouting( void* pContext, ThreadRoutine_t fpThreadRoutine ) = 0;
   
    virtual ~ThreadPlatform_t();
  
    ThreadPlatform_t( Kernel_t* pKernel );
    void SetId( uint32_t threadId );
    uint32_t GetId();
    void Start();
    void Stop();
    void Sleep( uint32_t seconds );
    void SleepMsec( uint32_t mSeconds );
    void SetPriority( uint8_t priority );
    void Yield();
    
    
private:
    uint32_t m_ThreadId;
    Kernel_t* m_pKernel;
};


#endif // THREAD_PLATFORM_H
