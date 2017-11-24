#include "ThreadPlatform.h"
#include "Kernel.h"

ThreadPlatform::ThreadPlatform(Kernel* kernel) :
    m_threadId(-1),
    m_kernel(kernel)
{
}

ThreadPlatform::~ThreadPlatform()
{
}

void ThreadPlatform::setId(uint32_t threadId)
{
    if (m_threadId == threadId)
        return;

    m_threadId = threadId;
}

void ThreadPlatform::start()
{
//    m_scheduler->threadStart(m_threadId);
}

void ThreadPlatform::stop()
{
//    m_scheduler->threadStop(m_threadId);
}

uint32_t ThreadPlatform::id()
{
    return m_threadId;
}

void ThreadPlatform::sleep(uint32_t seconds)
{
//    m_scheduler->threadSleep(m_threadId, seconds);
}

void ThreadPlatform::sleepMsec(uint32_t mSeconds)
{
//    m_scheduler->threadSleepMsec(m_threadId, mSeconds);
}

void ThreadPlatform::setPriority(uint8_t priority)
{
//    m_scheduler->threadSetPriority(m_threadId, priority);
}

void ThreadPlatform::yield()
{
    m_kernel->yield();
}
