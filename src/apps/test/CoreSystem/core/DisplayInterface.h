#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

typedef unsigned int Rgb;                        // RGB triplet

inline Rgb rgb(int r, int g, int b)// set RGB value
{ return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }

class DisplayInterface
{
public:
    virtual int width() = 0;
    virtual int height() = 0;

    virtual void drawLine(int x1, int y1, int x2, int y2, Rgb color = rgb(255, 255, 255)) = 0;
    virtual void drawRect(int x, int y, int w, int h, Rgb color = rgb(255, 255, 255)) = 0;

    virtual ~DisplayInterface() {}
};

#endif // DISPLAYINTERFACE_H
