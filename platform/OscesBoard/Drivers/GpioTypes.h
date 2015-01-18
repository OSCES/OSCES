#ifndef GPIOTYPES_H
#define GPIOTYPES_H

#include "stm32f4xx_gpio.h"

enum Port_t
{
    PORTA     = (AHB1PERIPH_BASE + 0x0000), // A - 0
    PORTB     = (AHB1PERIPH_BASE + 0x0400), // B - 1
    PORTC     = (AHB1PERIPH_BASE + 0x0800), // C - 2
    PORTD     = (AHB1PERIPH_BASE + 0x0C00), // D - 3
    PORTE     = (AHB1PERIPH_BASE + 0x1000), // E - 4
    PORTF     = (AHB1PERIPH_BASE + 0x1400), // F - 5
    PORTG     = (AHB1PERIPH_BASE + 0x1800), // G - 6
    PORTH     = (AHB1PERIPH_BASE + 0x1C00), // H - 7
    PORTI     = (AHB1PERIPH_BASE + 0x2000)  // I - 8
};

enum Pin_t
{
    PIN_0     = (uint16_t) 0x0001,  // 0
    PIN_1     = (uint16_t) 0x0002,  // 1
    PIN_2     = (uint16_t) 0x0004,  // 2
    PIN_3     = (uint16_t) 0x0008,  // 3
    PIN_4     = (uint16_t) 0x0010,  // 4
    PIN_5     = (uint16_t) 0x0020,  // 5
    PIN_6     = (uint16_t) 0x0040,  // 6
    PIN_7     = (uint16_t) 0x0080,  // 7
    PIN_8     = (uint16_t) 0x0100,  // 8
    PIN_9     = (uint16_t) 0x0200,  // 9
    PIN_10    = (uint16_t) 0x0400,  // A
    PIN_11    = (uint16_t) 0x0800,  // B
    PIN_12    = (uint16_t) 0x1000,  // C
    PIN_13    = (uint16_t) 0x2000,  // D
    PIN_14    = (uint16_t) 0x4000,  // E
    PIN_15    = (uint16_t) 0x8000,  // F
    PIN_All   = (uint16_t) 0xFFFF
};

enum PinMode_t
{
    MODE_IN   = (uint8_t) 0x00, // Input Mode
    MODE_OUT  = (uint8_t) 0x01, // Output Mode
    MODE_AF   = (uint8_t) 0x02, // Alternate function Mode
    MODE_AN   = (uint8_t) 0x03  // Analog Mode
};

enum OutType_t
{
    OUT_PP    = (uint8_t) 0x00,
    OUT_OD    = (uint8_t) 0x01
};

enum PullType_t
{
    PULL_NO   = (uint8_t) 0x00,
    PULL_UP   = (uint8_t) 0x01,
    PULL_DOWN = (uint8_t) 0x02
};

struct PinInfo
{
    Port_t port;
    Pin_t  pin;
};


#endif // GPIOTYPES_H
