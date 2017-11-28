#include "PaintEngine.h"

#include "AbstractDisplay.h"

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

PaintEngine::PaintEngine() :
    m_display(0)
{
}

PaintEngine::PaintEngine(AbstractDisplay *display) :
    m_display(display)
{
    drawBegin(m_display);
}

PaintEngine::~PaintEngine()
{
    drawEnd();
}

void PaintEngine::drawBegin(AbstractDisplay *display)
{
    if (m_display == display)
        return;
    m_display = display;
}

void PaintEngine::drawEnd()
{
    if (!m_display)
        return;
    m_display->present();
}

void PaintEngine::setPenColor(const Color &color)
{
#ifdef OSCES_BOARD
    m_pixelData.red = RedGreenColorValue[color.red()];
    m_pixelData.green = RedGreenColorValue[color.green()];
    m_pixelData.blue = BlueColorValue[color.blue()];
#else
    m_pixelData.red = color.red();
    m_pixelData.green = color.green();
    m_pixelData.blue = color.blue();
    m_pixelData.alfa = color.alpha();
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
    PixelStruct *pixel = pixelAddress(x, y);
    *pixel = m_pixelData;
}

inline void PaintEngine::drawLine(const Point &p1, const Point &p2)
{
    drawLine(p1.x, p1.y, p2.x, p2.y);
}

//#define abs(x) (x) > 0 ? (x) : (-(x))
static inline int abs(const int &a)
{
    return a > 0 ? a : -a;
}

static inline void swap(int &a, int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
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

    PixelStruct *pixel = pixelAddress(x, y);
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
    PixelStruct *pixel = pixelAddress(x1, y1);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
            *pixel++ = m_pixelData;
        pixel += lineOffset;
    }
}

void PaintEngine::drawText(int x, int y, const char *text)
{
    if (!m_display)
        return;

    // TODO:
    PixelStruct *pixel = pixelAddress(x, y);
    (void)pixel;
    (void)text;
}

inline PixelStruct* PaintEngine::pixelAddress(int x, int y) const
{
    if (!m_display)
        return 0;

    // not efficient
    bool xValid = x >= 0 && x < m_display->width();
    bool yValid = y >= 0 || y < m_display->height();
    if (!xValid || !yValid)
        return 0; // nothing to draw

    PixelStruct *data = reinterpret_cast<PixelStruct *>(m_display->displayBuffer());
    int dataOffset = m_display->width() * y + x;

    // TODO: think about depth
    // make more flexible
    return  data + dataOffset;
}
