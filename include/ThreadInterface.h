#ifndef _THREAD_INTERFACE_H_
#define _THREAD_INTERFACE_H_

#include <stdint.h>


#define THREAD_MAX_PRIORITY    32
#define THREAD_NORMAL_PRIORITY 0
#define THREAD_MIN_PRIORITY   -32

class ThreadInterface_t;

typedef void ( *ThreadRoutine_t )( ThreadInterface_t* pThisThread, void* pContext );

class ThreadInterface_t
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
//    virtual void Destroy() = 0;
    virtual void Sleep( uint32_t seconds ) = 0;
    virtual void SleepMsec( uint32_t mSeconds ) = 0;
    virtual void SetPriority( uint8_t priority ) = 0;
    virtual void Yield() = 0;
    virtual ~ThreadInterface_t(){};
};

#endif