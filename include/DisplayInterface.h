#ifndef _DISPLAY_INTERFACE_h_
#define _DISPLAY_INTERFACE_h_

#include <stdint.h>
#include "DisplayTypes.h"


class DisplayInterface_t
{
public:
	virtual void DrawPixel( uint16_t xPos, uint16_t yPos ) = 0;
	virtual void DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color ) = 0;
	virtual void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ) = 0; // compability issue
	virtual void DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos ) = 0;
	virtual void DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos, Color_t& color ) = 0;
	virtual void DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos ) = 0;
	virtual void DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos, Color_t& color ) = 0; // Fast Line
    virtual void DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos ) = 0;
    virtual void DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos, Color_t& color ) = 0; // Fast Line

	virtual void Fill( uint16_t xPos, uint16_t yPos ) = 0;
	virtual void Fill( uint16_t xPos, uint16_t yPos, Color_t& color ) = 0;

public:
    //virtual void CopyBitmapToSurface( const DisplayBitmap_t* pDestinationRect, uint32_t xPosInSurface, uint32_t yPosInSurface ) = 0;
    virtual void Flip() = 0;
    virtual void Clear() = 0;
};


#endif //_DISPLAY_INTERFACE_h_