#include "OscesFrameworkPlatform.h"
#include "SysTimer/SysTimerPlatform.h"
#include "PS2KeyboardPlatform.h"
#include "Display/DisplayPlatform.h"
#include "leds.h"
#include "buttons.h"
#include "ClockManager.h"
#include "InterruptManager.h"
#include "GpioDriver.h"
#include "DmaDriver.h"
#include "SysTimerDriver.h"
#include "Kernel/ThreadPlatform.h"
#include "Kernel/Kernel.h"
#include "UDA1334_Driver.h"
#include <intrinsics.h>
#include <stdio.h>
#include <stdlib.h>

extern OscesApplicationStatus osces_main(OscesFrameworkInterface *system);
Kernel m_Kernel;
uint8_t ProcessStack[512];
RCC_ClocksTypeDef freq;

OscesFramework::OscesFramework() :
    m_applicationRunning(true)
{
}

OscesFramework::~OscesFramework()
{
}

SysTimerInterface* OscesFramework::sysTimer()
{
    return m_sysTimer;
}

DisplayInterface* OscesFramework::display()
{
    return m_display;
}

KeyboardInterface* OscesFramework::keyboard()
{
    return m_keyboard;
}

ThreadInterface* OscesFramework::threadCreate(uint32_t stackSize, ThreadRoutine fpThreadRoutine, void* context )
{
    ThreadPlatform* pThreadPlatform = new ThreadPlatform( &m_Kernel );

    uint32_t threadId = m_scheduler->threadCreate( stackSize, fpThreadRoutine, pThreadPlatform, context );

    pThreadPlatform->setId( threadId );

    return pThreadPlatform;
}

void  OscesFramework::threadDestroy(ThreadInterface* thread )
{
    ThreadPlatform* pThreadPlatform = static_cast< ThreadPlatform* >( thread ); //TODO: delete cast !!!

    uint32_t threadId = pThreadPlatform->id();

    m_scheduler->threadDestroy( threadId );

    delete thread;// pThreadPlatform;
}

void OscesFramework::threadYield()
{
    uint32_t currentThreadId = 0;
    m_scheduler->threadYield(currentThreadId);
}


void *operator new(size_t size)
{
    return malloc(size);
}
void operator delete(void *p)
{
    free(p);
}

int main()
{
    ClockManager clockManager;
    clockManager.setSystemClock(ClockManager::SysClock_120MHz);

    //__svc(SVC_00);
    //__svc(0);
    asm("nop");
    //m_Kernel.Init();

    OscesFramework  oscesFramework;
    oscesFramework.init();
    osces_main(&oscesFramework);
    oscesFramework.deInit();

    return 0;
}

//$PROJ_DIR$\..\..\..\thirdparty\STM32F4\STM32F4xx_StdPeriph_Driver\stm32f4xx_conf.h
bool OscesFramework::applicationRunning()
{
    return m_applicationRunning;
}

OscesFrameworkStatus OscesFramework::init()
{
    OscesFrameworkStatus status = OSCES_FRAMEWORK_INIT_SUCCESS;

    InterruptManager::disableInterrupt();
    InterruptManager::init();

//    DmaInit();
//    ClockManager clockManager;
//    clockManager.setSystemClock(ClockManager::SysClock_120MHz);

    // WTF ? Use clock manager
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    try
    {
        m_display = new DisplayPlatform;
        m_keyboard = new KeyboardPlatform;
        m_sysTimer = new SysTimerPlatform;
        m_scheduler = new SchedulerPlatform;

    }
    catch(...)
    {

        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }

    m_keyboard->init();
    m_display->init(400, 300, false);
    m_display->clear();
    m_display->flip();
    m_display->clear();
    m_display->flip();

    m_sysTimer->init();

    UDA1334_DriverInit();

    InterruptManager::enableInterrupt();

    return status;
}


void OscesFramework::deInit()
{
    delete m_scheduler;
    delete m_sysTimer;
    delete m_keyboard;
    delete m_display;
}
