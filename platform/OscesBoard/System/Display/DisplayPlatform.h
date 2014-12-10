#ifndef DISPLAY_PLATFORM_H
#define DISPLAY_PLATFORM_H

#include <stdint.h>
#include "crossplatform/System/Display/Display.h"
#include "FsmcDriver.h"


enum DisplayBuffer_t
{
    DISPLAY_PRIMARY_BUFFER = 0,
    DISPLAY_BACK_BUFFER    = 1,
};

class DisplayPlatform_t : public Display_t
{
public:
	void Init( uint16_t xSize, uint16_t ySize );
	virtual  ~DisplayPlatform_t();

public:
    virtual void DrawPixel( uint16_t xPos, uint16_t yPos );
	virtual void DrawPixel( uint16_t xPos, uint16_t yPos, Color_t& color );
	virtual void DrawPixel( uint16_t xPos, uint16_t yPos, uint8_t red, uint8_t green, uint8_t blue ); // compability issue
	virtual void DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos );
	virtual void DrawLine( uint16_t xStartPos, uint16_t yStartPos, uint16_t xEndPos, uint16_t yEndPos, Color_t& color );
	virtual void DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos );
	virtual void DrawVerticalLine( uint16_t xPos, uint16_t yStartPos, uint16_t yEndPos, Color_t& color ); // Fast Line
    virtual void DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos );
    virtual void DrawHorizontalLine( uint16_t yPos, uint16_t xStartPos, uint16_t xEndPos, Color_t& color ); // Fast Line
	virtual void Fill( uint16_t xPos, uint16_t yPos );
	virtual void Fill( uint16_t xPos, uint16_t yPos, Color_t& color );
    virtual void Clear();

public:
	virtual void Flip();

public:
	void SetMousePos( uint16_t xPos, uint16_t yPos );
    void Present( PixelStruct_t* pData );

private:
    void SelectBuffer( DisplayBuffer_t buffer );

private:
    DisplayBuffer_t m_DisplayBuffer;
    Fsmc_t          m_ExtSram;
    uint16_t        m_WindowSizeX;
    uint16_t        m_WindowSizeY;
};

#endif // DISPLAY_H


