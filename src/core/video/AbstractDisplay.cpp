#include "AbstractDisplay.h"

AbstractDisplay::AbstractDisplay() :
    m_width(0),
    m_height(0),
    m_depth(0),
    m_bytesPerLine(0),
    m_frameBufferSize(0),
    m_fps(0),
    m_vsyncEnabled(false)
{
}

int AbstractDisplay::width() const
{
    return  m_width;
}

int AbstractDisplay::height() const
{
    return  m_height;
}

int AbstractDisplay::depth() const
{
    return m_depth;
}

int AbstractDisplay::bytesPerLine() const
{
    return m_bytesPerLine;
}

void AbstractDisplay::setVsynEnabled(bool enabled)
{
    if (m_vsyncEnabled == enabled)
        return;
    m_vsyncEnabled = enabled;
}

bool AbstractDisplay::vsyncEnabled() const
{
    return m_vsyncEnabled;
}

void AbstractDisplay::updateFpsInfo(int fps)
{
    m_fps = fps;
}

int AbstractDisplay::fpsInfo() const
{
    return m_fps;
}

void AbstractDisplay::blankDisplay(bool on)
{
    uint8_t *data = static_cast<uint8_t *>(displayBuffer());
    int count = m_bytesPerLine * m_height / 10;

    uint8_t color = on ? 0xff : 0x00;
    for (int i = 0; i < count; ++i)
    {
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
        *data++ = color;
    }

    present();
}
