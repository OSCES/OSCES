#include "GraphicalPrimitives/Surface.h"

Surface::Surface(SurfeceLocation location, PixelFormat pixelFormat, DisplayInterface *display) :
    m_location(location),
    m_pixelFormat(pixelFormat),
    m_display(display)
{
}

PixelFormat Surface::pixelFormat()
{
    return m_pixelFormat;
}

uint32_t Surface::height() const
{
    return m_display->height();
}

uint32_t Surface::width() const
{
    return m_display->width();
}

void* Surface::frameBuffer() const
{
    return m_display->frameBuffer();
}
