#ifndef DISPLAY_PLATFORM_H
#define DISPLAY_PLATFORM_H

#include <stdint.h>
#include "Display.h"
#include "FsmcDriver.h"

enum DisplayBuffer
{
    PrimaryBuffer,
    BackBuffer
};

class DisplayPlatform : public Display
{
public:
    DisplayPlatform();
    DisplayPlatform(int width, int height);
    ~DisplayPlatform();

    bool init(uint16_t width, uint16_t height, bool vsyncEnabled );
    void drawPixel(uint16_t x, uint16_t y);
    void drawPixel(uint16_t x, uint16_t y, const Color& color);
    void drawPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b); // compability issue
    void* frameBuffer();
    void clear();
    void setTitle(const char* title); // TODO: remove this fn
    void flip();
    uint32_t height() const;
    uint32_t width() const;

    void fill(uint16_t x, uint16_t y);
    void fill(uint16_t x, uint16_t y, const Color& color);

public:
    void setMousePos(uint16_t x, uint16_t y);
    void present(PixelStruct *data);

private:
    void selectBuffer(DisplayBuffer buffer);

private:
    DisplayBuffer m_DisplayBuffer;
    Fsmc m_externalSram;
    uint16_t m_width;
    uint16_t m_height;
    uint32_t m_bufferSize;
};

#endif // DISPLAY_H


