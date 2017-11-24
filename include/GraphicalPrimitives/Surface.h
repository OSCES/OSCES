#ifndef SURFACE_H
#define SURFACE_H

#include "include/DisplayInterface.h"
#include <stdint.h>

enum SurfeceLocation
{
    SURFACE_ALLOCATE_IN_FRAME_BUFFER,
    SURFACE_ALLOCATE_IN_SYSTEM_RAM,
};

class Surface
{
public:
    Surface(SurfeceLocation location, PixelFormat pixelFormat, DisplayInterface *display);
    Surface(uint16_t width, uint16_t height);

    uint32_t height() const;
    uint32_t width() const;
    void* frameBuffer() const;
    PixelFormat pixelFormat() const;

private:
    SurfeceLocation m_location;
    PixelFormat m_pixelFormat;
    DisplayInterface *m_display;
};

#endif // SURFACE_H
