#include "PlatformScreen.h"
#include <stdint.h>

PlatformScreen::PlatformScreen() :
    Screen()
{
}

PlatformScreen::~PlatformScreen()
{
    delete[] d_ptr->data;
}

bool PlatformScreen::initialize()
{
    d_ptr->width = 400;
    d_ptr->height = 300;
    d_ptr->bytesPerLine = d_ptr->width * sizeof(uint8_t);
    d_ptr->data = new uint8_t[d_ptr->bytesPerLine * d_ptr->height];
}

void PlatformScreen::present()
{
    // move d_ptr->data to the device
}
