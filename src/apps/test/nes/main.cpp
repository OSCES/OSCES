#include "OscesFrameworkInterface.h"
#include "GraphicalPrimitives/Line.h"
#include "NesEmulator_1/Emulator.h"

Emulator_t Emulator;
OscesFrameworkInterface_t* System;

OscesApplicationStatus_t osces_main( OscesFrameworkInterface_t* pSystem )
{
    System = pSystem;
    
    Emulator.Init();
    
    while( pSystem->IsApplicationRun() )
    {
        Emulator.Run();
    }
    
    return OSCES_APP_SUCCESS_STATUS;
}