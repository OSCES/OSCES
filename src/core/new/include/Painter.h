#ifndef PAINTER_H
#define PAINTER_H

#include <stdint.h>


struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Point
{
    int x;
    int y;
};

struct Rect
{
    int x1;
    int y1;
    int x2;
    int y2;
};


class Screen;

struct PainterPrivate;

class Painter
{
public:
    Painter();
    Painter(Screen *screen);
    ~Painter();

    void setScreen(Screen *screen);
    Screen* screen() const;

    void setPenColor(const Color &color);

    // drawing functions
    void drawPoint(const Point &point);
    void drawPoint(int x, int y);

    void drawLine(const Point &p1, const Point &p2);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawRect(const Rect &rect);

    void fillRect(const Rect &rect);

private:
    PainterPrivate *d_ptr;
};

#endif // PAINTER_H
