#include "SnakeItem.h"
#include "PaintEngine.h"
#include <assert.h>

SnakeItem::SnakeItem(uint16_t size) :
    m_next(0),
    m_itemSize(size),
    m_x(0),
    m_y(0)
{
}

void SnakeItem::redraw(PaintEngine *paintEngine)
{
    assert(paintEngine != 0);

    int x1 = m_x * m_itemSize;
    int y1 = m_y * m_itemSize;
    int x2 = x1 + m_itemSize - 2;
    int y2 = y1 + m_itemSize - 2;

    paintEngine->drawRect(x1, y1, x2, y2);
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
