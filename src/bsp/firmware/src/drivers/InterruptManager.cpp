#include "InterruptManager.h"

extern "C" void __iar_program_start( void );
extern "C" void __main( void );

void* InterruptManager_t::m_pContextTable[ INTERRUPT_MANAGER_VECTORS_AMOUNT ] = 
{ 
  0
};

InterruptRoutine_t InterruptManager_t::fp_IntRoutineTable[ INTERRUPT_MANAGER_VECTORS_AMOUNT ] = 
{ 
    DefaultInterruptRoutine 
};

void InterruptManager_t::Init()
{
    for( uint8_t idx = 0; idx < INTERRUPT_MANAGER_VECTORS_AMOUNT; idx++ )
    {
        m_pContextTable   [ idx ] = 0;
        fp_IntRoutineTable[ idx ] = DefaultInterruptRoutine;
    }
}

void InterruptManager_t::RegisterInterrupt( void* pContext, uint16_t vector, InterruptRoutine_t fp_Routine )
{
    if( vector < INTERRUPT_MANAGER_VECTORS_AMOUNT )
    {
        m_pContextTable   [ vector ] = pContext;
        fp_IntRoutineTable[ vector ] = fp_Routine;
    }
}
 
void InterruptManager_t::DefaultInterruptRoutine( void* pContext )
{
    for( ;; ) // Trap
    {
        asm("nop");
    }
}


// --------------------------- Interrupt Handlers --------------------------- //
void InterruptManager_t::ResetHandler( void )
{
    __iar_program_start();
}

void InterruptManager_t::NmiHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_NMI_VECTOR ]( m_pContextTable[ INTERRUPT_NMI_VECTOR ] );
}

void InterruptManager_t::HardFaultHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_HARD_FAULT_VECTOR ]( m_pContextTable[ INTERRUPT_HARD_FAULT_VECTOR ] );
}

void InterruptManager_t::MemManageHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_MEM_MANAGE_VECTOR ]( m_pContextTable[ INTERRUPT_MEM_MANAGE_VECTOR ] );
}

void InterruptManager_t::BusFaultHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_BUS_FAULT_VECTOR ]( m_pContextTable[ INTERRUPT_BUS_FAULT_VECTOR ] );
}

void InterruptManager_t::UsageFaultHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USAGE_FAULT_VECTOR ]( m_pContextTable[ INTERRUPT_USAGE_FAULT_VECTOR ] );
}

void InterruptManager_t::SvCallHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SVCALL_VECTOR ]( m_pContextTable[ INTERRUPT_SVCALL_VECTOR ] );
}

void InterruptManager_t::DebugMonitorHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DEBUG_MONITOR_VECTOR ]( m_pContextTable[ INTERRUPT_DEBUG_MONITOR_VECTOR ] );
}

void InterruptManager_t::PendSvHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_PENDSV_VECTOR ]( m_pContextTable[ INTERRUPT_PENDSV_VECTOR ] );
}

void InterruptManager_t::SysTickHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SYSTICK_VECTOR ]( m_pContextTable[ INTERRUPT_SYSTICK_VECTOR ] );
}

void InterruptManager_t::WwdgIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_WWDG_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_WWDG_IRQ_VECTOR ] );
}

void InterruptManager_t::PvdIRQHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_PVD_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_PVD_IRQ_VECTOR ] );
}
void InterruptManager_t::TampStampIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TAMP_STAMP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TAMP_STAMP_IRQ_VECTOR ] );
}

void InterruptManager_t::RtcWkupIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_RTC_WKUP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_RTC_WKUP_IRQ_VECTOR ] );
}

void InterruptManager_t::FlashIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_FLASH_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_FLASH_IRQ_VECTOR ] );
}

void InterruptManager_t::RccIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_RCC_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_RCC_IRQ_VECTOR ] );
}

void InterruptManager_t::Exti0IrqHandler( void )
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        fp_IntRoutineTable[ INTERRUPT_EXTI0_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_EXTI0_IRQ_VECTOR ] );
    }

    EXTI_ClearITPendingBit(EXTI_Line0);
}

void InterruptManager_t::Exti1IrqHandler( void )
{
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        fp_IntRoutineTable[ INTERRUPT_EXTI1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_EXTI1_IRQ_VECTOR ] );
    }

    EXTI_ClearITPendingBit(EXTI_Line1);
}

void InterruptManager_t::Exti2IrqHandler( void )
{
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        fp_IntRoutineTable[ INTERRUPT_EXTI2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_EXTI2_IRQ_VECTOR ] );
    }

    EXTI_ClearITPendingBit(EXTI_Line2);
}

void InterruptManager_t::Exti3IrqHandler( void )
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        fp_IntRoutineTable[ INTERRUPT_EXTI3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_EXTI3_IRQ_VECTOR ] );
    }

    EXTI_ClearITPendingBit(EXTI_Line3);
}

void InterruptManager_t::Exti4IrqHandler( void )
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        fp_IntRoutineTable[ INTERRUPT_EXTI4_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_EXTI4_IRQ_VECTOR ] );
    }

    EXTI_ClearITPendingBit(EXTI_Line4);
}

void InterruptManager_t::Dma1Stream0IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM0_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM0_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM1_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream2IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM2_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream3IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM3_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream4IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM4_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM4_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream5IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM5_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM5_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream6IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM6_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM6_IRQ_VECTOR ] );
}

void InterruptManager_t::AdcIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_ADC1_ADC2_ADC3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_ADC1_ADC2_ADC3_IRQ_VECTOR ] );
}

void InterruptManager_t::Can1TxIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN1_TX_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN1_TX_IRQ_VECTOR ] );
}

void InterruptManager_t::Can1Rx0IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN1_RX0_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN1_RX0_IRQ_VECTOR ] );
}

void InterruptManager_t::Can1Rx1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN1_RX1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN1_RX1_IRQ_VECTOR ] );
}

void InterruptManager_t::Can1SceIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN1_SCE_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN1_SCE_IRQ_VECTOR ] );
}

void InterruptManager_t::Exti95IrqHandler( void )
{
    uint32_t line  = 0;
    uint32_t index = 0;

    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        line  = EXTI_Line5;
        index = INTERRUPT_EXTI5_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        line  = EXTI_Line6;
        index = INTERRUPT_EXTI6_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        line  = EXTI_Line7;
        index = INTERRUPT_EXTI7_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        line  = EXTI_Line8;
        index = INTERRUPT_EXTI8_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
        line  = EXTI_Line9;
        index = INTERRUPT_EXTI9_IRQ_VECTOR;
    }

    fp_IntRoutineTable[ index ]( m_pContextTable[ index ] );

    EXTI_ClearITPendingBit(line);
}

void InterruptManager_t::Tim1BrkTim9IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM1_BRK_TIM9_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM1_BRK_TIM9_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim1UpTim10IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM1_UP_TIM10_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM1_UP_TIM10_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim1TrgComTim11IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM1_TRG_COM_TIM11_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM1_TRG_COM_TIM11_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim1CaptureCompareIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM1_CAPTURE_COMPARE_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM1_CAPTURE_COMPARE_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim2IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM2_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim3IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM3_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim4IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM4_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM4_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c1EventIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C1_EVENT_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C1_EVENT_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c1ErrorIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C1_ERROR_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C1_ERROR_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c2EventIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C2_EVENT_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C2_EVENT_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c2ErrorIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C2_ERROR_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C2_ERROR_IRQ_VECTOR ] );
}

void InterruptManager_t::Spi1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SPI1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_SPI1_IRQ_VECTOR ] );
}

void InterruptManager_t::Spi2IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SPI2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_SPI2_IRQ_VECTOR ] );
}

void InterruptManager_t::Usart1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USART1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_USART1_IRQ_VECTOR ] );
}

void InterruptManager_t::Usart2IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USART2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_USART2_IRQ_VECTOR ] );
}

void InterruptManager_t::Usart3IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USART3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_USART3_IRQ_VECTOR ] );
}

void InterruptManager_t::Exti1510IrqHandler( void )
{
    uint32_t line  = 0;
    uint32_t index = 0;

    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        line  = EXTI_Line10;
        index = INTERRUPT_EXTI10_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        line  = EXTI_Line11;
        index = INTERRUPT_EXTI11_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        line  = EXTI_Line12;
        index = INTERRUPT_EXTI12_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        line  = EXTI_Line13;
        index = INTERRUPT_EXTI13_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        line  = EXTI_Line14;
        index = INTERRUPT_EXTI14_IRQ_VECTOR;
    }
    else if(EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        line  = EXTI_Line15;
        index = INTERRUPT_EXTI15_IRQ_VECTOR;
    }

    fp_IntRoutineTable[ index ]( m_pContextTable[ index ] );

    EXTI_ClearITPendingBit(line);
}

void InterruptManager_t::RtcAlarmIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_RTC_Alarm_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_RTC_Alarm_IRQ_VECTOR ] );
}

void InterruptManager_t::OtgFsWkupIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_OTG_FS_WKUP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_OTG_FS_WKUP_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim8BrkTim12IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM8_BRK_TIM12_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM8_BRK_TIM12_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim8UpTim13IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM8_UP_TIM13_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM8_UP_TIM13_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim8TrgComTim14IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM8_TRG_COM_TIM14_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM8_TRG_COM_TIM14_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim8CaptureCompareIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM8_CC_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM8_CC_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma1Stream7IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA1_STREAM7_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA1_STREAM7_IRQ_VECTOR ] );
}

void InterruptManager_t::FsmcIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_FSMC_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_FSMC_IRQ_VECTOR ] );
}

void InterruptManager_t::SdioIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SDIO_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_SDIO_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim5IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM5_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM5_IRQ_VECTOR ] );
}

void InterruptManager_t::Spi3IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_SPI3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_SPI3_IRQ_VECTOR ] );
}

void InterruptManager_t::Uart4IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_UART4_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_UART4_IRQ_VECTOR ] );
}

void InterruptManager_t::Uart5IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_UART5_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_UART5_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim6DacIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM6_DAC_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM6_DAC_IRQ_VECTOR ] );
}

void InterruptManager_t::Tim7IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_TIM7_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_TIM7_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream0IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM0_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM0_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM1_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream2IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM2_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM2_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream3IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM3_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM3_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream4IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM4_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM4_IRQ_VECTOR ] );
}

void InterruptManager_t::EthIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_ETH_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_ETH_IRQ_VECTOR ] );
}

void InterruptManager_t::EthWkupIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_ETH_WKUP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_ETH_WKUP_IRQ_VECTOR ] );
}

void InterruptManager_t::Can2TxIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN2_TX_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN2_TX_IRQ_VECTOR ] );
}

void InterruptManager_t::Can2Rx0IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN2_RX0_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN2_RX0_IRQ_VECTOR ] );
}

void InterruptManager_t::Can2Rx1IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN2_RX1_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN2_RX1_IRQ_VECTOR ] );
}

void InterruptManager_t::Can2SceIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CAN2_SCE_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CAN2_SCE_IRQ_VECTOR ] );
}

void InterruptManager_t::UsbOtgFsIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USB_OTG_FS_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_USB_OTG_FS_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream5IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM5_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM5_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream6IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM6_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM6_IRQ_VECTOR ] );
}

void InterruptManager_t::Dma2Stream7IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DMA2_STREAM7_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DMA2_STREAM7_IRQ_VECTOR ] );
}

void InterruptManager_t::Usart6IrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_USART6_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_USART6_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c3EventIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C3_EV_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C3_EV_IRQ_VECTOR ] );
}

void InterruptManager_t::I2c3ErrorIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_I2C3_ER_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_I2C3_ER_IRQ_VECTOR ] );
}

void InterruptManager_t::OtgHsEp1OutIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_OTG_HS_EP1_OUT_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_OTG_HS_EP1_OUT_IRQ_VECTOR ] );
}

void InterruptManager_t::OtgHsEp1InIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_OTG_HS_EP1_IN_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_OTG_HS_EP1_IN_IRQ_VECTOR ] );
}

void InterruptManager_t::OtgHsWkupIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_OTG_HS_WKUP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_OTG_HS_WKUP_IRQ_VECTOR ] );
}

void InterruptManager_t::OtgHsIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_OTG_HS_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_OTG_HS_IRQ_VECTOR ] );
}

void InterruptManager_t::DcmiIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_DCMI_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_DCMI_IRQ_VECTOR ] );
}

void InterruptManager_t::CrypIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_CRYP_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_CRYP_IRQ_VECTOR ] );
}

void InterruptManager_t::HashRngIrqHandler( void )
{
    fp_IntRoutineTable[ INTERRUPT_HASH_RNG_IRQ_VECTOR ]( m_pContextTable[ INTERRUPT_HASH_RNG_IRQ_VECTOR ] );
}
//--------------------------------------------------------------------------- //


// --------------------------- Interrupt Handlers Table ----------------------//

#pragma language = extended   
#pragma segment  = "CSTACK"
#pragma location = ".intvec"
__root const InterruptManager_t::HandlerItem_t InterruptManager_t::m_InterruptVectorTable[] = 
{
    { .pHandler = __sfe( "CSTACK" ) }       ,   
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
