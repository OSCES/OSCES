#ifndef OSCES_FRAMEWORK_INTERFACE_H
#define OSCES_FRAMEWORK_INTERFACE_H

#include "DisplayInterface.h"
#include "KeyboardInterface.h"
#include "SysTimerInterface.h"

enum OscesApplicationStatus
{
    OSCES_APP_SUCCESS_STATUS,
    OSCES_APP_FAILED_STATUS,
};

enum OscesFrameworkStatus
{
    OSCES_FRAMEWORK_INIT_SUCCESS,
    OSCES_FRAMEWORK_INIT_FAILED,
};

class OscesFrameworkInterface
{
public:
    virtual DisplayInterface*  display() = 0;
    virtual KeyboardInterface* keyboard() = 0;
    virtual SysTimerInterface* sysTimer() = 0;
    virtual bool applicationRunning() = 0;

    virtual ~OscesFrameworkInterface() {}
};

#endif // OSCES_FRAMEWORK_INTERFACE_H
