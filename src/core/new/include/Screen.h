#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

// move to separate file
struct ScreenPrivate
{
    int width;
    int height;
    int bytesPerLine;

    // direct memory access
    uint8_t *data;
};

class Screen
{
public:
    Screen();
    virtual ~Screen();

    // init video device
    virtual bool initialize() = 0;

    // switch buffers
    virtual void present() = 0;

    // geometry
    int width() const;
    int height() const;

    uint8_t* bits() const;
    int bytesPerLine() const;

protected:
    ScreenPrivate *d_ptr;
};

#endif // SCREEN_H
