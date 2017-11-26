#include "OscesFrameworkInterface.h"

#define main osces_main

// Rework osces_main
OscesApplicationStatus main(OscesFrameworkInterface *system)
{
    do
    {
        // write your test code
    }
    while(system->applicationRunning());

    return OSCES_APP_SUCCESS_STATUS;
}
