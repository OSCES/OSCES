#ifndef _KEYBOARD_INTERFACE_h_
#define _KEYBOARD_INTERFACE_h_


#include <stdint.h>


enum KeyEvent_t
{
    KEY_RELEASED = 0,
    KEY_PRESSED  = 1
};

struct ModifKeysStates_t
{
    uint8_t Alt        : 1; // 0 - KEY_RELEASED, 1 - KEY_PRESSED
    uint8_t Ctrl       : 1;
    uint8_t Shift      : 1;
    uint8_t CapsLock   : 1;
    uint8_t NumLock    : 1;
    uint8_t ScrollLock : 1;
    uint8_t Reserved   : 2;
};

struct Key_t
{
    uint16_t          Code;     // Unicode, ASCII etc.
    uint8_t           KeyCode;
    uint8_t           ScanCode;
    uint8_t           ExtendedKeyFlag;
    KeyEvent_t        Event;
    ModifKeysStates_t ModifKeysStates;
};

typedef void ( *KeyboardCallBack_t )( void* pContext, Key_t key );

class KeyboardInterface_t
{
public:
    virtual void RegisterCallBack( void* pContext, KeyboardCallBack_t fp_CallBack ) = 0;
    virtual void UnRegisterCallBack( KeyboardCallBack_t fp_CallBack ) = 0;

};

#endif
