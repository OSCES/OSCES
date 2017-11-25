#ifndef _SNAKE_H_
#define _SNAKE_H_


#include  "SnakeItem.h"

enum SnakeDirection_t
{
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Snake_t
{
public:
    void SetDirection( SnakeDirection_t direction );
    void Init( DisplayInterface_t* pDisplay );

    void Increase();
    void Run( void );
    ~Snake_t();
    Snake_t();
    Snake_t( uint8_t itemSize, uint8_t itemStartAmount );

private:
    void AddItem();
    void UpdateCoordinates();
    SnakeItem_t* GetSnakeTail();
    SnakeItem_t* GetSnakeItemPrevious( SnakeItem_t* snakeItem );
    uint16_t ChekPosition( int16_t value, int16_t maxValue, int16_t minValue );
    void InitDefault();
    
private:
    SnakeDirection_t    m_SnakeDirection;
    DisplayInterface_t* m_pDisplay;
    SnakeItem_t*        m_pSnakeHead;
  
private:    
    int16_t             m_HeadPosX;
    int16_t             m_HeadPosY;
    uint16_t            m_MaxItems;
    bool                m_IsIncrease;
    uint16_t            m_ItemSize;
    uint16_t            m_ItemAmount;
};
#endif