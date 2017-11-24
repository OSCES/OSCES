#ifndef _KEYBOARD_INTERFACE_H_
#define _KEYBOARD_INTERFACE_H_

#include <stdint.h>
#include "KeyCode.h"

// TODO: remove
enum CodePage
{
    CP_ASCII,
    CP_UTF8,
    CP_1251
};

enum KeyEvent
{
    KeyReleased,
    KeyPressed
};

struct ModifyKeysState
{
    uint8_t Alt        : 1; // 0 - KEY_RELEASED, 1 - KEY_PRESSED
    uint8_t Ctrl       : 1;
    uint8_t Shift      : 1;
    uint8_t CapsLock   : 1;
    uint8_t NumLock    : 1;
    uint8_t ScrollLock : 1;
    uint8_t Reserved   : 2;
};

struct Key
{
    uint16_t          CharCode;     // Unicode, ASCII etc.
    KeyCode         KeyCode;
    uint8_t           ScanCode;
    uint8_t           ExtendedKeyFlag;
    KeyEvent        Event;
    ModifyKeysState ModifKeysStates;
};

typedef void (*KeyboardCallBack)(void *context, Key& key);

class KeyboardInterface
{
public:
    virtual ~KeyboardInterface() = {};

    virtual void registerCallBack( void* pContext, KeyboardCallBack fpCallBack ) = 0;
    virtual void unRegisterCallBack( KeyboardCallBack fp_CallBack ) = 0;
};

#endif
