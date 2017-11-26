#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <stdint.h>

typedef void (*InterruptRoutine)(void *context);

enum InterruptVector
{
    ResetVector = 0,
    NmiVector,
    HardFaultVector,
    MemManageVector,
    BusFaultVector,
    UsageFaultVector,
    ReservedVector0,
    ReservedVector1,
    ReservedVector2,
    ReservedVector3,
    SvCallVector,
    DebugMonitorVector,
    ReservedVector4,
    PendSvVector,
    SysTickVector,

    //External Interrupts
    WwdgIrqVector,
    PvdIrqVector,
    TampStampIrqVector,
    RtcWkupIrqVector,
    FlashIrqVector,
    RccIrqVector,
    Exti0IrqVector,
    Exti1IrqVector,
    Exti2IrqVector,
    Exti3IrqVector,
    Exti4IrqVector,
    Exti5IrqVector,
    Exti6IrqVector,
    Exti7IrqVector,
    Exti8IrqVector,
    Exti9IrqVector,
    Exti10IrqVector,
    Exti11IrqVector,
    Exti12IrqVector,
    Exti13IrqVector,
    Exti14IrqVector,
    Exti15IrqVector,
    Dma1Stream0IrqVector,
    Dma1Stream1IrqVector,
    Dma1Stream2IrqVector,
    Dma1Stream3IrqVector,
    Dma1Stream4IrqVector,
    Dma1Stream5IrqVector,
    Dma1Stream6IrqVector,
    Adc1Adc2Adc3IrqVector,
    Can1TxIrqVector,
    Can1Rx0IrqVector,
    Can1Rx1IrqVector,
    Can1SceIrqVector,
    Tim1BrkTim9IrqVector,
    Tim1UpTim10IqrVector,
    Tim1TrgComTim11IrqVector,
    Tim1CaptureCompareIrqVector,
    Tim2IrqVector,
    Tim3IrqVector,
    Tim4IrqVector,
    I2c1EventIrqVector,
    I2c1ErrorIrqVector,
    I2c2EventIrqVector,
    I2c2ErrorIrqVector,
    Spi1IrqVector,
    Spi2IrqVector,
    Usart1IrqVector,
    Usart2IrqVector,
    Usart3IrqVector,
    RtcAlarmIrqVector,
    OtgFsWkupIrqVector,
    Tim8BrkTim12IrqVector,
    Tim8UpTim13IrqVector,
    Tim8TrgComTim14IrqVector,
    Tim8CcIrqVector,
    Dma1Stream7IrqVector,
    FsmcIrqVector,
    SdioIrqVector,
    Tim5IrqVector,
    Spi3IrqVector,
    Uart4IrqVector,
    Uart5IrqVector,
    Tim6DacIrqVector,
    Tim7IrqVector,
    Dma2Stream0IrqVector,
    Dma2Stream1IrqVector,
    Dma2Stream2IrqVector,
    Dma2Stream3IrqVector,
    Dma2Stream4IrqVector,
    EthIrqVector,
    EthWkupIrqVector,
    Can2TxIrqVector,
    Can2Rx0IrqVector,
    Can2Rx1IrqVector,
    Can2SceIrqVector,
    UsbOtgFsIrqVector,
    Dma2Stream5IrqVector,
    Dma2Stream6IrqVector,
    Dma2Stream7IrqVector,
    Usart6IrqVector,
    I2c3EventIrqVector,
    I2c3ErrorIrqVector,
    OtgHsEp1OutIrqVector,
    OtgHsEp1InIrqVector,
    OtgHsWkupIrqVector,
    OtgHsIrqVector,
    DcmiIrqVector,
    CrypIrqVector,
    HashRngIrqVector,

    VectorsCount
};

class InterruptManager
{
public:
    static void init();
    static void registerInterrupt(void *context, InterruptVector vector, InterruptRoutine routine);
    static void unregisterInterrupt(InterruptVector vector);

    static void disableInterrupt();
    static void enableInterrupt();

private:

    union HandlerItem
    {
        void (*fp_Handler)(void);
        void *handler;
    };

    static void *m_contextTable[];
    static const HandlerItem m_interruptVectorTable[];
    static InterruptRoutine m_intRoutineTable[];

private:
    static void DefaultInterruptRoutine(void *context);

    static void ResetHandler();
    static void NmiHandler();
    static void HardFaultHandler();
    static void MemManageHandler();
    static void BusFaultHandler();
    static void UsageFaultHandler();
    static void SvCallHandler();
    static void DebugMonitorHandler();
    static void PendSvHandler();
    static void SysTickHandler();
    static void WwdgIrqHandler();
    static void PvdIrqHandler();
    static void TampStampIrqHandler();
    static void RtcWkupIrqHandler();
    static void FlashIrqHandler();
    static void RccIrqHandler();
    static void Exti0IrqHandler();
    static void Exti1IrqHandler();
    static void Exti2IrqHandler();
    static void Exti3IrqHandler();
    static void Exti4IrqHandler();
    static void Dma1Stream0IrqHandler();
    static void Dma1Stream1IrqHandler();
    static void Dma1Stream2IrqHandler();
    static void Dma1Stream3IrqHandler();
    static void Dma1Stream4IrqHandler();
    static void Dma1Stream5IrqHandler();
    static void Dma1Stream6IrqHandler();
    static void AdcIrqHandler();
    static void Can1TxIrqHandler();
    static void Can1Rx0IrqHandler();
    static void Can1Rx1IrqHandler();
    static void Can1SceIrqHandler();
    static void Exti95IrqHandler();
    static void Tim1BrkTim9IrqHandler();
    static void Tim1UpTim10IrqHandler();
    static void Tim1TrgComTim11IrqHandler();
    static void Tim1CaptureCompareIrqHandler();
    static void Tim2IrqHandler();
    static void Tim3IrqHandler();
    static void Tim4IrqHandler();
    static void I2c1EventIrqHandler();
    static void I2c1ErrorIrqHandler();
    static void I2c2EventIrqHandler();
    static void I2c2ErrorIrqHandler();
    static void Spi1IrqHandler();
    static void Spi2IrqHandler();
    static void Usart1IrqHandler();
    static void Usart2IrqHandler();
    static void Usart3IrqHandler();
    static void Exti1510IrqHandler();
    static void RtcAlarmIrqHandler();
    static void OtgFsWkupIrqHandler();
    static void Tim8BrkTim12IrqHandler();
    static void Tim8UpTim13IrqHandler();
    static void Tim8TrgComTim14IrqHandler();
    static void Tim8CaptureCompareIrqHandler();
    static void Dma1Stream7IrqHandler();
    static void FsmcIrqHandler();
    static void SdioIrqHandler();
    static void Tim5IrqHandler();
    static void Spi3IrqHandler();
    static void Uart4IrqHandler();
    static void Uart5IrqHandler();
    static void Tim6DacIrqHandler();
    static void Tim7IrqHandler();
    static void Dma2Stream0IrqHandler();
    static void Dma2Stream1IrqHandler();
    static void Dma2Stream2IrqHandler();
    static void Dma2Stream3IrqHandler();
    static void Dma2Stream4IrqHandler();
    static void Dma2Stream5IrqHandler();
    static void Dma2Stream6IrqHandler();
    static void Dma2Stream7IrqHandler();
    static void EthIrqHandler();
    static void EthWkupIrqHandler();
    static void Can2TxIrqHandler();
    static void Can2Rx0IrqHandler();
    static void Can2Rx1IrqHandler();
    static void Can2SceIrqHandler();
    static void UsbOtgFsIrqHandler();
    static void Usart6IrqHandler();
    static void I2c3EventIrqHandler();
    static void I2c3ErrorIrqHandler();
    static void OtgHsEp1OutIrqHandler();
    static void OtgHsEp1InIrqHandler();
    static void OtgHsWkupIrqHandler();
    static void OtgHsIrqHandler();
    static void DcmiIrqHandler();
    static void CrypIrqHandler();
    static void HashRngIrqHandler();
};

#endif // INTERRUPT_MANAGER_H
