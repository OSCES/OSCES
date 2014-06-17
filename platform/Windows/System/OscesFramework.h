#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H

#include "OscesFrameworkInterface.h"
#include "SysTimer/SysTimerPlatform.h"
#include "KeyBoard/KeyBoardPlatform.h"
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
    DisplayPlatform_t*  m_pDisplay;
    KeyboardPlatform_t* m_pKeyboard;
    SysTimerPlatform_t* m_pSysTimer;

private:
    bool m_IsApplicationRun;

};


#endif // OSCES_FRAMEWORK_H
