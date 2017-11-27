#include "DisplayPlatform.h"
#include <math.h>

/*
#define RED(x)   (8 * (x) / 255)
#define GREEN(x) (8 * (x) / 255)
#define BLUE(x)  (4 * (x) / 255)
*/

static const uint8_t BitsPerPixel = sizeof(uint8_t);

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

void DisplayPlatform::setTitle(const char* title)
{
}

bool DisplayPlatform::init(uint16_t width, uint16_t height, bool vsyncEnabled)
{
    m_DisplayBuffer = PrimaryBuffer;
    m_width = width;
    m_height = height;
    m_bufferSize = m_width * m_height * BitsPerPixel;

    m_externalSram.setMemoryDataWidth(Fsmc::MemoryDataWidth_8bit);
    m_externalSram.sramControllerInit();
}

void* DisplayPlatform::frameBuffer()
{
    return m_externalSram.pointerBank1() + m_bufferSize * m_DisplayBuffer;
}

void DisplayPlatform::drawPixel(uint16_t x, uint16_t y)
{
}

void DisplayPlatform::drawPixel(uint16_t x, uint16_t y, const Color &color)
{
}

void DisplayPlatform::drawPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t *data = frameBuffer();
    data += m_width * y + x * BitsPerPixel;

    PixelStruct pixel;
    pixel.red   = RedGreenColorValue[r];
    pixel.green = RedGreenColorValue[g];
    pixel.blue  = BlueColorValue[b];

    *data = *static_cast<uint8_t *>(&pixel);
}

void DisplayPlatform::fill(uint16_t x, uint16_t y)
{
}

void DisplayPlatform::fill(uint16_t x, uint16_t y, const Color &color)
{
}

void DisplayPlatform::flip()
{
    m_DisplayBuffer = (m_DisplayBuffer == PrimaryBuffer) ? BackBuffer : PrimaryBuffer;
    selectBuffer(m_DisplayBuffer);
}

uint32_t DisplayPlatform::height() const
{
    return m_height;
}

uint32_t DisplayPlatform::width() const
{
    return m_width;
}

void DisplayPlatform::clear()
{
    uint8_t *data = frameBuffer();
    uint32_t len = m_width * m_height / 10;

    for (uint32_t i = 0; i < len; ++i)
    {
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
        *data++ = 0;
    }
}

DisplayPlatform::DisplayPlatform() :
    m_bufferSize(0),
    m_width(0),
    m_height(0)
{
}

DisplayPlatform::DisplayPlatform(int width, int height)
{
    init(width, height, false);
}

DisplayPlatform::~DisplayPlatform()
{
    //delete m_pFrame;
}

void DisplayPlatform::selectBuffer( DisplayBuffer buffer )
{
    uint8_t *data = m_externalSram.pointerBank1();
    data += 0x0007FFFF;

    if (buffer == PrimaryBuffer)
        *data |= 0x01;
    else
        *data &= ~0x01;
}

void DisplayPlatform::setMousePos(uint16_t x, uint16_t y)
{
    uint8_t* data = m_externalSram.pointerBank1();
    data += 0x0007FFFE;
    *data = x;
}

void DisplayPlatform::present(PixelStruct *data)
{
}
