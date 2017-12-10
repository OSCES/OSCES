#ifndef _SNAKE_ITEM_H_
#define _SNAKE_ITEM_H_

#include <stdint.h>

class Snake;
class DisplayInterface;

class SnakeItem
{
    friend class Snake;

public:
    SnakeItem(DisplayInterface* display, uint16_t size);

    void setNext(SnakeItem* next);
    SnakeItem* next() const { return m_next; }

    void move(uint16_t x, uint16_t y);
    void redraw();

private:
    DisplayInterface *m_display;
    SnakeItem *m_next;
    uint16_t m_itemSize;
    uint16_t m_x;
    uint16_t m_y;
};

#endif
