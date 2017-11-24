#include "UDA1334_Driver.h"
#include "I2SDriver.h"
#include "GpioDriver.h"
#include "stm32f4xx_rcc.h"

static GpioPin pinSfor0( PortB, Pin0  );
static GpioPin pinSfor1( PortF, Pin11 );
static GpioPin pinMute ( PortB, Pin1  );
static GpioPin pinPcs  ( PortC, Pin5  );
static GpioPin pinDeem ( PortC, Pin4  );

// ??? What is this
const int Period = 20;

static void PinsInit()
{
    pinSfor0.makeOut();
    pinSfor1.makeOut();
    pinMute.makeOut();
    pinPcs.makeOut();
    pinDeem.makeOut();

    pinPcs.clear();

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void SetDataFormatI2S()
{
    pinSfor0.clear();
    pinSfor1.clear();
}

static void MuteControl(bool isMute)
{
    isMute ? pinMute.set() : pinMute.clear();
}

static void DeEmphasisControl(bool isOn)
{
    isOn ? pinDeem.set() : pinDeem.clear();
}

static void Timer2Init( uint32_t freqInHz )
{
    TIM_TimeBaseInitTypeDef TimerInitStruct;
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );

    TimerInitStruct.TIM_Prescaler         = 0;
    TimerInitStruct.TIM_Period            = Period;
    TimerInitStruct.TIM_ClockDivision     = 0;
    TimerInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TimerInitStruct.TIM_RepetitionCounter = 0; // Only for Tim 1,8
    TIM_TimeBaseInit(TIM2, &TimerInitStruct);

    TIM_Cmd(TIM2, ENABLE);
}

static void Timer2InitOutput4( uint32_t freqInHz )
{
    TIM_OCInitTypeDef OCInitStruct;
    OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
    OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    OCInitStruct.TIM_Pulse       = Period;
    OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC4Init(TIM2, &OCInitStruct);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);

    TIM_SetCompare4(TIM2, Period / 2);
}

static void SysClkInit()
{
    // TODO: Constants
    Timer2Init(12228000);
    Timer2InitOutput4(12228000);
}

void UDA1334_DriverInit()
{
    PinsInit();
    SetDataFormatI2S();
    MuteControl( false );
    DeEmphasisControl( false );
    SysClkInit();
    I2S_DriverInit();
}
