#ifndef SYSTIMER_DRIVER_H
#define SYSTIMER_DRIVER_H

#define HZ_IN_MHZ               1000000
#define SYS_TICK_TIMER_INT_FREQ 10

class SysTimerDriver_t
{
public:
    void Init();
    uint32_t GetValueUsec();

private:
    static void SysTimerInterruptRoutine( void* pContext );
    
private:    
    uint64_t m_Usec;
    uint32_t m_SysTickValue;
};

#endif // SYSTIMER_DRIVER_H
