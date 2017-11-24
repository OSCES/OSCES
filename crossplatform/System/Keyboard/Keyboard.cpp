#include "Keyboard.h"
#include "KeyCode.h"
#include "CodePageTable.h"

static const uint8_t ExtendKeyOffset = 0x78;

static KeyCode Set2KeyCodeTable[] =
{
    Key_Unknown, Key_F9, Key_Unknown, Key_F5, Key_F3, Key_F1, Key_F2, Key_F12, Key_Unknown, Key_F10, Key_F8, Key_F6, Key_F4, Key_Tab, Key_Accent, Key_Unknown,
    Key_Unknown, Key_LeftAlt, Key_LeftShift, Key_Unknown, Key_LeftCtrl, Key_Q, Key_1, Key_Unknown, Key_Unknown, Key_Unknown, Key_Z, Key_S, Key_A, Key_W, Key_2, Key_Unknown,
    Key_Unknown, Key_C, Key_X, Key_D, Key_E, Key_4, Key_3, Key_Unknown, Key_Unknown, Key_Spaec, Key_V, Key_F, Key_T, Key_R, Key_5, Key_Unknown,
    Key_Unknown, Key_N, Key_B, Key_H, Key_G, Key_Y, Key_6, Key_Unknown, Key_Unknown, Key_Unknown, Key_M, Key_J, Key_U, Key_7, Key_8, Key_Unknown,
    Key_Unknown, Key_Comma, Key_K, Key_I, Key_O, Key_0, Key_9, Key_Unknown, Key_Unknown, Key_Point, Key_Slash, Key_L, Key_Semicolon, Key_P, Key_Minus, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Apostrophe, Key_Unknown, Key_LeftBracket, Key_Equal, Key_Unknown, Key_Unknown, Key_Caps, Key_RightShift, Key_Enter, Key_RightBracket, Key_Unknown, Key_Backslash, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Backspace, Key_Unknown, Key_Unknown, Key_Num_1, Key_Unknown, Key_Num_4, Key_Num_7, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Num_0  , Key_Num_Point, Key_Num_2, Key_Num_5, Key_Num_6, Key_Num_8, Key_Esc, Key_NumLock, Key_F11, Key_Num_Add, Key_Num_3, Key_Num_Minus, Key_Num_Multiply, Key_Num_9, Key_Scroll, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_F7, Key_RightAlt, Key_PrntScrn, Key_Unknown, Key_RightCtrl, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_LeftGui, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_RightGui, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Apps, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Num_Divide, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Num_Enter, Key_Unknown, Key_Unknown,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_End, Key_Unknown, Key_Left, Key_Home,
    Key_Unknown, Key_Unknown, Key_Unknown, Key_Insert, Key_Delete, Key_Down, Key_Unknown, Key_Right, Key_Up, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_PageDown, Key_Unknown, Key_Unknown,
    Key_PageUp, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown, Key_Unknown
};

Keyboard::Keyboard() :
    m_fpCallBack(0),
    m_context(0),
    m_codePage(0)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::registerCallBack(void *context, KeyboardCallBack fpCallBack)
{
    m_fpCallBack = fpCallBack;
    m_context = pContext;
}

void Keyboard::unRegisterCallBack(KeyboardCallBack fpCallBack)
{
    m_fpCallBack = 0;
    m_context = 0;
}

void Keyboard::setCodePage(CodePage codePage)
{
    switch (codePage)
    {
    case CP_ASCII: m_codePage = CPTable::AsciiTable;  break;
    case CP_UTF8 : m_codePage = CPTable::Utf8Table;   break;
    case CP_1251 : m_codePage = CPTable::Cp1251Table; break;
    default:
        m_codePage = 0;
        break;
    }
}

KeyCode Keyboard::keyCodeFromScanCode(uint8_t scanCode, uint8_t extendKeyFlag)
{
    return Set2KeyCodeTable[extendKeyFlag ? scanCode + ExtendKeyOffset : scanCode];
}

uint16_t Keyboard::charCodeFromkeyCode(uint8_t keyCode)
{
    return m_codePage ? m_codePage[keyCode] : 0xff;
}
