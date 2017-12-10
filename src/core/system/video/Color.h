#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

enum GlobalColor
{
    black,
    white,
    red,
    green,
    blue,
    yellow
};

class Color
{
public:
    Color();
    Color(GlobalColor color);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    ~Color();

    uint8_t red() const;
    uint8_t green() const;
    uint8_t blue() const;
    uint8_t alpha() const;

private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

#endif // COLOR_H
