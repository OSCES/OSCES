#ifndef _KEYBOARD_INTERFACE_h_
#define _KEYBOARD_INTERFACE_h_

#include <stdint.h>


enum KeyboardKeyCode_t
{

    KEYBOARD_KEYCODE_a     = 'a',

    KEYBOARD_KEYCODE_RIGHT = 79,
    KEYBOARD_KEYCODE_LEFT  = 80,
    KEYBOARD_KEYCODE_DOWN  = 81,
    KEYBOARD_KEYCODE_UP    = 82,
};


enum KeyboardEvent_t
{
    KEYBOARD_PRESSED,
    KEYBOARD_UNPRESSED
};

enum KeyboardStatus_t
{
    KEYBOARD_SUCCESS_STATUS = 0,
    KEYBOARD_FAILED_STATUS
};

typedef void ( *KeyboardCallBack_t )( void* pContext, KeyboardEvent_t event, uint8_t scanCode );

class KeyboardInterface_t
{
public:
    virtual KeyboardStatus_t RegisterCallBack( void* pContext, KeyboardCallBack_t fp_CallBack ) = 0;
    virtual KeyboardStatus_t UnRegisterCallBack( KeyboardCallBack_t fp_CallBack ) = 0;


};

#endif