#ifndef PAINTENGINE_H
#define PAINTENGINE_H

#include "Color.h"
#include <stdint.h>

//struct Color
//{
//    uint8_t r;
//    uint8_t g;
//    uint8_t b;
//    uint8_t a;
//};

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

struct PixelStruct // maybe it better to use Rgb
{
#ifdef OSCES_BOARD
    uint8_t blue  : 2;
    uint8_t green : 3;
    uint8_t red   : 3;
#else
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alfa;
#endif
};

struct Bitmap
{
    int width;
    int height;
    int bytesPerLine;
    PixelStruct *bitmapData;
};

class AbstractDisplay;

class PaintEngine
{
public:
    PaintEngine();

    // call this constructor only for scoped using
    PaintEngine(AbstractDisplay *display);
    ~PaintEngine();

    // init draw device
    void drawBegin(AbstractDisplay *display);
    void drawEnd();

    void setPenColor(const Color &color);

    // drawing functions
    inline void drawPixel(const Point &point); // very slow function
    void drawPixel(int x, int y); // very slow function

    inline void drawLine(const Point &p1, const Point &p2);
    void drawLine(int x1, int y1, int x2, int y2);
    inline void drawRect(const Rect &rect);
    void drawRect(int x1, int y1, int x2, int y2);

    inline void drawBitmap(const Point &point, const Bitmap &bitmap);
    void drawBitmap(int x, int y, const Bitmap &bitmap);

    inline void fillRect(const Rect &rect);
    void fillRect(int x1, int y1, int x2, int y2);

    void drawText(int x, int y, const char *text);

private:
    inline PixelStruct* pixelAt(int x, int y) const;

private:
    PixelStruct m_pixel;
    AbstractDisplay *m_display;
    uint8_t *m_displayData;
    int m_displayWidth;
    int m_displayHeight;

};

#endif // PAINTENGINE_H
