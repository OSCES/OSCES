#include "Keyboard.h"

Keyboard::Keyboard() :
    m_context(0),
    m_keyEventHandler(0)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::registerCallBack(void *context, KeyEventHandler callBack)
{
    m_context = context;
    m_keyEventHandler = callBack;
}

void Keyboard::unRegisterCallBack(KeyEventHandler callBack)
{
    (void)callBack;
    m_keyEventHandler = 0;
    m_context = 0;
}

void Keyboard::proceedKeyEvent(const KeyEvent &event)
{
    if (!m_keyEventHandler)
        return;

    m_keyEventHandler(m_context, event);
}
