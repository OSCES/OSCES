#ifndef GPIOTYPES_H
#define GPIOTYPES_H

#include "stm32f4xx_gpio.h"

enum Port
{
    PortA     = (AHB1PERIPH_BASE + 0x0000), // A - 0
    PortB     = (AHB1PERIPH_BASE + 0x0400), // B - 1
    PortC     = (AHB1PERIPH_BASE + 0x0800), // C - 2
    PortD     = (AHB1PERIPH_BASE + 0x0C00), // D - 3
    PortE     = (AHB1PERIPH_BASE + 0x1000), // E - 4
    PortF     = (AHB1PERIPH_BASE + 0x1400), // F - 5
    PortG     = (AHB1PERIPH_BASE + 0x1800), // G - 6
    PortH     = (AHB1PERIPH_BASE + 0x1C00), // H - 7
    PortI     = (AHB1PERIPH_BASE + 0x2000)  // I - 8
};

enum Pin
{
    Pin0     = (uint16_t) 0x0001,  // 0
    Pin1     = (uint16_t) 0x0002,  // 1
    Pin2     = (uint16_t) 0x0004,  // 2
    Pin3     = (uint16_t) 0x0008,  // 3
    Pin4     = (uint16_t) 0x0010,  // 4
    Pin5     = (uint16_t) 0x0020,  // 5
    Pin6     = (uint16_t) 0x0040,  // 6
    Pin7     = (uint16_t) 0x0080,  // 7
    Pin8     = (uint16_t) 0x0100,  // 8
    Pin9     = (uint16_t) 0x0200,  // 9
    Pin10    = (uint16_t) 0x0400,  // A
    Pin11    = (uint16_t) 0x0800,  // B
    Pin12    = (uint16_t) 0x1000,  // C
    Pin13    = (uint16_t) 0x2000,  // D
    Pin14    = (uint16_t) 0x4000,  // E
    Pin15    = (uint16_t) 0x8000,  // F
    PinAll   = (uint16_t) 0xFFFF
};

enum PinMode
{
    ModeIn   = (uint8_t) 0x00, // Input Mode
    ModeOut  = (uint8_t) 0x01, // Output Mode
    ModeAf   = (uint8_t) 0x02, // Alternate function Mode
    ModeAn   = (uint8_t) 0x03  // Analog Mode
};

enum OutType
{
    OutPp    = (uint8_t) 0x00,
    OutOd    = (uint8_t) 0x01
};

enum PullType
{
    PullNo   = (uint8_t) 0x00,
    PullUp   = (uint8_t) 0x01,
    PullDown = (uint8_t) 0x02
};

struct PinInfo
{
    Port port;
    Pin  pin;
};


#endif // GPIOTYPES_H
