#include "FsmcDriver.h"
#include "stm32f4xx_gpio.h"

Fsmc_t::Fsmc_t()
{
    m_DataWidth = MEMORY_DATA_WITH_8BIT;    
}

void Fsmc_t::SetMemoryDataWidth( FsmcDataWidth_t dataWith )
{
    m_DataWidth = dataWith;
}

void Fsmc_t::SramControllerInit( void )
{
    GpioControlBusInit();  
    GpioDataBusInit();
    GpioAddressBusInit();
    FsmcInit();
}

uint8_t* Fsmc_t::GetPointerBank1( void )
{
    return ( uint8_t * )BANK1_SRAM1_ADDR;
}

uint32_t Fsmc_t::GetAddressBank2( void )
{
    return BANK1_SRAM2_ADDR;
}

uint32_t Fsmc_t::GetAddressBank3( void )
{
    return BANK1_SRAM3_ADDR;
}

uint32_t Fsmc_t::GetAddressBank4( void )
{
    return BANK1_SRAM4_ADDR;
}

void Fsmc_t::GpioAddressBusInit( void )
{
    GPIO_InitTypeDef GpioInit; 
  
    GpioInit.GPIO_Mode  = GPIO_Mode_AF;
    GpioInit.GPIO_Speed = GPIO_Speed_100MHz;
    GpioInit.GPIO_OType = GPIO_OType_PP;
    GpioInit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOG, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
  //RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_0;  //FSMC_A0
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource1 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_1;  //FSMC_A1
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource2 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_2;  //FSMC_A2
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource3 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_3;  //FSMC_A3
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource4 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_4;  //FSMC_A4
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource5 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_5;  //FSMC_A5
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource12, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_12; //FSMC_A6
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource13, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_13; //FSMC_A7
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource14, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_14; //FSMC_A8
    GPIO_PinAFConfig( GPIOF, GPIO_PinSource15, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_15; //FSMC_A9

    GPIO_Init( GPIOF, &GpioInit );

    GPIO_PinAFConfig( GPIOG, GPIO_PinSource0 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_0;  //FSMC_A10
    GPIO_PinAFConfig( GPIOG, GPIO_PinSource1 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_1;  //FSMC_A11
    GPIO_PinAFConfig( GPIOG, GPIO_PinSource2 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_2;  //FSMC_A12
    GPIO_PinAFConfig( GPIOG, GPIO_PinSource3 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_3;  //FSMC_A13
    GPIO_PinAFConfig( GPIOG, GPIO_PinSource4 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_4;  //FSMC_A14
    GPIO_PinAFConfig( GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_5;  //FSMC_A15

    GPIO_Init( GPIOG, &GpioInit );

    GPIO_PinAFConfig( GPIOD, GPIO_PinSource11, GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_11; //FSMC_A16
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource12, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_12; //FSMC_A17
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource13, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_13; //FSMC_A18
     
    GPIO_Init( GPIOD, &GpioInit );
    
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource3 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_3; // FSMC_A19 
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource4 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_4; // FSMC_A20
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource5 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_5; // FSMC_A21
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource6 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_6; // FSMC_A22
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource2 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_2; // FSMC_A23

    //GPIO_Init( GPIOE, &GpioInit );
}


void Fsmc_t::GpioDataBusInit( void )
{
    GPIO_InitTypeDef GpioInit; 

    GpioInit.GPIO_Mode  = GPIO_Mode_AF;
    GpioInit.GPIO_Speed = GPIO_Speed_100MHz;
    GpioInit.GPIO_OType = GPIO_OType_PP;
    GpioInit.GPIO_PuPd  = GPIO_PuPd_NOPULL;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE );
    
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource14, GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_14; // FSMC_D0
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource15, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_15; // FSMC_D1
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource0 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_0;  // FSMC_D2
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource1 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_1;  // FSMC_D3

    GPIO_Init(GPIOD, &GpioInit);
    
    GPIO_PinAFConfig( GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_7;  // FSMC_D4
    GPIO_PinAFConfig( GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_8;  // FSMC_D5
    GPIO_PinAFConfig( GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_9;  // FSMC_D6
    GPIO_PinAFConfig( GPIOE, GPIO_PinSource10, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_10; // FSMC_D7
 
    GPIO_Init(GPIOE, &GpioInit);
        
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource11, GPIO_AF_FSMC ); GpioInit.GPIO_Pin  = GPIO_Pin_11;// FSMC_D8
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource12, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_12;// FSMC_D9
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource13, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_13;// FSMC_D10
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource14, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_14;// FSMC_D11
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource15, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_15;// FSMC_D12
    //GPIO_PinAFConfig( GPIOD, GPIO_PinSource8,  GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_8; // FSMC_D13
    //GPIO_PinAFConfig( GPIOD, GPIO_PinSource9,  GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_9; // FSMC_D14
    //GPIO_PinAFConfig( GPIOD, GPIO_PinSource10, GPIO_AF_FSMC ); GpioInit.GPIO_Pin |= GPIO_Pin_10;// FSMC_D15

    //GPIO_Init(GPIOE, &GpioInit);
}

void Fsmc_t::GpioControlBusInit( void )
{
    GPIO_InitTypeDef GpioInit; 

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    
    GpioInit.GPIO_Mode  = GPIO_Mode_AF;
    GpioInit.GPIO_Speed = GPIO_Speed_100MHz;
    GpioInit.GPIO_OType = GPIO_OType_PP;
    GpioInit.GPIO_PuPd  = GPIO_PuPd_NOPULL;

    
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC); GpioInit.GPIO_Pin  = GPIO_Pin_4; //FSMC_NOE
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC); GpioInit.GPIO_Pin |= GPIO_Pin_5; //FSMC_NWE
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC); GpioInit.GPIO_Pin |= GPIO_Pin_7; //CE
      
    GPIO_Init(GPIOD, &GpioInit);

    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource0 , GPIO_AF_FSMC ); // FSMC_NBL0
    //GPIO_PinAFConfig( GPIOE, GPIO_PinSource1 , GPIO_AF_FSMC ); // FSMC_NBL1
    //GPIO_PinAFConfig( GPIOG, GPIO_PinSource9 , GPIO_AF_FSMC);  // FSMC_NE2
}

void Fsmc_t::FsmcInit( void )
{
        
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); /* Enable FSMC clock */

    FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTimingStructure;

#if 0    
    FSMC_NORSRAMTimingStructure.FSMC_AddressSetupTime      = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_AddressHoldTime       = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_DataSetupTime         = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_BusTurnAroundDuration = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_CLKDivision           = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_DataLatency           = 0x00;
#else    
    FSMC_NORSRAMTimingStructure.FSMC_AddressSetupTime      = 0x04;
    FSMC_NORSRAMTimingStructure.FSMC_AddressHoldTime       = 0x04;
    FSMC_NORSRAMTimingStructure.FSMC_DataSetupTime         = 0x05;
    FSMC_NORSRAMTimingStructure.FSMC_BusTurnAroundDuration = 0x05;
    FSMC_NORSRAMTimingStructure.FSMC_CLKDivision           = 0x00;
    FSMC_NORSRAMTimingStructure.FSMC_DataLatency           = 0x00;
#endif    
    
    FSMC_NORSRAMTimingStructure.FSMC_AccessMode            = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank                    = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux          = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType              = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth         = m_DataWidth;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode         = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait        = FSMC_AsynchronousWait_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity      = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode                = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive        = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation          = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal              = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode            = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst              = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct   = &FSMC_NORSRAMTimingStructure;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct       = &FSMC_NORSRAMTimingStructure;

    FSMC_NORSRAMInit( &FSMC_NORSRAMInitStructure ); 

    FSMC_NORSRAMCmd( FSMC_Bank1_NORSRAM1, ENABLE ); 
}

