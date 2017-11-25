#include "GraphicalPrimitives/Line.h"
#include <math.h>

Line::Line(Surface* surface) :
    m_surface(surface)
{
    // Ugly code do not use call black
    switch (m_surface->pixelFormat())
    {
    case DISPLAY_PIXEL_FORMAT_RGB888:
        //TODO:
        break;
    case DISPLAY_PIXEL_FORMAT_RGBA8888:
        fp_drawHorizontal = drawHorizontal888ATo888A;
        fp_drawVertical = drawVertical888ATo888A;
        break;
    case DISPLAY_PIXEL_FORMAT_RGB332:
        //TODO:
        break;
    default:
        fp_drawHorizontal = drawHorizontal888ATo888A;
        fp_drawVertical = drawVertical888ATo888A;
        break;
    }

    m_color = Color(GlobalColor::white);
}

void Line::setColor(const Color &color)
{
    m_color = color;
}

uint32_t Line::abs(int32_t value)
{
    // TODO: optimize
    return value < 0 ? -value : value;
}

void Line::draw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 )
{
    int denumerator = 0;
    int numerator = 0;
    int numAdd = 0;

    int xInc1 = (x2 >= x1) ? 1 : -1;
    int yInc1 = (y2 >= y1) ? 1 : -1;

    int xInc2 = xInc1;
    int yInc2 = yInc1;

    uint32_t deltaX = abs(x2 - x1);
    uint32_t deltaY = abs(y2 - y1);
    uint32_t pixelsCount = 0;
    if (deltaX >= deltaY) // There is at least one x-value for every y-value
    {
        xInc1 = 0; // Don't change the x when numerator >= denominator
        yInc2 = 0; // Don't change the y for every iteration
        denumerator = deltaX;
        numerator = deltaX / 2;
        numAdd = deltaY;
        pixelsCount = deltaX; // There are more x-values than y-values
    }
    else // There is at least one y-value for every x-value
    {
        xInc2 = 0; // Don't change the x for every iteration
        yInc1 = 0; // Don't change the y when numerator >= denominator
        denumerator = deltaY;
        numerator = deltaY / 2;
        numAdd = deltaX;
        pixelsCount = deltaY; // There are more y-values than x-values
    }

    PixelStructRGBA8888 pixel;
    pixel.red   = m_color.red();
    pixel.green = m_color.green();
    pixel.blue  = m_color.blue();

    int xPos = x1;
    int yPos = y1;

    uint32_t width = m_surface->width();
    uint32_t height= m_surface->height();
    PixelStructRGBA8888 *frameBuffer = static_cast<PixelStructRGBA8888 *>(m_surface->frameBuffer());

    for (uint32_t i = 0; i <= pixelsCount; ++i)
    {
        uint32_t offset = xPos % width + width * (yPos % height);
        *(frameBuffer + offset) = pixel;

        numerator += numAdd;  //Increase the numerator by the top of the fraction

        if (numerator >= denumerator)
        {
            numerator -= denumerator; //Calculate the new numerator value
            xPos += xInc1;
            yPos += yInc1;
        }
        xPos += xInc2;
        yPos += yInc2;
    }
}

void Line::drawVertical(uint16_t x, uint16_t y, uint16_t length )
{
    fp_drawVertical(x, y, length);
}

void Line::drawHorizontal(uint16_t x, uint16_t y, uint16_t length )
{
    fp_drawHorizontal(x, y, length);
}

// ----------------------------------------- Drawing factory -----------------------------------------
void Line::drawHorizontal888ATo888A(uint16_t x, uint16_t y, uint16_t length)
{
    // WTF? Why we need this convert?
    PixelStructRGBA8888 pixel;
    pixel.red = m_color.red();
    pixel.green = m_color.green();
    pixel.blue = m_color.blue();

    PixelStructRGBA8888 *frameBuffer = static_cast<PixelStructRGBA8888 *>(m_surface->frameBuffer());
    frameBuffer += m_surface->width() * y + x;

    for (uint32_t i = 0; i < length; ++i, ++frameBuffer)
        *frameBuffer = pixel;
}

void Line::drawHorizontal322To322(uint16_t x, uint16_t y, uint16_t length)
{
}

void Line::drawHorizontal322To888A(uint16_t x, uint16_t y, uint16_t length)
{
}

void Line::drawVertical322To888A(uint16_t x, uint16_t y, uint16_t length)
{
}

void Line::drawVertical888ATo888A(uint16_t x, uint16_t y, uint16_t length)
{
}

void Line::drawVertical322To322(uint16_t x, uint16_t y, uint16_t length)
{
}
