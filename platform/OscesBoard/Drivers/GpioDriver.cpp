
#include <assert.h>
#include "GpioDriver.h"
#include "ClockManager.h"

GpioPin::GpioPin(Port port, Pin pin) :
    m_port(0)
{
    m_port = static_cast<GPIO_TypeDef *>(port);
    m_pin = pin;

    ClockManager &clockManager = ClockManager::instance();

    switch (port)
    {
    case PortA: clockManager.enableGpioClock(ClockManager::PortA); break;
    case PortB: clockManager.enableGpioClock(ClockManager::PortB); break;
    case PortC: clockManager.enableGpioClock(ClockManager::PortC); break;
    case PortD: clockManager.enableGpioClock(ClockManager::PortD); break;
    case PortE: clockManager.enableGpioClock(ClockManager::PortE); break;
    case PortF: clockManager.enableGpioClock(ClockManager::PortF); break;
    case PortG: clockManager.enableGpioClock(ClockManager::PortG); break;
    case PortH: clockManager.enableGpioClock(ClockManager::PortH); break;
    case PortI: clockManager.enableGpioClock(ClockManager::PortI); break;
    default:
        assert(false);
        break;
    }
}

GpioPin::~GpioPin()
{
    // deinit
}

void GpioPin::initPin(PinMode pinMode, OutType outType, PullType pullType)
{
    GPIO_InitTypeDef gpioInitStruct;
    gpioInitStruct.GPIO_Pin   = m_pin;
    gpioInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    gpioInitStruct.GPIO_Mode  = static_cast<GPIOMode_TypeDef>(pinMode);
    gpioInitStruct.GPIO_OType = static_cast<GPIOOType_TypeDef>(outType);
    gpioInitStruct.GPIO_PuPd  = static_cast<GPIOPuPd_TypeDef>(pullType);

    GPIO_Init(m_port, &gpioInitStruct);
}

void GpioPin::makeOutOd( void )
{
    initPin(ModeOut, OutOd, PullNo);
}

void GpioPin::makeOut( void )
{
    initPin(ModeOut, OutPp, PullNo);
}

void GpioPin::makeInNonPull()
{
    makeOut();
}

void GpioPin::makeInPullUp()
{
    initPin(ModeIn, OutPp, PullUp);
}

void GpioPin::makeInPullDown()
{
    initPin(ModeIn, OutPp, PullDown);
}

void GpioPin::set()
{
    GPIO_SetBits(m_port, m_pin);
}

void GpioPin::clear()
{
    GPIO_ResetBits(m_port, m_pin);
}

uint8_t GpioPin::read()
{
    return GPIO_ReadInputDataBit(m_port, m_pin);
}

