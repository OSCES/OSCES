#include "SysTimerPlatform.h"
#include <SDL.h>

uint32_t SysTimerPlatform::valueUsec()
{
    uint64_t perfCounter = SDL_GetPerformanceCounter();
    uint64_t perfFreq = SDL_GetPerformanceFrequency();

    uint32_t msec = ( uint32_t )( 1000000 * perfCounter / perfFreq );

    return msec;  
}


