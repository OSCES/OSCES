#ifndef LINE_H
#define LINE_H

//#include "include/DisplayInterface.h"
#include <stdint.h>
#include "Surface.h"
#include "DisplayTypes.h"

class Line_t
{
public:
	Line_t::Line_t( Surface_t* pSurface );

	void SetColor( Color_t& color );
    void Draw( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos );
	void DrawVertical( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos );
    void DrawHorizontal( uint16_t xPos, uint16_t yPos, uint16_t size );

private:
	void DrawHorizontal322To888( uint16_t xPos, uint16_t yPos, uint16_t size );


private:
	Surface_t* m_pSurface;
};

#endif // LINE_H
