#include "GraphicalPrimitives/Surface.h"



Surface_t::Surface_t( SurfeceLocation_t location, DisplayInterface_t* pDisplay )
{
	m_Location = location;
	m_pDisplay = pDisplay;
}


void* Surface_t::GetFrameBuffer()
{
	return m_pDisplay->GetFrameBuffer();
}