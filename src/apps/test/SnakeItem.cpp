#include "SnakeItem.h"
#include "DisplayInterface.h"

SnakeItem::SnakeItem(DisplayInterface* display, uint16_t size) :
    m_display(display),
    m_next(0),
    m_itemSize(size),
    m_x(0),
    m_y(0)
{
}

void SnakeItem::redraw()
{
    m_display->drawRect(m_x * m_itemSize, m_y * m_itemSize, m_itemSize - 2, m_itemSize - 2);
}

void SnakeItem::move(uint16_t x, uint16_t y)
{
    m_x = x;
    m_y = y;
}

void SnakeItem::setNext(SnakeItem* next)
{
    m_next = next;
}
