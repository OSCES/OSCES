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

KeyboardPlatform::KeyboardPlatform() :
    m_dataPin(0),
    m_clockPin(0),
    m_started(false),
    m_bitCount(0),
    m_data(0),
    m_parity(0)
{
}

KeyboardPlatform::~KeyboardPlatform()
{
    delete m_dataPin;
    delete m_clockPin;
}

void KeyboardPlatform::init()
{
    m_dataPin  = new GpioPin(DATA);
    m_clockPin = new GpioPin(CLOCK);

    m_dataPin->makeInPullUp();
    m_clockPin->makeInPullUp();

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

    InterruptManager::registerInterrupt(this, InterruptVector::Exti1IrqVector, interruptHandler);
}

void KeyboardPlatform::proceedInterrupt()
{
    uint8_t dataBit = m_dataPin->read();

    if (m_started)
    {
        if (m_bitCount < 8) // Data bit
        {
            m_data |= dataBit << m_bitCount;

            if (dataBit)
                ++m_parity;
        }
        else if (m_bitCount == 8) // Parity bit
        {
            m_parity = !(m_parity % 2) == dataBit ? 1 : 0;
        }
        else // Stop bit
        {
            if (m_parity && dataBit)
                decodeData(m_data);
            m_started = false;
        }

        ++m_bitCount;
    }
    else
    {
        if (dataBit == 0)
        {
            m_started = true;
            m_bitCount = 0;
            m_data = 0;
            m_parity = 0;
        }
    }
}

void KeyboardPlatform::interruptHandler(void *context)
{
    static_cast<KeyboardPlatform *>(context)->proceedInterrupt();
}

void KeyboardPlatform::decodeData(uint8_t data)
{
    // TODO: State machine
    static uint8_t waitBytes = 0;
    static uint8_t extendCode = 0;
    static uint8_t breakCode = 0;

    if (waitBytes)
    {
        --waitBytes;
        return;
    }

    switch(data)
    {
    case 0xE0:
        extendCode = 1;
        return;
    case 0xE1: // PAUSE
        waitBytes = 7;
        return;
    case 0xF0:
        breakCode = 1;
        return;
    case 0x12: // L Shift
    case 0x59: // R Shift
        m_key.ModifKeysStates.Shift = !breakCode;
        break;
    case 0x14: // L R Ctrl
        m_key.ModifKeysStates.Ctrl = !breakCode;
        break;
    case 0x11: // L R Alt
        m_key.ModifKeysStates.Alt  = !breakCode;
        break;
    case 0x77: // NumLock
        // TODO: LED ON/OFF
        m_key.ModifKeysStates.NumLock = !m_key.ModifKeysStates.NumLock;
        break;
    case 0x58: // CapsLock
        // TODO: LED ON/OFF
        m_key.ModifKeysStates.CapsLock = !m_key.ModifKeysStates.CapsLock;
        break;
    case 0x7E: // ScrollLock
        // TODO: LED ON/OFF
        m_key.ModifKeysStates.ScrollLock = !m_key.ModifKeysStates.ScrollLock;
        break;
    }

    if (m_fpCallBack)
    {
        m_key.CharCode = charCodeFromkeyCode(data);
        m_key.KeyCode = keyCodeFromScanCode(data, extendCode);
        m_key.ExtendedKeyFlag = extendCode;
        m_key.ScanCode = data;
        m_key.Event = breakCode ? KeyReleased : KeyPressed;

        m_fpCallBack(m_context, m_key);
    }

    waitBytes = 0;
    extendCode = 0;
    breakCode = 0;
}
