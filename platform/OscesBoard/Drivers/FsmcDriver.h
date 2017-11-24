#ifndef _FSMC_DRIVER_
#define _FSMC_DRIVER_

#include <stdint.h>
#include "NonCopyable.h"

/*
---------------------------Default GPIOs Configuration -------------------------

 Address Bus                Data Bus                Control Bus

PF0  <-> FSMC_A0         PD14 <-> FSMC_D0         PE0  <-> FSMC_NBL0
PF1  <-> FSMC_A1         PD15 <-> FSMC_D1         PE1  <-> FSMC_NBL1
PF2  <-> FSMC_A2         PD0  <-> FSMC_D2         PD4  <-> FSMC_NOE
PF3  <-> FSMC_A3         PD1  <-> FSMC_D3         PD5  <-> FSMC_NWE
PF4  <-> FSMC_A4         PE7  <-> FSMC_D4         PD7 <-> FSMC_NE1
PF5  <-> FSMC_A5         PE8  <-> FSMC_D5         PG9 <-> FSMC_NE2
PF12 <-> FSMC_A6         PE9  <-> FSMC_D6
PF13 <-> FSMC_A7         PE10 <-> FSMC_D7
PF14 <-> FSMC_A8         PE11 <-> FSMC_D8
PF15 <-> FSMC_A9         PE12 <-> FSMC_D9
PG0  <-> FSMC_A10        PE13 <-> FSMC_D10
PG1  <-> FSMC_A11        PE14 <-> FSMC_D11
PG2  <-> FSMC_A12        PE15 <-> FSMC_D12
PG3  <-> FSMC_A13        PD8  <-> FSMC_D13
PG4  <-> FSMC_A14        PD9  <-> FSMC_D14
PG5  <-> FSMC_A15        PD10 <-> FSMC_D15
PD11 <-> FSMC_A16
PD12 <-> FSMC_A17
PD13 <-> FSMC_A18
PE3  <-> FSMC_A19
PE4  <-> FSMC_A20
PE5  <-> FSMC_A21
PE6  <-> FSMC_A22
PE2  <-> FSMC_A23

--------------------------------------------------------------------------------
*/

class Fsmc : NonCopyable
{
public:
    // TODO: C++11 enum MemoryDataWidth : uint32_t
    enum MemoryDataWidth
    {
        MemoryDataWidth_8bit  = (uint32_t)0x00000000,
        MemoryDataWidth_16bit = (uint32_t)0x00000010,
    };

public:
    Fsmc();
    ~Fsmc();

    void setMemoryDataWidth(MemoryDataWidth dataWith);
    void sramControllerInit();

    uint8_t* pointerBank1();
    uint32_t addressBank2();
    uint32_t addressBank3();
    uint32_t addressBank4();

private:
    void gpioAddressBusInit();
    void gpioDataBusInit();
    void gpioControlBusInit();
    void fsmcInit();

private:
    MemoryDataWidth m_DataWidth;
};

#endif // _FSMC_DRIVER_
