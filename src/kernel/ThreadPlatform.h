#ifndef THREAD_PLATFORM_H
#define THREAD_PLATFORM_H

#include "ThreadInterface.h"

class Kernel;

class ThreadPlatform : public ThreadInterface
{
public:
    ThreadPlatform(Kernel *kernel);
    virtual ~ThreadPlatform();

    void start();
    void stop();
    void sleep(uint32_t seconds);
    void sleepMsec(uint32_t mSeconds);
    void setPriority(uint8_t priority);
    void yield();

    void setId(uint32_t threadId);
    uint32_t id();

private:
    uint32_t m_threadId;
    Kernel* m_kernel;
};

#endif // THREAD_PLATFORM_H
