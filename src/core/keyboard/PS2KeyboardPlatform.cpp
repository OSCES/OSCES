#include "PS2KeyboardPlatform.h"
#include "InterruptManager.h"
#ifdef OSCES_BOARD
#include "GpioDriver.h"
#endif


#ifdef OSCES_BOARD
// Pin config
#define DATA                PortA, Pin0
#define CLOCK               PortA, Pin1
#define EXTI_LINE           EXTI_Line1
#define EXTI_TRIGGER        EXTI_Trigger_Falling
#define IRQ_CHANNEL         EXTI1_IRQn
#define PREEMPTION_PRIORITY 0x0F
#define SUB_PRIORITY        0x0F
#endif

static const uint8_t ExtendKeyOffset = 0x78;
static const KeyCode Set2KeyCodeTable[] =
{
    Key_Unknown, Key_F9, Key_Unknown, Key_F5, Key_F3, Key_F1, Key_F2, Key_F12, Key_Unknown, Key_F10, Key_F8, Key_F6, Key_F4, Key_Tab, Key_Accent, Key_Unknown,
    Key_Unknown, Key_LeftAlt, Key_LeftShift, Key_Unknown, Key_LeftCtrl, Key_Q, Key_1, Key_Unknown, Key_Unknown, Key_Unknown, Key_Z, Key_S, Key_A, Key_W, Key_2, Key_Unknown,
    Key_Unknown, Key_C, Key_X, Key_D, Key_E, Key_4, Key_3, Key_Unknown, Key_Unknown, Key_Spaec, Key_V, Key_F, Key_T, Key_R, Key_5, Key_Unknown,
    Key_Unknown, Key_N, Key_B, Key_H, Key_G, Key_Y, Key_6, Key_Unknown, Key_Unknown, Key_Unknown, Key_M, Key_J, Key_U, Key_7, Key_8, Key_Unknown,
    Key_Unknown, Key_Comma, Key_K, Key_I, Key_O, Key_0, Key_9, Key_Unknown, Key_Unknown, Key_Point, Key_Slash, Key_L, Key_Semicolon, Key_P, Key_Minus, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Apostrophe, Key_Unknown, Key_LeftBracket, Key_Equal, Key_Unknown, Key_Unknown, Key_Caps, Key_RightShift, Key_Enter, Key_RightBracket, Key_Unknown, Key_Backslash, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Backspace, Key_Unknown, Key_Unknown, Key_Num_1, Key_Unknown, Key_Num_4, Key_Num_7, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Num_0, Key_Num_Point, Key_Num_2, Key_Num_5, Key_Num_6, Key_Num_8, Key_Esc, Key_NumLock, Key_F11, Key_Num_Add, Key_Num_3, Key_Num_Minus, Key_Num_Multiply, Key_Num_9, Key_Scroll, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_F7, Key_RightAlt, Key_PrntScrn, Key_Unknown, Key_RightCtrl, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_LeftGui, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_RightGui, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Apps, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Num_Divide, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Num_Enter, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_End, Key_Unknown, Key_Left, Key_Home,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Insert, Key_Delete, Key_Down, Key_Unknown, Key_Right, Key_Up, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_PageDown, Key_Unknown, Key_Unknown,
    Key_PageUp, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown
};

KeyboardPlatform::KeyboardPlatform() :
    Keyboard(),
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
#ifdef OSCES_BOARD
    delete m_dataPin;
    delete m_clockPin;
#endif
}

void KeyboardPlatform::init()
{
#ifdef OSCES_BOARD
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
#endif

    InterruptManager::registerInterrupt(this, InterruptVector::Exti1IrqVector, interruptHandler);
}

// state
// receive data
//

void KeyboardPlatform::proceedInterrupt()
{
#ifdef OSCES_BOARD
    uint8_t dataBit = m_dataPin->read();
#else
    uint8_t dataBit = 0;
#endif

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
            m_parity = !((m_parity % 2) == dataBit) ? 1 : 0;
        }
        else // Stop bit
        {
            // call time of decodeData() function can be too long
            // so we can just skip next keyboard event
            // it should not be called inside irq function
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
        m_keyEvent.key.modifKeysStates.Shift = !breakCode;
        break;
    case 0x14: // L R Ctrl
        m_keyEvent.key.modifKeysStates.Ctrl = !breakCode;
        break;
    case 0x11: // L R Alt
        m_keyEvent.key.modifKeysStates.Alt  = !breakCode;
        break;
    case 0x77: // NumLock
        // TODO: LED ON/OFF
        m_keyEvent.key.modifKeysStates.NumLock = !m_keyEvent.key.modifKeysStates.NumLock;
        break;
    case 0x58: // CapsLock
        // TODO: LED ON/OFF
        m_keyEvent.key.modifKeysStates.CapsLock = !m_keyEvent.key.modifKeysStates.CapsLock;
        break;
    case 0x7E: // ScrollLock
        // TODO: LED ON/OFF
        m_keyEvent.key.modifKeysStates.ScrollLock = !m_keyEvent.key.modifKeysStates.ScrollLock;
        break;
    }

    m_keyEvent.key.text = '\0';
    m_keyEvent.key.keyCode = keyCodeFromScanCode(data, extendCode);
    m_keyEvent.key.extendedKeyFlag = extendCode;
    m_keyEvent.key.scanCode = data;
    m_keyEvent.eventType = breakCode ? KeyReleased : KeyPressed;
    proceedKeyEvent(m_keyEvent);

    waitBytes = 0;
    extendCode = 0;
    breakCode = 0;
}

KeyCode KeyboardPlatform::keyCodeFromScanCode(uint8_t scanCode, uint8_t extendKeyFlag)
{
    return Set2KeyCodeTable[extendKeyFlag ? scanCode + ExtendKeyOffset : scanCode];
}
