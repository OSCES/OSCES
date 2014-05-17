#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

enum SystemClock_t
{
    SYSTEM_CLOCK_24MHz,
    SYSTEM_CLOCK_120MHz,
    

};

class ClockManager_t
{
public:
    void SetSystemClock( SystemClock_t clock );    
  
  
};

#endif // SYSTIMER_H
