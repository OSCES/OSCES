#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "KeyboardInterface.h"

class Keyboard : public KeyboardInterface
{
public:
    Keyboard();
    ~Keyboard();

public:
    void registerCallBack(void* context, KeyboardCallBack fpCallBack );
    void unRegisterCallBack( KeyboardCallBack fpCallBack );

    void setCodePage( CodePage codePage );
    KeyCode keyCodeFromScanCode(uint8_t scanCode, uint8_t extendKeyFlag);
    uint16_t charCodeFromkeyCode(uint8_t keyCode);

protected:
    KeyboardCallBack m_fpCallBack;
    void *m_context;

    Key m_key;
    uint32_t *m_codePage;
};

#endif // KEYBOARD_H
