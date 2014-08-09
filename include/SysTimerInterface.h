#ifndef _SYSTIMER_INTERFACE_H_
#define _SYSTIMER_INTERFACE_H_

#include <stdint.h>



//typedef void ( *KeyboardCallBack_t )( void* pContext, KeyboardEvent_t event, uint8_t scanCode );

class SysTimerInterface_t
{
public:
    virtual uint32_t GetValueUsec() = 0;


};

#endif