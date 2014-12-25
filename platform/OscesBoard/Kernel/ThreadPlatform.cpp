#include "ThreadPlatform.h"

ThreadPlatform_t::~ThreadPlatform_t()
{

}

ThreadPlatform_t::ThreadPlatform_t( Kernel_t* pKernel )
{
    m_pKernel = pKernel;
}

void ThreadPlatform_t::SetId( uint32_t threadId )
{
    m_ThreadId = threadId;
}

void ThreadPlatform_t::Start()
{
    //m_pScheduler->ThreadStart( m_ThreadId );
}

void ThreadPlatform_t::Stop()
{
    //m_pScheduler->ThreadStop( m_ThreadId );
}

uint32_t ThreadPlatform_t::GetId()
{
    return m_ThreadId;
}

void ThreadPlatform_t::Sleep( uint32_t seconds )
{
    //m_pScheduler->ThreadSleep( m_ThreadId, seconds );
}

void ThreadPlatform_t::SleepMsec( uint32_t mSeconds )
{
    //m_pScheduler->ThreadSleepMsec( m_ThreadId, mSeconds );
}

void ThreadPlatform_t::SetPriority( uint8_t priority )
{
    //m_pScheduler->ThreadSetPriority( m_ThreadId, priority );
}

void ThreadPlatform_t::Yield()
{
    m_pKernel->Yield();
}