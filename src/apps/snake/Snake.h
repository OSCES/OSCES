#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeItem.h"
#include "KeyboardInterface.h"
#include <stdint.h>

class AbstractDisplay;

class Snake
{
    enum SnakeDirection
    {
        Up,
        Right,
        Down,
        Left,
    };

public:
    Snake(uint8_t itemSize, uint8_t snakeLenght, AbstractDisplay *display = 0);
    ~Snake();

    void initialize();
    void run();

    static void keyEventHandler(void *context, const KeyEvent &event);
    void keyEvent(const KeyEvent &keyEvent);

private:
    void addItem();

    void updateCoordinates();
    uint16_t chekPosition(int16_t value, int16_t maxValue, int16_t minValue);

    SnakeItem* prevItem(SnakeItem* nextItem);

private:
    AbstractDisplay *m_display;
    SnakeItem *m_head;
    SnakeItem *m_tail;
    SnakeDirection m_direction;
    int16_t m_headPosX;
    int16_t m_headPosY;
    uint16_t m_maxLength;
    uint16_t m_itemSize;
    uint16_t m_snakeLenght;
};

#endif
