#include "Buttons.h"


Button_t::Button_t(Buttons_t button)
{
    Port_t port;
    Pin_t  pin;

    port = g_ButtonInfo[button].port;
    pin  = g_ButtonInfo[button].pin;

    m_button = new GpioPin_t(port, pin);

    m_button->MakeInPullUp();

}

Button_t::~Button_t()
{
    delete m_button;
}

bool Button_t::IsPressed( void )
{
    // if Pressed - return false
    return m_button->Read() ? false : true;
}
