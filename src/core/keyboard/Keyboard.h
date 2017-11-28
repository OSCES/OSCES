#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "KeyboardInterface.h"

class Keyboard : public AbstractKeyboard
{
public:
    Keyboard();
    ~Keyboard();

public:
    void registerCallBack(void *context, KeyEventHandler callBack);
    void unRegisterCallBack(KeyEventHandler callBack);

    void proceedKeyEvent(const KeyEvent &event);

    char charFromKeycode(KeyCode keyCode);

private:
    void *m_context;
    KeyEventHandler m_keyEventHandler;
};

#endif // KEYBOARD_H
