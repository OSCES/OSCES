#include "DmaDriver.h"
#include "stm32f4xx_dma.h"
#include "InterruptManager.h"

static DMA_InitTypeDef DMA_InitStructure;
static bool TransferFinished = false;

static void DmaInterruptHandler(void *context)
{
    DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TC);
    DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, DISABLE);

    TransferFinished = true;
    while (DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) == RESET)
    {
        asm("nop");
    };

    asm("nop");
}

void DmaInit()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE)
    {};

    DMA_InitStructure.DMA_Channel            = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = 0;
    DMA_InitStructure.DMA_Memory0BaseAddr    = 0;
    DMA_InitStructure.DMA_BufferSize         = 0;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;

    DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToMemory;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;//DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;

    NVIC_InitTypeDef nvicInit;
    nvicInit.NVIC_IRQChannel                   = DMA2_Stream1_IRQn;
    nvicInit.NVIC_IRQChannelPreemptionPriority = 0;
    nvicInit.NVIC_IRQChannelSubPriority        = 0;
    nvicInit.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&nvicInit);

    InterruptManager::registerInterrupt(0, Dma2Stream1IrqVector, DmaInterruptHandler);

    DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);
}

void DmaM2MCopy(void *dst, void *src, uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack)
{
}

uint8_t Source[256];
uint8_t Destination[256];

void DmaM2MFill(void *dst, uint8_t data, uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack)
{
    DMA_InitStructure.DMA_PeripheralBaseAddr = static_cast<uint32_t>(data);
    DMA_InitStructure.DMA_Memory0BaseAddr    = static_cast<uint32_t>(dst);
    DMA_InitStructure.DMA_BufferSize         = len;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;

    DMA_DeInit(DMA2_Stream1);
    DMA_Init(DMA2_Stream1, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream1, ENABLE);
    DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);

    if (fpDmaCompleateCallBack == 0)
    {
        uint32_t counter = 0;
        TransferFinished = false;
        while (!TransferFinished)
            ++counter;

        asm("nop");
    }
}
