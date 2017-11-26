#include "InterruptManager.h"
#include "stm32f4xx_exti.h"

extern "C" void __iar_program_start(void);
extern "C" void __main(void);

void* InterruptManager::m_contextTable[InterruptVector::VectorsCount] =
{
    0
};

InterruptRoutine InterruptManager::m_intRoutineTable[InterruptVector::VectorsCount] =
{
    DefaultInterruptRoutine
};

void InterruptManager::init()
{
    for (uint8_t index = 0; index < InterruptVector::VectorsCount; ++index)
    {
        m_contextTable[index] = 0;
        m_intRoutineTable[index] = DefaultInterruptRoutine;
    }
}

void InterruptManager::registerInterrupt(void *context, InterruptVector vector, InterruptRoutine routine)
{
    if (vector < 0 && vector >= InterruptVector::VectorsCount)
        return;

    m_contextTable[vector] = context;
    m_intRoutineTable[vector] = routine;
}

void InterruptManager::unregisterInterrupt(InterruptVector vector)
{
    if (vector < 0 && vector >= InterruptVector::VectorsCount)
        return;

    m_contextTable[vector] = 0;
    m_intRoutineTable[vector] = DefaultInterruptRoutine;
}

void InterruptManager::disableInterrupt()
{
    __disable_interrupt();
}

void InterruptManager::enableInterrupt()
{
    __enable_interrupt();
}

void InterruptManager::DefaultInterruptRoutine(void *context)
{
    while (true) // Trap
    {
        asm("nop");
    }
}

// --------------------------- Interrupt Handlers --------------------------- //
#define CALL_VECTOR(vector) \
    m_IntRoutineTable[vector](m_pContextTable[vector])

void InterruptManager::ResetHandler()
{
    __iar_program_start();
}

void InterruptManager::NmiHandler()
{
    CALL_VECTOR(InterruptVector::NmiVector);
}

void InterruptManager::HardFaultHandler()
{
    CALL_VECTOR(InterruptVector::HardFaultVector);
}

void InterruptManager::MemManageHandler()
{
    CALL_VECTOR(InterruptVector::MemManageVector);
}

void InterruptManager::BusFaultHandler()
{
    CALL_VECTOR(InterruptVector::BusFaultVector);
}

void InterruptManager::UsageFaultHandler()
{
    CALL_VECTOR(InterruptVector::UsageFaultVector);
}

void InterruptManager::SvCallHandler()
{
    CALL_VECTOR(InterruptVector::SvCallVector);
}

void InterruptManager::DebugMonitorHandler()
{
    CALL_VECTOR(InterruptVector::DebugMonitorVector);
}

void InterruptManager::PendSvHandler()
{
    CALL_VECTOR(InterruptVector::PendSvVector);
}

void InterruptManager::SysTickHandler()
{
    CALL_VECTOR(InterruptVector::SysTickVector);
}

void InterruptManager::WwdgIrqHandler()
{
    CALL_VECTOR(InterruptVector::WwdgIrqVector);
}

void InterruptManager::PvdIrqHandler()
{
    CALL_VECTOR(InterruptVector::PvdIrqVector);
}
void InterruptManager::TampStampIrqHandler()
{
    CALL_VECTOR(InterruptVector::TampStampIrqVector);
}

void InterruptManager::RtcWkupIrqHandler()
{
    CALL_VECTOR(InterruptVector::RtcWkupIrqVector);
}

void InterruptManager::FlashIrqHandler()
{
    CALL_VECTOR(InterruptVector::FlashIrqVector);
}

void InterruptManager::RccIrqHandler()
{
    CALL_VECTOR(InterruptVector::RccIrqVector);
}

void InterruptManager::Exti0IrqHandler()
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
        CALL_VECTOR(InterruptVector::Exti0IrqVector);
    }
}

void InterruptManager::Exti1IrqHandler()
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line1);
        CALL_VECTOR(InterruptVector::Exti1IrqVector);
    }
}

void InterruptManager::Exti2IrqHandler()
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line2);
        CALL_VECTOR(InterruptVector::Exti2IrqVector);
    }
}

void InterruptManager::Exti3IrqHandler()
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line3);
        CALL_VECTOR(InterruptVector::Exti3IrqVector);
    }
}

void InterruptManager::Exti4IrqHandler()
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line4);
        CALL_VECTOR(InterruptVector::Exti4IrqVector);
    }
}

void InterruptManager::Dma1Stream0IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream0IrqVector);
}

void InterruptManager::Dma1Stream1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream1IrqVector);
}

void InterruptManager::Dma1Stream2IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream2IrqVector);
}

void InterruptManager::Dma1Stream3IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream3IrqVector);
}

void InterruptManager::Dma1Stream4IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream4IrqVector);
}

void InterruptManager::Dma1Stream5IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream5IrqVector);
}

void InterruptManager::Dma1Stream6IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream6IrqVector);
}

void InterruptManager::AdcIrqHandler()
{
    CALL_VECTOR(InterruptVector::Adc1Adc2Adc3IrqVector);
}

void InterruptManager::Can1TxIrqHandler()
{
    CALL_VECTOR(InterruptVector::Can1TxIrqVector);
}

void InterruptManager::Can1Rx0IrqHandler()
{
    CALL_VECTOR(InterruptVector::Can1Rx0IrqVector);
}

void InterruptManager::Can1Rx1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Can1Rx1IrqVector);
}

void InterruptManager::Can1SceIrqHandler()
{
    CALL_VECTOR(InterruptVector::Can1SceIrqVector);
}

void InterruptManager::Exti95IrqHandler()
{
    uint32_t line  = 0;
    uint32_t vector = 0;

    if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        line  = EXTI_Line5;
        vector = Exti5IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        line  = EXTI_Line6;
        vector = Exti6IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line7) != RESET )
    {
        line  = EXTI_Line7;
        vector = Exti7IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line8) != RESET )
    {
        line  = EXTI_Line8;
        vector = Exti8IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line9) != RESET )
    {
        line  = EXTI_Line9;
        vector = Exti9IrqVector;
    }

    EXTI_ClearITPendingBit(line);
    CALL_VECTOR(vector);
}

void InterruptManager::Tim1BrkTim9IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim1BrkTim9IrqVector);
}

void InterruptManager::Tim1UpTim10IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim1UpTim10IqrVector);
}

void InterruptManager::Tim1TrgComTim11IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim1TrgComTim11IrqVector);
}

void InterruptManager::Tim1CaptureCompareIrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim1CaptureCompareIrqVector);
}

void InterruptManager::Tim2IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim2IrqVector);
}

void InterruptManager::Tim3IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim3IrqVector);
}

void InterruptManager::Tim4IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim4IrqVector);
}

void InterruptManager::I2c1EventIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c1EventIrqVector);
}

void InterruptManager::I2c1ErrorIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c1ErrorIrqVector);
}

void InterruptManager::I2c2EventIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c2EventIrqVector);
}

void InterruptManager::I2c2ErrorIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c2ErrorIrqVector);
}

void InterruptManager::Spi1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Spi1IrqVector);
}

void InterruptManager::Spi2IrqHandler()
{
    CALL_VECTOR(InterruptVector::Spi2IrqVector);
}

void InterruptManager::Usart1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Usart1IrqVector);
}

void InterruptManager::Usart2IrqHandler()
{
    CALL_VECTOR(InterruptVector::Usart2IrqVector);
}

void InterruptManager::Usart3IrqHandler()
{
    CALL_VECTOR(InterruptVector::Usart3IrqVector);
}

void InterruptManager::Exti1510IrqHandler()
{
    uint32_t line  = 0;
    uint32_t vector = 0;

    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        line  = EXTI_Line10;
        vector = Exti10IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        line  = EXTI_Line11;
        vector = Exti11IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        line  = EXTI_Line12;
        vector = Exti12IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        line  = EXTI_Line13;
        vector = Exti13IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        line  = EXTI_Line14;
        vector = Exti14IrqVector;
    }
    else if (EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        line  = EXTI_Line15;
        vector = Exti15IrqVector;
    }

    EXTI_ClearITPendingBit(line);
    CALL_VECTOR(vector);
}

void InterruptManager::RtcAlarmIrqHandler()
{
    CALL_VECTOR(InterruptVector::RtcAlarmIrqVector);
}

void InterruptManager::OtgFsWkupIrqHandler()
{
    CALL_VECTOR(InterruptVector::OtgFsWkupIrqVector);
}

void InterruptManager::Tim8BrkTim12IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim8BrkTim12IrqVector);
}

void InterruptManager::Tim8UpTim13IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim8UpTim13IrqVector);
}

void InterruptManager::Tim8TrgComTim14IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim8TrgComTim14IrqVector);
}

void InterruptManager::Tim8CaptureCompareIrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim8CcIrqVector);
}

void InterruptManager::Dma1Stream7IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma1Stream7IrqVector);
}

void InterruptManager::FsmcIrqHandler()
{
    CALL_VECTOR(InterruptVector::FsmcIrqVector);
}

void InterruptManager::SdioIrqHandler()
{
    CALL_VECTOR(InterruptVector::SdioIrqVector);
}

void InterruptManager::Tim5IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim5IrqVector);
}

void InterruptManager::Spi3IrqHandler()
{
    CALL_VECTOR(InterruptVector::Spi3IrqVector);
}

void InterruptManager::Uart4IrqHandler()
{
    CALL_VECTOR(InterruptVector::Uart4IrqVector);
}

void InterruptManager::Uart5IrqHandler()
{
    CALL_VECTOR(InterruptVector::Uart5IrqVector);
}

void InterruptManager::Tim6DacIrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim6DacIrqVector);
}

void InterruptManager::Tim7IrqHandler()
{
    CALL_VECTOR(InterruptVector::Tim7IrqVector);
}

void InterruptManager::Dma2Stream0IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream0IrqVector);
}

void InterruptManager::Dma2Stream1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream1IrqVector);
}

void InterruptManager::Dma2Stream2IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream2IrqVector);
}

void InterruptManager::Dma2Stream3IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream3IrqVector);
}

void InterruptManager::Dma2Stream4IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream4IrqVector);
}

void InterruptManager::EthIrqHandler()
{
    CALL_VECTOR(InterruptVector::EthIrqVector);
}

void InterruptManager::EthWkupIrqHandler()
{
    CALL_VECTOR(InterruptVector::EthWkupIrqVector);
}

void InterruptManager::Can2TxIrqHandler()
{
    CALL_VECTOR(InterruptVector::Can2TxIrqVector);
}

void InterruptManager::Can2Rx0IrqHandler()
{
    CALL_VECTOR(InterruptVector::Can2Rx0IrqVector);
}

void InterruptManager::Can2Rx1IrqHandler()
{
    CALL_VECTOR(InterruptVector::Can2Rx1IrqVector);
}

void InterruptManager::Can2SceIrqHandler()
{
    CALL_VECTOR(InterruptVector::Can2SceIrqVector);
}

void InterruptManager::UsbOtgFsIrqHandler()
{
    CALL_VECTOR(InterruptVector::UsbOtgFsIrqVector);
}

void InterruptManager::Dma2Stream5IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream5IrqVector);
}

void InterruptManager::Dma2Stream6IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream6IrqVector);
}

void InterruptManager::Dma2Stream7IrqHandler()
{
    CALL_VECTOR(InterruptVector::Dma2Stream7IrqVector);
}

void InterruptManager::Usart6IrqHandler()
{
    CALL_VECTOR(InterruptVector::Usart6IrqVector);
}

void InterruptManager::I2c3EventIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c3EventIrqVector);
}

void InterruptManager::I2c3ErrorIrqHandler()
{
    CALL_VECTOR(InterruptVector::I2c3ErrorIrqVector);
}

void InterruptManager::OtgHsEp1OutIrqHandler()
{
    CALL_VECTOR(InterruptVector::OtgHsEp1OutIrqVector);
}

void InterruptManager::OtgHsEp1InIrqHandler()
{
    CALL_VECTOR(InterruptVector::OtgHsEp1InIrqVector);
}

void InterruptManager::OtgHsWkupIrqHandler()
{
    CALL_VECTOR(InterruptVector::OtgHsWkupIrqVector);
}

void InterruptManager::OtgHsIrqHandler()
{
    CALL_VECTOR(InterruptVector::OtgHsIrqVector);
}

void InterruptManager::DcmiIrqHandler()
{
    CALL_VECTOR(InterruptVector::DcmiIrqVector);
}

void InterruptManager::CrypIrqHandler()
{
    CALL_VECTOR(InterruptVector::CrypIrqVector);
}

void InterruptManager::HashRngIrqHandler()
{
    CALL_VECTOR(InterruptVector::HashRngIrqVector);
}
//--------------------------------------------------------------------------- //


// --------------------------- Interrupt Handlers Table ----------------------//
#pragma language = extended
#pragma segment  = "CSTACK"
#pragma location = ".intvec"
__root const InterruptManager::HandlerItem InterruptManager::m_interruptVectorTable[InterruptVector::VectorsCount] =
{
    { .handler = __sfe("CSTACK") }          ,
    ResetHandler                            ,  //Reset Handler
    NmiHandler                              ,  //NMI_Handler
    HardFaultHandler                        ,  //HardFault_Handler
    MemManageHandler                        ,  //MemManage_Handler
    BusFaultHandler                         ,  //BusFault_Handler
    UsageFaultHandler                       ,  //UsageFault_Handler
    0                                       ,  //Reserved
    0                                       ,  //Reserved
    0                                       ,  //Reserved
    0                                       ,  //Reserved
    SvCallHandler                           ,  //SVCall_Handler
    DebugMonitorHandler                     ,  //DebugMonitor_Handler
    0                                       ,  //Reserved
    PendSvHandler                           ,  //PendSV_Handler
    SysTickHandler                          ,  //SysTick Handler

    //External Interrupts
    WwdgIrqHandler                          ,  //WWDG_IRQHandler
    PvdIRQHandler                           ,  //PVD_IRQHandler            //PVD through EXTI Line detection
    TampStampIrqHandler                     ,  //TAMP_STAMP_IRQHandler     //Tamper and TimeStamps through the EXTI line
    RtcWkupIrqHandler                       ,  //RTC_WKUP_IRQHandler       //RTC Wakeup through the EXTI line
    FlashIrqHandler                         ,  //FLASH_IRQHandler
    RccIrqHandler                           ,  //RCC_IRQHandler
    Exti0IrqHandler                         ,  //EXTI0_IRQHandler
    Exti1IrqHandler                         ,  //EXTI1_IRQHandler
    Exti2IrqHandler                         ,  //EXTI2_IRQHandler
    Exti3IrqHandler                         ,  //EXTI3_IRQHandler
    Exti4IrqHandler                         ,  //EXTI4_IRQHandler
    Dma1Stream0IrqHandler                   ,  //DMA1_Stream0_IRQHandler
    Dma1Stream1IrqHandler                   ,  //DMA1_Stream1_IRQHandler
    Dma1Stream2IrqHandler                   ,  //DMA1_Stream2_IRQHandler
    Dma1Stream3IrqHandler                   ,  //DMA1_Stream3_IRQHandler
    Dma1Stream4IrqHandler                   ,  //DMA1_Stream4_IRQHandler
    Dma1Stream5IrqHandler                   ,  //DMA1_Stream5_IRQHandler
    Dma1Stream6IrqHandler                   ,  //DMA1_Stream6_IRQHandler
    AdcIrqHandler                           ,  //ADC_IRQHandler             //ADC1, ADC2 and ADC3s
    Can1TxIrqHandler                        ,  //CAN1_TX_IRQHandler
    Can1Rx0IrqHandler                       ,  //CAN1_RX0_IRQHandler
    Can1Rx1IrqHandler                       ,  //CAN1_RX1_IRQHandler
    Can1SceIrqHandler                       ,  //CAN1_SCE_IRQHandler
    Exti95IrqHandler                        ,  //EXTI9_5_IRQHandler         //External Line[9:5]s
    Tim1BrkTim9IrqHandler                   ,  //TIM1_BRK_TIM9_IRQHandler   //TIM1 Break and TIM9
    Tim1UpTim10IrqHandler                   ,  //TIM1_UP_TIM10_IRQHandler   //TIM1 Update and TIM10
    Tim1TrgComTim11IrqHandler               ,  //TIM1_TRG_COM_TIM11_IRQHandler //TIM1 Trigger and Commutation and TIM11
    Tim1CaptureCompareIrqHandler            ,  //TIM1_CAPTURE_COMPARE_IRQHandler
    Tim2IrqHandler                          ,  //TIM2_IRQHandler
    Tim3IrqHandler                          ,  //TIM3_IRQHandler
    Tim4IrqHandler                          ,  //TIM4_IRQHandler
    I2c1EventIrqHandler                     ,  //I2C1_EVENT_IRQHandler
    I2c1ErrorIrqHandler                     ,  //I2C1_ERROR_IRQHandler
    I2c2EventIrqHandler                     ,  //I2C2_EVENT_IRQHandler
    I2c2ErrorIrqHandler                     ,  //I2C2_ERROR_IRQHandler
    Spi1IrqHandler                          ,  //SPI1_IRQHandler
    Spi2IrqHandler                          ,  //SPI2_IRQHandler
    Usart1IrqHandler                        ,  //USART1_IRQHandler
    Usart2IrqHandler                        ,  //USART2_IRQHandler
    Usart3IrqHandler                        ,  //USART3_IRQHandler
    Exti1510IrqHandler                      ,  //EXTI15_10_IRQHandler      //External Line[15:10]s
    RtcAlarmIrqHandler                      ,  //RTC_Alarm_IRQHandler      //RTC Alarm (A and B) through EXTI Line
    OtgFsWkupIrqHandler                     ,  //OTG_FS_WKUP_IRQHandler    //USB OTG FS Wakeup through EXTI line
    Tim8BrkTim12IrqHandler                  ,  //TIM8_BRK_TIM12_IRQHandler //TIM8 Break and TIM12
    Tim8UpTim13IrqHandler                   ,  //TIM8_UP_TIM13_IRQHandler  //TIM8 Update and TIM13
    Tim8TrgComTim14IrqHandler               ,  //TIM8_TRG_COM_TIM14_IRQHandler //TIM8 Trigger and Commutation and TIM14
    Tim8CaptureCompareIrqHandler            ,  //TIM8_CC_IRQHandler        //TIM8 Capture Compare
    Dma1Stream7IrqHandler                   ,  //DMA1_Stream7_IRQHandler   //DMA1 Stream7
    FsmcIrqHandler                          ,  //FSMC_IRQHandler
    SdioIrqHandler                          ,  //SDIO_IRQHandler
    Tim5IrqHandler                          ,  //TIM5_IRQHandler
    Spi3IrqHandler                          ,  //SPI3_IRQHandler
    Uart4IrqHandler                         ,  //UART4_IRQHandler
    Uart5IrqHandler                         ,  //UART5_IRQHandler
    Tim6DacIrqHandler                       ,  //TIM6_DAC_IRQHandler       //TIM6 and DAC1&2 underrun errors
    Tim7IrqHandler                          ,  //TIM7_IRQHandler
    Dma2Stream0IrqHandler                   ,  //DMA2_Stream0_IRQHandler
    Dma2Stream1IrqHandler                   ,  //DMA2_Stream1_IRQHandler
    Dma2Stream2IrqHandler                   ,  //DMA2_Stream2_IRQHandler
    Dma2Stream3IrqHandler                   ,  //DMA2_Stream3_IRQHandler
    Dma2Stream4IrqHandler                   ,  //DMA2_Stream4_IRQHandler
    EthIrqHandler                           ,  //ETH_IRQHandler
    EthWkupIrqHandler                       ,  //ETH_WKUP_IRQHandler       //Ethernet Wakeup through EXTI line
    Can2TxIrqHandler                        ,  //CAN2_TX_IRQHandler
    Can2Rx0IrqHandler                       ,  //CAN2_RX0_IRQHandler
    Can2Rx1IrqHandler                       ,  //CAN2_RX1_IRQHandler
    Can2SceIrqHandler                       ,  //CAN2_SCE_IRQHandler
    UsbOtgFsIrqHandler                      ,  //USB_OTG_FS_IRQHandler
    Dma2Stream5IrqHandler                   ,  //DMA2_Stream5_IRQHandler
    Dma2Stream6IrqHandler                   ,  //DMA2_Stream6_IRQHandler
    Dma2Stream7IrqHandler                   ,  //DMA2_Stream7_IRQHandler
    Usart6IrqHandler                        ,  //USART6_IRQHandler
    I2c3EventIrqHandler                     ,  //I2C3_EV_IRQHandler
    I2c3ErrorIrqHandler                     ,  //I2C3_ER_IRQHandler
    OtgHsEp1OutIrqHandler                   ,  //OTG_HS_EP1_OUT_IRQHandler //USB OTG HS End Point 1 Out
    OtgHsEp1InIrqHandler                    ,  //OTG_HS_EP1_IN_IRQHandler  //USB OTG HS End Point 1 In
    OtgHsWkupIrqHandler                     ,  //OTG_HS_WKUP_IRQHandler    //USB OTG HS Wakeup through EXTI
    OtgHsIrqHandler                         ,  //OTG_HS_IRQHandler         //USB OTG HS
    DcmiIrqHandler                          ,  //DCMI_IRQHandler           //DCMI
    CrypIrqHandler                          ,  //CRYP_IRQHandler           //CRYP crypto
    HashRngIrqHandler                          //HASH_RNG_IRQHandler       //Hash and Rng
};

//----------------------------------------------------------------------------//
