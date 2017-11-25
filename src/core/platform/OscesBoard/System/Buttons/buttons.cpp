#include "buttons.h"

// const has internal linkage by default
// TODO: Rework and Refactor
static const PinInfo g_ButtonInfo[] =
{
    {PortE, Pin14},    // Button 1
    {PortE, Pin15},    // Button 2
    {PortB, Pin10}     // Button 3
};

Button::Button(ButtonType button)
{
    Port port;
    Pin pin;

    port = g_ButtonInfo[button].port;
    pin  = g_ButtonInfo[button].pin;

    m_button = new GpioPin(port, pin);
    m_button->makeInPullUp();
}

Button::~Button()
{
    delete m_button;
}

bool Button::pressed()
{
    // if Pressed - return false
    return !m_button->read();
}
