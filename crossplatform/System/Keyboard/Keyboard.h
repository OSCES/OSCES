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
    void RegisterCallBack( void* pContext, KeyboardCallBack_t fpCallBack );
    void UnRegisterCallBack( KeyboardCallBack_t fpCallBack );

    void    SetCodePage( CodePage_t codePage );
    uint8_t ScanCodeToKeyCode( uint8_t scanCode, uint8_t extendKeyFlag );
    uint8_t KeyCodeToCharCode( uint8_t keyCode );

protected:
    KeyboardCallBack_t m_fpCallBack;
    void              *m_pContext;

    Key_t              m_Key;
    uint32_t*          m_pCodePage;
};

#endif // KEYBOARD_H
