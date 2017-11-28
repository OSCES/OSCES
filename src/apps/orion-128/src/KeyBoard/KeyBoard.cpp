#include "KeyBoard.h"

void KeyBoard_t::PressKey( uint8_t scanCode )
{
    m_PressedKeys = scanCode;
}

void KeyBoard_t::UnPressKey( uint8_t scanCode )
{
    m_PressedKeys = 0;//scanCode;
}

void KeyBoard_t::Write( uint16_t addr, uint8_t data )
{
    PpiPortAddr_t port = ( PpiPortAddr_t )( addr & 0x03 );
    m_KeyboardPpi.Write( port, data );
}

uint8_t KeyBoard_t::Read( uint16_t addr )
{
    PpiPortAddr_t port = ( PpiPortAddr_t )( addr & 0x03 );
    uint8_t retValue = m_KeyboardPpi.Read( port );
    return retValue;
}

void KeyBoard_t::Init( void )
{
    m_KeyboardPpi.SetPortWriteCallBack( this, PpiPortWrite );
    m_KeyboardPpi.SetPortReadCallBack ( this, PpiPortRead  );
    m_ScanLine     = 0;
    m_ResetCounter = 0;
}


void KeyBoard_t::PpiPortWrite( void* pContext, PpiPortAddr_t port, uint8_t data )
{
    KeyBoard_t* keyboard = static_cast< KeyBoard_t* >( pContext );

    uint8_t bp = 0;

  
    switch( port )
    {
        case PPI_ADDR_PORTA:
           bp = 0;
        
        keyboard->m_ScanLine = data;

        if( 0xFE != data )
        {
            bp = 0;
        }
        break;
    
        case PPI_ADDR_PORTB:
            bp = 0;
        break;
    
        case PPI_ADDR_PORTC:
            bp = 0;
        break;
    
        case PPI_ADDR_CTRL:
            bp = 0;
        break;
    
        default: break;
    };
}


uint8_t KeyBoard_t::PpiPortRead( void* pContext, PpiPortAddr_t port )
{
    KeyBoard_t* keyboard = static_cast< KeyBoard_t* >( pContext );

    uint8_t retValue = 0xFF; 
    
    switch( port )
    {
        case PPI_ADDR_PORTA:
          
        break;
    
        case PPI_ADDR_PORTB:
            
            if( keyboard->m_ResetCounter < KEYBOARD_RESET_TIME )
            {
                keyboard->m_ResetCounter++;
            }
            else
            {
                retValue = keyboard->GetKeyFromMatrix( keyboard->m_ScanLine );
            }
            

        break;
    
        case PPI_ADDR_PORTC:
             retValue = 0xEF;
        break;
    
        case PPI_ADDR_CTRL:
     
        break;
    
        default: break;
    };

    return retValue;
}

//0b11111011 0b11111110 //0
//0b11111011 0b11111101 //1
//0b11111011 0b11111011 //2
//0b11111011 0b11110111 //3
//0b11111011 0b11101111 //4
//0b11111011 0b11011111 //5
//0b11111011 0b10111111 //6
//0b11111011 0b01111111 //7

//0b1111101101111111

//0b1111110111011111 - Vertical tab up
//0b1111110101111111 - Vertical tab down      
//0b1111011110111111 - Enter
//0b1110111111111110 - @
//0b0111111110111111 - /\
0b0111111101111111 - пробел
uint16_t ScanCode[ ] = 
{
    0xFFFF, //0 nul ^@ Нуль
    0xFFFF, //1 soh ^A Начало заголовка ☺
    0xFFFF, //2 stx ^B Начало текста ☻
    0xFFFF, //3 etx ^C Конец текста ♥
    0xFFFF, //4 eot ^D Конец передачи ♦
    0xFFFF, //5 enq ^E Запрос ♣
    0xFFFF, //6 ack ^F Подтверждение ♠
    0xFFFF, //7 bel ^G Сигнал (звонок) •
    0b0111111101111111, //8 bs ^H Забой (шаг назад) ◘   0b1111110111101111 !!!
    //00000000
    0xFDFE, //9 Tab - success
    0xFFFF, //10 lf ^J Перевод строки ◙
    0xFDFD, //11 vt ^K Вертикальная табуляция ♂
    0xFFFF, //12 ff ^L Новая страница ♀
    0b1111110111111011,//0xFB01, //13 (0b11111011 0b11110111) Enter 0xFBBF (0b11111011 0b10111111) 
    //00000000 
    
    0xFFFF, //14 so ^N Выключить сдвиг ♫
    0xFFFF, //15 si ^O Включить сдвиг ☼
    0xFFFF, //16 dle ^P Ключ связи данных ►
    0xFFFF, //17 dc1 ^Q Управление устройством 1 ◄
    0xFFFF, //18 dc2 ^R Управление устройством 2 ↕
    0xFFFF, //19 dc3 ^S Управление устройством 3 ‼
    0xFFFF, //20 dc4 ^T Управление устройством 4 ¶
    0xFFFF, //21 nak ^U Отрицательное подтверждение §
    0xFFFF, //22 syn ^V Синхронизация ▬
    0xFFFF, //23 etb ^W Конец передаваемого блока ↨
    0xFFFF, //24 can ^X Отказ ↑
    0xFFFF, //25 em ^Y Конец среды ↓
    0xFFFF, //26 sub ^Z Замена →
    0xFFFF, //27 esc ^[ Ключ ←
    0xFFFF, //28 fs ^\ Разделитель файлов ∟
    0xFFFF, //29 gs ^] Разделитель группы ↔
    0xFFFF, //30 rs ^^ Разделитель записей ▲
    0xFFFF, //31 us ^_ Разделитель модулей ▼
    0xFEF7, //32 пробел --success 
    0xFFFF, //33 ! 
    0xFFFF, //34 “ 
    0xFFFF, //35 # 
    0xFFFF, //36 $ 
    0xFFFF, //37 % 
    0xFFFF, //38 & 
    0xFFFF, //39 ' 
    0xFFFF, //40 ( 
    0xFFFF, //41 )
    0xFFFF, //42 * 
    0xBFFE, //43 + 
    0xF7EF, //44 , --success
    0xF7DF, //45 - --success
    0xF7BF, //46 . --success
    0xF77F, //47 / --success
    0xFBFE, //48 0 --success
    0xFBFD, //49 1 --success
    0xFBFB, //50 2 --success
    0xFBF7, //51 3 --success
    0xFBEF, //52 4 --success
    0xFBDF, //53 5 --success
    0xFBBF, //54 6 --success
    0xFB7F, //55 7 --success
    0xF7FE, //56 8 --success
    0xF7FD, //57 9 --success
    0xF7FB, //58 : --success
    0xF7F7, //59 ; --success
    0xF7EF, //60 < --fail
    0xF7DF, //61 = -
    0xF7BF, //62 >
    0xF7FD, //63 ? 
    0xEFFE, //64 @ -- success
    0xEFFD, //65 A -- success
    0xEFFB, //66 B -- success
    0xEFF7, //67 C -- success
    0xEFEF, //68 D -- success
    0xEFDF, //69 E -- success
    0xEFBF, //70 F -- success
    0xEF7F, //71 G -- success
    0xDFFE, //72 H -- success
    0xDFFD, //73 I -- success
    0xDFFB, //74 J -- success 
    0xDFF7, //75 K -- success
    0xDFEF, //76 L -- success
    0xDFDF, //77 M -- success
    0xDFBF, //78 N -- success
    0xDF7F, //79 O -- success
    0xBFFE, //80 P -- success
    0xBFFD, //81 Q -- success
    0xBFFB, //82 R -- success
    0xBFF7, //83 S -- success
    0xBFEF, //84 T -- success
    0xBFDF, //85 U -- success
    0xBFBF, //86 V -- success
    0xBF7F, //87 W -- success
    0x7FFE, //88 X -- success
    0x7FFD, //89 Y -- success
    0x7FFB, //90 Z -- success
    0x7FF7, //91 [ -- success
    0x7FEF, //92 \\ -- success
    0x7FDF, //93 ] -- success
    0x7FBF, //94 ^ -- success
    0xFFFF, //95 _ 
    0xFFFF, //96 `
    0xF7FE, //97 a 
    0xFFFF, //98 b
    0x7FEF, //99 c 
    0xFFFF, //100 d 
    0xFFFF, //101 e 
    0xFFFF, //102 f 
    0xFFFF, //103 g 
    0xFFFF, //104 H
    0xFFFF, //105 I
    0xFFFF, //106 J
    0xFFFF, //107 K
    0xFFFF, //108 L
    0xFFFF, //109 m
    0xFFFF, //110 n
    0xFFFF, //111 o
    0xFFFF, //112 p
    0xFFFF, //113 q
    0xFFFF, //114 r
    0xFFFF, //115 s
    0xFFFF, //116 t
    0xFFFF, //117 u
    0xFFFF, //118 v
    0xFFFF, //119 w
    0xFFFF, //120 x
    0xFFFF, //121 y
    0xFFFF, //122 z
    0xFFFF, //123 {
    0xFFFF, //124 |
    0xFFFF, //125 }
    0xFFFF, //126 ~
    0xFFFF, //127 del
};






uint8_t KeyBoard_t::GetKeyFromMatrix( uint8_t scanLine )
{
    uint8_t retValue = 0xFF;

    uint16_t scanCode = ScanCode[ m_PressedKeys ];

    if( scanLine == ( ( scanCode >> 8 ) & 0x00FF ) )
    {
        retValue = scanCode & 0x00FF;// ~( 1 << 2 );
    }


    return retValue;
}
