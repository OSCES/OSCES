#ifndef LCDTYPES_H
#define LCDTYPES_H


#include <stdint.h>


// TODO: Add | Remove commands
enum LcdCommand_t
{
    NOP         = 0x00,     // No Operation
    SWRESET     = 0x01,     // Software Reset
    RDDID       = 0x04,     // Read Display ID
    RDDCOLMOD   = 0x0C,     // Read Display Pixel Format
    RDDIM       = 0x0D,     // Read Display Image Mode
    RDDSM       = 0x0E,     // Read Display Signal Mode
    SLPIN       = 0x10,     // Sleep In
    SLPOUT      = 0x11,     // Sleep Out
    PTLON       = 0x12,     // Partial Display Mode On
    NORON       = 0x13,     // Normal Display Mode On
    INVOFF      = 0x20,     // Display Inversion Off
    INVON       = 0x21,     // Display Inversion On
    GAMSET      = 0x26,     // Gamma Set
    DISPOFF     = 0x28,     // Display Off
    DISPON      = 0x29,     // Display On
    CASET       = 0x2A,     // Column Address Set
    RASET       = 0x2B,     // Row Address Set
    RAMWR       = 0x2C,     // Memory Write
    RAMRD       = 0x2E,     // Memory Read
    PTLAR       = 0x30,     // Partial Area
    TEOFF       = 0x34,     // Tearing Effect Line OFF
    TEON        = 0x35,     // Tearing Effect Line ON
    MADCTR      = 0x36,     // Memory Data Access Control
    IDMOFF      = 0x38,     // Idle Mode Off
    IDMON       = 0x39,     // Idle Mode On
    COLMOD      = 0x3A,     // Interface Pixel Format
    GAMCTR1     = 0xC8,     // Set Gamma Correction Characteristics
    GAMCTR2     = 0xC9,     // Set Gamma Correction Characteristics
    GAMCTR3     = 0xCA,     // Set Gamma Correction Characteristics
    GAMCTR4     = 0xCB      // Set Gamma Correction Characteristics

};

struct Color_t
{
    Color_t(uint8_t R, uint8_t G, uint8_t B):
        r(R), g(G), b(B)
    {}

    uint8_t r;
    uint8_t g;
    uint8_t b;
    //uint8_t a;
};

struct Point_t
{
    uint8_t x;
    uint8_t y;
};

struct Rect_t
{
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
};

#endif // LCDTYPES_H
