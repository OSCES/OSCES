#include "PS2KeyboardPlatform.h"
#include "InterruptManager.h"

// Pin config
#define DATA                PORTA, PIN_0
#define CLOCK               PORTA, PIN_1
#define EXTI_LINE           EXTI_Line1
#define EXTI_TRIGGER        EXTI_Trigger_Falling
#define IRQ_CHANNEL         EXTI1_IRQn
#define PREEMPTION_PRIORITY 0x0F
#define SUB_PRIORITY        0x0F


void KeyboardPlatform_t::Init()
{
    m_DataPin  = new GpioPin_t( DATA  );
    m_ClockPin = new GpioPin_t( CLOCK );

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
    
    InterruptManager_t::RegisterInterrupt( this, INTERRUPT_EXTI1_IRQ_VECTOR, InterruptHandler );
}

void KeyboardPlatform_t::OnInterrupt()
{
    uint8_t dataBit = m_DataPin->Read();

    if( m_started == 1 )
    {
        if( m_bitCount < 8 ) // Data bit
        {
            data |= dataBit << bitCount;

            if( dataBit )
            {
                m_parity++;
            }
        }
        else if( m_bitCount == 8 ) // Parity bit
        {
            if( !( m_parity % 2 ) == dataBit )
            {
                m_parity = 1;
            }
            else
            {
                m_parity = 0;
            }
        }
        else // Stop bit
        {
            if( m_parity && dataBit )
            {
                DecodeData( data );
            }

            m_started = 0;
        }

        m_bitCount++;
    }
    else
    {
        if( dataBit == 0 )
        {
            m_started  = 1;
            m_bitCount = 0;
            m_data     = 0;
            m_parity   = 0;
        }
    }
}

void KeyboardPlatform_t::InterruptHandler( void* pContext )
{
    static_cast< KeyboardPlatform_t* >( pContext )->OnInterrupt();
}

void KeyboardPlatform_t::DecodeData( uint8_t data )
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

    if( 0 != m_fpCallBack )
    {
        m_Key.CharCode        = KeyCodeToCharCode( data );
        m_Key.KeyCode         = ScanCodeToKeyCode( data, extendCode );
        m_Key.ExtendedKeyFlag = extendCode;
        m_Key.ScanCode        = data;
        m_Key.Event           = breakCode ? KEY_RELEASED : KEY_PRESSED;

        m_fpCallBack( m_pContext, m_Key );
    }

    waitBytes  = 0;
    extendCode = 0;
    breakCode  = 0;
}
