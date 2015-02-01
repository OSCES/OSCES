#include "I2SDriver.h"
#include "stm32f4xx.h"


static void I2S_PinsInit()
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE );  // TODO: fix, enable alternate function clock
   
    
    /* configure alternative functions */
    GPIO_PinAFConfig( GPIOB, GPIO_PinSource12, GPIO_AF_SPI2 );  // I2S3_WS
    GPIO_PinAFConfig( GPIOB, GPIO_PinSource13, GPIO_AF_SPI2 );  // I2S3_CK
    GPIO_PinAFConfig( GPIOC, GPIO_PinSource3,  GPIO_AF_SPI2 );  // I2S3_SD
     
    GPIO_InitStructure.GPIO_Pin   = GPIO_PinSource12 | GPIO_PinSource13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; // TODO: fix
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
     
    GPIO_Init( GPIOB, &GPIO_InitStructure );
     
    GPIO_InitStructure.GPIO_Pin = GPIO_PinSource3;
    
    GPIO_Init( GPIOC, &GPIO_InitStructure );
}

void I2S_DriverInit()
{
  
   
  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);
  
    RCC_PLLI2SCmd( ENABLE );
  
    I2S_PinsInit();
  
     
    SPI_I2S_DeInit( SPI2 );
    
    I2S_InitTypeDef I2S_InitStructure;
    
    I2S_InitStructure.I2S_Standard    = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat  = I2S_DataFormat_24b;
    I2S_InitStructure.I2S_MCLKOutput  = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq   = I2S_AudioFreq_48k;
    I2S_InitStructure.I2S_CPOL        = I2S_CPOL_High;
    I2S_InitStructure.I2S_Mode        = I2S_Mode_MasterTx;
    
    I2S_Init( SPI2, &I2S_InitStructure );
    //I2S_FullDuplexConfig( I2S2ext, &I2S_InitStructure );

    I2S_Cmd( SPI2, ENABLE );
    I2S_Cmd( I2S2ext, ENABLE );
    
    
    //for( ;; )
    {
      
        while( RESET == SPI_I2S_GetFlagStatus( SPI2, SPI_FLAG_TXE ) )
        {}
    
        SPI_I2S_SendData( SPI2, 0xAAAA );
        
       
        
        asm( "nop" );
    }
}