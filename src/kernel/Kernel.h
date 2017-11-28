#ifndef KERNEL_H
#define KERNEL_H

class SchedulerPlatform;
class ContextSwitcher;

class Kernel
{
public:
    Kernel();
    ~Kernel();

    void init();
    void yield();

private:
    static void pentSvInterruptRoutine(void *context);

private:
    ContextSwitcher *m_contextSwitcher;
    SchedulerPlatform *m_schedulerPlatform;
};

#endif // KERNEL_H
