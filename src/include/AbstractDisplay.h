#ifndef ABSTRACTDISPLAY_H
#define ABSTRACTDISPLAY_H

#include <stdint.h>

class AbstractDisplay
{
public:
    enum DisplayBufferType
    {
        FrontBuffer, // buffer that is currently showing on the LCD
        BackBuffer   // alway hiden buffer
    };

    AbstractDisplay();
    virtual ~AbstractDisplay() {}

    virtual bool initialize() = 0;
    virtual uint8_t* displayBuffer(DisplayBufferType bufferType = BackBuffer) = 0;

    // present data contained in BackBuffer
    virtual void present() = 0;

    int width() const;
    int height() const;
    int depth() const;
    int bytesPerLine() const;

    void setVsynEnabled(bool enabled);
    bool vsyncEnabled() const;

    void updateFpsInfo(int fps);
    int fpsInfo() const;

protected:
    void blankDisplay(bool on);

protected:
    // TODO: hide impl
    int m_width;
    int m_height;
    int m_depth;
    int m_bytesPerLine;
    int m_frameBufferSize;
    int m_fps;
    bool m_vsyncEnabled;
};

#endif // ABSTRACTDISPLAY_H
