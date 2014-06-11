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
