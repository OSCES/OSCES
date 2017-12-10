#include "Snake.h"
#include "DisplayInterface.h"

Snake::Snake() :
    m_head(0),
    m_tail(0),
    m_display(0),
    m_direction(Right),
    m_headPosX(0),
    m_headPosY(0),
    m_maxLength(1000),
    m_itemSize(10),
    m_snakeLenght(4)
{
}

Snake::Snake(uint8_t itemSize, uint8_t snakeLenght) :
    m_head(0),
    m_tail(0),
    m_display(0),
    m_direction(Right),
    m_headPosX(10),
    m_headPosY(5),
    m_maxLength(1000),
    m_itemSize(itemSize),
    m_snakeLenght(snakeLenght)
{
}

Snake::~Snake()
{
    do
    {
        SnakeItem *item = m_head;
        m_head = item->next();
        delete item;
    }
    while (m_head);
}

void Snake::initialize()
{
    m_head = new SnakeItem(m_display, m_itemSize);
    m_head->move(m_headPosX, m_headPosY);
    m_tail = m_head;
    for (uint8_t idx = 0; idx < m_snakeLenght; ++idx)
        addItem();
}

void Snake::addItem()
{
    SnakeItem* snakeItem = new SnakeItem(m_display, m_itemSize);
    snakeItem->move(m_tail->m_x, m_tail->m_y);
    m_tail->setNext(snakeItem);
    m_tail = snakeItem;
}

void Snake::setDisplay(DisplayInterface *display)
{
    if (m_display == display)
        return;
    m_display = display;
}

void Snake::keyPressEvent(int key)
{
    switch (key) {
    case Key_Up: m_direction = Up; break;
    case Key_Right: m_direction = Right; break;
    case Key_Down: m_direction = Down; break;
    case Key_Left: m_direction = Left; break;
    default:
        ;
    }
}

uint16_t Snake::chekPosition(int16_t value, int16_t maxValue, int16_t minValue)
{
    uint16_t retValue = value;

    if (value >= maxValue)
        retValue = 0;
        
    if (value < minValue)
        retValue = maxValue - 1;

    return retValue;
}

void Snake::updateCoordinates()
{
    switch (m_direction)
    {
    case Left:  --m_headPosX; break;
    case Right: ++m_headPosX; break;
    case Up:    --m_headPosY; break;
    case Down:  ++m_headPosY; break;
    };

    m_headPosX = chekPosition(m_headPosX, m_display->width() / m_itemSize, 0);
    m_headPosY = chekPosition(m_headPosY, m_display->height() / m_itemSize, 0);
}

SnakeItem* Snake::prevItem(SnakeItem* nextItem)
{
    SnakeItem *item = m_head;
    while (item->next() != nextItem)
        item = item->next();
    return item;
}

void Snake::run()
{
    updateCoordinates();

    SnakeItem *prevItem = this->prevItem(m_tail);
    prevItem->setNext(0);

    m_head->move(m_headPosX, m_headPosY);
    m_tail->move(m_head->m_x, m_head->m_y);
    m_tail->setNext(m_head->next());
    m_head->setNext(m_tail);
    m_tail = prevItem;

    SnakeItem *item = m_head;
    while (item)
    {
        item->redraw();
        item = item->next();
    }
}
