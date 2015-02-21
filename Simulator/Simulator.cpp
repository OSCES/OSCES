

#include "OscesFrameworkInterface.h"


OscesApplicationStatus_t osces_main( OscesFrameworkInterface_t* system )
{
	do
	{
		// write your test code
	} 
	while( system->IsApplicationRun() );

	return OSCES_APP_SUCCESS_STATUS;
}