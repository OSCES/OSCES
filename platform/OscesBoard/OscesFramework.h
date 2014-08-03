#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "InterruptManager.h"
#include "SysTimer/SysTimerPlatform.h"
#include "KeyBoard/PS2Keyboard.h"
#include "Display/DisplayPlatform.h"

class OscesFramework_t : public OscesFrameworkInterface_t
{
public:
    OscesFramework_t();
    DisplayInterface_t*  GetDisplay();
    KeyboardInterface_t* GetKeyboard();
    SysTimerInterface_t* GetSysTimer();
    bool        IsApplicationRun();

    OscesFrameworkStatus_t Init();
    void DeInit();


private:
    InterruptManager_t *m_pInterruptManager;
    DisplayPlatform_t  *m_pDisplay;
    PS2Keyboard_t      *m_pPS2Keyboard;
    SysTimerPlatform_t *m_pSysTimer;

private:
    bool m_IsApplicationRun;

};


#endif // OSCES_FRAMEWORK_H
