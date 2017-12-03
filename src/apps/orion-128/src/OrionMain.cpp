/*
 * File:   main.cpp
 * Author: IBilorus
 *
 * Created on 17 Сентябрь 2013 г., 15:12
 */

//#include "SDL.h"
//#include "Display/Display.h"

#include "Cpu/Cpu.h"
#include "Orion.h"

#include "Osces.h"
#include "OscesCore.h"
#include "VideoSystem.h"
#include "AbstractDisplay.h"
#include "PaintEngine.h"
#include "KeyCode.h"

void keyEventHandler(void *context, const KeyEvent &event)
{
    Orion_t *orion = static_cast<Orion_t *>(context);
    if (event.eventType == KeyPressed)
        orion->PressKey(event.key.keyCode);
    else
        orion->UnPressKey(event.key.keyCode);
}

void PresentFrameCallBack(void* pContext, uint8_t* pData, uint16_t lineNumber)
{
    static PaintEngine paintEngine;
    static AbstractDisplay *display = OscesCore::videoSystem()->display();
    static int xOffset = (display->width() - 384) / 2;
    static int yOffset = (display->height() - 256) / 2;

    if (!pData)
    {
        paintEngine.drawEnd();
        return;
    }

    paintEngine.drawBegin(display);
    int y = lineNumber + yOffset;
    for (uint16_t x = xOffset; x != 384 + xOffset; ++x)
    {
        Color color(pData[0], pData[1], pData[2]);
        paintEngine.setPenColor(color);
        paintEngine.drawPixel(x, y);

        pData += 3;
    }
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Orion_t orion;

    orion.SetPresentLineCallBack(0, PresentFrameCallBack);
    orion.Reset();

    OscesCore::setActiveInputHandler(&orion, keyEventHandler);

    while (OscesCore::applicationRuning())
    {
        orion.RunFrame();
    }

    return 0;
}

