#include "OscesFrameworkInterface.h"

// Rework osces_main
OscesApplicationStatus osces_main(OscesFrameworkInterface *system)
{
    do
    {
        // write your test code
    }
    while(system->applicationRunning());

    return OSCES_APP_SUCCESS_STATUS;
}
