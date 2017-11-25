#ifndef LINE_H
#define LINE_H

#include "Surface.h"
#include "DisplayTypes.h"
#include <stdint.h>

class Line
{
public:
    Line(Surface *surface);

    void setColor(const Color &color);
    void draw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    void drawVertical(uint16_t x, uint16_t y, uint16_t length); // remove
    void drawHorizontal(uint16_t x, uint16_t y, uint16_t length); // remove

private:
    void drawHorizontal322To888A(uint16_t x, uint16_t y, uint16_t length);
    void drawHorizontal888ATo888A(uint16_t x, uint16_t y, uint16_t length);
    void drawHorizontal322To322(uint16_t x, uint16_t y, uint16_t length);

    void drawVertical322To888A(uint16_t x, uint16_t y, uint16_t length);
    void drawVertical888ATo888A(uint16_t x, uint16_t y, uint16_t length);
    void drawVertical322To322(uint16_t x, uint16_t y, uint16_t length);

private:
    uint32_t abs(int32_t value);

private:
    void (*fp_drawHorizontal)(uint16_t x, uint16_t y, uint16_t length);
    void (*fp_drawVertical)(uint16_t x, uint16_t y, uint16_t length);

    Surface *m_surface;
    Color m_color;
};

#endif // LINE_H
