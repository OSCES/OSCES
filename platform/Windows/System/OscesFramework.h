#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "SysTimer/SysTimerPlatform.h"
#include "KeyboardPlatform.h"
#include "Display/DisplayPlatform.h"

class OscesFramework : public OscesFrameworkInterface
{
public:
    OscesFramework();
    DisplayInterface*  display();
    KeyboardInterface* keyboard();
    SysTimerInterface* sysTimer();
    bool applicationRunning();

    OscesFrameworkStatus Init();
    void DeInit();

private:
    DisplayPlatform *m_pDisplay;
    KeyboardPlatform *m_pKeyboard;
    SysTimerPlatform *m_pSysTimer;

private:
    bool m_IsApplicationRun;
};


#endif // OSCES_FRAMEWORK_H
