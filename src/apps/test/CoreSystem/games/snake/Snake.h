#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "SnakeItem.h"
#include "GameInterface.h"

#include <stdint.h>

class Snake : public GameInterface
{
    enum SnakeDirection
    {
        Up,
        Right,
        Down,
        Left,
    };

public:
    Snake();
    Snake(uint8_t itemSize, uint8_t snakeLenght);
    ~Snake();

    void setDisplay(DisplayInterface *display);
    void initialize();

    void run();
    void keyPressEvent(int key);

private:
    void addItem();

    void updateCoordinates();
    uint16_t chekPosition(int16_t value, int16_t maxValue, int16_t minValue);

    SnakeItem* prevItem(SnakeItem* nextItem);

private:
    SnakeItem *m_head;
    SnakeItem *m_tail;
    DisplayInterface *m_display;
    SnakeDirection m_direction;
    int16_t m_headPosX;
    int16_t m_headPosY;
    uint16_t m_maxLength;
    uint16_t m_itemSize;
    uint16_t m_snakeLenght;
};

#endif
