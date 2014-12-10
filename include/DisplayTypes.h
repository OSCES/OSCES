#ifndef DISPLAY_TYPES
#define DISPLAY_TYPES


#include <stdint.h>


struct PixelStruct_t
{
  uint8_t Red   : 3;
  uint8_t Green : 3;
  uint8_t Blue  : 2;
};

struct PixelStructRGBA8888_t
{
  uint32_t Red   : 8;
  uint32_t Green : 8;
  uint32_t Blue  : 8;
  uint32_t Alpha : 8;
};

enum DisplayPixelFormat_t
{
    DISPLAY_PIXEL_FORMAT_RGB888  ,
    DISPLAY_PIXEL_FORMAT_RGBA8888,
    DISPLAY_PIXEL_FORMAT_RGB332
};

enum DisplayRectFormat_t
{

};

struct DisplayBitmap_t
{
    DisplayPixelFormat_t PixelFormat;
    uint32_t             Height;
    uint32_t             Width;

    union
    {
        uint32_t* pDataUint32;
        void*     pBitmap;
        PixelStructRGBA8888_t* pBitmapRGBA8888;

    };

};

struct Color_t
{
    Color_t() {};
	Color_t( uint8_t red, uint8_t green, uint8_t blue ) :
		Red(red), Green(green), Blue(blue)
	{}

	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};

#endif // DISPLAY_TYPES