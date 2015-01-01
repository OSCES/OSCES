#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

enum SystemClock_t
{
    SYSTEM_CLOCK_24MHz,
    SYSTEM_CLOCK_120MHz,
};

enum GpioClock_t
{
    GPIO_CLOCK__PORTA = 0,
    GPIO_CLOCK__PORTB = 1,
    GPIO_CLOCK__PORTC = 2,
    GPIO_CLOCK__PORTD = 3,
    GPIO_CLOCK__PORTE = 4,
    GPIO_CLOCK__PORTF = 5,
    GPIO_CLOCK__PORTG = 6,
    GPIO_CLOCK__PORTH = 7,
    GPIO_CLOCK__PORTI = 8,
};

class ClockManager_t
{
private:
    ClockManager_t();
    ~ClockManager_t();
    ClockManager_t(const ClockManager_t& value);
    ClockManager_t& operator = (const ClockManager_t& value);

public:
    static ClockManager_t& GetInstance();
    void SetSystemClock( SystemClock_t clock );
    void EnableGpioClock(GpioClock_t clock);

private:
    bool m_IsEnabledGpioClock[9]; // A B C D E F G H I
};

#endif // SYSTIMER_H
