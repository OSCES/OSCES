#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <stdint.h>

typedef void ( *InterruptRoutine_t )( void* pContext );

#define INTERRUPT_MANAGER_VECTORS_AMOUNT 105

enum
{
    INTERRUPT_RESET_VECTOR                 = 0,
    INTERRUPT_NMI_VECTOR                      ,
    INTERRUPT_HARD_FAULT_VECTOR               ,
    INTERRUPT_MEM_MANAGE_VECTOR               ,
    INTERRUPT_BUS_FAULT_VECTOR                , 
    INTERRUPT_USAGE_FAULT_VECTOR              ,
    INTERRUPT_RESERVED_VECTOR0                ,
    INTERRUPT_RESERVED_VECTOR1                ,
    INTERRUPT_RESERVED_VECTOR2                ,
    INTERRUPT_RESERVED_VECTOR3                ,
    INTERRUPT_SVCALL_VECTOR                   ,
    INTERRUPT_DEBUG_MONITOR_VECTOR            ,
    INTERRUPT_RESERVED_VECTOR4                ,
    INTERRUPT_PENDSV_VECTOR                   ,
    INTERRUPT_SYSTICK_VECTOR                  ,

    //External Interrupts
    INTERRUPT_WWDG_IRQ_VECTOR                 ,                         
    INTERRUPT_PVD_IRQ_VECTOR                  ,                
    INTERRUPT_TAMP_STAMP_IRQ_VECTOR           ,         
    INTERRUPT_RTC_WKUP_IRQ_VECTOR             ,            
    INTERRUPT_FLASH_IRQ_VECTOR                ,                        
    INTERRUPT_RCC_IRQ_VECTOR                  ,                           
    INTERRUPT_EXTI0_IRQ_VECTOR                , 
    INTERRUPT_EXTI1_IRQ_VECTOR                ,                         
    INTERRUPT_EXTI2_IRQ_VECTOR                ,                          
    INTERRUPT_EXTI3_IRQ_VECTOR                ,                      
    INTERRUPT_EXTI4_IRQ_VECTOR                ,
    INTERRUPT_EXTI5_IRQ_VECTOR                ,
    INTERRUPT_EXTI6_IRQ_VECTOR                ,
    INTERRUPT_EXTI7_IRQ_VECTOR                ,
    INTERRUPT_EXTI8_IRQ_VECTOR                ,
    INTERRUPT_EXTI9_IRQ_VECTOR                ,
    INTERRUPT_EXTI10_IRQ_VECTOR               ,
    INTERRUPT_EXTI11_IRQ_VECTOR               ,
    INTERRUPT_EXTI12_IRQ_VECTOR               ,
    INTERRUPT_EXTI13_IRQ_VECTOR               ,
    INTERRUPT_EXTI14_IRQ_VECTOR               ,
    INTERRUPT_EXTI15_IRQ_VECTOR               ,
    INTERRUPT_DMA1_STREAM0_IRQ_VECTOR         ,                                   
    INTERRUPT_DMA1_STREAM1_IRQ_VECTOR         ,                                   
    INTERRUPT_DMA1_STREAM2_IRQ_VECTOR         ,                                  
    INTERRUPT_DMA1_STREAM3_IRQ_VECTOR         ,                                   
    INTERRUPT_DMA1_STREAM4_IRQ_VECTOR         ,                                  
    INTERRUPT_DMA1_STREAM5_IRQ_VECTOR         ,                                 
    INTERRUPT_DMA1_STREAM6_IRQ_VECTOR         ,                        
    INTERRUPT_ADC1_ADC2_ADC3_IRQ_VECTOR       ,                            
    INTERRUPT_CAN1_TX_IRQ_VECTOR              ,                                        
    INTERRUPT_CAN1_RX0_IRQ_VECTOR             ,                                     
    INTERRUPT_CAN1_RX1_IRQ_VECTOR             ,                                
    INTERRUPT_CAN1_SCE_IRQ_VECTOR             ,                                                       
    INTERRUPT_TIM1_BRK_TIM9_IRQ_VECTOR        ,                   
    INTERRUPT_TIM1_UP_TIM10_IRQ_VECTOR        ,                 
    INTERRUPT_TIM1_TRG_COM_TIM11_IRQ_VECTOR   ,
    INTERRUPT_TIM1_CAPTURE_COMPARE_IRQ_VECTOR ,                                 
    INTERRUPT_TIM2_IRQ_VECTOR                 ,              
    INTERRUPT_TIM3_IRQ_VECTOR                 ,                      
    INTERRUPT_TIM4_IRQ_VECTOR                 ,                  
    INTERRUPT_I2C1_EVENT_IRQ_VECTOR           ,                              
    INTERRUPT_I2C1_ERROR_IRQ_VECTOR           ,                             
    INTERRUPT_I2C2_EVENT_IRQ_VECTOR           ,                           
    INTERRUPT_I2C2_ERROR_IRQ_VECTOR           ,                               
    INTERRUPT_SPI1_IRQ_VECTOR                 ,                     
    INTERRUPT_SPI2_IRQ_VECTOR                 ,              
    INTERRUPT_USART1_IRQ_VECTOR               ,                         
    INTERRUPT_USART2_IRQ_VECTOR               ,                      
    INTERRUPT_USART3_IRQ_VECTOR               ,                                                  
    INTERRUPT_RTC_Alarm_IRQ_VECTOR            ,                  
    INTERRUPT_OTG_FS_WKUP_IRQ_VECTOR          ,                        
    INTERRUPT_TIM8_BRK_TIM12_IRQ_VECTOR       ,                  
    INTERRUPT_TIM8_UP_TIM13_IRQ_VECTOR        ,                 
    INTERRUPT_TIM8_TRG_COM_TIM14_IRQ_VECTOR   ,
    INTERRUPT_TIM8_CC_IRQ_VECTOR              ,                                   
    INTERRUPT_DMA1_STREAM7_IRQ_VECTOR         ,                                           
    INTERRUPT_FSMC_IRQ_VECTOR                 ,       
    INTERRUPT_SDIO_IRQ_VECTOR                 ,           
    INTERRUPT_TIM5_IRQ_VECTOR                 ,          
    INTERRUPT_SPI3_IRQ_VECTOR                 ,               
    INTERRUPT_UART4_IRQ_VECTOR                ,              
    INTERRUPT_UART5_IRQ_VECTOR                ,              
    INTERRUPT_TIM6_DAC_IRQ_VECTOR             ,                   
    INTERRUPT_TIM7_IRQ_VECTOR                 ,               
    INTERRUPT_DMA2_STREAM0_IRQ_VECTOR         ,                      
    INTERRUPT_DMA2_STREAM1_IRQ_VECTOR         ,                      
    INTERRUPT_DMA2_STREAM2_IRQ_VECTOR         ,                     
    INTERRUPT_DMA2_STREAM3_IRQ_VECTOR         ,                      
    INTERRUPT_DMA2_STREAM4_IRQ_VECTOR         ,                     
    INTERRUPT_ETH_IRQ_VECTOR                  ,                              
    INTERRUPT_ETH_WKUP_IRQ_VECTOR             ,                       
    INTERRUPT_CAN2_TX_IRQ_VECTOR              ,                              
    INTERRUPT_CAN2_RX0_IRQ_VECTOR             ,                                
    INTERRUPT_CAN2_RX1_IRQ_VECTOR             ,                          
    INTERRUPT_CAN2_SCE_IRQ_VECTOR             ,                               
    INTERRUPT_USB_OTG_FS_IRQ_VECTOR           ,                        
    INTERRUPT_DMA2_STREAM5_IRQ_VECTOR         ,                      
    INTERRUPT_DMA2_STREAM6_IRQ_VECTOR         ,                        
    INTERRUPT_DMA2_STREAM7_IRQ_VECTOR         ,                   
    INTERRUPT_USART6_IRQ_VECTOR               ,                  
    INTERRUPT_I2C3_EV_IRQ_VECTOR              ,                      
    INTERRUPT_I2C3_ER_IRQ_VECTOR              ,                     
    INTERRUPT_OTG_HS_EP1_OUT_IRQ_VECTOR       ,                      
    INTERRUPT_OTG_HS_EP1_IN_IRQ_VECTOR        ,                       
    INTERRUPT_OTG_HS_WKUP_IRQ_VECTOR          ,                         
    INTERRUPT_OTG_HS_IRQ_VECTOR               ,                                      
    INTERRUPT_DCMI_IRQ_VECTOR                 ,                                            
    INTERRUPT_CRYP_IRQ_VECTOR                 ,                                     
    INTERRUPT_HASH_RNG_IRQ_VECTOR
};

class InterruptManager_t
{
public:
    static void Init();    
    static void RegisterInterrupt( void* pContext, uint16_t vector, InterruptRoutine_t fp_Routine );
    
private:
    
    union HandlerItem_t
    {
        void ( *fp_Handler )( void );
        void *pHandler;
    };

    static const HandlerItem_t m_InterruptVectorTable[];
    static void*               m_pContextTable[];
    static InterruptRoutine_t  fp_IntRoutineTable[];
    
private:
    static void DefaultInterruptRoutine( void* pContext );   

    static void ResetHandler( void );
    static void NmiHandler( void );
    static void HardFaultHandler( void );
    static void MemManageHandler( void );
    static void BusFaultHandler( void );
    static void UsageFaultHandler( void );
    static void SvCallHandler( void );
    static void DebugMonitorHandler( void );
    static void PendSvHandler( void );
    static void SysTickHandler( void );
    static void WwdgIrqHandler( void );
    static void PvdIRQHandler( void );
    static void TampStampIrqHandler( void );
    static void RtcWkupIrqHandler( void );
    static void FlashIrqHandler( void );
    static void RccIrqHandler( void );
    static void Exti0IrqHandler( void );
    static void Exti1IrqHandler( void );
    static void Exti2IrqHandler( void );
    static void Exti3IrqHandler( void );
    static void Exti4IrqHandler( void );
    static void Dma1Stream0IrqHandler( void );
    static void Dma1Stream1IrqHandler( void );
    static void Dma1Stream2IrqHandler( void );
    static void Dma1Stream3IrqHandler( void );
    static void Dma1Stream4IrqHandler( void );
    static void Dma1Stream5IrqHandler( void );
    static void Dma1Stream6IrqHandler( void );
    static void AdcIrqHandler( void );
    static void Can1TxIrqHandler( void );
    static void Can1Rx0IrqHandler( void );
    static void Can1Rx1IrqHandler( void );
    static void Can1SceIrqHandler( void );
    static void Exti95IrqHandler( void );
    static void Tim1BrkTim9IrqHandler( void );
    static void Tim1UpTim10IrqHandler( void );
    static void Tim1TrgComTim11IrqHandler( void );
    static void Tim1CaptureCompareIrqHandler( void );
    static void Tim2IrqHandler( void );
    static void Tim3IrqHandler( void );
    static void Tim4IrqHandler( void );
    static void I2c1EventIrqHandler( void );
    static void I2c1ErrorIrqHandler( void );
    static void I2c2EventIrqHandler( void );
    static void I2c2ErrorIrqHandler( void );
    static void Spi1IrqHandler( void );
    static void Spi2IrqHandler( void );
    static void Usart1IrqHandler( void );
    static void Usart2IrqHandler( void );
    static void Usart3IrqHandler( void );
    static void Exti1510IrqHandler( void );
    static void RtcAlarmIrqHandler( void );
    static void OtgFsWkupIrqHandler( void );
    static void Tim8BrkTim12IrqHandler( void );
    static void Tim8UpTim13IrqHandler( void );
    static void Tim8TrgComTim14IrqHandler( void );
    static void Tim8CaptureCompareIrqHandler( void );
    static void Dma1Stream7IrqHandler( void );
    static void FsmcIrqHandler( void );
    static void SdioIrqHandler( void );
    static void Tim5IrqHandler( void );
    static void Spi3IrqHandler( void );
    static void Uart4IrqHandler( void );
    static void Uart5IrqHandler( void );
    static void Tim6DacIrqHandler( void );
    static void Tim7IrqHandler( void );
    static void Dma2Stream0IrqHandler( void );
    static void Dma2Stream1IrqHandler( void );
    static void Dma2Stream2IrqHandler( void );
    static void Dma2Stream3IrqHandler( void );
    static void Dma2Stream4IrqHandler( void );
    static void EthIrqHandler( void );
    static void EthWkupIrqHandler( void );
    static void Can2TxIrqHandler( void );
    static void Can2Rx0IrqHandler( void );
    static void Can2Rx1IrqHandler( void );
    static void Can2SceIrqHandler( void );
    static void UsbOtgFsIrqHandler( void );
    static void Dma2Stream5IrqHandler( void );
    static void Dma2Stream6IrqHandler( void );
    static void Dma2Stream7IrqHandler( void );
    static void Usart6IrqHandler( void );
    static void I2c3EventIrqHandler( void );
    static void I2c3ErrorIrqHandler( void );
    static void OtgHsEp1OutIrqHandler( void );
    static void OtgHsEp1InIrqHandler( void );
    static void OtgHsWkupIrqHandler( void );
    static void OtgHsIrqHandler( void );
    static void DcmiIrqHandler( void );
    static void CrypIrqHandler( void );
    static void HashRngIrqHandler( void );
};


#endif // INTERRUPT_MANAGER_H
