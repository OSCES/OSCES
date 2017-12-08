#include "PaintEngine.h"
#include "AbstractDisplay.h"

#ifndef OSCES_BOARD
#include <assert.h>
#endif

static const uint8_t RedGreenColorValue[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static const uint8_t BlueColorValue[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

//static inline int abs(const int &a)
//{
//    return a > 0 ? a : -a;
//}

//static inline void swap(int &a, int &b)
//{
//    a ^= b;
//    b ^= a;
//    a ^= b;
//}

#define abs(x) ((x) > 0 ? (x) : -(x))
#define swap(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y))

PaintEngine::PaintEngine() :
    m_display(0),
    m_displayData(0),
    m_displayWidth(0),
    m_displayHeight(0)
{
}

PaintEngine::PaintEngine(AbstractDisplay *display)
{
    drawBegin(display);
}

PaintEngine::~PaintEngine()
{
    drawEnd();
}

void PaintEngine::drawBegin(AbstractDisplay *display)
{
    if (m_display)
        return;

    m_display = display;
    m_displayWidth = m_display->width();
    m_displayHeight = m_display->height();
    m_displayData = display->displayBuffer();
}

void PaintEngine::drawEnd()
{
    if (!m_display)
        return;

    // flip buffers
    m_display->present();

    m_display = 0;
    m_displayWidth = 0;
    m_displayHeight = 0;
    m_displayData = 0;
}

void PaintEngine::setPenColor(const Color &color)
{
#ifdef OSCES_BOARD
    m_penData.red = RedGreenColorValue[color.red()];
    m_penData.green = RedGreenColorValue[color.green()];
    m_penData.blue = BlueColorValue[color.blue()];
#else
    m_pixel.red = color.red();
    m_pixel.green = color.green();
    m_pixel.blue = color.blue();
    m_pixel.alfa = color.alpha();
#endif
}

void PaintEngine::drawPixel(const Point &point)
{
    drawPixel(point.x, point.y);
}

void PaintEngine::drawPixel(int x, int y)
{
    if (!m_display)
        return;

    // let compiler optimize it
    PixelStruct *pixel = pixelAt(x, y);
    *pixel = m_pixel;
}

inline void PaintEngine::drawLine(const Point &p1, const Point &p2)
{
    drawLine(p1.x, p1.y, p2.x, p2.y);
}

void PaintEngine::drawLine(int x1, int y1, int x2, int y2)
{
    if (!m_display)
        return;

    // Bresenham's line algorithm

    bool steep = false;
    if (abs(x1 - x2) < abs(y1 - y2))
    {
        swap(x1, y1);
        swap(x2, y2);
        steep = true;
    }

    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y1;
    for (int x = x1; x <= x2; ++x)
    {
        if (steep)
            drawPixel(y, x);
        else
            drawPixel(x, y);

        error2 += derror2;

        if (error2 > dx)
        {
            y += (y2 > y1 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

inline void PaintEngine::drawRect(const Rect &rect)
{
    drawRect(rect.x1, rect.y1, rect.x2, rect.y2);
}

void PaintEngine::drawRect(int x1, int y1, int x2, int y2)
{
    if (!m_display)
        return;

    drawLine(x1, y1, x2, y1); // right
    drawLine(x2, y1, x2, y2); // down
    drawLine(x2, y2, x1, y2); // left
    drawLine(x1, y2, x1, y1); // up
}

inline void PaintEngine::drawBitmap(const Point &point, const Bitmap &bitmap)
{
    drawBitmap(point.x, point.y, bitmap);
}

void PaintEngine::drawBitmap(int x, int y, const Bitmap &bitmap)
{
    if (!m_display)
        return;

    PixelStruct *pixel = pixelAt(x, y);
    if (!pixel)
        return;

    int displayWidth = m_display->width();
    int bitmapOffset = 0;
    int pixelOffset = 0;
    for (int j = 0; j < bitmap.height; ++j)
    {
        for (int i = 0; i < bitmap.width; ++i)
            pixel[pixelOffset++] = bitmap.bitmapData[bitmapOffset++];

        bitmapOffset += bitmap.width;
        pixel += displayWidth;
    }
}

inline void PaintEngine::fillRect(const Rect &rect)
{
    fillRect(rect.x1, rect.y1, rect.x2, rect.y2);
}

void PaintEngine::fillRect(int x1, int y1, int x2, int y2)
{
    if (!m_display)
        return;

    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;
    int lineOffset = m_display->width() - width;
    PixelStruct *pixel = pixelAt(x1, y1);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
            *pixel++ = m_pixel;
        pixel += lineOffset;
    }
}

void PaintEngine::drawText(int x, int y, const char *text)
{
    if (!m_display)
        return;

    // TODO:
    PixelStruct *pixel = pixelAt(x, y);
    (void)pixel;
    (void)text;
}

inline PixelStruct* PaintEngine::pixelAt(int x, int y) const
{
#ifndef OSCES_BOARD
    assert(m_display != 0);
#endif

    // not efficient
    bool xValid = x >= 0 && x < m_displayWidth;
    bool yValid = y >= 0 || y < m_displayHeight;
    if (!xValid || !yValid)
        return 0; // nothing to draw

    PixelStruct *data = reinterpret_cast<PixelStruct *>(m_displayData);
    int dataOffset = m_displayWidth * y + x;

    // TODO: think about depth
    // make more flexible
    return  data + dataOffset;
}
