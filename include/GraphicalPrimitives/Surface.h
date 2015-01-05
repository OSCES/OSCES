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
	Surface_t( SurfeceLocation_t location, DisplayInterface_t* pDisplay );

	Surface_t( uint16_t sizeVertical, uint16_t sizeHorizontal );
	
	void GetSizeVertical();
	void GetSizeHorizontal();
	void* GetFrameBuffer();

	
private:
	SurfeceLocation_t   m_Location;
	DisplayInterface_t* m_pDisplay;
};

#endif // SURFACE_H
