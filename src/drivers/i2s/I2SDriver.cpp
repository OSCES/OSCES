#include "I2SDriver.h"
#include "stm32f4xx.h"

static void I2S_PinsInit()
{
    // TODO: fix, enable alternate function clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);

    // configure alternative functions
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_SPI2); // I2S3_WS
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2); // I2S3_CK
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3,  GPIO_AF_SPI2); // I2S3_SD

    GPIO_InitTypeDef gpio_initStructure;
    gpio_initStructure.GPIO_Pin   = GPIO_PinSource12 | GPIO_PinSource13;
    gpio_initStructure.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_initStructure.GPIO_Mode  = GPIO_Mode_AF; // TODO: fix
    gpio_initStructure.GPIO_OType = GPIO_OType_PP;
    gpio_initStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &gpio_initStructure);

    gpio_initStructure.GPIO_Pin = GPIO_PinSource3;
    GPIO_Init(GPIOC, &gpio_initStructure);
}

void I2S_DriverInit()
{
    I2S_PinsInit();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_PLLI2SCmd(ENABLE);

    SPI_I2S_DeInit(SPI2);

    I2S_InitTypeDef i2s_InitStructure;
    i2s_InitStructure.I2S_Standard   = I2S_Standard_Phillips;
    i2s_InitStructure.I2S_DataFormat = I2S_DataFormat_24b;
    i2s_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    i2s_InitStructure.I2S_AudioFreq  = I2S_AudioFreq_48k;
    i2s_InitStructure.I2S_CPOL       = I2S_CPOL_High;
    i2s_InitStructure.I2S_Mode       = I2S_Mode_MasterTx;
    I2S_Init(SPI2, &i2s_InitStructure);
    //I2S_FullDuplexConfig( I2S2ext, &I2S_InitStructure );

    I2S_Cmd(SPI2, ENABLE);
    I2S_Cmd(I2S2ext, ENABLE);

    //for( ;; )
    {
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET)
        {}

        SPI_I2S_SendData(SPI2, 0xAAAA);
        asm("nop");
    }
}
