#include "OscesFrameworkInterface.h"
#include "Emulator.h"

Emulator_t Emulator;

OscesApplicationStatus_t osces_main()
{
    Emulator.Init();
  
    while( Sys::IsApplicationRun() )
    {
        Emulator.Run();
    }
    
    return OSCES_APP_SUCCESS_STATUS;
}