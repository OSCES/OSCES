#ifndef _KEYBOARD_INTERFACE_H_
#define _KEYBOARD_INTERFACE_H_


#include <stdint.h>

enum CodePage_t
{
    CP_ASCII = 0,
    CP_UTF8  = 1,
    CP_1251  = 2
};

enum KeyEvent_t
{
    KEY_RELEASED = 0,
    KEY_PRESSED  = 1
};

struct ModifyKeysState_t
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
    uint16_t          CharCode;     // Unicode, ASCII etc.
    uint8_t           KeyCode;
    uint8_t           ScanCode;
    uint8_t           ExtendedKeyFlag;
    KeyEvent_t        Event;
    ModifyKeysState_t ModifKeysStates;
};

typedef void ( *KeyboardCallBack_t )( void* pContext, Key_t& key );

class KeyboardInterface_t
{
public:
    virtual void RegisterCallBack( void* pContext, KeyboardCallBack_t fpCallBack ) = 0;
    virtual void UnRegisterCallBack( KeyboardCallBack_t fp_CallBack ) = 0;
};

#endif
