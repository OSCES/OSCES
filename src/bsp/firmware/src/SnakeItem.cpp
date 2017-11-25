#include  "SnakeItem.h"

Display_t*        m_pDisplay;


void LineVertical( uint16_t xPos, uint16_t yPos, uint16_t size, uint8_t red, uint8_t green, uint8_t blue )
{
    for( uint32_t y = 0; y < size; y ++ )
    {
       m_pDisplay->DrawPixel( xPos, yPos + y, red, green, blue );
    }
}

void LineHorizontal( uint16_t xPos, uint16_t yPos, uint16_t size, uint8_t red, uint8_t green, uint8_t blue )
{
    for( uint32_t x = 0; x < size; x ++ )
    {
       m_pDisplay->DrawPixel( xPos +x, yPos, red, green, blue );
    }
}

void SetRectangle( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t red, uint8_t green, uint8_t blue )
{
    LineVertical( x, y, height, red, green, blue );
    LineVertical( x + width, y, height, red, green, blue );
    
    LineHorizontal( x, y, width, red, green, blue );
    LineHorizontal( x, y + height, width, red, green, blue );
}

 
void FillRectangle( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t red, uint8_t green, uint8_t blue )
{
	for( uint32_t yPos = 0; yPos != height; yPos++ )
	{
		LineHorizontal( x, y + yPos, width, red, green, blue );
	}
}

SnakeItem_t::SnakeItem_t()
{
	m_PosX          = 0;
	m_PosY          = 0;
	m_SnakeItemSize = 20;
	m_Next          = 0;
}

SnakeItem_t::SnakeItem_t( Display_t* pDisplay, uint16_t size  )
{
	m_pDisplay = pDisplay;
	m_PosX          = 0;
	m_PosY          = 0;
	m_SnakeItemSize = size;
	m_Next          = 0;
}

void SnakeItem_t::Redraw()
{
	Move( m_PosX, m_PosY );
}

void SnakeItem_t::Move( uint16_t xPos, uint16_t yPos )
{
	uint16_t x = xPos * m_SnakeItemSize;
	uint16_t y = yPos * m_SnakeItemSize;

	FillRectangle( m_PosX * m_SnakeItemSize , m_PosY * m_SnakeItemSize, m_SnakeItemSize, m_SnakeItemSize, 0x00, 0x00, 0x00 );
    FillRectangle( x  , y  , m_SnakeItemSize, m_SnakeItemSize, 0xFF, 0x00, 0x00 );
	SetRectangle ( x  , y  , m_SnakeItemSize, m_SnakeItemSize, 0x00, 0x00, 0x00 );
	SetRectangle ( x + 1  , y + 1  , m_SnakeItemSize - 2, m_SnakeItemSize - 2, 0x00, 0xFF, 0x00 );

	m_PosX = xPos;
	m_PosY = yPos;
}

void SnakeItem_t::SetNext( SnakeItem_t* next )
{
	m_Next = next;
}

SnakeItem_t* SnakeItem_t::GetNext()
{
    return m_Next;
}