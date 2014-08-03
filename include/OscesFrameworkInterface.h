#ifndef OSCES_FRAMEWORK_INTERFACE_H
#define OSCES_FRAMEWORK_INTERFACE_H


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


class OscesFrameworkInterface_t
{
public:
    virtual DisplayInterface_t*  GetDisplay() = 0;
    virtual KeyboardInterface_t* GetKeyboard() = 0;
    virtual SysTimerInterface_t* GetSysTimer() = 0;
    virtual bool IsApplicationRun() = 0;

};

extern OscesApplicationStatus_t osces_main( OscesFrameworkInterface_t* system );




#endif // OSCES_FRAMEWORK_INTERFACE_H
