#ifndef DISPLAY_TYPES
#define DISPLAY_TYPES

#include <stdint.h>

#define COLOR_DEFAULT_RED   0xFF
#define COLOR_DEFAULT_GREEN 0xFF
#define COLOR_DEFAULT_BLUE  0xFF
#define COLOR_DEFAULT_ALPHA 0xFF

struct PixelStruct
{
    uint8_t blue  : 2;
    uint8_t green : 3;
    uint8_t red   : 3;
};

struct PixelStructRGBA8888
{
    uint32_t alpha : 8;
    uint32_t blue  : 8;
    uint32_t green : 8;
    uint32_t red   : 8;
};

enum PixelFormat
{
    DISPLAY_PIXEL_FORMAT_RGB888,
    DISPLAY_PIXEL_FORMAT_RGBA8888,
    DISPLAY_PIXEL_FORMAT_RGB332,
    DISPLAY_PIXEL_FORMAT_DEFAULT
};

// ???
enum DisplayRectFormat
{
};

struct DisplayBitmap
{
    PixelFormat pixelFormat;
    uint32_t height;
    uint32_t width;

    union
    {
        uint32_t *pDataUint32;
        void *pBitmap;
        PixelStructRGBA8888 *pBitmapRGBA8888;
    };
};

typedef uint32_t Rgb;

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
    Color() :
        m_red(0), m_green(0), m_blue(0), m_alpha(255)
    {}

    Color(GlobalColor color)
    {
        // TODO:
    }

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
        m_red(r), m_green(g), m_blue(b), m_alpha(a)
    {}

    Color(Rgb rgb)
    {}

    uint8_t red() { return m_red; }
    uint8_t green() { return m_green; }
    uint8_t blue() { return m_blue; }
    uint8_t alpha() { return m_alpha; }

private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

#endif // DISPLAY_TYPES
