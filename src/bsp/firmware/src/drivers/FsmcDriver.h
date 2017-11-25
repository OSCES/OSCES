#ifndef _FSMC_DRIVER_
#define _FSMC_DRIVER_

#include <stdint.h>

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

#define BANK1_SRAM1_ADDR     ( uint32_t ) 0x60000000 
#define BANK1_SRAM2_ADDR     ( uint32_t ) 0x64000000 
#define BANK1_SRAM3_ADDR     ( uint32_t ) 0x68000000 
#define BANK1_SRAM4_ADDR     ( uint32_t ) 0x6C000000 


enum FsmcDataWidth_t
{
    MEMORY_DATA_WITH_8BIT  = ( uint32_t ) 0x00000000,
    MEMORY_DATA_WITH_16BIT = ( uint32_t ) 0x00000010
};


class Fsmc_t
{

public:
    Fsmc_t();
    void SetMemoryDataWidth( FsmcDataWidth_t dataWith );
    void SramControllerInit( void );
        
    uint8_t* GetPointerBank1( void );
    uint8_t* GetAddressBank2( void );
    uint8_t* GetAddressBank3( void );
    uint8_t* GetAddressBank4( void );


private:
    void GpioAddressBusInit( void );
    void GpioDataBusInit( void );
    void GpioControlBusInit( void );
    void FsmcInit( void );
    
private:    
    FsmcDataWidth_t m_DataWidth;

};

#endif // _FSMC_DRIVER_
