

#include "PS2Keyboard.h"


// Pin config
#define DATA                PORTA, PIN_0
#define CLOCK               PORTA, PIN_1
#define EXTI_LINE           EXTI_Line1
#define EXTI_TRIGGER        EXTI_Trigger_Falling
#define IRQ_CHANNEL         EXTI1_IRQn
#define PREEMPTION_PRIORITY 0x0F
#define SUB_PRIORITY        0x0F


void PS2Keyboard_t::Init( void )
{
    m_DataPin  = new GpioPin_t(DATA );
    m_ClockPin = new GpioPin_t(CLOCK);

    m_DataPin->MakeInPullUp();
    m_ClockPin->MakeInPullUp();

    // FIXME
    // Create smth to mannage this
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

    /* Configure EXTI*/
    EXTI_InitStruct.EXTI_Line    = EXTI_LINE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    /* Enable and set EXTI Line Interrupt to the lowest priority */
    NVIC_InitStruct.NVIC_IRQChannel                   = IRQ_CHANNEL;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = PREEMPTION_PRIORITY;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = SUB_PRIORITY;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void PS2Keyboard_t::OnInterrupt( void )
{
    static uint8_t started  = 0;
    static uint8_t bitCount = 0;
    static uint8_t data     = 0;
    static uint8_t parity   = 0;

    uint8_t dataBit = m_DataPin->Read();

    if( started == 1 )
    {
        if( bitCount < 8 ) // Data bit
        {
            data |= dataBit << bitCount;

            if( dataBit )
            {
                parity++;
            }
        }
        else if( bitCount == 8 ) // Parity bit
        {
            if( !(parity % 2) == dataBit )
            {
                parity = 1;
            }
            else
            {
                parity = 0;
            }
        }
        else // Stop bit
        {
            if( parity && dataBit )
            {
                DecodeData( data );
            }

            started  = 0;
        }

        bitCount++;
    }
    else
    {
        if( dataBit == 0 )
        {
            started  = 1;
            bitCount = 0;
            data     = 0;
            parity   = 0;
        }
    }
}

void PS2Keyboard_t::InterruptHandler( void* pContext )
{
    reinterpret_cast< PS2Keyboard_t* >( pContext )->OnInterrupt();
}

void PS2Keyboard_t::DecodeData( uint8_t data )
{
    static uint8_t waitBytes  = 0;
    static uint8_t extendCode = 0;
    static uint8_t breakCode  = 0;

    if( waitBytes )
    {
        --waitBytes;
        return;
    }

    switch( data )
    {
        case 0xE0:
        {
            extendCode = 1;
            return;
        }
        case 0xE1: // PAUSE
        {
            waitBytes = 7;
            return;
        }
        case 0xF0:
        {
            breakCode = 1;
            return;
        }
        case 0x12: // L Shift
        case 0x59: // R Shift
        {
           m_Key.ModifKeysStates.Shift = !breakCode;
           break;
        }
        case 0x14: // L R Ctrl
        {
            m_Key.ModifKeysStates.Ctrl = !breakCode;
            break;
        }
        case 0x11: // L R Alt
        {
            m_Key.ModifKeysStates.Alt  = !breakCode;
            break;
        }
        case 0x77: // NumLock
        {
            // TODO: LED ON/OFF
            m_Key.ModifKeysStates.NumLock = !m_Key.ModifKeysStates.NumLock;
            break;
        }
        case 0x58: // CapsLock
        {
            // TODO: LED ON/OFF
            m_Key.ModifKeysStates.CapsLock = !m_Key.ModifKeysStates.CapsLock;
            break;
        }
        case 0x7E: // ScrollLock
        {
            // TODO: LED ON/OFF
            m_Key.ModifKeysStates.ScrollLock = !m_Key.ModifKeysStates.ScrollLock;
            break;
        }
    }

    if( m_CallBack )
    {
        m_Key.CharCode        = KeyCodeToCharCode( data );
        m_Key.KeyCode         = ScanCodeToKeyCode( data, extendCode );
        m_Key.ScanCode        = data;
        m_Key.ExtendedKeyFlag = extendCode;
        breakCode ? m_Key.Event = KEY_RELEASED : m_Key.Event = KEY_PRESSED;

        m_CallBack( m_Context, m_Key );
    }

    waitBytes  = 0;
    extendCode = 0;
    breakCode  = 0;
}
