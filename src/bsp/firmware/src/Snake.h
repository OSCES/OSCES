#ifndef _SNAKE_H_
#define _SNAKE_H_

#include  "Display.h"
#include  "SnakeItem.h"

enum SnakeDirection_t
{
	LEFT = 0,
	RIGHT,
    UP,
    DOWN,
};

class Snake_t
{
public:
    void SetDirection( SnakeDirection_t direction );
    void Init( Display_t* pDisplay );

	void Increase();
    void Run( void );
	~Snake_t();
	Snake_t();

private:
 
	void AddItem();
	void UpdateCoordinates();
	SnakeItem_t* GetSnakeTail();
	SnakeItem_t* GetSnakeItemPrevious( SnakeItem_t* snakeItem );
	uint16_t ChekPosition( int16_t value, int16_t maxValue, int16_t minValue );

private:
	SnakeDirection_t   m_SnakeDirection;
	Display_t*         m_pDisplay;
	int16_t            m_HeadPosX;
    int16_t            m_HeadPosY;
	SnakeItem_t*       m_SnakeHead;
	uint8_t            m_MaxItems;
	bool               m_IsIncrease;
};
#endif