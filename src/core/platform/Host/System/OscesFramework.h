#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "SysTimer/SysTimerPlatform.h"
#include "KeyboardPlatform.h"
#include "Display/DisplayPlatform.h"

class OscesCore : public OscesFrameworkInterface
{
public:
    OscesCore();
    DisplayInterface*  display();
    KeyboardInterface* keyboard();
    SysTimerInterface* sysTimer();
    bool applicationRunning();

    OscesFrameworkStatus init();
    void deInit();

private:
    DisplayPlatform *m_display;
    KeyboardPlatform *m_keyboard;
    SysTimerPlatform *m_sysTimer;

private:
    bool m_applicationRunning;
};


#endif // OSCES_FRAMEWORK_H
