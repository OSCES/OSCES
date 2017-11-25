#ifndef BUTTONS_H
#define BUTTONS_H


//          TEMPORARY CODE
//
// TODO:    Delete this code
//          Determine role of each button and implement the functionality using IMR


#include "GpioDriver.h"


enum Buttons_t
{
    BUTTON_1 = 0,       // TODO: set button name (BUTTON__START, BUTTON__RESET and so on)
    BUTTON_2,
    BUTTON_3
};

static const PinInfo g_ButtonInfo[] =
{
    {PORTE, PIN_14},    // Button 1
    {PORTE, PIN_15},    // Button 2
    {PORTB, PIN_10}     // Button 3
};


class Button_t
{
public:
    Button_t(Buttons_t button);
    ~Button_t();

    bool IsPressed( void );

private:
    GpioPin_t* m_button;
};

#endif // BUTTONS_H
