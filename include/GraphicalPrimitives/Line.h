#ifndef LINE_H
#define LINE_H

#include <stdint.h>
#include "Surface.h"
#include "DisplayTypes.h"

class Line_t
{
public:
	Line_t( Surface_t* pSurface );

	void SetColor( Color_t& color );
    void Draw( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos );
	void DrawVertical( uint16_t xPos, uint16_t yPos, uint16_t size );
    void DrawHorizontal( uint16_t xPos, uint16_t yPos, uint16_t size );

private:
	void DrawHorizontal322To888A( uint16_t xPos, uint16_t yPos, uint16_t size );
	void DrawHorizontal888ATo888A( uint16_t xPos, uint16_t yPos, uint16_t size );
	void DrawHorizontal322To322( uint16_t xPos, uint16_t yPos, uint16_t size );

private:
    void DrawVertical322To888A( uint16_t xPos, uint16_t yPos, uint16_t size );
	void DrawVertical888ATo888A( uint16_t xPos, uint16_t yPos, uint16_t size );
	void DrawVertical322To322( uint16_t xPos, uint16_t yPos, uint16_t size );

private:
	uint32_t GetAbs( int32_t value );


private:
	void ( Line_t::*fp_DrawHorizontal )( uint16_t xPos, uint16_t yPos, uint16_t size );
	void ( Line_t::*fp_DrawVertical )( uint16_t xPos, uint16_t yPos, uint16_t size );
	


private:
	Surface_t* m_pSurface;
	Color_t    m_Color;
};

#endif // LINE_H
