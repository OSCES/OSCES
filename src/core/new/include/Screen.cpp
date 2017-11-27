#include "Screen.h"
#include <stdint.h>

Screen::Screen() :
    d_ptr(new ScreenPrivate)
{
    d_ptr->width = 0;
    d_ptr->height = 0;
    d_ptr->bytesPerLine = 0;
    d_ptr->data = 0;
}

Screen::~Screen()
{
    delete d_ptr;
}

int Screen::width() const
{
    return d_ptr->width;
}

int Screen::height() const
{
    return d_ptr->height;
}

uint8_t *Screen::bits() const
{
    return d_ptr->data;
}

int Screen::bytesPerLine() const
{
    return d_ptr->bytesPerLine;
}

Screen::PixelFormat Screen::pixelFormat() const
{
    return d_ptr->pixelFormat;
}
