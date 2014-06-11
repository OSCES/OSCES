#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "include/KeyboardInterface.h"



struct HandlersList_t 
{
    KeyboardCallBack_t CallBack;
    void*              Context;
};



class Keyboard_t : public KeyboardInterface_t
{
public:
    Keyboard_t();
    KeyboardStatus_t RegisterCallBack( void* pContext, KeyboardCallBack_t fp_CallBack );
    KeyboardStatus_t UnRegisterCallBack( KeyboardCallBack_t fp_CallBack );
    void ReceiveEvent( KeyboardEvent_t event, uint8_t scanCode );
private:
    static HandlersList_t HandlersList[ 20 ];
};

#endif // KEYBOARD_H
