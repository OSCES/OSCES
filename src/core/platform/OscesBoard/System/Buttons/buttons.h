#ifndef BUTTONS_H
#define BUTTONS_H

//          TEMPORARY CODE
//
// TODO:    Delete this code
//          Determine role of each button and implement the functionality using IMR

#include "GpioDriver.h"

enum ButtonType
{
    Button1,       // TODO: set button name (BUTTON__START, BUTTON__RESET and so on)
    Button2,
    Button3
};

class Button
{
public:
    Button(ButtonType button);
    ~Button();

    bool pressed();

private:
    GpioPin* m_button;
};

#endif // BUTTONS_H
