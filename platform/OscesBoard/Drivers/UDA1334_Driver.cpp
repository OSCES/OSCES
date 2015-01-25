#include "UDA1334_Driver.h"
#include "I2SDriver.h"
#include "GpioDriver.h"
#include "stm32f4xx_rcc.h"


static GpioPin_t pinSfor0( PORTB, PIN_0  );
static GpioPin_t pinSfor1( PORTF, PIN_11 );
static GpioPin_t pinMute ( PORTB, PIN_1  );
static GpioPin_t pinPcs  ( PORTC, PIN_5  );
static GpioPin_t pinDeem ( PORTC, PIN_4  );


static void PinsInit()
{
     
    pinSfor0.MakeOut();
    pinSfor1.MakeOut();
    pinMute.MakeOut();
    pinPcs.MakeOut();
    pinDeem.MakeOut();
        
    pinPcs.Clear();
    
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

static void SetDataFormatI2S()
{
    pinSfor0.Clear();
    pinSfor1.Clear();
}

static void MuteControl( bool isMute )
{
    if( true == isMute )
    {
        pinMute.Set();
    }
    else
    {
        pinMute.Clear();
    }
}

static void DeEmphasisControl( bool isOn )
{
    if( true == isOn )
    {
        pinDeem.Set();
    }
    else
    {
        pinDeem.Clear();
    }
}

#define PERIOD 20

static void Timer2Init( uint32_t freqInHz )
{
    TIM_TimeBaseInitTypeDef TimerInitStruct;
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE ); 

    TimerInitStruct.TIM_Prescaler         = 0;
    TimerInitStruct.TIM_Period            = PERIOD;
    TimerInitStruct.TIM_ClockDivision     = 0;
    TimerInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TimerInitStruct.TIM_RepetitionCounter = 0; // Only for Tim 1,8

    TIM_TimeBaseInit( TIM2, &TimerInitStruct );

    TIM_Cmd( TIM2, ENABLE );
}

static void Timer2InitOutput4( uint32_t freqInHz )
{
    TIM_OCInitTypeDef OCInitStruct;

    OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
    OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    OCInitStruct.TIM_Pulse       = PERIOD;
    OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;

    TIM_OC4Init( TIM2, &OCInitStruct );
    TIM_OC4PreloadConfig( TIM2, TIM_OCPreload_Enable );
    
    GPIO_PinAFConfig( GPIOB, GPIO_PinSource11, GPIO_AF_TIM2 );

    TIM_SetCompare4( TIM2, PERIOD / 2 );

}


static void SysClkInit()
{
    Timer2Init( 12228000 );
    Timer2InitOutput4( 12228000 );
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
