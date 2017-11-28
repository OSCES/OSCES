#include "Osces.h"
#include "OscesCore.h"
#include "Emulator.h"

static uint8_t joysticA = 0x00;
static uint8_t joysticB = 0x00;

void keyEventHandler(void *context, const KeyEvent &event)
{
    if (event.eventType == KeyPressed)
    {
        switch (event.key.keyCode)
        {
        case Key_Up:
            joysticA |= JOYSTIC_BUTTON_UP;
            break;
        case Key_Left:
            joysticA |= JOYSTIC_BUTTON_LEFT;
            break;
        case Key_Down:
            joysticA |= JOYSTIC_BUTTON_DOWN;
            break;
        case Key_Right:
            joysticA |= JOYSTIC_BUTTON_RIGHT;
            break;
        case Key_Z:
            joysticA |= JOYSTIC_BUTTON_A;
            break;
        case Key_X:
            joysticA |= JOYSTIC_BUTTON_B;
            break;
        case Key_Tab:
            joysticA |= JOYSTIC_BUTTON_SELECT;
            break;
        case Key_Enter:
            joysticA |= JOYSTIC_BUTTON_START;
            break;
        default:
            break;
        }
    }
    else if (event.eventType == KeyReleased)
    {
        switch (event.key.keyCode)
        {
        case Key_Up:
            joysticA &= ~JOYSTIC_BUTTON_UP;
            break;
        case Key_Left:
            joysticA &= ~JOYSTIC_BUTTON_LEFT;
            break;
        case Key_Down:
            joysticA &= ~JOYSTIC_BUTTON_DOWN;
            break;
        case Key_Right:
            joysticA &= ~JOYSTIC_BUTTON_RIGHT;
            break;
        case Key_Z:
            joysticA &= ~JOYSTIC_BUTTON_A;
            break;
        case Key_X:
            joysticA &= ~JOYSTIC_BUTTON_B;
            break;
        case Key_Tab:
            joysticA &= ~JOYSTIC_BUTTON_SELECT;
            break;
        case Key_Enter:
            joysticA &= ~JOYSTIC_BUTTON_START;
            break;
        default:
            break;
        }
    }

    Emulator_t::JoysticEvent(context, joysticA, joysticB);
}

int main(int argc, char* argv[])
{
    Emulator_t emulator;
    emulator.Init();

    OscesCore::setActiveInputHandler(&emulator, keyEventHandler);

    while (OscesCore::applicationRuning())
    {
        emulator.Run();
    }

    return 0;
}
