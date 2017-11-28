#include "Color.h"

Color::Color() :
    m_red(0),
    m_green(0),
    m_blue(0),
    m_alpha(255)
{}

Color::Color(GlobalColor color)
{
#define MAKER_COLOR(r, g, b, a) \
    m_red = r; \
    m_green = g; \
    m_blue = b; \
    m_alpha = a; \

    switch (color)
    {
    case GlobalColor::black:  MAKER_COLOR(0x00, 0x00, 0x00, 0xFF); break;
    case GlobalColor::white:  MAKER_COLOR(0xFF, 0xFF, 0xFF, 0xFF); break;
    case GlobalColor::red:    MAKER_COLOR(0xFF, 0x00, 0x00, 0xFF); break;
    case GlobalColor::green:  MAKER_COLOR(0x00, 0xFF, 0x00, 0xFF); break;
    case GlobalColor::blue:   MAKER_COLOR(0x00, 0x00, 0xFF, 0xFF); break;
    case GlobalColor::yellow: MAKER_COLOR(0xFF, 0xFF, 0x00, 0xFF); break;
    default:
        ;
    }

#undef MAKER_COLOR
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    m_red(r),
    m_green(g),
    m_blue(b),
    m_alpha(a)
{}

Color::~Color()
{
}

uint8_t Color::red() const
{
    return m_red;
}

uint8_t Color::green() const
{
    return m_green;
}

uint8_t Color::blue() const
{
    return m_blue;
}

uint8_t Color::alpha() const
{
    return m_alpha;
}
