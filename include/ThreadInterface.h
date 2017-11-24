#ifndef _THREAD_INTERFACE_H_
#define _THREAD_INTERFACE_H_

#include <stdint.h>

#define THREAD_MAX_PRIORITY    32
#define THREAD_NORMAL_PRIORITY 0
#define THREAD_MIN_PRIORITY   -32

class ThreadInterface;
typedef void (*ThreadRoutine)(ThreadInterface *thisThread, void *context);

enum ThreadPriority
{
    Max = 32,
    Normal = 0,
    Min = 31
};

class ThreadInterface
{
public:
    virtual ~ThreadInterface() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void sleep(uint32_t seconds) = 0;
    virtual void sleepMsec(uint32_t mSeconds) = 0;
    virtual void setPriority(uint8_t priority) = 0;
    virtual void yield() = 0;
};

#endif
