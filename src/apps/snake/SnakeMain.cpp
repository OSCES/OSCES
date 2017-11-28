#include "Osces.h"
#include "OscesCore.h"
#include "VideoSystem.h"
#include "KeyCode.h"
#include "Snake.h"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    AbstractDisplay *display = OscesCore::videoSystem()->display();
    Snake snake(10, 10, display);
    snake.initialize();

    OscesCore::setActiveInputHandler(&snake, Snake::keyEventHandler);

    int lastTickValue = 0;
    while (OscesCore::applicationRuning())
    {
        int tickValue = OscesCore::tickCount();
        int deltaTickValue = tickValue - lastTickValue;

        if (deltaTickValue >= 50)
        {
            lastTickValue = tickValue;
            snake.run();
        }
    }

    return 0;
}
