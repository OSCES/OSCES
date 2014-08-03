#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdint.h>
#include "KeyboardInterface.h"


class Keyboard_t : public KeyboardInterface_t
{
public:
    Keyboard_t();
    ~Keyboard_t();

public:
    void RegisterCallBack( void* pContext, KeyboardCallBack_t fp_CallBack );
    void UnRegisterCallBack( KeyboardCallBack_t fp_CallBack );

    void    SetCodePage( CodePage_t codePage );
    uint8_t ScanCodeToKeyCode(uint8_t scanCode, uint8_t extendKeyFlag);
    uint8_t KeyCodeToCharCode(uint8_t keyCode);

protected:
    KeyboardCallBack_t m_CallBack;
    void              *m_Context;

    Key_t              m_Key;
    uint32_t          *m_CodePage;
};

#endif // KEYBOARD_H
