
#include "Keyboard.h"                                                                                                                                              KEY_NONE
#include "KeyCode.h"
#include "CodePageTable.h"


#define EXTEND_KEY_OFFSET 0x72

static uint8_t Set2KeyCodeTable[] =
{
    0x00, KEY_F9, 0x00, KEY_F5, KEY_F3, KEY_F1, KEY_F2, KEY_F12, 0x00, KEY_F10, KEY_F8, KEY_F6, KEY_F4, KEY_TAB, KEY_ACCENT, 0x00,
    0x00, KEY_L_ALT, KEY_L_SHFT, 0x00, KEY_L_CTRL, KEY_Q, KEY_1, 0x00, 0x00, 0x00, KEY_Z, KEY_S, KEY_A, KEY_W, KEY_2, 0x00,
    0x00, KEY_C, KEY_X, KEY_D, KEY_E, KEY_4, KEY_3, 0x00, 0x00, KEY_SPACE, KEY_V, KEY_F, KEY_T, KEY_R, KEY_5, 0x00,
    0x00, KEY_N, KEY_B, KEY_H, KEY_G, KEY_Y, KEY_6, 0x00, 0x00, 0x00, KEY_M, KEY_J, KEY_U, KEY_7, KEY_8, 0x00,
    0x00, KEY_COMMA, KEY_K, KEY_I, KEY_O, KEY_0, KEY_9, 0x00, 0x00, KEY_POINT, KEY_SLASH, KEY_L, KEY_SEMICOLON, KEY_P, KEY_MINUS, 0x00,
    0x00, 0x00, KEY_APOSTROPHE, 0x00, KEY_LEFTBRACKET, KEY_EQUAL, 0x00, 0x00, KEY_CAPS, KEY_R_SHFT, KEY_ENTER, KEY_RIGHTBRACKET, 0x00, KEY_BACKSLASH, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_BACKSPACE, 0x00, 0x00, KEY_NUM_1, 0x00, KEY_NUM_4, KEY_NUM_7, 0x00, 0x00, 0x00,
    KEY_NUM_0, KEY_NUM_POINT, KEY_NUM_2, KEY_NUM_5, KEY_NUM_6, KEY_NUM_8, KEY_ESC, KEY_NUMLOCK, KEY_F11, KEY_NUM_ADD, KEY_NUM_3, KEY_NUM_MINUS, KEY_NUM_MULTIPLY, KEY_NUM_9, KEY_SCROLL, 0x00,
    0x00, 0x00, 0x00, KEY_F7, KEY_R_ALT, KEY_PRNTSCRN, 0x00, KEY_R_CTRL, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, KEY_L_GUI, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_R_GUI, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, KEY_APPS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_NUM_DIVIDE, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_NUM_ENTER, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_END, 0x00, KEY_LEFT, KEY_HOME,
    0x00, 0x00, 0x00, KEY_INSERT, KEY_DELETE, KEY_DOWN, 0x00, KEY_RIGHT, KEY_UP, 0x00, 0x00, 0x00, 0x00, KEY_PAGE_DOWN, 0x00, 0x00,
    KEY_PAGE_UP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}

Keyboard_t::Keyboard_t() :
    m_fpCallBack(0),
    m_pContext(0),
    m_pCodePage(0)
{
}

Keyboard_t::~Keyboard_t()
{
}

void Keyboard_t::RegisterCallBack(void* pContext, KeyboardCallBack_t fpCallBack)
{
    m_fpCallBack = fpCallBack;
    m_pContext = pContext;
}

void Keyboard_t::UnRegisterCallBack(KeyboardCallBack_t fpCallBack)
{
    m_fpCallBack = 0;
    m_pContext = 0;
}

void Keyboard_t::SetCodePage(CodePage_t codePage)
{
    switch (codePage)
    {
    case CP_ASCII: m_pCodePage = CPTable::AsciiTable;  break;
    case CP_UTF8 : m_pCodePage = CPTable::Utf8Table;   break;
    case CP_1251 : m_pCodePage = CPTable::Cp1251Table; break;

    default:
        m_pCodePage = 0;
        break;
    }
}

uint8_t Keyboard_t::ScanCodeToKeyCode(uint8_t scanCode, uint8_t extendKeyFlag)
{
    if (extendKeyFlag)
    {
        scanCode += EXTEND_KEY_OFFSET;
    }

    return Set2KeyCodeTable[scanCode];
}

uint8_t Keyboard_t::KeyCodeToCharCode(uint8_t keyCode)
{
    uint16_t CharCode = 0xFF;

    if (m_pCodePage)
    {
        CharCode = m_pCodePage[keyCode];
    }
    return CharCode;
}
