#include  "Snake.h"


void Snake_t::SetDirection( SnakeDirection_t direction )
{
    if( NONE != direction )
    {
        m_SnakeDirection = direction;
    }
}

void Snake_t::InitDefault()
{
    m_ItemSize       = 10;
    m_HeadPosX       = 0;
    m_HeadPosY       = 5;
    m_pSnakeHead     = 0;
    m_SnakeDirection = RIGHT;
    m_MaxItems       = 1000;
    m_IsIncrease     = false;
    m_ItemAmount     = 7;
}

Snake_t::Snake_t()
{
    InitDefault();
}

Snake_t::Snake_t( uint8_t itemSize, uint8_t itemStartAmount )
{
    InitDefault();
    m_ItemSize   = itemSize;
    m_ItemAmount = itemStartAmount;
}

Snake_t::~Snake_t()
{
    for( uint8_t idx = 0; idx < m_MaxItems; idx ++ )
    {
        if( 0 == m_pSnakeHead->GetNext() ) //Is Tail?
        {
            break;
        }

        SnakeItem_t* snakeItemNext = m_pSnakeHead->GetNext();
        delete m_pSnakeHead;
        m_pSnakeHead = snakeItemNext;
    }

    delete m_pSnakeHead;
}

SnakeItem_t* Snake_t::GetSnakeTail()
{
    SnakeItem_t* snakeItem = m_pSnakeHead;
    SnakeItem_t* snakeTail = 0;

    for( uint8_t idx = 0; idx < m_MaxItems; idx ++ )
    {
        if( 0 == snakeItem->GetNext() ) //Is Tail?
        {
            snakeTail = snakeItem;
            break;
        }

        snakeItem = snakeItem->GetNext();
    }

    return snakeTail;
}


SnakeItem_t* Snake_t::GetSnakeItemPrevious( SnakeItem_t* snakeItem )
{
    SnakeItem_t* snakeItemCollection = m_pSnakeHead;
    SnakeItem_t* snakeItemPrevious = 0;

    for( uint8_t idx = 0; idx < m_MaxItems; idx ++ )
    {
        if( snakeItem == snakeItemCollection->GetNext() )
        {
            snakeItemPrevious = snakeItemCollection;
            break;
        }

        snakeItemCollection = snakeItemCollection->GetNext();
    }

    return snakeItemPrevious;
}

void Snake_t::AddItem()
{
    SnakeItem_t* snakeItem = new SnakeItem_t( m_pDisplay, m_ItemSize );

    if( 0 == m_pSnakeHead )
    {
        m_pSnakeHead = snakeItem;
    }

    snakeItem->Move( m_HeadPosX, m_HeadPosY );

    SnakeItem_t* snakeTail = GetSnakeTail();
    
    snakeTail->SetNext( snakeItem );
    
    snakeItem->SetNext( 0 );
}

void Snake_t::Init( DisplayInterface_t* pDisplay )
{
    m_pDisplay = pDisplay;


    for( uint8_t idx = 0; idx < m_ItemAmount; idx ++ )
    {
        AddItem();
    }
}

void Snake_t::Increase()
{
    m_IsIncrease = true;
}

uint16_t Snake_t::ChekPosition( int16_t value, int16_t maxValue, int16_t minValue )
{
    uint16_t retValue = value;

    if( value >= maxValue )
    {
        retValue = 0;
    }
        
    if( value < minValue )
    {
        retValue = maxValue - 1;
    }

    return retValue;
}

void Snake_t::UpdateCoordinates()
{
    switch( m_SnakeDirection )
    {
        case LEFT:
            m_HeadPosX --;
        break;

        case RIGHT:
            m_HeadPosX ++;
        break;

        case UP:
            m_HeadPosY --;
        break;

        case DOWN:
            m_HeadPosY ++;
        break;
    };

    m_HeadPosX = ChekPosition( m_HeadPosX, 400 / m_ItemSize, 0 );
    m_HeadPosY = ChekPosition( m_HeadPosY, 300 / m_ItemSize, 0 );
}

void Snake_t::Run( void )
{      
    UpdateCoordinates();
        

    if( true == m_IsIncrease )
    {
        m_IsIncrease = false;
        AddItem();
    }

    SnakeItem_t* snakeTail = GetSnakeTail();
        
    snakeTail->SetNext( m_pSnakeHead );
    SnakeItem_t* snakeItemPrevious = GetSnakeItemPrevious( snakeTail );
    snakeItemPrevious->SetNext( 0 );
    snakeTail->Move( m_HeadPosX, m_HeadPosY );
    m_pSnakeHead = snakeTail;

    SnakeItem_t* snakeItem = m_pSnakeHead->GetNext();

    for( uint8_t idx = 0; idx < m_MaxItems; idx ++ )
    {
        snakeItem->Redraw();

        if( 0 == snakeItem->GetNext() ) //Is Tail?
        {
            break;
        }

        snakeItem = snakeItem->GetNext();
    }

}