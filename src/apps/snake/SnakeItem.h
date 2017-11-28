#ifndef SNAKEITEM_H
#define SNAKEITEM_H

#include <stdint.h>

class Snake;
class PaintEngine;

class SnakeItem
{
    friend class Snake;

public:
    SnakeItem(uint16_t size);

    void setNext(SnakeItem* next);
    SnakeItem* next() const { return m_next; }

    void move(uint16_t x, uint16_t y);
    void redraw(PaintEngine *paintEngine);

private:
    SnakeItem *m_next;
    uint16_t m_itemSize;
    uint16_t m_x;
    uint16_t m_y;
};

#endif // SNAKEITEM_H
