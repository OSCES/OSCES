#ifndef SURFACE_H
#define SURFACE_H

#include "include/DisplayInterface.h"
#include <stdint.h>


enum SurfeceLocation_t
{
    SURFACE_ALLOCATE_IN_FRAME_BUFFER,
    SURFACE_ALLOCATE_IN_SYSTEM_RAM,
};

class Surface_t
{
public:
    Surface_t( SurfeceLocation_t location, PixelFormat_t pixelFormat, DisplayInterface_t* pDisplay );
    Surface_t( uint16_t sizeVertical, uint16_t sizeHorizontal );

    uint32_t GetSizeVertical();
    uint32_t GetSizeHorizontal();
    void* GetFrameBuffer();
    PixelFormat_t GetPixelFormat();

private:
    SurfeceLocation_t   m_Location;
    PixelFormat_t       m_PixelFormat;
    DisplayInterface_t* m_pDisplay;
};

#endif // SURFACE_H
