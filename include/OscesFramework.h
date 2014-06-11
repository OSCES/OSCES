#ifndef OSCES_FRAMEWORK_H
#define OSCES_FRAMEWORK_H


#include "DisplayInterface.h"
#include "KeyboardInterface.h"
#include "SysTimerInterface.h"

enum OscesApplicationStatus_t
{
    OSCES_APP_SUCCESS_STATUS = 0,
    OSCES_APP_FAILED_STATUS,
};

enum OscesFrameworkStatus_t
{
    OSCES_FRAMEWORK_INIT_SUCCESS = 0,
    OSCES_FRAMEWORK_INIT_FAILED = 0,
};


class OscesFramework_t
{
public:
    DisplayInterface_t*  GetDisplay();
    KeyboardInterface_t* GetKeyboard();
    SysTimerInterface_t* GetSysTimer();
    bool        IsApplicationRun();

};

OscesApplicationStatus_t osces_main( OscesFramework_t* system );

OscesFrameworkStatus_t OscesFrameworkInit();
void OscesFrameworkDeInit();



#endif // KEYBOARD_H
