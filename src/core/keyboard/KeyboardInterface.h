#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include <stdint.h>
#include "KeyCode.h"

enum KeyEventType
{
    KeyReleased = 0x0000, // uint_8
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
    char text;
    KeyCode keyCode;
    uint8_t scanCode;
    uint8_t extendedKeyFlag;
    ModifyKeysState modifKeysStates;
};

struct KeyEvent
{
    Key key;
    KeyEventType eventType;
};

typedef void (*KeyEventHandler)(void *context, const KeyEvent &event);

class AbstractKeyboard
{
public:
    virtual ~AbstractKeyboard() {}

    virtual void registerCallBack(void *context, KeyEventHandler callBack) = 0;
    virtual void unRegisterCallBack(KeyEventHandler callBack) = 0;

    virtual void proceedKeyEvent(const KeyEvent &event) = 0;
};

#endif
